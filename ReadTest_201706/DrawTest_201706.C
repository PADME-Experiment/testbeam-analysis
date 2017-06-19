/*
This macro is designed to work on data acquired during the test beam of
5-11 June 2017 @ LNF;

There are 2 function:
- single run: Scan(char* infile, int run, int max_mult=0, bool SaveImages=false)
- general: Scan(bool SaveImages=false, int max_mult=0)

This macro evluates:
- single channel charge spectrum (taken from infile)
- global charge spectrum of non saturated events with interaction point 
  distant from the center of the central crystal <0.7 cm (taken from infile)
- global charge spectrum of saturated events with interaction point distant 
  from the center of the central crystal <0.7 cm (taken from infile)
- position of each event (taken from infile)
- resolution @ 1 GeV (%) VS energy, single and all runs
- resolution (%) VS energy, single and all runs 
- charge VS energy, single and all runs

the all runs version of last 3 plots have also a fit, flat, ResoFunc, 
linear (w/ and w/o intercept) respectively.

Variables are:
infile = input file produced, as output, by Monitor.exe
run = run number
max_mult = maximum mltiplicity to be considered from Q spectrum 
(<0 max multiplicity available for each run, 
=0 optimized multiplicity (specific for this test beam), 
>1 required multiplicity (or up to the maximum, if too large))
SaveImages = set true to save images

Check all the paths:
CommonPath = directory where to save images
infile in the all runs version


Run as:
Scan("Out.root",305,1,false)

or (to cycle over all the Test Beam runs)
Scan.C(false,0)
*/

double ResoFunc(double* x, double* par);


void TimeTrend(char* infile, int run, int mult=0, bool SaveImages=false){

  gStyle->SetOptStat();
  gStyle->SetOptFit();


  // path where images are saved
  char* CommonPath = "/home/daq/DigiDaq/TestBeam201606/figures/";

  double beam_energy_MeV;
  char* detector = "";
  TString infileS = infile;
  
  if(run == 448){beam_energy_MeV = 446; detector = "PMT";}
  else if(run == 449){beam_energy_MeV = 446; detector = "PMT";}
  else if(run == 453){beam_energy_MeV = 446; detector = "PMT";}
  else if(run == 470){beam_energy_MeV = 450; detector = "PMT";}
  else if(run == 471){beam_energy_MeV = 250; detector = "PMT";}
  else if(run == 472){beam_energy_MeV = 150; detector = "PMT";}
  else {
    cout<<"\nRun number not known!\n\n"
	<<"MACRO WILL BE TERMINATED\n"<<endl;
    
    return;
  }
  cout<<"Run: "<<run<<" <:=:> "<<beam_energy_MeV<<" MeV"
      <<" <:=:> "<<detector<<endl;

  TFile *_file0 = TFile::Open(infile);
  char hisname[50];

  int chmin;
  int chmax;
  if(detector=="PMT"){
    chmin = 0;
    chmax = 24;
  } else {

    // no other kind for this test beam

  }



}



