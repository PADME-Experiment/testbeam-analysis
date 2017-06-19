#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"

double SigmaTest(double *x, double *par) { //Input variable Egamma
//   double a=0.023;
//   double b=0.000;
//   double c=0.005;
   double s;
   //   s = par[0]/sqrt(x[0]/1000.)+par[1]/(x[0]/1000.)+par[2];
   s = sqrt( (par[0]*par[0])/(x[0]*1E-3) + par[1]/(x[0]*x[0]/1.E6) + (par[2]*par[2]) );
   return s;
}

double SigmaTest2(double *x, double *par) { //Input variable Egamma
//   double a=0.023;
//   double b=0.000;
//   double c=0.005;
   double s;
   // s = par[0]/sqrt(x[0]*1E-3)+par[1];
   s = sqrt( (par[0]*par[0])/(x[0]*1E-3) + (par[1]*par[1]) );
   return s;
}

double Lin(double *x, double *par) { //Input variable Egamma
//   double a=0.023;
//   double b=0.000;
//   double c=0.005;
   double s;
   s = par[0]*x[0];
   return s;
}

double Lin2(double *x, double *par) { //Input variable Egamma
//   double a=0.023;
//   double b=0.000;
//   double c=0.005;
   double s;
   s = par[0]*x[0]+par[1];
   return s;
}

