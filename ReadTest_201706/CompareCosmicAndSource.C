#include "TH1D.h"
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include <map>


void CompareCosmicAndSource(bool SaveFig=false){
   gROOT->SetStyle("Plain");
   gROOT->ForceStyle();
   //   gStyle->SetOptTitle(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(1);

  Int_t NCalo=12;
  Int_t Nrow=4;
  Int_t Ncol=3;

  TF1 *g1 = new TF1("g1","gaus",-10,30);    
  TF1 *g2 = new TF1("g2","landau",120,800);   
  TF1 *g3;

  TH1D * hPedHis    = new TH1D("hPedHis","",170,3700.,3870.);
  
  Int_t NFit;
  char hisname[50];

  Int_t    IsOn[25]={0.};

  for(int cc=0;cc<NCalo;cc++) IsOn[cc]=1;
  /*  IsOn[18]=1.;  IsOn[17]=1.;  IsOn[16]=1.;
  IsOn[13]=1.;  IsOn[12]=1.;  IsOn[11]=1.;
  IsOn[8] =1.;  IsOn[7] =1.;  IsOn[6] =1.;
  */



  ///////////// COSMIC RAY DATA //////////////


  Double_t Mean[13];

  // CR data in run 681
  TFile * _file0;
  printf("Opening file \n");
  _file0 = TFile::Open("/home/daq/DigiDaq/TestBeamOld/output/outCosmic681.root");


  Int_t count = 0;
  Double_t Ind[13];
  TCanvas * c5= new TCanvas("Verical CR Charge","Vertical CR Charge",800,800);
  c5->Divide(Ncol,Nrow); 
  for(int kk=0;kk<NCalo;kk++){

    //sprintf(hisname,Form("hQAllVertCh%d",kk));
    //sprintf(hisname,Form("hQ3maxCh%d",kk));
    if(IsOn[kk]){

      sprintf(hisname,Form("hQCh%d",kk));
      TH1D* H1 = (TH1D*)_file0->Get(hisname);

      double pedCR = H1->GetXaxis()->GetBinCenter(H1->GetMaximumBin());
      cout<<"pedCR "<<pedCR<<endl;

      sprintf(hisname,Form("hQVertCh%d",kk));
      c5->cd(NCalo-kk)->SetLogy();
      TH1D* H2 = (TH1D*)_file0->Get(hisname);
      std::cout<<"Name "<<hisname<<std::endl<<std::endl;
      H2->Rebin(5);
      H2->SetFillColor(kRed); 
      H2->SetLineColor(kBlack);
      H2->GetXaxis()->SetRangeUser(-200.,1500.);
      H2->GetXaxis()->SetTitle("Charge [pC]");
      H2->Draw();
      H2->SetTitle(Form("Vertical CR ch. %d",kk));
      g2->SetLineColor(kBlack);

      H2->Fit("g2","R");

      Mean[count] =g2->GetParameter(1) - pedCR;
      cout<<endl<<"Mean "<<Mean[count]<<endl<<endl<<endl;
      Ind[count]=count;
      count++;
      //    c5->Update();
    }
  }



  ///////////// NA-22 SOURCE DATA //////////////


  TCanvas* Qspectra1150 = new TCanvas("Charge Spectra HV = 1150V","Charge Spectra HV = 1150V",800,800);
  Qspectra1150->Divide(Ncol,Nrow);
  TCanvas* Qspectra1250 = new TCanvas("Charge Spectra HV = 1250V","Charge Spectra HV = 1250V",800,800);
  Qspectra1250->Divide(Ncol,Nrow);
  TCanvas* Qspectra1400 = new TCanvas("Charge Spectra HV = 1400V","Charge Spectra HV = 1400V",800,800);
  Qspectra1400->Divide(Ncol,Nrow);

  TCanvas* PeakAmpl = new TCanvas("Peak Amplitude","Peak Amplitude",800,800);
  PeakAmpl->Divide(Ncol,Nrow);

  TCanvas* PeakSlope = new TCanvas("Peak Slope","Peak Slope",800,800);

  TH1D* slopeTOT = new TH1D("global slope","",10,0.0050,0.0065);
  TH1D* slope511 = new TH1D("511keV slope","",10,0.0050,0.0065);
  TH1D* slope1273 = new TH1D("1273keV slope","",10,0.0050,0.0065);
  TH1D* slope1784 = new TH1D("1784keV slope","",10,0.0050,0.0065);


  TCanvas* CRERelease = new TCanvas("CR energy release","CR energy release",800,800);

  TH1D* ERTOT = new TH1D("CR global En. release","",24,10,26);
  TH1D* ER511 = new TH1D("CR En. release 511keV","",24,10,26);
  TH1D* ER1273 = new TH1D("CR En. release 1273keV","",24,10,26);
  TH1D* ER1784 = new TH1D("CR En. release 1784keV","",24,10,26);

  TCanvas* Calibration = new TCanvas("Calibration of the crystals","Calibration of the crystals",800,800); //CT
  Calibration->Divide(Ncol,Nrow); //CT

  // first element: channel
  // second element: HV
  // third element: run
  map<int, map<double, int> > Ch_HV_run;

  Ch_HV_run[0][1150] = 693;
  Ch_HV_run[0][1250] = 694;
  Ch_HV_run[0][1400] = 695;
  Ch_HV_run[1][1150] = 696;
  Ch_HV_run[1][1250] = 697;
  Ch_HV_run[1][1400] = 698;
  Ch_HV_run[2][1150] = 699;
  Ch_HV_run[2][1250] = 700;
  Ch_HV_run[2][1400] = 701;
  Ch_HV_run[3][1150] = 702;
  Ch_HV_run[3][1250] = 703;
  Ch_HV_run[3][1400] = 704;
  Ch_HV_run[4][1150] = 705;
  Ch_HV_run[4][1250] = 706;
  Ch_HV_run[4][1400] = 707;
  Ch_HV_run[5][1150] = 708;
  Ch_HV_run[5][1250] = 709;
  Ch_HV_run[5][1400] = 710;
  Ch_HV_run[6][1150] = 711;
  Ch_HV_run[6][1250] = 712;
  Ch_HV_run[6][1400] = 713;
  Ch_HV_run[7][1150] = 714;
  Ch_HV_run[7][1250] = 715;
  Ch_HV_run[7][1400] = 716;
  Ch_HV_run[8][1150] = 717;
  Ch_HV_run[8][1250] = 718;
  Ch_HV_run[8][1400] = 719;
  Ch_HV_run[9][1150] = 720;
  Ch_HV_run[9][1250] = 721;
  Ch_HV_run[9][1400] = 722;
  Ch_HV_run[10][1150] = 723;
  Ch_HV_run[10][1250] = 724;
  Ch_HV_run[10][1400] = 725;
  Ch_HV_run[11][1150] = 726;
  Ch_HV_run[11][1250] = 727;
  Ch_HV_run[11][1400] = 728;

  int run;
  double HV;
  int linecolor;
  double lastvalue;


  // loop on channels
  for(int ch=0;ch<NCalo;ch++){


    TGraphErrors* Q511graph = new TGraphErrors(3);
    TGraphErrors* Q1273graph = new TGraphErrors(3);
    TGraphErrors* Q1784graph = new TGraphErrors(3);

    double th[3]={.511,1.273,1.784};//CT

    double pos1150[3],pos1250[3],pos1400[3],err1150[3],err1250[3],err1400[3];//CT

    // loop on voltages
    for(int nhv=0;nhv<3;nhv++){

      switch (nhv){

      case 0:
	HV = 1150.;
	linecolor = 1;
	lastvalue = 60;
	break;
	
      case 1:
	HV = 1250.;
	linecolor = 2;
	lastvalue = 100;
	break;

      case 2:
	HV = 1400.;
	linecolor = 4;
	lastvalue = 220;
	break;

      default:
	cout<<"No HV available"<<endl;
	break;
      }

      if(HV == 1150) Qspectra1150->cd(NCalo - ch)->SetLogy();
      if(HV == 1250) Qspectra1250->cd(NCalo - ch)->SetLogy();
      if(HV == 1400) Qspectra1400->cd(NCalo - ch)->SetLogy();


      run = Ch_HV_run[ch][HV];

      TFile * _fileCh;
      char* filetoopen = Form("/home/daq/DigiDaq/TestBeamOld/output/outSource%d.root",run);
      cout<<endl<<endl;
      cout<<"Ch "<<ch<<", HV (nhv "<<nhv<<") "<<HV<<" => Opening file "<<filetoopen<<endl;
      _fileCh = TFile::Open(filetoopen);

      sprintf(hisname,Form("hQCh%d",ch));
      cout<<"Name "<<hisname<<endl<<endl;
      TH1D* ChSpec = (TH1D*)_fileCh->Get(hisname);
      //ChSpec->Rebin(5);
      //ChSpec->SetLineColor(linecolor);
      ChSpec->GetXaxis()->SetRangeUser(-20.,lastvalue);
      ChSpec->GetXaxis()->SetLabelSize(0.06);
      ChSpec->GetXaxis()->SetTitle("Charge [pC]");
      ChSpec->GetXaxis()->SetTitleOffset(0.8);
      ChSpec->GetXaxis()->SetTitleSize(0.06);
      ChSpec->Draw();
      ChSpec->SetTitle(Form("Na-22 source ch. %d, HV = %4.0f",ch,HV));
      
      // peak search
      TSpectrum* spec = new TSpectrum();
      int n_peaks = spec->Search(ChSpec,3.,"goff",0.02);
      //int n_peaks = spec->SearchHighRes(source,dest,nbins,100,0.001,kFALSE,3,kTRUE,10);
      TH1* bkg = spec->Background(ChSpec,80,"goff");
      bkg->SetLineColor(linecolor);
      bkg->SetLineWidth(2);
      bkg->SetLineStyle(2);
      
      float* peakpos = spec->GetPositionX();
      float* ampl =  spec->GetPositionY();
      

      double pedX = ChSpec->GetXaxis()->GetBinCenter(ChSpec->GetMaximumBin());
      double mean1273 = 1273./511.*(peakpos[1]-peakpos[0]) + pedX;
      double mean1784 = 1784./511.*(peakpos[1]-peakpos[0]) + pedX;
      
      int par = -1;
      TF1 *ffit = new TF1("ffit","[0] + [1]*exp([2]*x) + [3]*exp(-0.5*((x-[4])/[5])**2) + [6]*exp(-0.5*((x-[7])/[8])**2) + [9]*exp(-0.5*((x-[10])/[11])**2) + [12]*exp(-0.5*((x-[13])/[14])**2)",pedX-3.,/*mean1784*/lastvalue);
      
      ffit->SetParName(++par,"Const"); //0
      ffit->FixParameter(par,0.);
      //ffit->SetParameter(par,10);
      //ffit->SetParLimits(par,0,100);
      //ffit->SetNpx(10000);
      
      ffit->SetParName(++par,"Ampl_{exp}"); //1
      ffit->SetParameter(par,500);
      ffit->SetParLimits(par,50,2000);
      ffit->SetNpx(10000);
      
      ffit->SetParName(++par,"Slope_{exp}"); //2
      ffit->SetParameter(par,-0.5);
      ffit->SetParLimits(par,-3,0);
      ffit->SetNpx(10000);
      
      ffit->SetParName(++par,"Ampl_{ped}"); //3
      ffit->SetParameter(par,ChSpec->GetBinContent(ChSpec->GetMaximumBin()));
      ffit->SetParLimits(par,ChSpec->GetBinContent(ChSpec->GetMaximumBin())/5.,2*(ChSpec->GetBinContent(ChSpec->GetMaximumBin())));
      ffit->SetNpx(10000);
      
      ffit->SetParName(++par,"Mean_{ped}"); //4
      ffit->SetParameter(par,pedX);
      ffit->SetParLimits(par,pedX-3.,pedX+3.);
      ffit->SetNpx(10000);

      ffit->SetParName(++par,"#sigma_{ped}"); //5
      ffit->SetParameter(par,1);
      ffit->SetParLimits(par,0.2,3);
      ffit->SetNpx(10000);
      
      ffit->SetParName(++par,"Ampl_{511}"); //6
      ffit->SetParameter(par,ChSpec->GetBinContent(ChSpec->GetMaximumBin())/5.);
      ffit->SetParLimits(par,ChSpec->GetBinContent(ChSpec->GetMaximumBin())/50.,(ChSpec->GetBinContent(ChSpec->GetMaximumBin()))/2.);
      ffit->SetNpx(10000);
      
      ffit->SetParName(++par,"Mean_{511}"); //7
      ffit->SetParameter(par,peakpos[1]);
      ffit->SetParLimits(par,0.8*peakpos[1],1.2*peakpos[1]);
      ffit->SetNpx(10000);

      ffit->SetParName(++par,"#sigma_{511}"); //8
      ffit->SetParameter(par,1);
      ffit->SetParLimits(par,0.5,5);
      ffit->SetNpx(10000);
      
      ffit->SetParName(++par,"Ampl_{1273}"); //9
      ffit->SetParameter(par,ChSpec->GetBinContent(ChSpec->GetMaximumBin())/100.);
      ffit->SetParLimits(par,ChSpec->GetBinContent(ChSpec->GetMaximumBin())/500.,0.02*(ChSpec->GetBinContent(ChSpec->GetMaximumBin())));
      ffit->SetNpx(10000);
      
      ffit->SetParName(++par,"Mean_{1273}"); //10
      ffit->SetParameter(par,mean1273);
      ffit->SetParLimits(par,0.8*mean1273,(mean1273+mean1784)/2.);
      ffit->SetNpx(10000);

      ffit->SetParName(++par,"#sigma_{1273}"); //11
      ffit->SetParameter(par,8);
      ffit->SetParLimits(par,1,25);
      ffit->SetNpx(10000);
      
      ffit->SetParName(++par,"Ampl_{1784}"); //12
      ffit->SetParameter(par,ChSpec->GetBinContent(ChSpec->GetMaximumBin())/200.);
      ffit->SetParLimits(par,ChSpec->GetBinContent(ChSpec->GetMaximumBin())/1000.,0.01*(ChSpec->GetBinContent(ChSpec->GetMaximumBin())));
      ffit->SetNpx(10000);
      
      ffit->SetParName(++par,"Mean_{1784}"); //13
      ffit->SetParameter(par,mean1784);
      ffit->SetParLimits(par,(mean1273+mean1784)/2.,1.2*mean1784);
      ffit->SetNpx(10000);

      ffit->SetParName(++par,"#sigma_{1784}"); //14
      ffit->SetParameter(par,8);
      ffit->SetParLimits(par,1,25);
      ffit->SetNpx(10000);

      ChSpec->Fit("ffit","Q","",pedX-3,1.4*mean1784/* lastvalue*/);
      
      double pos511 = ffit->GetParameter(7)-ffit->GetParameter(4);
      double err511 = sqrt((ffit->GetParError(7))**2 + (ffit->GetParError(7))**2);
      Q511graph->SetPoint(nhv,HV,pos511);
      Q511graph->SetPointError(nhv,0.,err511);

      double pos1273 = ffit->GetParameter(10)-ffit->GetParameter(4);
      double err1273 = sqrt((ffit->GetParError(10))**2 + (ffit->GetParError(7))**2);
      Q1273graph->SetPoint(nhv,HV,pos1273);
      Q1273graph->SetPointError(nhv,0.,err1273);

      double pos1784 = ffit->GetParameter(13)-ffit->GetParameter(4);
      double err1784 = sqrt((ffit->GetParError(13))**2 + (ffit->GetParError(7))**2);
      Q1784graph->SetPoint(nhv,HV,pos1784);
      Q1784graph->SetPointError(nhv,0.,err1784);

double zero[3]={0.,0.,0.};//CT

if (nhv==0){
       pos1150[0]=ffit->GetParameter(7)-ffit->GetParameter(4);//CT
       pos1150[1]=ffit->GetParameter(10)-ffit->GetParameter(4);//CT
       pos1150[2]=ffit->GetParameter(13)-ffit->GetParameter(4);//CT
       err1150[0]=sqrt((ffit->GetParError(7))**2 + (ffit->GetParError(7))**2);//CT
       err1150[1]=sqrt((ffit->GetParError(10))**2 + (ffit->GetParError(7))**2);//CT
       err1150[2]=sqrt((ffit->GetParError(13))**2 + (ffit->GetParError(7))**2);//CT
       TGraphErrors* CalPeak1150 = new TGraphErrors(3,th,pos1150,zero,err1150);//CT
	   }

if (nhv==1){
       pos1250[0]=ffit->GetParameter(7)-ffit->GetParameter(4);//CT
       pos1250[1]=ffit->GetParameter(10)-ffit->GetParameter(4);//CT
       pos1250[2]=ffit->GetParameter(13)-ffit->GetParameter(4);//CT
       err1250[0]=sqrt((ffit->GetParError(7))**2 + (ffit->GetParError(7))**2);//CT
       err1250[1]=sqrt((ffit->GetParError(10))**2 + (ffit->GetParError(7))**2);//CT
       err1250[2]=sqrt((ffit->GetParError(13))**2 + (ffit->GetParError(7))**2);//CT
       TGraphErrors* CalPeak1250 = new TGraphErrors(3,th,pos1250,zero,err1250);//CT
	   }

if (nhv==2){
       pos1400[0]=ffit->GetParameter(7)-ffit->GetParameter(4);//CT
       pos1400[1]=ffit->GetParameter(10)-ffit->GetParameter(4);//CT
       pos1400[2]=ffit->GetParameter(13)-ffit->GetParameter(4);//CT
       err1400[0]=sqrt((ffit->GetParError(7))**2 + (ffit->GetParError(7))**2);//CT
       err1400[1]=sqrt((ffit->GetParError(10))**2 + (ffit->GetParError(7))**2);;//CT
       err1400[2]=sqrt((ffit->GetParError(13))**2 + (ffit->GetParError(7))**2);//CT
       TGraphErrors* CalPeak1400 = new TGraphErrors(3,th,pos1400,zero,err1400);//CT
	   }

      if(nhv == 0){
	ER511->Fill(0.511*Mean[ch]/pos511);
	ER1273->Fill(1.273*Mean[ch]/pos1273);
	ER1784->Fill(1.784*Mean[ch]/pos1784);
	ERTOT->Fill(0.511*Mean[ch]/pos511);
	ERTOT->Fill(1.273*Mean[ch]/pos1273);
	ERTOT->Fill(1.784*Mean[ch]/pos1784);
	
	cout<<"CR energy: "<<0.511*Mean[ch]/pos511<<" (511keV), "
	    <<1.273*Mean[ch]/pos1273<<" (1273keV), "
	    <<1.784*Mean[ch]/pos1784<<" (1784keV)"<<endl;
      }

    } // end of loop on voltages

    ////////////////////
    Q511graph->SetMarkerStyle(20);
    Q511graph->SetMarkerColor(kBlack);
    Q1273graph->SetMarkerStyle(23);
    Q1273graph->SetMarkerColor(kBlue);
    Q1784graph->SetMarkerStyle(33);
    Q1784graph->SetMarkerColor(kRed);

    CalPeak1150->SetMarkerStyle(20);//CT
    CalPeak1150->SetMarkerColor(kGray+3);//CT
    CalPeak1250->SetMarkerStyle(23);//CT
    CalPeak1250->SetMarkerColor(kMagenta);//CT
    CalPeak1400->SetMarkerStyle(33);//CT
    CalPeak1400->SetMarkerColor(kAzure);//CT

    PeakAmpl->cd(NCalo - ch);

    TMultiGraph* PeakPosGlobal = new TMultiGraph("peak pos",Form("peak positions ch. %d",ch));
    PeakPosGlobal->Add(Q511graph);
    PeakPosGlobal->Add(Q1273graph);
    PeakPosGlobal->Add(Q1784graph);

    PeakPosGlobal->Draw("AP");
    PeakPosGlobal->GetXaxis()->SetTitle("HV [V]");
    PeakPosGlobal->GetYaxis()->SetTitle("Charge [pC]");
    PeakPosGlobal->GetXaxis()->SetLabelSize(0.06);
    PeakPosGlobal->GetYaxis()->SetLabelSize(0.06);
    PeakPosGlobal->GetXaxis()->SetTitleSize(0.06);
    PeakPosGlobal->GetYaxis()->SetTitleSize(0.06);
    PeakPosGlobal->GetXaxis()->SetTitleOffset(0.8);
    PeakPosGlobal->GetYaxis()->SetTitleOffset(0.8);

    TLegend* sl_leg = new TLegend(0.59,0.15,0.81,0.41);
    sl_leg->AddEntry(Q511graph,"511keV","p");
    sl_leg->AddEntry(Q1273graph,"1273keV","p");
    sl_leg->AddEntry(Q1784graph,"1784keV","p");

    sl_leg->Draw("SAME");

    Calibration->cd(NCalo - ch);//CT

    TMultiGraph* CalGlobal = new TMultiGraph("Mean peak",Form("peak positions ch. %d",ch));//CT
    CalGlobal->Add(CalPeak1150);//CT
    CalGlobal->Add(CalPeak1250);//CT
    CalGlobal->Add(CalPeak1400);//CT

    CalGlobal->Draw("AP");//CT
    CalGlobal->GetXaxis()->SetTitle("Energy [MeV]");//CT
    CalGlobal->GetYaxis()->SetTitle("Mean Peak [pC]");//CT
    CalGlobal->GetXaxis()->SetLabelSize(0.06);//CT
    CalGlobal->GetYaxis()->SetLabelSize(0.06);//CT
    CalGlobal->GetXaxis()->SetTitleSize(0.06);//CT
    CalGlobal->GetYaxis()->SetTitleSize(0.06);//CT
    CalGlobal->GetXaxis()->SetTitleOffset(0.8);//CT
    CalGlobal->GetYaxis()->SetTitleOffset(0.8);//CT

    TLegend* cal_leg = new TLegend(0.59,0.15,0.81,0.41);//CT
    cal_leg->AddEntry(CalPeak1150,"1150V","p");//CT
    cal_leg->AddEntry(CalPeak1250,"1250V","p");//CT
    cal_leg->AddEntry(CalPeak1400,"1400V","p");//CT

    cal_leg->Draw("SAME");//CT

    TF1 *g1 = new TF1("g1","pol1");//CT
    TF1 *g2 = new TF1("g2","pol1");//CT
    TF1 *g3 = new TF1("g3","pol1");//CT

    CalPeak1150->Fit("g1");//CT
    CalPeak1250->Fit("g2");//CT
    CalPeak1400->Fit("g3");//CT

    CalPeak1150->GetFunction("g1")->SetLineWidth(1);//CT
    CalPeak1250->GetFunction("g2")->SetLineWidth(1);//CT
    CalPeak1400->GetFunction("g3")->SetLineWidth(1);//CT
    CalPeak1150->GetFunction("g1")->SetLineColor(kGray+3);//CT
    CalPeak1250->GetFunction("g2")->SetLineColor(kMagenta);//CT
    CalPeak1400->GetFunction("g3")->SetLineColor(kAzure);//CT

    //TF1 *f1 = new TF1("f1","[0]*exp([1]*x)",1150,1400);
    TF1 *f1 = new TF1("f1","expo");
    TF1 *f2 = new TF1("f2","expo");
    TF1 *f3 = new TF1("f3","expo");

    //Q511graph->Fit("f1","","",1150,1400);
    Q511graph->Fit("f1");
    Q1273graph->Fit("f2");
    Q1784graph->Fit("f3");

    Q511graph->GetFunction("f1")->SetLineWidth(1);
    Q1273graph->GetFunction("f2")->SetLineWidth(1);
    Q1784graph->GetFunction("f3")->SetLineWidth(1);
    Q511graph->GetFunction("f1")->SetLineColor(kBlack);
    Q1273graph->GetFunction("f2")->SetLineColor(kBlue);
    Q1784graph->GetFunction("f3")->SetLineColor(kRed);

    PeakAmpl->cd(NCalo - ch)->Update();
    
    TPaveStats* stats511 = (TPaveStats*)Q511graph->GetListOfFunctions()->FindObject("stats");
    TPaveStats* stats1273 = (TPaveStats*)Q1273graph->GetListOfFunctions()->FindObject("stats");
    TPaveStats* stats1784 = (TPaveStats*)Q1784graph->GetListOfFunctions()->FindObject("stats");
    stats511->SetTextColor(kBlack);
    stats1273->SetTextColor(kBlue);
    stats1784->SetTextColor(kRed);
    stats511->SetX1NDC(0.12); stats511->SetX2NDC(0.42); stats511->SetY1NDC(0.75); stats511->SetY2NDC(0.90);
    stats1273->SetX1NDC(0.12); stats1273->SetX2NDC(0.42); stats1273->SetY1NDC(0.59); stats1273->SetY2NDC(0.74);
    stats1784->SetX1NDC(0.12); stats1784->SetX2NDC(0.42); stats1784->SetY1NDC(0.43); stats1784->SetY2NDC(0.58);

    PeakAmpl->cd(NCalo - ch)->Modified();

    Calibration->cd(NCalo - ch)->Update();//CT
    
    TPaveStats* stats1150 = (TPaveStats*)CalPeak1150->GetListOfFunctions()->FindObject("stats");//CT
    TPaveStats* stats1250 = (TPaveStats*)CalPeak1250->GetListOfFunctions()->FindObject("stats");//CT
    TPaveStats* stats1400 = (TPaveStats*)CalPeak1400->GetListOfFunctions()->FindObject("stats");//CT
    stats1150->SetTextColor(kGray+3);
    stats1250->SetTextColor(kMagenta);
    stats1400->SetTextColor(kAzure);
    stats1150->SetX1NDC(0.12); stats1150->SetX2NDC(0.42); stats1150->SetY1NDC(0.75); stats1150->SetY2NDC(0.90);//CT
    stats1250->SetX1NDC(0.12); stats1250->SetX2NDC(0.42); stats1250->SetY1NDC(0.59); stats1250->SetY2NDC(0.74);//CT
    stats1400->SetX1NDC(0.12); stats1400->SetX2NDC(0.42); stats1400->SetY1NDC(0.43); stats1400->SetY2NDC(0.58);//CT

    Calibration->cd(NCalo - ch)->Modified();//CT

    double slope1 = f1->GetParameter(1);
    double slope2 = f2->GetParameter(1);
    double slope3 = f3->GetParameter(1);

    slope511->Fill(slope1);
    slope1273->Fill(slope2);
    slope1784->Fill(slope3);
    slopeTOT->Fill(slope1);
    slopeTOT->Fill(slope2);
    slopeTOT->Fill(slope3);

  } // end of loop on channels

  ///////////////////
  
  PeakSlope->cd();
 
  //gStyle->SetOptFit();
  
  TLegend* slopeleg = new TLegend(0.15,0.68,0.40,0.89);
  slopeleg->SetFillColor(0);

  slopeTOT->Draw("SAME");
  slopeTOT->SetFillColor(7);
  slopeTOT->SetLineColor(0);
  slopeTOT->GetXaxis()->SetTitle("Slope [V]");
  slope511->Draw("SAME");
  slope511->SetLineColor(kBlack);
  slope511->SetLineWidth(2);
  slope1273->Draw("SAME");
  slope1273->SetLineColor(kBlue);
  slope1273->SetLineWidth(2);
  slope1273->SetLineStyle(2);
  slope1784->Draw("SAME");
  slope1784->SetLineColor(kRed);
  slope1784->SetLineWidth(2);
  slope1784->SetLineStyle(3);

  slopeTOT->Fit("gaus");
  /*
  double maxy1sl = slope511->GetMaximum()>slope1273->GetMaximum() ? slope511->GetMaximum() : slope1273->GetMaximum();
  double maxy2sl = maxy1sl > slope1784->GetMaximum() ? maxy1 : slope1784->GetMaximum(); 

  slope511->SetMaximum(1.2*maxy2sl);
  */
  slopeleg->AddEntry(slopeTOT,"Global slope","f");
  slopeleg->AddEntry(slope511,"511keV slope","l");
  slopeleg->AddEntry(slope1273,"1273keV slope","l");
  slopeleg->AddEntry(slope1784,"1784keV slope","l");
  slopeleg->Draw("SAME");


  ///////////////////
  CRERelease->cd();

  TLegend* CRleg = new TLegend(0.15,0.68,0.40,0.89);
  CRleg->SetFillColor(0);

  ERTOT->Draw("SAME");
  ERTOT->SetFillColor(7);
  ERTOT->SetLineColor(0);
  ERTOT->GetXaxis()->SetTitle("Energy [MeV]");
  ER511->Draw("SAME");
  ER511->SetLineColor(kBlack);
  ER511->SetLineWidth(2);
  ER1273->Draw("SAME");
  ER1273->SetLineColor(kBlue);
  ER1273->SetLineWidth(2);
  ER1273->SetLineStyle(2);
  ER1784->Draw("SAME");
  ER1784->SetLineColor(kRed);
  ER1784->SetLineWidth(2);
  ER1784->SetLineStyle(3);

  ERTOT->Fit("gaus");

  CRleg->AddEntry(ERTOT,"CR from 3 peaks","f");
  CRleg->AddEntry(ER511,"CR from 511keV","l");
  CRleg->AddEntry(ER1273,"CR from 1273keV","l");
  CRleg->AddEntry(ER1784,"CR from 1784keV","l");
  CRleg->Draw("SAME");



  if(SaveFig){

    char* Common_path = "/home/daq/DigiDaq/TestBeamOld/figures/";
    
    c5->SaveAs(Form("%sVertical_CR_Qspectra.pdf",Common_path));
    c5->SaveAs(Form("%sVertical_CR_Qspectra.eps",Common_path));
    c5->SaveAs(Form("%sVertical_CR_Qspectra.root",Common_path));

    Qspectra1150->SaveAs(Form("%sQspectra1150V.pdf",Common_path));
    Qspectra1150->SaveAs(Form("%sQspectra1150V.eps",Common_path));
    Qspectra1150->SaveAs(Form("%sQspectra1150V.root",Common_path));

    Qspectra1250->SaveAs(Form("%sQspectra1250V.pdf",Common_path));
    Qspectra1250->SaveAs(Form("%sQspectra1250V.eps",Common_path));
    Qspectra1250->SaveAs(Form("%sQspectra1250V.root",Common_path));

    Qspectra1400->SaveAs(Form("%sQspectra1400V.pdf",Common_path));
    Qspectra1400->SaveAs(Form("%sQspectra1400V.eps",Common_path));
    Qspectra1400->SaveAs(Form("%sQspectra1400V.root",Common_path));

    Calibration->SaveAs(Form("%sCalibration.pdf",Common_path));
    Calibration->SaveAs(Form("%sCalibration.eps",Common_path));
    Calibration->SaveAs(Form("%sCalibration.root",Common_path));

    PeakAmpl->SaveAs(Form("%sPeaksAmplFit.pdf",Common_path));
    PeakAmpl->SaveAs(Form("%sPeaksAmplFit.eps",Common_path));
    PeakAmpl->SaveAs(Form("%sPeaksAmplFit.root",Common_path));

    PeakSlope->SaveAs(Form("%sPeaksSlopeDistr.pdf",Common_path));
    PeakSlope->SaveAs(Form("%sPeaksSlopeDistr.eps",Common_path));
    PeakSlope->SaveAs(Form("%sPeaksSlopeDistr.root",Common_path));
    
    CRERelease->SaveAs(Form("%sCR_EnergyRelease_no1784peak.pdf",Common_path));
    CRERelease->SaveAs(Form("%sCR_EnergyRelease_no1784peak.eps",Common_path));
    CRERelease->SaveAs(Form("%sCR_EnergyRelease_no1784peak.root",Common_path));

  }
  

}