void Scan(char* infile, int run, int max_mult=0, bool SaveImages=false){

  gStyle->SetOptStat();
  gStyle->SetOptFit();

  // path where images are saved
  char* CommonPath = "/home/daq/DigiDaq/TestBeam201606/figures/";

  double beam_energy_MeV;
  char* detector = "";
  TString infileS = infile;
  

  if(run == 448){beam_energy_MeV = 446; detector = "PMT";}
  else if(run == 449){beam_energy_MeV = 446; detector = "PMT";}
  else if(run == 453){beam_energy_MeV = 446; detector = "PMT";}
  else if(run == 470){beam_energy_MeV = 450; detector = "PMT";}
  else if(run == 471){beam_energy_MeV = 250; detector = "PMT";}
  else if(run == 472){beam_energy_MeV = 150; detector = "PMT";}
  else {
    cout<<"\nRun number not known!\n\n"
	<<"MACRO WILL BE TERMINATED\n"<<endl;
    
    return;
  }
  cout<<"Run: "<<run<<" <:=:> "<<beam_energy_MeV<<" MeV"
      <<" <:=:> "<<detector<<endl;

  TFile *_file0 = TFile::Open(infile);
  char hisname[50];


  int chmin;
  int chmax;
  if(detector=="PMT"){
    chmin = 0;
    chmax = 25;
  } else {
  }

  // Decomment only if there are the raw pulse and the signal saved
  // in the opened file
  /*  
  TCanvas* RawCanv = new TCanvas("RawCanv","RawCanv",800,800);
  RawCanv->Divide(5,5);
  for(Int_t k2=chmin;k2<chmax;k2++){
    RawCanv->cd(k2-chmin+1);
    sprintf(hisname,Form("ECALRawCh%d",k2));
    TH1D* Raw = (TH1D*)_file0->Get(hisname);
    Raw->SetLineColor(kBlue);
    Raw->GetYaxis()->SetRangeUser(0.,4096.);
    Raw->Draw();
  }
  
  TCanvas* SigCanv = new TCanvas("SigCanv","SigCanv",800,800);
  SigCanv->Divide(5,5);
  for(Int_t k2=chmin;k2<chmax;k2++){
    SigCanv->cd(k2-chmin+1);
    sprintf(hisname,Form("ECALSigCh%d",k2));
    TH1D* Sig = (TH1D*)_file0->Get(hisname);
    Sig->SetLineColor(kBlue);
    Sig->GetYaxis()->SetRangeUser(-1.,0.02);
    Sig->Draw();
  }
  
  //char* RawPath = Form("%srun_%d_Raw_ev10000_000",CommonPath,run);
  //RawCanv->SaveAs(Form("%srun_%d_Raw_ev10000_000.eps",CommonPath,run));
  //RawCanv->SaveAs(Form("%srun_%d_Raw_ev10000_000.pdf",CommonPath,run));
  //RawCanv->SaveAs(Form("%srun_%d_Raw_ev10000_000.root",CommonPath,run));

  //char* SigPath = Form("%srun_%d_Sig_ev10000_000",CommonPath,run);
  //SigCanv->SaveAs(Form("%srun_%d_Sig_ev10000_000.eps",CommonPath,run));
  //SigCanv->SaveAs(Form("%srun_%d_Sig_ev10000_000.pdf",CommonPath,run));
  //SigCanv->SaveAs(Form("%srun_%d_Sig_ev10000_000.root",CommonPath,run));
  
  return;
  */  

  /// Single channel charge spectra ///

  char* c3Name = Form("Charge single channel run %d",run);
  TCanvas* c3 = new TCanvas(c3Name, c3Name, 800, 800);
  c3->Divide(5,5);

  for(Int_t kk=chmin;kk<chmax;kk++){
    c3->cd(25 - (kk-chmin));
    gPad->SetLogy();
    
    sprintf(hisname,Form("ECALQCh%d",kk));
    TH1D* H1 = (TH1D*)_file0->Get(hisname);
    H1->SetFillColor(kRed);
    H1->SetLineColor(kBlack);
    H1->GetXaxis()->SetTitle("Charge [pC]");
    H1->GetYaxis()->SetTitle("Counts/pC");
    H1->GetYaxis()->SetTitleOffset(1.5);
    H1->Draw();
    //H1->GetXaxis()->SetRangeUser(-50.,60.);
    
    /*
    sprintf(hisname,Form("ECALPedQCh%d",kk));
    TH1D* Hped = (TH1D*)_file0->Get(hisname);
    Hped->SetFillColor(0);
    Hped->SetLineColor(kBlue);
    Hped->Draw("SAME");
    
    sprintf(hisname,Form("ECALPedQDoubleCheckCh%d",kk));
    TH1D* Hped2c = (TH1D*)_file0->Get(hisname);
    Hped2c->SetFillColor(0);
    Hped2c->SetLineColor(kGreen);
    Hped2c->Draw("SAME");
    */
  }

  // save graphs
  if(SaveImages){
    c3->SaveAs(Form("%sSingleChs_Q_run%d.pdf",CommonPath,run));
    c3->SaveAs(Form("%sSingleChs_Q_run%d.eps",CommonPath,run));
    c3->SaveAs(Form("%sSingleChs_Q_run%d.root",CommonPath,run));
  }

  /// end of single channel charge spectra ///


  /// Saturated charge spectrum (global), if present ///

  if(infileS.Contains("NoSat")){
    TCanvas* SatCanv = new TCanvas("Saturated histo", "Saturated histo", 800, 800);
    SatCanv->SetLogy();
    sprintf(hisname,Form("ECALQTotSat%s",detector));
    TH1D* H3 = (TH1D*)_file0->Get(hisname);
    H3->SetFillColor(kRed);
    H3->SetLineColor(kBlack);
    //H3->Rebin(2);
    H3->Draw();
    H3->GetXaxis()->SetTitle("Charge [pC]");
    H3->GetYaxis()->SetTitle("Counts");
 
    // save graphs
    if(SaveImages){
      SatCanv->SaveAs(Form("%sTOT_Q_saturated_run%d.pdf",CommonPath,run));
      SatCanv->SaveAs(Form("%sTOT_Q_saturated_run%d.eps",CommonPath,run));
      SatCanv->SaveAs(Form("%sTOT_Q_saturated_run%d.root",CommonPath,run));
    }

  }

  /// end of global saturated charge spectrum ///


  /// Position ///

  char* PosCanvName = Form("Position run %d",run);
  TCanvas* PosCanv = new TCanvas(PosCanvName,PosCanvName, 800, 800);
  PosCanv->cd();
  PosCanv->SetLogz();

  char* PosName = "ECALPos";
  if(detector=="PMT") PosName = Form("%sPMT",PosName);
  else PosName = Form("%sAPD",PosName);
  
  TH2D* Position = (TH2D*)_file0->Get(PosName);
  Position->SetTitle(Form("ECAL - Position run %d",run));
  Position->Draw("colz");
  
  // save graphs
  if(SaveImages){
    PosCanv->SaveAs(Form("%sPosition_run%d.pdf",CommonPath,run));
    PosCanv->SaveAs(Form("%sPosition_run%d.eps",CommonPath,run));
    PosCanv->SaveAs(Form("%sPosition_run%d.root",CommonPath,run));
  } 

  /// end of position ///


  /// Global charge spectrum ///

  char* c4Name = Form("Total Charge run %d",run);
  TCanvas* c4 = new TCanvas(c4Name, c4Name, 800, 800);
  c4->SetLogy();
  TString QTotName = "ECALQTot";
  if(detector=="PMT") QTotName += "PMT";
  else QTotName += "APD";

  sprintf(hisname,Form("ECALQTot%s",detector));
  TH1D* H2 = (TH1D*)_file0->Get(hisname);
  H2->SetTitle(Form("ECAL - Total Charge run %d",run));
  H2->SetFillColor(kRed);
  H2->SetLineColor(kBlack);
  H2->Rebin(5);
  H2->GetXaxis()->SetTitle("Charge [pC]");
  H2->GetYaxis()->SetTitle("Counts");
  H2->Rebin(5);
  H2->Draw();

  int nbins = H2->GetNbinsX();

  float* source = new double[nbins];
  for(int ij=0;ij<nbins;ij++) source[ij] = H2->GetBinContent(ij+1);

  //float* dest = new float[nbins];

  TSpectrum* spec = new TSpectrum();
  int n_peaks = spec->Search(H2,5.,"",0.005);
  //int n_peaks = spec->SearchHighRes(source,dest,nbins,100,0.001,kFALSE,3,kTRUE,10);
  TH1* bkg = spec->Background(H2,80,"LSAME");
  bkg->SetLineColor(kYellow);
  bkg->SetLineWidth(2);
  
  cout<<"\n\n Found "<<n_peaks<<" peak(s):"<<endl;

  float* peakpos = spec->GetPositionX();
  float* ampl =  spec->GetPositionY();

  for(int ii=0;ii<n_peaks;ii++){
    float xp = peakpos[ii];
    int bin = H2->GetXaxis()->FindBin(xp);
    //int bin = 1 + int(xp+0.5);
    double binw = H2->GetBinWidth(1);

    ampl[ii] = ampl[ii] - bkg->GetBinContent(bin);
  }

  //start of arays sorting (based on charge values)
  for(int k1 = 0; k1 < n_peaks-1; k1++){
    for(int k2 = n_peaks-1; k2 > k1; k2--){
      if(peakpos[k2-1] > peakpos[k2]){
	
	double aux;
	
	aux = peakpos[k2-1];
	peakpos[k2-1] = peakpos[k2];
	peakpos[k2] = aux;
	
	aux = ampl[k2-1];
	ampl[k2-1] = ampl[k2];
	ampl[k2] = aux;
      }
    }
  } //end of sorting
  

  for(int i2=0;i2<n_peaks;i2++){
    int bin = H2->GetXaxis()->FindBin(peakpos[i2]);
    cout<<i2+1<<") "<<"x "<<peakpos[i2]<<" (bin "<<bin<<")"
	<<" y "<<ampl[i2]<<" (bkg "<<bkg->GetBinContent(bin)<<")"
	<<endl;
    
  }
  cout<<endl;


  double* positions = new double[n_peaks];
  double* positionsErr = new double[n_peaks];
  double* sigmas = new double[n_peaks];
  double* sigmasErr = new double[n_peaks];

  // fit to the total charge distribution //
  DoFit(H2,n_peaks,peakpos,ampl,positions,positionsErr,sigmas,sigmasErr);

  // save graphs
  if(SaveImages){
    c4->SaveAs(Form("%sTOT_Q_run%d.pdf",CommonPath,run));
    c4->SaveAs(Form("%sTOT_Q_run%d.eps",CommonPath,run));
    c4->SaveAs(Form("%sTOT_Q_run%d.root",CommonPath,run));
  }


  // if only pedestal continue
  if(n_peaks == 1){
    cout<<"Only pedestal for this run."<<endl
	<<"This run will be skipped."<<endl;

    continue;
  }

  int n_max;
  if(max_mult < 0) n_max = n_peaks-1;
  else if(max_mult == 0) n_max = 1;
  else {
    if(max_mult >= n_peaks) n_max = n_peaks-1;
    else n_max = max_mult;
  }
  if(max_mult==0 && run==313) n_max = 3;

  cout<<"n_max "<<n_max<<endl;

  /// end of total charge spectrum ///


  /// Resolution @1GeV graph ///
  
  TGraphErrors* ResoGraph = new TGraphErrors();
  
  for(int kk=1;kk<n_max+1;kk++){
    
    double Xr = beam_energy_MeV*(kk);
    double realpos = positions[kk]-positions[0];
    double realposErr = sqrt(positionsErr[kk]*positionsErr[kk]
			     +positionsErr[0]*positionsErr[0]);
    double Yr = 100*sigmas[kk]/realpos*sqrt(Xr/1000);
    double Yr_err = 100*sqrt(
			     Xr/1000/(realpos*realpos)
			     *(sigmasErr[kk]*sigmasErr[kk])
			     + (sigmas[kk]*sigmas[kk]*Xr/1000
				*(realposErr*realposErr)
				/pow(realpos,4))
			     );
    
    ResoGraph->SetPoint(kk-1,Xr,Yr);
    ResoGraph->SetPointError(kk-1,0,Yr_err);
    
    
    cout<<"E "<<Xr<<" MeV, Reso @ 1GeV ("<<Yr<<" +- "<<Yr_err<<") %"
      //<<", realpos "<<realpos<<" +- "<<realposErr
      //<<", sigma "<<sigmas[kk]<<" +- "<<sigmasErr[kk]
	<<endl;
  }
  
  
  char* ResoCanvName = Form("Resolution @ 1GeV run %d",run);
  TCanvas* ResoCanv = new TCanvas(ResoCanvName,ResoCanvName,800,600);
  ResoCanv->cd();
    if(detector == "PMT") ResoGraph->SetTitle(Form("PMT resolution @ 1GeV run %d",run));
  else ResoGraph->SetTitle(Form("APD resolution @ 1GeV run %d",run));
  ResoGraph->GetXaxis()->SetTitle("Energy [MeV]");
  ResoGraph->GetYaxis()->SetTitle("Resolution @ 1GeV [%]");
  ResoGraph->GetYaxis()->SetTitleOffset(1.3);
  ResoGraph->Draw("AP");
  ResoGraph->SetMarkerStyle(33);
  
  /// end of resolution @1GeV graph ///
  
  
  /// Resolution graph ///

  TGraphErrors* ResoGraph2 = new TGraphErrors();

  for(int kk=1;kk<n_max+1;kk++){

    double Xr = beam_energy_MeV*(kk)/1000.;
    double realpos = positions[kk]-positions[0];
    double realposErr = sqrt(positionsErr[kk]*positionsErr[kk]
			     +positionsErr[0]*positionsErr[0]);
    double Yr = 100*sigmas[kk]/realpos;
    double Yr_err = 100*sqrt(
			     1./(realpos*realpos)
			     *(sigmasErr[kk]*sigmasErr[kk])
			     + (sigmas[kk]*sigmas[kk]
				*(realposErr*realposErr)
				/pow(realpos,4))
			     );


    ResoGraph2->SetPoint(kk-1,Xr,Yr);
    ResoGraph2->SetPointError(kk-1,0,Yr_err);

    cout<<"E "<<Xr<<" GeV, Reso ("<<Yr<<" +- "<<Yr_err<<") %"
      //<<", realpos "<<realpos<<" +- "<<realposErr
      //<<", sigma "<<sigmas[kk]<<" +- "<<sigmasErr[kk]
	<<endl;
  }


  char* ResoCanvName2 = Form("Resolution trend run %d",run);
  TCanvas* ResoCanv2 = new TCanvas(ResoCanvName2,ResoCanvName2,800,600);
  ResoCanv2->cd();
  if(detector == "PMT") ResoGraph2->SetTitle(Form("PMT resolution run %d",run));
  else ResoGraph2->SetTitle(Form("APD resolution run %d",run));
  ResoGraph2->GetXaxis()->SetTitle("Energy [GeV]");
  ResoGraph2->GetYaxis()->SetTitle("Resolution [%]");
  ResoGraph2->GetYaxis()->SetTitleOffset(1.3);
  ResoGraph2->Draw("AP");
  ResoGraph2->SetMarkerStyle(33);

  /// end of resolution graph ///  


  /// Charge graph ///

  cout<<endl;

  TGraphErrors* ChargeGraph = new TGraphErrors();

  for(int kk=1;kk<n_max+1;kk++){

    double Xc = beam_energy_MeV*(kk);
    double Yc = positions[kk]-positions[0];
    double Yc_err = sqrt(positionsErr[kk]*positionsErr[kk]
			 +positionsErr[0]*positionsErr[0]);

    ChargeGraph->SetPoint(kk-1,Xc,Yc);
    ChargeGraph->SetPointError(kk-1,0,Yc_err);

    cout<<"E "<<Xc<<" MeV "<<", Q ("<<Yc<<" +- "<<Yc_err<<") pC"<<endl;
  }

  char* ChargeCanvName = Form("Charge trend run %d",run);
  TCanvas* ChargeCanv = new TCanvas(ChargeCanvName,ChargeCanvName,800,600);

  ChargeCanv->cd();
  if(detector == "PMT") ChargeGraph->SetTitle(Form("PMT charge run %d",run));
  else ChargeGraph->SetTitle(Form("APD charge run %d",run));
  ChargeGraph->GetXaxis()->SetTitle("Energy [MeV]");
  ChargeGraph->GetYaxis()->SetTitle("Charge [pC]");
  ChargeGraph->GetYaxis()->SetTitleOffset(1.5);
  ChargeGraph->Draw("AP");
  ChargeGraph->SetMarkerStyle(33);

  /// end of charge graph ///

}