void DrawCosmic(){
   gROOT->SetStyle("Plain");
   gROOT->ForceStyle();
   //   gStyle->SetOptTitle(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(1);

  Int_t    NGaus  = 5;
  Int_t    IsOn[25]={0.};
  Double_t Compare= 0;
  Double_t Mean[13];
  Double_t RMS[5];
  Double_t ENE[5];
  Double_t RMSE[5];
  Double_t EMean[5]={1.43,2.1,5.6,12.8,0.};
  Double_t ERESO[5]={2e-4,1.5e-4,1e-4,0.5e-4,0.};
  //  Double_t ENE_E[5]={2.5,5,7.5,10.};
  Double_t ENE_E[5]={0.,0.,0.,0.};  
  Double_t RESO[5];
  Double_t par[15];
  Double_t epar[15];
  TF1 *g1;    
  TF1 *g2;   
  TF1 *g3;    
  TF1 *g4;
  TF1 *g5;
  TF1 *total;
  TH1D * hPedHis    = new TH1D("hPedHis","",170,3700.,3870.);
  TH2D * hPedHis2D  = new TH2D("hPedHis2D","",32,-0.5,31.5,170,3700.,3870.);
  TH2D * hQPedHis2D = new TH2D("hQPedHis2D","",32,-0.5,31.5,200,-150.,150.);
  
  Int_t NCalo=12;
  Int_t Nrow=4;
  Int_t Ncol=3;
  Int_t NFit;
  char hisname[50];
  for(int cc=0;cc<NCalo;cc++) IsOn[cc]=1;
  /*  IsOn[18]=1.;  IsOn[17]=1.;  IsOn[16]=1.;
  IsOn[13]=1.;  IsOn[12]=1.;  IsOn[11]=1.;
  IsOn[8] =1.;  IsOn[7] =1.;  IsOn[6] =1.;
  */
  TFile * _file0;
  
  printf("Opening file \n");
  //_file0 = TFile::Open("output/E250NoBug472.root");
  //_file0 = TFile::Open("output/250Nov.root");
  //_file0 = TFile::Open("output/outCosmic679.root");
  //_file0 = TFile::Open("output/outCosmic678.root");
  //_file0 = TFile::Open("output/outCosmic678_AllVert_OnlyInCentralCol.root");
  _file0 = TFile::Open("output/outCosmic681.root");
  //_file0 = TFile::Open("output/outCosmic538.root");
  //_file0 = TFile::Open("output/E250NoBug.root");

  Int_t binmax;
  Double_t x;
  TCanvas * c4= new TCanvas("CaloPed","CaloPed",800,600);
  c4->Divide(Ncol,Nrow);
  std::cout<<"NCalo "<<NCalo<<std::endl;
  for(int kk=0;kk<NCalo;kk++){
    c4->cd(NCalo-kk);
    sprintf(hisname,Form("hQCh%d",kk));
    //sprintf(hisname,Form("hQVertCh%d",kk));
    TH1D* H1 = (TH1D*)_file0->Get(hisname);
    H1->SetFillColor(kRed); H1->SetLineColor(kBlack);
    H1->GetXaxis()->SetTitle("Charge [pC]");
    H1->Draw();
    binmax = H1->GetMaximumBin();
    x   = H1->GetXaxis()->GetBinCenter(binmax);
    cout<<" Ped "<<kk<<" = "<<x<<endl;
    hPedHis->Fill(x);
    //    c4->Update();
  }

  Int_t count= 0;
  Double_t Ind[13];
  g1    = new TF1("g1","gaus",150,800);
  g2    = new TF1("g2","landau",120,800);
  TCanvas * c5= new TCanvas("QCh","QCh",1280,1024);
  c5->Divide(Ncol,Nrow); 
  //c5->Divide(3,3); 
  for(int kk=0;kk<NCalo;kk++){
    //c5->cd(NCalo-kk);
    //gPad->SetLogy();
    //    sprintf(hisname,Form("hQVert2Ch%d",kk));
    //    sprintf(hisname,Form("hQPedCalo%d",kk));

    //sprintf(hisname,Form("hQCh%d",kk));
    sprintf(hisname,Form("hQVertCh%d",kk));
    //sprintf(hisname,Form("hQAllVertCh%d",kk));
    //sprintf(hisname,Form("hQ3maxCh%d",kk));
    if(IsOn[kk]){
      //c5->cd(count+1.);
      c5->cd(NCalo-kk)->SetLogy();
      std::cout<<"Name "<<hisname<<std::endl;
      TH1D* H2 = (TH1D*)_file0->Get(hisname);
      std::cout<<"Name "<<hisname<<" "<<H2<<std::endl<<std::endl;
      H2->Rebin(5);
      H2->SetFillColor(kRed); H2->SetLineColor(kBlack);
      H2->GetXaxis()->SetRangeUser(-200.,1500.);
      H2->GetXaxis()->SetTitle("Charge [pC]");
      H2->Draw();
      //    if(kk==17) g2->SetParameter(1,450);
      g2->SetLineColor(kBlack);

      H2->Fit("g2","R");
      if(kk==17) {
	g2->SetParameter(1,400);
	H2->Fit("g2","S","",120.,800.);
      }      
      Mean[count] =g2->GetParameter(1);
      cout<<endl<<"Mean "<<Mean[count]<<endl<<endl<<endl;
      Ind[count]=count;
      count++;
      //      //    c5->Update();
    }
  }
  //  
TCanvas * c7= new TCanvas("Calib","Calib",800,600); c7->SetGrid();
  TGraph * gCalo = new TGraph(12,Ind,Mean);
  
  gCalo->SetMarkerStyle(21);
  gCalo->SetMarkerColor(kBlue);
  gCalo->Draw("AP");
  
  Double_t CalConst[12];
  for(int kk=0;kk<12;kk++){
    CalConst[kk]=Mean[kk]/Mean[4];
    cout<<"Channel "<<kk<<", Mean "<<Mean[kk]<<", Mean4 "<<Mean[4]<<" => "<<CalConst[kk]<<endl;
  }
  TCanvas * c8= new TCanvas("CalibCons","CalibCons",800,600); 
  c8->SetGrid();
  TGraph * gCaloCons = new TGraph(12,Ind,CalConst);
  
  gCaloCons->SetMarkerStyle(21);
  gCaloCons->SetMarkerColor(kBlue);
  gCaloCons->Draw("AP");
}

