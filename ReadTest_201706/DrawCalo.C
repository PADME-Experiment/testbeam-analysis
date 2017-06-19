#include "TH1D.h"
#include "TF1.h"
#include "TFile.h"

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

void DrawCalo(){
  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  Int_t    NGaus  = 5;
  Double_t E      = 50.;
  Double_t Compare= 0;
  Double_t Mean[5];
  Double_t MRatio[5];
  Double_t RMS[5];
  Double_t ENE[5];
  Double_t ENEFit[5];
  Double_t RMSE[5];
  Double_t MRatioE[5];
  Double_t SuperBUn[2]={0.025,0.011};
  Double_t EMean[5]={1.43,2.1,5.6,12.8,0.};
  Double_t ERESO[5]={2e-4,1.5e-4,1e-4,0.5e-4,0.};
  //  Double_t ENE_E[5]={2.5,5,7.5,10.};
  Double_t ENE_E[5]={0.,0.,0.,0.,0.};  
  Double_t RESO[5];
  Double_t RESO_UN[5];
  Double_t par[15];
  Double_t epar[15];
  TF1 *g1;    
  TF1 *g2;   
  TF1 *g3;    
  TF1 *g4;
  TF1 *g5;
  TF1 *total;
  TH1D * hPedHis    = new TH1D("hPedHis","",170,3700.,3870.);;
  TH2D * hPedHis2D  = new TH2D("hPedHis2D","",32,-0.5,31.5,170,3700.,3870.);;
  TH2D * hQPedHis2D = new TH2D("hQPedHis2D","",32,-0.5,31.5,200,-150.,150.);;
  
  Int_t NCalo=25;
  Int_t Nrow=5;
  Int_t Ncol=5;
  Int_t NFit;
  char hisname[50];
  TFile * _file0;
  
  if(E==250.){
    printf("Drawing 250 MeV histograms\n");
    //    _file0 = TFile::Open("output/E250NoBug472.root");
    //    _file0 = TFile::Open("output/250Nov.root");
    //    _file0 = TFile::Open("output/out_537.root");
    // _file0 = TFile::Open("output/merda.root");
    //    _file0 = TFile::Open("output/250MeVColla.root");
    _file0 = TFile::Open("output/out472.root");
    //    _file0 = TFile::Open("output/out540_10pC.root");
    //_file0 = TFile::Open("output/E250NoBug.root");
    NFit = NGaus;
  }
  if(E==450.){
    printf("Drawing 450 MeV histograms\n");
    //    _file0 = TFile::Open("output/E450NoBug.root");
    _file0 = TFile::Open("output/out470.root");
    NFit = NGaus;
  }

  if(E==100.){
    printf("Drawing 100 MeV histograms\n");
    _file0 = TFile::Open("output/run654.root");
    NFit = 5;
  }


  if(E==50.){
    printf("Drawing 50 MeV histograms\n");
    _file0 = TFile::Open("output/run667.root");
    NFit = 5;
  }

  Int_t binmax;
  Double_t x;
  TCanvas * c4= new TCanvas("CaloPed","CaloPed",800,600);
  c4->Divide(Nrow,Ncol); 
  for(int kk=0;kk<NCalo;kk++){
    c4->cd(25-kk);
    sprintf(hisname,Form("hPedCalo%d",kk));
    TH1D* H1 = (TH1D*)_file0->Get(hisname);
    H1->SetFillColor(kRed); H1->SetLineColor(kBlack);
    H1->Draw();
    binmax = H1->GetMaximumBin();
    x   = H1->GetXaxis()->GetBinCenter(binmax);
    cout<<" Ped "<<kk<<" = "<<x<<endl;
    hPedHis->Fill(x);
    //    c4->Update();
  }
  TCanvas * c5= new TCanvas("QCh","QCh",800,600);
  c5->Divide(Nrow,Ncol); 
  for(int kk=0;kk<NCalo;kk++){
    c5->cd(25-kk);
    gPad->SetLogy();
    sprintf(hisname,Form("hQCh%d",kk));

    TH1D* H1 = (TH1D*)_file0->Get(hisname);
    H1->SetFillColor(kRed); H1->SetLineColor(kBlack);
    if(kk != 12) H1->GetXaxis()->SetRangeUser(0.,10000.);
    H1->Draw();
    //    c5->Update();
  }
  
  TCanvas * c3= new TCanvas("QChPed","QChPed",800,600);
  c3->Divide(Nrow,Ncol); 
  for(int kk=0;kk<NCalo;kk++){
    c3->cd(25-kk);
    gPad->SetLogy();
    sprintf(hisname,Form("hQPedCalo%d",kk));
    TH1D* H1 = (TH1D*)_file0->Get(hisname);
    H1->SetFillColor(kRed);
    H1->SetLineColor(kBlack);
    H1->Draw();
    binmax = H1->GetMaximumBin();
    x   = H1->GetXaxis()->GetBinCenter(binmax);
    cout<<" QPed "<<kk<<" = "<<x<<endl;
    binmax = H1->GetMaximumBin();
    x   = H1->GetXaxis()->GetBinCenter(binmax);
    cout<<" Ped "<<kk<<" = "<<x<<endl;
    hQPedHis2D->Fill(kk,x);    
    //    c5->Update();
  }
  TCanvas * c55= new TCanvas("PedHis","PedHis",800,600);
  hQPedHis2D->SetMarkerStyle(21);
  hQPedHis2D->Draw("");

//    if(hQCh!=0){
//      hQCh[kk]->SetLineColor(kBlack);
//      hQCh[kk]->SetFillColor(kRed);
//      hQCh[kk]->Draw();
//    }
//    c5->Update();
//  }
//  
  TCanvas * c6= new TCanvas("QTot","QTot",800,600);
  TH1D* hQTotZS = (TH1D*)_file0->Get("hQTot");
  gPad  -> SetLogy();
  hQTotZS->Rebin(10);
  hQTotZS->SetLineColor(kBlack);
  hQTotZS->SetFillColor(kRed);
  hQTotZS->Draw();
  
  if(E==450.){
    g1    = new TF1("g1","gaus",5000,9000);
    g2    = new TF1("g2","gaus",13000,16000);
    g3    = new TF1("g3","gaus",19000,23000);
    g4    = new TF1("g4","gaus",24000,32000);
    total = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)",1000,30000);
  }
  if(E==250.){
    g1    = new TF1("g1","gaus",2500,5000);
    g2    = new TF1("g2","gaus",7000,9000);
    g3    = new TF1("g3","gaus",10500,13500);
    g4    = new TF1("g4","gaus",14500,17500);
    //    total = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)",1000,20000);
//    if(NGaus==5) g5    = new TF1("g5","gaus",17500,22000);
//    if(NGaus==5) 
    g5    = new TF1("g5","gaus",17500,21000);
    total = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)",1000,25000);
  }

  if(E==100.){
    g1    = new TF1("g1","gaus",1200,2000);
    g2    = new TF1("g2","gaus",3000,3600);
    g3    = new TF1("g3","gaus",4600,5400);
    g4    = new TF1("g4","gaus",6200,7000);
    total = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)",1000,20000);
    if(NGaus==5) g5    = new TF1("g5","gaus",7200,9000);
    if(NGaus==5) total = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)",1000,25000);
  }
  
  total->SetLineColor(2);
  hQTotZS->Fit(g1,"R");
  hQTotZS->Fit(g2,"R+");
  hQTotZS->Fit(g3,"R+");
  hQTotZS->Fit(g4,"R+");
  if(NGaus==5) hQTotZS->Fit(g5,"R+");
  //hQTotZS->Fit(g5,"R+");

  g1->GetParameters(&par[0]);
  g2->GetParameters(&par[3]);
  g3->GetParameters(&par[6]);
  g4->GetParameters(&par[9]);
  if(NGaus==5) g5->GetParameters(&par[12]);

  total->SetParameters(par);
  total->SetLineColor(kBlue);
  hQTotZS -> Fit(total,"RE+");
  hQTotZS -> GetXaxis()->SetTitle("Charge (pC)");

  for(int ig=0;ig<NGaus;ig++){
   Mean[ig] =total->GetParameter(ig*3+1);
   EMean[ig]=total->GetParError(ig*3+1);

   RMS[ig] =total->GetParameter(ig*3+2);
   RMSE[ig]=total->GetParError(ig*3+2);
  }
  total->SetLineColor(kBlue);
  hQTotZS->Draw();
 
  for(Int_t kk=0;kk<NGaus;kk++) {
    ENE[kk]    = E*(kk+1);///1000.
    ENE_E[kk]  = E*(kk+1)*0.01;///1000.
    RESO[kk]   = RMS[kk]/Mean[kk];

    RESO_UN[kk] = sqrt(RMS[kk]*RMS[kk]-Mean[kk]*0.01/sqrt(kk+1)*Mean[kk]*0.01/sqrt(kk+1))/Mean[kk];
    //    if(E==250) RESO_UN[kk]= sqrt(RMS[kk]*RMS[kk]-Mean[kk]*0.024/sqrt(kk+1)*Mean[kk]*0.024/sqrt(kk+1))/Mean[kk]; //superB like
    //    if(E==450) RESO_UN[kk]= sqrt(RMS[kk]*RMS[kk]-Mean[kk]*0.011/sqrt(kk+1)*Mean[kk]*0.011/sqrt(kk+1))/Mean[kk]; //superB like
    
    ERESO[kk]  = RMSE[kk]/Mean[kk];
    cout<<"Unfold "<<Mean[kk]<<" "<<kk<<" "<<Mean[kk]*0.01/sqrt(kk+1)<<endl;
  }
  
  for(Int_t ll=0;ll<3*NGaus;ll++) cout<<"Parametri " <<par[ll]<< " errors "<<epar[ll]<<endl;

  for(Int_t ll=0;ll<NFit;ll++) cout<<"ENE "<<ENE[ll]<<" "<<Mean[ll]<<" "<<EMean[ll]<<" RESO "<<RESO[ll]<<" "<<ERESO[ll]<<" RESO UN "<<RESO_UN[ll]<<endl;
  TGraphErrors * gCaloLin    = new TGraphErrors(NFit,ENE,Mean,ENE_E,EMean);