////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void Scan(int kind=1, bool SaveImages=false, int max_mult=0){

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);


  if(kind<1 || kind>3){
    cout<<"ERROR: kind goes from 1 to 3:\n"
	<<"1: first samples mean subtraction"
	<<"2: first samples linear fit subtraction"
	<<"3: average empty pulse subtraction"
	<<endl;

    return;
  }

  char* kname = "";
  if(kind==2) kname = "_LF";
  else if(kind==3) kname = "_AS";


  // path where images are saved
  TString CommonPath = "/home/daq/DigiDaq/TestBeamOld/figures/";


  int run;
  char* infile = "";


  TMultiGraph* ResoGlobalGraphPMT = new TMultiGraph("PMT Resolution @ 1GeV global","PMT Resolution @ 1GeV global");

  TMultiGraph* ResoGlobalGraphPMT2 = new TMultiGraph("PMT Resolution global trend","PMT Resolution global trend");

  TMultiGraph* ChargeGlobalGraphPMT = new TMultiGraph("PMT Charge global trend 1","PMT Charge global trend 1");

  TMultiGraph* ChargeGlobalGraphPMT2 = new TMultiGraph("PMT Charge global trend 2","PMT Charge global trend 2");
  /*
  TMultiGraph* ResoGlobalGraphAPD = new TMultiGraph("APD Resolution @ 1GeV global","APD Resolution @ 1GeV global");

  TMultiGraph* ResoGlobalGraphAPD2 = new TMultiGraph("APD Resolution global trend","APD Resolution global trend");

  TMultiGraph* ChargeGlobalGraphAPD = new TMultiGraph("APD Charge global trend 1","APD Charge global trend 1");

  TMultiGraph* ChargeGlobalGraphAPD2 = new TMultiGraph("APD Charge global trend 2","APD Charge global trend 2"); 
  */


  leg = new TLegend(0.17,0.61,0.43,0.89);
  leg->SetFillColor(0);
  leg->AddEntry((TObject*)0,"Run  Energy [MeV]","");


  // cycle over the runs
  for(int irun=0;irun<5;irun++){

    cout<<"\n\n=========================================================="
	<<"==========="<<endl;

    double beam_energy_MeV;
    char* detector = "";

    if(irun == 0){run = 775; beam_energy_MeV = 100; detector = "PMT";}
    else if(irun == 1){run = 799; beam_energy_MeV = 200; detector = "PMT";}
    else if(irun == 2){run = 804; beam_energy_MeV = 150; detector = "PMT";}
    else if(irun == 3){run = 806; beam_energy_MeV = 250; detector = "PMT";}
    else if(irun == 4){run = 807; beam_energy_MeV = 300; detector = "PMT";}
     else {
      cout<<"\nRun number not known!\n\n"
	  <<"MACRO WILL BE TERMINATED\n"<<endl;
      
      return;
    }
    cout<<"Run "<<run<<" <:=:> "<<beam_energy_MeV<<" MeV"
	<<" <:=:> "<<detector<<endl;

    // select the files to open

    infile = Form("/home/daq/DigiDaq/TestBeamOld/out%d_000%s.root",run,kname);
    cout<<"\nOpening: "<<infile<<endl;


    char hisname[50];
    TFile *_file0 = TFile::Open(infile);
    TString infileS = infile;


    /// Single channel charge ///

    char* c3Name = Form("Charge single channel run %d",run);
    TCanvas* c3 = new TCanvas(c3Name, c3Name, 800, 800);
    c3->Divide(5,5);

    int chmin;
    int chmax;
    if(detector=="PMT"){
      chmin = 0;
      chmax = 25;
    } else {
      chmin = 0;
      chmax = 25;
    }

    for(Int_t kk=chmin;kk<chmax;kk++){
      c3->cd(kk-chmin+1);
      gPad->SetLogy();
      sprintf(hisname,Form("hQCh%d",kk));
      TH1D* H1 = (TH1D*)_file0->Get(hisname);
      H1->SetFillColor(kRed);
      H1->SetLineColor(kBlack);
      H1->Draw();
    }


    // save graphs
    if(SaveImages){
      c3->SaveAs(Form("%sSingleChs_Q_run%d.pdf",CommonPath,run));
      c3->SaveAs(Form("%sSingleChs_Q_run%d.eps",CommonPath,run));
      c3->SaveAs(Form("%sSingleChs_Q_run%d.root",CommonPath,run));
    }

    /// end of single channel charge ///


    /// Saturated charge spectrum (global), if present ///

    if(infileS.Contains("NoSat")){
      char* SatCanvName = Form("Total Charge Saturated run %d",run);
      TCanvas* SatCanv = new TCanvas(SatCanvName,SatCanvName, 800, 800);
      SatCanv->cd();
      SatCanv->SetLogy();
      char* QTotSatName = "ECALQTotSat";
      if(detector=="PMT") QTotSatName = Form("%sPMT",QTotSatName);
      else QTotSatName = Form("%sAPD",QTotSatName);
      sprintf(hisname,QTotSatName);
      TH1D* H3 = (TH1D*)_file0->Get(hisname);
      H3->SetTitle(Form("ECAL - Total Charge Saturated run %d",run));
      H3->SetFillColor(kRed);
      H3->SetLineColor(kBlack);
      //H3->Rebin(2);
      H3->Draw();

      // save graphs
      if(SaveImages){
	SatCanv->SaveAs(Form("%sTOT_Q_saturated_run%d.pdf",CommonPath,run));
	SatCanv->SaveAs(Form("%sTOT_Q_saturated_run%d.eps",CommonPath,run));
	SatCanv->SaveAs(Form("%sTOT_Q_saturated_run%d.root",CommonPath,run));
      }

    }

    /// end of global saturated charge spectrum ///
    

    /// Position ///

    char* PosCanvName = Form("Position run %d",run);
    TCanvas* PosCanv = new TCanvas(PosCanvName,PosCanvName, 800, 800);
    PosCanv->cd();

    char* PosName = "hECALPos";

    TH2D* Position = (TH2D*)_file0->Get(PosName);
    Position->SetTitle(Form("ECAL - Position run %d",run));
    Position->Draw();

    // save graphs
    if(SaveImages){
      PosCanv->SaveAs(Form("%sPosition_run%d.pdf",CommonPath,run));
      PosCanv->SaveAs(Form("%sPosition_run%d.eps",CommonPath,run));
      PosCanv->SaveAs(Form("%sPosition_run%d.root",CommonPath,run));
    }

    /// end of position ///


    /// global charge spectrum ///

    char* c4Name = Form("Total Charge run %d",run);
    TCanvas* c4 = new TCanvas(c4Name, c4Name, 800, 800);
    c4->SetLogy();
    char* QTotName = "hQTotCal";

    sprintf(hisname,QTotName);
    TH1D* H2 = (TH1D*)_file0->Get(hisname);
    H2->SetTitle(Form("ECAL - Total Charge run %d",run));
    H2->SetFillColor(kRed);
    H2->SetLineColor(kBlack);
    H2->Rebin(2);
    H2->GetXaxis()->SetTitle("Charge [pC]");
    H2->GetYaxis()->SetTitle("Counts");
    H2->Draw();
    
    int nbins = H2->GetNbinsX();
    
    float* source = new double[nbins];
    for(int ij=0;ij<nbins;ij++) source[ij] = H2->GetBinContent(ij+1);
    
    //float* dest = new float[nbins];
    
    TSpectrum* spec = new TSpectrum();
    //spec->SetResolution(10);

    int n_peaks = spec->Search(H2,5.,"",0.0005);
    //int n_peaks = spec->SearchHighRes(source,dest,nbins,100,0.001,kFALSE,3,kTRUE,10);
    TH1* bkg = spec->Background(H2,20,"LSAME");
    bkg->SetLineColor(kYellow);
    bkg->SetLineWidth(2);

    cout<<"\n\n Found "<<n_peaks<<" peak(s):"<<endl;
    
    float* peakpos = spec->GetPositionX();
    float* ampl = spec->GetPositionY();
    
    for(int ii=0;ii<n_peaks;ii++){
      float xp = peakpos[ii];
      int bin = H2->GetXaxis()->FindBin(xp);
      //int bin = 1 + int(xp+0.5);
      
      ampl[ii] = ampl[ii] - bkg->GetBinContent(bin);
    }
    
    //start of arays sorting (based on charge values)
    for(int k1 = 0; k1 < n_peaks-1; k1++){
      for(int k2 = n_peaks-1; k2 > k1; k2--){
	if(peakpos[k2-1] > peakpos[k2]){
	  
	  double aux;

	  aux = peakpos[k2-1];
	  peakpos[k2-1] = peakpos[k2];
	  peakpos[k2] = aux;

	  aux = ampl[k2-1];
	  ampl[k2-1] = ampl[k2];
	  ampl[k2] = aux;
	}
      }
    } //end of sorting
    

    for(int i2=0;i2<n_peaks;i2++){
      int bin = H2->GetXaxis()->FindBin(peakpos[i2]);
      cout<<i2+1<<") "<<"x "<<peakpos[i2]<<" (bin "<<bin<<")"
	  <<" y "<<ampl[i2]<<" (bkg "<<bkg->GetBinContent(bin)<<")"
	  <<endl;
      
    }
    cout<<endl;
    
    
    double* positions = new double[n_peaks];
    double* positionsErr = new double[n_peaks];
    double* sigmas = new double[n_peaks];
    double* sigmasErr = new double[n_peaks];
    
    // fit to the total charge distribution //
    DoFit(H2,n_peaks,peakpos,ampl,positions,positionsErr,sigmas,sigmasErr);

    // save graphs
    if(SaveImages){
      c4->SaveAs(Form("%sTOT_Q_run%d.pdf",CommonPath,run));
      c4->SaveAs(Form("%sTOT_Q_run%d.eps",CommonPath,run));
      c4->SaveAs(Form("%sTOT_Q_run%d.root",CommonPath,run));
    }

    
    // if only pedestal continue
    if(n_peaks == 1){
      cout<<"Only pedestal for this run."<<endl
	  <<"This run will be skipped."<<endl;

      continue;
    }
    
    /*
    for(int j2=0;j2<n_peaks;j2++){
      cout<<"positions["<<j2<<"] "<<positions[j2]
	  <<", positionsErr["<<j2<<"] "<<positionsErr[j2]
	  <<", sigmas["<<j2<<"] "<<sigmas[j2]
	  <<", sigmasErr["<<j2<<"] "<<sigmasErr[j2]
	  <<endl;
    }
    */

    int n_max;
    if(max_mult < 0) n_max = n_peaks-1;
    else if(max_mult == 0) n_max = 1;
    else {
      if(max_mult >= n_peaks-1) n_max = n_peaks-1;
      else n_max = max_mult;
    }
 
    cout<<"n_max "<<n_max<<endl;

    /// end of total charge spectrum ///


    /// Resolution @1GeV graph ///

    TGraphErrors* ResoGraph = new TGraphErrors();
    
    for(int kk=1;kk<n_max+1;kk++){
      
      double Xr = beam_energy_MeV*(kk);
      double realpos = positions[kk]-positions[0];
      double realposErr = sqrt(positionsErr[kk]*positionsErr[kk]
			       +positionsErr[0]*positionsErr[0]);
      double Yr = 100*sigmas[kk]/realpos*sqrt(Xr/1000);
      double Yr_err = 100*sqrt(
			       Xr/1000/(realpos*realpos)
			       *(sigmasErr[kk]*sigmasErr[kk])
			       + (sigmas[kk]*sigmas[kk]*Xr/1000
				  *(realposErr*realposErr)
				  /pow(realpos,4))
			       );

      ResoGraph->SetPoint(kk-1,Xr,Yr);
      ResoGraph->SetPointError(kk-1,0,Yr_err);

      
      cout<<"E "<<Xr<<" MeV, Reso @ 1GeV ("<<Yr<<" +- "<<Yr_err<<") %"
	//<<", realpos "<<realpos<<" +- "<<realposErr
	//<<", sigma "<<sigmas[kk]<<" +- "<<sigmasErr[kk]
	  <<endl;
    }

    
    char* ResoCanvName = Form("Resolution @ 1GeV run %d",run);
    TCanvas* ResoCanv = new TCanvas(ResoCanvName,ResoCanvName,800,600);
    ResoCanv->cd();
    //ResoGraph->SetMarkerStyle(33);
    ResoGraph->SetMarkerStyle(20+irun+int(irun/3));
    ResoGraph->SetTitle(Form("Resolution @ 1GeV run %d",run));
    ResoGraph->GetXaxis()->SetTitle("Energy [MeV]");
    ResoGraph->GetYaxis()->SetTitle("Resolution @ 1GeV [%]");
    ResoGraph->GetYaxis()->SetTitleOffset(1.3);
    ResoGraph->Draw("AP");
    
    // filling of the global graph
    if(1){
      ResoGlobalGraphPMT->Add(ResoGraph);
    }
    else{
      ResoGlobalGraphAPD->Add(ResoGraph);
    }

    /// end of resolution @1GeV graph ///


    /// Resolution graph ///
    
    cout<<endl;
    TGraphErrors* ResoGraph2 = new TGraphErrors();
    
    for(int kk=1;kk<n_max+1;kk++){
      
      double Xr = beam_energy_MeV*(kk)/1000;
      double realpos = positions[kk]-positions[0];
      double realposErr = sqrt(positionsErr[kk]*positionsErr[kk]
			       +positionsErr[0]*positionsErr[0]);
      double Yr = 100*sigmas[kk]/realpos;
      double Yr_err = 100*sqrt(
			   1/(realpos*realpos)
			   *(sigmasErr[kk]*sigmasErr[kk])
			   + (sigmas[kk]*sigmas[kk]
			      *(realposErr*realposErr)
			      /pow(realpos,4))
			   );

      ResoGraph2->SetPoint(kk-1,Xr,Yr);
      ResoGraph2->SetPointError(kk-1,0,Yr_err);

      
      cout<<"E "<<Xr<<" GeV, Reso ("<<Yr<<" +- "<<Yr_err<<") %"
	//<<", realpos "<<realpos<<" +- "<<realposErr
	//<<", sigma "<<sigmas[kk]<<" +- "<<sigmasErr[kk]
	  <<endl;
    }

    
    char* ResoCanvName2 = Form("Resolution trend run %d",run);
    TCanvas* ResoCanv2 = new TCanvas(ResoCanvName2,ResoCanvName2,800,600);
    ResoCanv2->cd();
    //ResoGraph2->SetMarkerStyle(33);
    ResoGraph2->SetMarkerStyle(20+irun+int(irun/3));
    ResoGraph2->SetTitle(Form("Resolution run %d",run));
    ResoGraph2->GetXaxis()->SetTitle("Energy [GeV]");
    ResoGraph2->GetYaxis()->SetTitle("Resolution [%]");
    ResoGraph2->GetYaxis()->SetTitleOffset(1.3);
    ResoGraph2->Draw("AP");
    
    // filling of the global PMT/APD graphs
    if(1){
      ResoGlobalGraphPMT2->Add(ResoGraph2);
    }
    else{
      ResoGlobalGraphAPD2->Add(ResoGraph2);
    }

    /// end of resolution graph ///
    
    
    /// Charge graph ///

    cout<<endl;    
    TGraphErrors* ChargeGraph = new TGraphErrors();
    
    for(int kk=1;kk<n_max+1;kk++){
      
      double Xc = beam_energy_MeV*(kk);
      double Yc = positions[kk]-positions[0];
      double Yc_err = sqrt(positionsErr[kk]*positionsErr[kk]
			   +positionsErr[0]*positionsErr[0]);
      
      ChargeGraph->SetPoint(kk-1,Xc,Yc);
      ChargeGraph->SetPointError(kk-1,0,Yc_err);

      
      cout<<"E "<<Xc<<" MeV, Q ("<<Yc<<" +- "<<Yc_err<<") pC"<<endl;
    }


    char* ChargeCanvName = Form("Charge trend run %d",run);
    TCanvas* ChargeCanv = new TCanvas(ChargeCanvName,ChargeCanvName,800,600);
    
    ChargeCanv->cd();
    ChargeGraph->SetTitle(Form("Charge run %d",run));
    ChargeGraph->GetXaxis()->SetTitle("Energy [MeV]");
    ChargeGraph->GetYaxis()->SetTitle("Charge [pC]");
    ChargeGraph->GetYaxis()->SetTitleOffset(1.5);
    //ChargeGraph->SetMarkerStyle(33);
    ChargeGraph->SetMarkerStyle(20+irun+int(irun/3));
    ChargeGraph->Draw("AP");
    
    // filling of the global graph
    if(1){
      ChargeGlobalGraphPMT->Add(ChargeGraph);
      ChargeGlobalGraphPMT2->Add(ChargeGraph);
    }
    else{
      ChargeGlobalGraphAPD->Add(ChargeGraph);
      ChargeGlobalGraphAPD2->Add(ChargeGraph);
    }

    /// end of charge graph ///


    // filling legend
    leg->AddEntry(ChargeGraph,Form("%d                  %3.0f",
				   run,beam_energy_MeV),"p");


  }// end of cycle on irun (over run number)


  cout<<"\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
      <<"\nGLOBAL GRAPHS"<<endl<<endl;


  /// Resolution @1GeV multigraph ///
  
  TCanvas* TOTResCanv = new TCanvas("Multi run resolution @ 1GeV","Multi run resolution @ 1GeV");
  TOTResCanv->cd();
  //TMultiGraph* ResoGlobalGraph = new TMultiGraph("Resolution @ 1GeV","Resolution @ 1GeV");

  /*ResoGlobalGraph->Add(ResoGlobalGraphPMT);
  ResoGlobalGraph->Add(ResoGlobalGraphAPD);
  ResoGlobalGraph->Draw("AP");
  ResoGlobalGraph->GetXaxis()->SetTitle("Energy [MeV]");
  ResoGlobalGraph->GetYaxis()->SetTitle("Resolution @ 1GeV [%]");
  */
  ResoGlobalGraphPMT->Draw("AP");
  ResoGlobalGraphPMT->GetXaxis()->SetTitle("Energy [MeV]");
  ResoGlobalGraphPMT->GetYaxis()->SetTitle("Resolution @ 1GeV [%]");


  leg->Draw("SAME");
 
  double minx = ResoGlobalGraphPMT->GetXaxis()->GetXmin();
  double maxx = ResoGlobalGraphPMT->GetXaxis()->GetXmax();

  cout<<"\n\n"
      <<"**********************"<<endl
      <<"*Resolution @1GeV fit*"<<endl
      <<"**********************"<<endl<<endl;
  TF1* resoflatPMT = new TF1("resoflatPMT","[0]",minx,maxx);
  ResoGlobalGraphPMT->Fit(resoflatPMT,"+","",minx,maxx);
  resoflatPMT->Draw("LSAME");
  resoflatPMT->SetLineColor(kBlue);
  /*
  TOTResCanv->Update();
  TPaveStats* statsReso1GeV = (TPaveStats*)ResoGlobalGraphPMT->GetListOfFunctions()->FindObject("stats");
  //statsReso1GeV->SetX1NDC(0.12); statsReso1GeV->SetX2NDC(0.42); statsReso1GeV->SetY1NDC(0.75); statsReso1GeV->SetY2NDC(0.90);
  TOTResCanv->Modified();
  */

  /// end of resolution @1GeV multigraph ///


  /// Resolution multigraph ///

  TCanvas* TOTResCanv2 = new TCanvas("Multi run resolution","Multi run resolution");
  TOTResCanv2->cd();
  TMultiGraph* ResoGlobalGraph2 = new TMultiGraph("Resolution global trend","Resolution global trend");
  ResoGlobalGraph2->Add(ResoGlobalGraphPMT2);
  ResoGlobalGraph2->Draw("AP");
  ResoGlobalGraph2->GetXaxis()->SetTitle("Energy [GeV]");
  ResoGlobalGraph2->GetYaxis()->SetTitle("Resolution [%]");

  leg->Draw("SAME");

  double minx2 = ResoGlobalGraph2->GetXaxis()->GetXmin();
  double maxx2 = ResoGlobalGraph2->GetXaxis()->GetXmax();

  cout<<"\n\n"
      <<"****************"<<endl
      <<"*Resolution fit*"<<endl
      <<"****************"<<endl<<endl;
  TF1* resoslopePMT = new TF1("resoslopePMT",ResoFunc,minx2,maxx2,2);
  resoslopePMT->SetParLimits(1,0,10);
  ResoGlobalGraphPMT2->Fit(resoslopePMT);
  resoslopePMT->Draw("LSAME");
  resoslopePMT->SetLineColor(kBlue);
  /*
  cout<<"\n\n"
      <<"********************"<<endl
      <<"*APD resolution fit*"<<endl
      <<"********************"<<endl<<endl;
  TF1* resoslopeAPD = new TF1("resoslopeAPD",ResoFunc,minx2,maxx2,2);
  resoslopeAPD->SetParLimits(1,0,10);
  ResoGlobalGraphAPD2->Fit(resoslopeAPD);
  resoslopeAPD->Draw("LSAME");
  resoslopeAPD->SetLineColor(kRed);
  */
  /// end of resolution multigraph ///


  /// Charge multigraph ///

  TCanvas* TOTQCanv = new TCanvas("Multi run charge w/o intercept","Multi run charge w/o intercept");
  TOTQCanv->cd();
  TMultiGraph* ChargeGlobalGraph = new TMultiGraph("Charge global trend - w/o intercept","Charge global trend - w/o interept");
  ChargeGlobalGraph->Add(ChargeGlobalGraphPMT);
  //ChargeGlobalGraph->Add(ChargeGlobalGraphAPD);
  ChargeGlobalGraph->Draw("AP");
  ChargeGlobalGraph->GetXaxis()->SetTitle("Energy [MeV]");
  ChargeGlobalGraph->GetYaxis()->SetTitle("Charge [pC]");
  ChargeGlobalGraph->GetYaxis()->SetTitleOffset(1.5);

  leg->Draw("SAME");

  double minx3 = ChargeGlobalGraph->GetXaxis()->GetXmin();
  double maxx3 = ChargeGlobalGraph->GetXaxis()->GetXmax();

  cout<<"\n\n"
      <<"*********************************"<<endl
      <<"*Charge linear fit w/o intercept*"<<endl
      <<"*********************************"<<endl<<endl;
  TF1* lfitPMT = new TF1("lfitPMT","[0]*x",minx3,maxx3);
  ChargeGlobalGraphPMT->Fit("lfitPMT","+","",minx3,maxx3);
  ChargeGlobalGraphPMT->GetFunction("lfitPMT")->SetLineColor(kBlue);
  //ChargeGlobalGraphPMT->GetFunction("lfitPMT")->SetLineStyle(kDashed);
  //lfitPMT->SetLineColor(kBlue);
  //lfitPMT->Draw("SAME");
  /*
  cout<<"\n\n"
      <<"*************************************"<<endl
      <<"*APD charge linear fit w/o intercept*"<<endl
      <<"*************************************"<<endl<<endl;
  TF1* lfitAPD = new TF1("lfitAPD","[0]*x",minx3,maxx3);
  ChargeGlobalGraphAPD->Fit("lfitAPD","+","",minx3,maxx3);
  ChargeGlobalGraphAPD->GetFunction("lfitAPD")->SetLineColor(kRed);
  //ChargeGlobalGraphAPD->GetFunction("lfitAPD")->SetLineStyle(kDashed);
  //lfitAPD->SetLineColor(kRed);
  //lfitAPD->Draw("SAME");
  */
  ChargeGlobalGraphPMT->Draw();
  //ChargeGlobalGraphAPD->Draw();

  
  TCanvas* TOTQCanv2 = new TCanvas("Multi run charge w/ intercept","Multi run charge w/ intercept");
  TOTQCanv2->cd();
  TMultiGraph* ChargeGlobalGraph2 = new TMultiGraph("Charge global trend w/ intercept","Charge global trend w/ intercept");
  ChargeGlobalGraph2->Add(ChargeGlobalGraphPMT2);
  //ChargeGlobalGraph2->Add(ChargeGlobalGraphAPD2);
  ChargeGlobalGraph2->Draw("AP");
  ChargeGlobalGraph2->GetXaxis()->SetTitle("Energy [MeV]");
  ChargeGlobalGraph2->GetYaxis()->SetTitle("Charge [pC]");
  ChargeGlobalGraph2->GetYaxis()->SetTitleOffset(1.5);

  leg->Draw("SAME");  
  
  cout<<"\n\n"
      <<"********************************"<<endl
      <<"*Charge linear fit w/ intercept*"<<endl
      <<"********************************"<<endl<<endl;
  TF1* l2fitPMT = new TF1("l2fitPMT","[0]+[1]*x",minx3,maxx3);
  ChargeGlobalGraphPMT2->Fit("l2fitPMT","+","",minx3,maxx3);
  ChargeGlobalGraphPMT2->GetFunction("l2fitPMT")->SetLineColor(kBlue);
  /*
  cout<<"\n\n"
      <<"************************************"<<endl
      <<"*APD charge linear fit w/ intercept*"<<endl
      <<"************************************"<<endl<<endl;
  TF1* l2fitAPD = new TF1("l2fitAPD","[0]+[1]*x",minx3,maxx3);
  ChargeGlobalGraphAPD2->Fit("l2fitAPD","+","",minx3,maxx3);
  ChargeGlobalGraphAPD2->GetFunction("l2fitAPD")->SetLineColor(kRed);
  */
  ChargeGlobalGraphPMT2->Draw();
  //ChargeGlobalGraphAPD2->Draw();

  /*
  gPad->Modified();
  gPad->Update();
  TPaveStats* stAPD2 = (TPaveStats*) ResoGlobalGraphAPD2->FindObject("stats");
  stAPD2->SetFillStyle(0);
  stAPD2->SetX1NDC(0.15);
  stAPD2->SetX2NDC(0.55);
  stAPD2->SetY1NDC(0.15);
  stAPD2->SetY2NDC(0.55);
  */


  
  /// end of charge multigraph ///


  // save global graphs
  if(SaveImages){
    TString mult_text = "";
    if(max_mult == 0) mult_text = "opt";
    else if(max_mult < 0) mult_text = "max";
    else mult_text = max_mult;

    TOTResCanv->SaveAs(Form("%sReso1GeV_M%s_NovTestBeamAllRuns.pdf",CommonPath,mult_text));
    TOTResCanv->SaveAs(Form("%sReso1GeV_M%s_NovTestBeamAllRuns.eps",CommonPath,mult_text));
    TOTResCanv->SaveAs(Form("%sReso1GeV_M%s_NovTestBeamAllRuns.root",CommonPath,mult_text));

    TOTResCanv2->SaveAs(Form("%sReso_M%s_NovTestBeamAllRuns.pdf",CommonPath,mult_text));
    TOTResCanv2->SaveAs(Form("%sReso_M%s_NovTestBeamAllRuns.eps",CommonPath,mult_text));
    TOTResCanv2->SaveAs(Form("%sReso_M%s_NovTestBeamAllRuns.root",CommonPath,mult_text));

    TOTQCanv->SaveAs(Form("%sQ_trend_WithIntercept_M%s_NovTestBeamAllRuns.pdf",CommonPath,mult_text));
    TOTQCanv->SaveAs(Form("%sQ_trend_WithIntercept_M%s_NovTestBeamAllRuns.eps",CommonPath,mult_text));
    TOTQCanv->SaveAs(Form("%sQ_trend_WithIntercept_M%s_NovTestBeamAllRuns.root",CommonPath,mult_text));
  }

}



