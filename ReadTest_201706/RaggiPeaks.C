// Illustrates how to find peaks in histograms.
// This script generates a random number of gaussian peaks
// on top of a linear background.
// The position of the peaks is found via TSpectrum and injected
// as initial values of parameters to make a global fit.
// The background is computed and drawn on top of the original histogram.
//
// To execute this example, do
//  root > .x peaks.C  (generate 10 peaks by default)
//  root > .x peaks.C++ (use the compiler)
//  root > .x peaks.C++(30) (generates 30 peaks)
//
// To execute only the first part of the script (without fitting)
// specify a negative value for the number of peaks, eg
//  root > .x peaks.C(-20)
//
//Author: Rene Brun

#include "TCanvas.h"
#include "TMath.h"
#include "TH1.h"
#include "TF1.h"
#include "TRandom.h"
#include "TSpectrum.h"
#include "TVirtualFitter.h"
   
Int_t npeaks = 30;
Double_t fpeaks(Double_t *x, Double_t *par) {
   Double_t result = par[0] + par[1]*x[0];
   for (Int_t p=0;p<npeaks;p++) {
      Double_t norm  = par[3*p+2];
      Double_t mean  = par[3*p+3];
      Double_t sigma = par[3*p+4];
      result += norm*TMath::Gaus(x[0],mean,sigma);
   }
   return result;
}

Double_t fitf(Double_t *x, Double_t *par)
{
   Double_t arg = 0;
   if (par[2] != 0) arg = (x[0] - par[1])/par[2];

   Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
   return fitval;
}