//  Double_t Mean450[2]={7507.4,14777.};
//  Double_t RES450[2]={0.0329,0.0243};
  Double_t ENE450[4]={450.,900.,1350.,1800.};
  //  Double_t Mean450[4]={7503.4,14761.3,20934.,26384};
  //  Double_t RES450[4]={0.03116,0.02281,0.02227,0.023043};

  Double_t Mean450[4]  = {7275.4,14293.3,20218.,25404.};
  Double_t RES450[4]   = {0.03348,0.02475,0.023444,0.023526};
  Double_t RES450Un[4] = {0.031812,0.02263,0.02120,0.02133};
  for(Int_t kk=0;kk<4;kk++) {
    RES450Un[kk]= sqrt(RES450[kk]*Mean450[kk]*RES450[kk]*Mean450[kk]-Mean450[kk]*0.011/sqrt(kk+1)*Mean450[kk]*0.011/sqrt(kk+1))/Mean450[kk];// superB
    //    RES450Un[kk]= sqrt(RES450[kk]*Mean450[kk]*RES450[kk]*Mean450[kk]-Mean450[kk]*0.01/sqrt(kk+1)*Mean450[kk]*0.01/sqrt(kk+1))/Mean450[kk];
    cout<<"res 450 Unfold "<<Mean450[kk]<<" "<<RES450Un[kk]<<endl; 
  }
  TGraphErrors * gCaloLin450   = new TGraphErrors(4,ENE450,Mean450,ENE_E,EMean);
  TGraphErrors * gCaloRES450   = new TGraphErrors(4,ENE450,RES450);// not used in fits
  TGraphErrors * gCaloRES450Un = new TGraphErrors(4,ENE450,RES450Un);//not used in fits
  
  TCanvas * c7= new TCanvas("Lin","Lin",800,600); c7->SetGrid();
  gCaloLin->SetMarkerStyle(21);
  gCaloLin->SetMarkerColor(kBlue);
  gCaloLin->Draw("AP");
  
  if(Compare==1){
    gCaloLin450->SetMarkerStyle(21);
    gCaloLin450->SetMarkerColor(kRed);
    gCaloLin450->Draw("Psame");
  }

  //  gCaloLin->Fit("pol1","E");
  if(E==250.) TF1 *func = new TF1("fLin",Lin2,200.,1300.,2);
  if(E==450.) TF1 *func = new TF1("fLin",Lin2,200.,1300.,2);
  if(Compare==1){
    Int_t npo=gCaloLin->GetN();
    gCaloLin->SetPoint(npo,ENE450[0],Mean450[0]);
    gCaloLin->SetPointError(npo,450.*0.01,5.);
    npo=gCaloLin->GetN();
    gCaloLin->SetPoint(npo,ENE450[1],Mean450[1]);
    gCaloLin->SetPointError(npo,900.*0.01,5.);
    gCaloLin->Draw("Psame");
  }
  gCaloLin->Draw("AP");
  gCaloLin->Fit("fLin","ER+");
  gCaloLin->GetXaxis()->SetTitle("Energy (MeV)");
  gCaloLin->SetMinimum(1.);
  gCaloLin->GetYaxis()->SetTitle("Charge (pC)");

  if(Compare==1){
    gCaloLin450->SetMarkerStyle(21);
    gCaloLin450->SetMarkerColor(kRed);
    gCaloLin450->Draw("Psame");
  }
  
  TF1 *funzione = new TF1("fLinear",Lin2,1000.,1800.,2);
  funzione->SetParameters(16.02,-56.846);
  funzione->SetLineStyle(2);
  funzione->Draw("same");

  gCaloLin->GetXaxis()->SetLimits(0,2000.);
  gCaloLin->GetYaxis()->SetRangeUser(0.,35000.);

  for(Int_t ig=0;ig<NFit;ig++) {
    MRatio[ig]  = Mean[ig]/fLin->Eval(E*(ig+1));
    MRatioE[ig] = EMean[ig]/fLin->Eval(E*(ig+1));
    ENEFit[ig]=fLin->GetX(Mean[ig]);
    cout<<"Ratio "<<fLin->Eval(E*(ig+1))<<" "<<MRatio[ig]<<" "<<E*(ig+1)<<" "<<ENEFit[ig]<<endl;
  }
  TGraphErrors * gCaloLinRat = new TGraphErrors(NFit,ENE,MRatio,ENE_E,MRatioE);
  //Ratio of the linear behavior
  TCanvas * c71= new TCanvas("LinRat","LinRat",800,600); c71->SetGrid();
  gCaloLinRat->SetMarkerStyle(21);
  gCaloLinRat->SetMarkerColor(kBlue);
  gCaloLinRat->SetMinimum(0.9);
  gCaloLinRat->SetMaximum(1.05);
  gCaloLinRat->GetXaxis()->SetTitle("Energy (MeV)");
  gCaloLinRat->GetYaxis()->SetTitle("E/F(E)");
  gCaloLinRat->Draw("AP");

  //
  //STARTING RESOLUTION STUDY
  //
  TGraphErrors * gCaloRes = new TGraphErrors(NFit,ENEFit,RESO,ENE_E,ERESO);
  TCanvas * c8= new TCanvas("Res","Res",800,600); c8->SetGrid();
  gCaloRes->SetMarkerStyle(21);
  gCaloRes->SetMinimum(0.015);
  gCaloRes->SetMaximum(0.05);
  gCaloRes->SetMarkerColor(kBlue);

  if(Compare==1){
    Int_t npo=gCaloRes->GetN();
    gCaloRes->SetPoint(npo,450.,RES450[0]);
    gCaloRes->SetPointError(npo,450.*0.01,5E-4);
    npo=gCaloRes->GetN();
    gCaloRes->SetPoint(npo,900.,RES450[1]);
    gCaloRes->SetPointError(npo,900.*0.01,5E-4);
    gCaloRes->Draw("Psame");
  }
  gCaloRes->Draw("AP");
  if(Compare==1){
    gCaloRES450->SetMarkerStyle(21);
    gCaloRES450->SetMarkerColor(kRed);
    gCaloRES450->Draw("Psame");
  }

  gCaloRes->GetYaxis()->SetTitle("#sigma(E)/E");
  gCaloRes->GetXaxis()->SetTitle("Energy (MeV)");
  gCaloRes->GetXaxis()->SetRangeUser(150.,1100.);
  cout<<"N points "<<gCaloRes->GetN()<<endl;
  
  TF1 *func = new TF1("fit",SigmaTest,230.,1050.,3);
  func->SetParNames("a","b","c");
  func->SetParLimits(2,0,1); // set c>0 and c<1
  gCaloRes->Fit("fit","ER+");
  
  //Unfolded using 1% BTF beam resolution
  //  TCanvas * c9= new TCanvas("ResUn","ResUn",800,600); c9->SetGrid();

  TGraphErrors * gCaloResUn = new TGraphErrors(NFit,ENEFit,RESO_UN,ENE_E,ERESO);
  gCaloResUn->SetMarkerStyle(22);
  gCaloResUn->SetMarkerColor(kBlue);
  gCaloResUn->SetMinimum(0.015);
  gCaloResUn->SetMaximum(0.05);
  gCaloResUn->Draw("Psame");
  gCaloResUn->GetYaxis()->SetTitle("#sigma(E)/E");
  gCaloResUn->GetXaxis()->SetTitle("Energy (MeV)");
  cout<<"N pints "<<gCaloRes->GetN()<<endl;

  if(Compare==1){
    Int_t npo=gCaloResUn->GetN();
    gCaloResUn->SetPoint(npo,450.,RES450Un[0]);
    gCaloResUn->SetPointError(npo,450.*0.01,5E-4);
    npo=gCaloResUn->GetN();
    gCaloResUn->SetPoint(npo,900.,RES450Un[1]);
    gCaloResUn->SetPointError(npo,900.*0.01,5E-4);
    gCaloResUn->Draw("Psame");
  }
  
  if(Compare==1){
    gCaloRES450Un->SetMarkerStyle(22);
    gCaloRES450Un->SetMarkerColor(kRed);
    gCaloRES450Un->Draw("Psame");
  }
  TF1 *func = new TF1("fit",SigmaTest,230.,1050.,3);
  func->SetParNames("a","b","c");
  func->SetParLimits(2,0,1); // set c>0 and c<1
  gCaloResUn->Fit("fit","ER+");
}