void DoFit(TH1D* histo, int np, float* peaks, float* amplitudes,
	   double* pos, double* poserr, double* sig, double* sigerr){

  //fit all'istogramma usando fit func con i valori inizializzati correttamente

  double min = histo->GetXaxis()->GetXmin();
  double max = histo->GetXaxis()->GetXmax();
  cout<<"\n\nFitting in range: ["<<min<<","<<max<<"]"<<endl;


  char* func = "gaus";
  for(int ip=1;ip<np;ip++) func = Form("%s+gaus(%d)",func,int(ip*3));
  cout<<"Using the function: "<<func<<endl<<endl<<endl;

  int ipar = -1;
  TF1* fitfunc = new TF1("fitfunc",func,min,max);
  
  for(int iip=0;iip<np;iip++){
    fitfunc->SetParName(++ipar,Form("A%d",iip+1));
    fitfunc->SetParameter(ipar,amplitudes[iip]);
    fitfunc->SetParLimits(ipar,amplitudes[iip]/2,3*amplitudes[iip]);
    fitfunc->SetNpx(10000);
    
    fitfunc->SetParName(++ipar,Form("#mu%d",iip+1));
    fitfunc->SetParameter(ipar,peaks[iip]);
    if(iip==0) fitfunc->SetParLimits(ipar,peaks[iip]-40,peaks[iip]+40);
    else fitfunc->SetParLimits(ipar,peaks[iip]-200,peaks[iip]+200);
    fitfunc->SetNpx(10000);

    fitfunc->SetParName(++ipar,Form("#sigma%d",iip+1));
    fitfunc->SetParameter(ipar,100);
    fitfunc->SetParLimits(ipar,10,700);
    fitfunc->SetNpx(10000);
  }

  fitfunc->SetLineColor(kBlue);
  histo->Fit("fitfunc","Q","",min,max);


  for(int jj=0;jj<np;jj++){
    pos[jj] = fitfunc->GetParameter(3*jj+1);
    poserr[jj] = fitfunc->GetParError(3*jj+1);
    sig[jj] = fitfunc->GetParameter(3*jj+2);
    sigerr[jj] = fitfunc->GetParError(3*jj+2);
  }

}