void RaggiPeaks(Int_t np=10) {
  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);  
  Int_t npeaks = TMath::Abs(np);
  char hisname[50];
  TFile * _file0;
  Double_t par[300];
  _file0 = TFile::Open("ntusac490.root");
  Int_t IsRaw=1;
  Int_t IsReco=0;

  if(IsRaw==1){
    TH1D * hPedHis  = new TH1D("hPedHis","",1000,3600.,3800.);
    TH1D * hPedCHI2 = new TH1D("hPedCHI2","hPedCHI2",1000,0.,1000.);
    TH1D * hPedTrend = new TH1D("hPedTred","hPedTrend",1000,0.,1000.);
    TH1D * hPeakPos  = new TH1D("hPeakPos","hPeakPos",1000,0.,1000.*0.2);
    TH1D * hPeakHei  = new TH1D("hPeakHei","hPeakHei",400,0.,1.);
    TH2D * hPedVsIev = new TH2D("hPedVsIev","hPedVsIev",500,0.,500.,500,3700.,3750.);
    TH1D * hNPeak  = new TH1D("hNPeak","",21,-0.5,20.5);
    TH1D * hTDiffPeak  = new TH1D("hTDiffPeak","",800,-100.,100.);
  }
  if(IsReco==1){
    TH1D * hPedHis  = new TH1D("hPedHis","",1000,0.,0.001);
    TH1D * hPedCHI2 = new TH1D("hPedCHI2","hPedCHI2",1000,0.,50.);
    TH1D * hPedTrend = new TH1D("hPedTred","hPedTrend",1000,0.,0.001);
    TH2D * hPedVsIev = new TH2D("hPedVsIev","hPedVsIev",500,0.,500.,500,0.,0.005);
  }
  TCanvas * c4 = new TCanvas("CaloPed","CaloPed",800,600);
  Int_t NHis = 5000;
  Double_t PedFit[5000];
  //  Double_t Const[1024]={3740.}
  for(int kk=0;kk<NHis;kk++){
     //     c4->cd(25-kk);
    sprintf(hisname,Form("hSCh%d",kk));
    TH1D* H1 = (TH1D*)_file0->Get(hisname);
    //TH1D* H2 = (TH1D*)H1->Clone("H2");
    //H2->SetContent(Const);
    //H2->Draw("");

    H1->GetXaxis()->SetRange(0.,NHis);
    std::cout<<"P0 "<<H1->GetEntries()<<std::endl;
    if(H1->GetEntries()>0){
      H1->Fit("pol0");
      //      H1->Draw("");
      //      getchar();
      //      c4->Update();
      TF1 *myfunc = H1->GetFunction("pol0");
      Double_t p0 = myfunc->GetParameter(0);
      Double_t chi2 = myfunc->GetChisquare();
      PedFit[kk]=p0;
      //     std::cout<<"P0 "<<p0<<std::endl;
      if(chi2>15.) c4->Update();
      std::cout<<kk<<" P0 "<<p0<<std::endl;
      hPedHis  ->Fill(-p0);
      hPedCHI2 ->Fill(chi2);
      hPedVsIev->Fill(kk,-p0);
      if(chi2<15.) hPedTrend->Fill(kk,-p0);
      if(chi2>15.){
	TSpectrum *s = new TSpectrum(2*npeaks);
	Int_t nfound = s->Search(H1,3,"",0.15);
	printf("Found %d candidate peaks to fit\n",nfound);
	if(nfound>10) continue;
	hNPeak->Fill(nfound);
	Float_t *xpeaks = s->GetPositionX();
	Float_t *ypeaks = s->GetPositionY();

	TH1 *hb = s->Background(H1,20,"same");
	//	if (hb) c4->Update();
	if (np <0) return;
	TF1 *fline = new TF1("fline","pol1",0,1000);
	H1->Fit("fline","qn");
	//	  //Loop on all found peaks. Eliminate peaks at the background level
	par[0] = fline->GetParameter(0);
	par[1] = fline->GetParameter(1);
	printf("p1 fit %f %f \n",par[0],par[1]);	  
	
	Double_t TDiff=0;
	for(Int_t ll=0;ll<nfound;ll++){
	  hPeakPos->Fill(xpeaks[ll]*0.2);
	  hPeakHei->Fill((-p0+ypeaks[ll])/4096*1.);
	  printf("candidate position %f %f %f\n",xpeaks[ll],ypeaks[ll],(-p0+ypeaks[ll])/4096*1.);
	  Float_t xp = xpeaks[ll];
	  Int_t bin  = H1->GetXaxis()->FindBin(xp);
	  Float_t yp = H1->GetBinContent(bin);
	  //	  if (yp-TMath::Sqrt(yp) < fline->Eval(xp)) continue;
//	  par[3*npeaks+2] = yp;
//	  par[3*npeaks+3] = xp;
//	  par[3*npeaks+4] = 3;
//	  npeaks++;
	  par[3*ll+2] = yp;
	  par[3*ll+3] = xp;
	  par[3*ll+4] = 3;
	  if(nfound>1 && ll>0){ 
	    TDiff=xpeaks[ll]-xpeaks[0];
	    hTDiffPeak->Fill(TDiff*0.2);
	  }
	  //	  npeaks++;
	}
	//	npeaks=nfound;
	//	printf("Found %d useful peaks to fit of %d\n",npeaks,nfound);
//	printf("Now fitting: Be patient\n");
	printf("Now fitting: Be patient %d %f %f %f\n",par[0],par[1],par[2],par[3]);
	TF1 *fit = new TF1("fit",fpeaks,0,1000,2+3*nfound);
	//	TF1 *g1  = new TF1("g1","gaus",par[3]-10,par[3]+10,3);
//	////	//   //we may have more than the default 25 parameters
//	//	TVirtualFitter::Fitter(H1,10+3*npeaks);
//	TVirtualFitter::Fitter(H1,2+3*nfound);
//	fit->SetParameters(par);
//	fit->SetNpx(1000);
//	//	fit->FixParameter(0,par[0]);
//	fit->FixParameter(1,par[1]);
//	for(Int_t mm=0;mm<nfound;mm++) {
//	  fit->FixParameter(3*mm+3,par[3*mm+3]);
//	  fit->SetParLimits(3*mm+4,0.,10.);
//	}
	//	H1->Fit("fit","R");

	/* restore
	TF1 *func = new TF1("fitf",fitf,par[3]-10,par[3]+10,3);
	// Sets initial values and parameter names
	func->SetParameters(600,par[3],3);
	func->SetParNames("Constant","Mean_value","Sigma");
	func->SetLineColor(kRed);
	// Fit histogram in range defined by function
	H1->Fit("fitf","r");
	// Gets integral of function between fit limits
	//	printf("Integral of function = %g\n",func->Integral(-2,2));
	
	//	H1->Fit("func","R");

	c4->Update();
	getchar();
	*/
      } //end of trigger if
    }
    //    getchar();
  }//Loop on NHist
  for(int kk=0;kk<NHis;kk++) std::cout<<kk<<" Ped "<<PedFit[kk]<<std::endl;
  TCanvas * c5= new TCanvas("CaloPed","CaloPed",800,600);
  hPedHis->Draw("");

  TCanvas * c6= new TCanvas("CaloPedVsIev","CaloPedVsIev",800,600);
  //  hPedVsIev->Draw("P");
  hPedTrend->Draw("P");

  TCanvas * c7= new TCanvas("Chi2","Chi2",800,600);
  hPedCHI2->Draw("");

  TCanvas * c8= new TCanvas("PeakPos","PeakPos",800,600);
  c8->Divide(1,2);
  c8->cd(1);
  hPeakHei->Draw("");
  c8->cd(2);
  hPeakPos->Draw("");

  TCanvas * c9= new TCanvas("NPeak","NPeak",800,600);
  c9->Divide(1,2);
  c9->cd(1);
  hNPeak->Draw("");
  c9->cd(2);
  hTDiffPeak->Draw("");

  //   TH1F *h2 = (TH1F*)h->Clone("h2");
  //   //Use TSpectrum to find the peak candidates
//   //Estimate background using TSpectrum::Background
//   TH1 *hb = s->Background(h,20,"same");
//   if (hb) c1->Update();
//   if (np <0) return;
//
//   //estimate linear background using a fitting method
//   c1->cd(2);
//   TF1 *fline = new TF1("fline","pol1",0,1000);
//   h->Fit("fline","qn");
//   //Loop on all found peaks. Eliminate peaks at the background level
//   par[0] = fline->GetParameter(0);
//   par[1] = fline->GetParameter(1);
//   npeaks = 0;
//   Float_t *xpeaks = s->GetPositionX();
//   for (p=0;p<nfound;p++) {
//      Float_t xp = xpeaks[p];
//      Int_t bin = h->GetXaxis()->FindBin(xp);
//      Float_t yp = h->GetBinContent(bin);
//      if (yp-TMath::Sqrt(yp) < fline->Eval(xp)) continue;
//      par[3*npeaks+2] = yp;
//      par[3*npeaks+3] = xp;
//      par[3*npeaks+4] = 3;
//      npeaks++;
//   }
//   printf("Found %d useful peaks to fit\n",npeaks);
//   printf("Now fitting: Be patient\n");
//   TF1 *fit = new TF1("fit",fpeaks,0,1000,2+3*npeaks);
//   //we may have more than the default 25 parameters
//   TVirtualFitter::Fitter(h2,10+3*npeaks);
//   fit->SetParameters(par);
//   fit->SetNpx(1000);
//   h2->Fit("fit");             

}