double ChargeFunc(double* x, double* par){

  /*
    legend:

    x[0] = charge (Q)

    single hit
    par[0] = G1 amplitude (A1)
    par[1] = G1 mean (m1)
    par[2] = G1 sigma (s1)
 
    double hit
    par[3] = G2 amplitude (A2)
    par[4] = G2 mean (m2)
    par[5] = G2 sigma (s2)

    triple hit
    par[6] = G3 amplitude (A3)
    par[7] = G3 mean (m3)
    par[8] = G3 sigma (s3)

    exponential bkg
    par[9] = amplitude
    par[10] = shift
    par[11] = X scale

   */

  double xx = x[0];
  double a;
  
  a = par[0]*exp(-0.5*((xx-par[1])/par[2])**2) +
    par[3]*exp(-0.5*((xx-par[4])/par[5])**2) +
    par[6]*exp(-0.5*((xx-par[7])/par[8])**2);
  //par[9]*exp((par[10]-xx)/par[11]);
  
  return a;

}


double ResoFunc(double* x, double* par){

  /*
    legend:

    x[0] = energy (E)

    par[0] = a
    par[1] = b
    par[2] = c


    formula:

    a/sqrt(E) + c + b/E

   */

  double xx = x[0];
  double a;

  // linear term not used
  a = sqrt(par[0]**2/xx + par[1]**2);// + par[2]**2/xx**2;

  return a;

}
