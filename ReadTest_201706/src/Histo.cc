#define Histo_cxx
#include "Histo.hh"
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TList.h>
#include <TFile.h>
#include <iostream>
#include "cstdlib"

using namespace std;
Histo* Histo::fInstance = 0;
Histo* Histo::GetInstance()
{
  //  ntupl=0;
  if ( fInstance == 0 ) { fInstance = new Histo(); }
  return fInstance;
}

void Histo::InitHisto()
{
  Int_t NCalo=32;
  //  NTrigCalo=2;
  printf("Initializing  Histograms NCalo\n");
  hListCal    = new TList();      // list of Ecal histograms to store

  //Histogram arrays for different data Type 
  hPedCalo = new TH1D*[32];
  hPedMean = new TH1D*[32];
  hQPedCalo= new TH1D*[32];
  hQCh     = new TH1D*[32];
  hQVertCh = new TH1D*[32];
  hQVert2Ch= new TH1D*[32];
  hQAllVertCh = new TH1D*[32];
  hQ3maxCh = new TH1D*[32];
  hTCh     = new TH1D*[32];
  hTTrig   = new TH1D*[32];
  hPedTarg = new TH1D*[32];
  hRMS100  = new TH1D*[32];
  //  hQPedCaloProf = new TProfile*[32];

  hNCry    = new TH1D("hNCry","hNCry",26,-0.5,25.5);
  hNCol    = new TH2D("hNCol","hNCol",4,-0.5,3.5,4,-0.5,3.5);
  hNTCry   = new TH1D("hNTCry","hNTCry",26,-0.5,25.5);
  hTT0_TT1 = new TH1D("hTT0_TT1","hTT0_TT1",20,-10,10);
  hTT2_TT3 = new TH1D("hTT2_TT3","hTT2_TT3",20,-10,10);

  hQTotNoCut = new TH1D("hQTotNoCut","hQTotNoCut",3020,-200.,30000.);
  hQTot2cry  = new TH1D("hQTot2cry","hQTot2cry",3020,-200.,30000.);

  hQTot    = new TH1D("hQTot","hQTot",3020,-200.,30000.);
  hQTotCal = new TH1D("hQTotCal","hQTotCal",3020,-200.,30000.);
  hQTotZS  = new TH1D("hQTotZS","hQTotZS",3020,-200.,30000.);
  hQTotWP  = new TH1D("hQTotWP","hQTotWP",3020,-200.,30000.);
  hTevRes  = new TH1D("hTevRes","hTevRes",400,-200.,200.);
  hQtotVsNevt = new TH2D("hQtotVsNevt","hQtotVsNevt",40000,0.,40000.,250,0,10000.);

  hECALPos = new TH2D("hECALPos","hECALPos",400,-5.,5.,400,-5.,5.);
  hECALPosZS = new TH2D("hECALPosZS","hECALPosZS",400,-5.,5.,400,-5.,5.);
  hECALPosZS1e = new TH2D("hECALPosZS1e","hECALPosZS1e",400,-5.,5.,400,-5.,5.);
  hSigAmplitudes = new TH2D*[32];
  hListCal->Add(hNCry);
  hListCal->Add(hNTCry);
  hListCal->Add(hNCol);
  hListCal->Add(hTT0_TT1);
  hListCal->Add(hTT2_TT3);
  hListCal->Add(hTevRes);
  hListCal->Add(hECALPos);
  hListCal->Add(hECALPosZS);
  hListCal->Add(hECALPosZS1e);
  hListCal->Add(hQTot);
  hListCal->Add(hQTotCal);
  hListCal->Add(hQTotZS);
  hListCal->Add(hQTotNoCut);
  hListCal->Add(hQTot2cry);
  hListCal->Add(hQTotWP);
  hListCal->Add(hQtotVsNevt);

  for(int ll=0;ll<4;ll++){
    hTTrig[ll]= new TH1D(Form("hTTrig%d",ll),Form("hTTrig%d",ll),400,-200.,200.);
    hListCal->Add(hTTrig[ll]);
  }
  for(int kk=0;kk<NCalo;kk++){
    //  hInvThEi[kk]    = new TH2D(Form("hInvThEi%d",kk),Form("hInvThEi%d",kk),300,0.,600.,60,0.,12.);
    hQCh[kk]     = new TH1D(Form("hQCh%d",kk),Form("hQCh%d",kk),5040,-200.,2000.);
    hQVertCh[kk] = new TH1D(Form("hQVertCh%d",kk),Form("hQVertCh%d",kk),1300,-200.,5000.);
    hQVert2Ch[kk]= new TH1D(Form("hQVert2Ch%d",kk),Form("hQVert2Ch%d",kk),1300,-200.,5000.);
    hQAllVertCh[kk] = new TH1D(Form("hQAllVertCh%d",kk),Form("hQAllVertCh%d",kk),1040,-200.,5000.);
    hQ3maxCh[kk] = new TH1D(Form("hQ3maxCh%d",kk),Form("hQ3maxCh%d",kk),1300,-200.,5000.);
    hTCh[kk]     = new TH1D(Form("hTCh%d",kk),Form("hTCh%d",kk),2000,0.,200.);
    hPedCalo[kk] = new TH1D(Form("hPedCalo%d",kk),Form("hPedCalo%d",kk),200,3700.,3800);
    hPedMean[kk] = new TH1D(Form("hPedMean%d",kk),Form("hPedMean%d",kk),1000,3740.,3840);
    hRMS100[kk] = new TH1D(Form("hRMS100%d",kk),Form("hRMS100%d",kk),110,-10.,100.);
    hQPedCalo[kk] = new TH1D(Form("hQPedCalo%d",kk),Form("hQPedCalo%d",kk),800,-50.,150);
    //    hQPedCaloProf[kk] = new TProfile("hQPedCaloProf","hQPedCaloProf",100,0,75000.,-300,300);
    //    hPedTarg[kk] = new TH1D(Form("hPedTarg%d",kk),Form("hPedTarg%d",kk),600,3600.,3900);
    hListCal->Add(hPedCalo[kk]);
    hListCal->Add(hPedMean[kk]);
    hListCal->Add(hQPedCalo[kk]);
    hListCal->Add(hRMS100[kk]);
    //    hListCal->Add(hQPedCaloProf[kk]);
    hListCal->Add(hQCh[kk]);
    hListCal->Add(hQVertCh[kk]);
    hListCal->Add(hQVert2Ch[kk]);
    hListCal->Add(hQAllVertCh[kk]);
    hListCal->Add(hQ3maxCh[kk]);
    hListCal->Add(hTCh[kk]);
    //    hListCal->Add(hPedTarg[kk]);


    hSigAmplitudes[kk] = new TH2D(Form("SigCh%d",kk),Form("SigCh%d",kk),1024,-0.5,1023.5,400,-0.5,399.5);
hListCal->Add(hSigAmplitudes[kk]);

  }
}

void Histo::InitMonitor(){
//  fMainWindow = MainWindow;
//  if(fMainWindow) fMainWindow->StartEmbedding(1,-1);
//  fMainTabFrame = new TGMainFrame(gClient->GetRoot(),10,10,kMainFrame | kVerticalFrame);
//  fMainTabFrame->SetName(Name);
//  fMainTabFrame->SetWindowName(Name);
//  fMainTab = new TGTab(fMainTabFrame,300,300);
//  fMainTab->SetName(Name);
//  //  fMainTab->Draw();
}

void Histo::WriteHisto()
{
  printf("Writing  general Histograms\n");
  fileOut->cd();
  hListCal->Write();
  //  hListComp->Write();
}

void Histo::DrawChannels(Int_t NTrig, Int_t NCalo)
{
  //  Int_t NCalo=25;
  Int_t Nrow=5;
  Int_t Ncol=5;
  printf("Drawing Channels histograms %d \n",NCalo);
  //  TCanvas * c1= new TCanvas("CaloRawMon","CaloRawMon",1040,780);

  //  c1->Divide(Nrow,Ncol); 
  //  for(int kk=0;kk<NCalo;kk++){
  //  if(gCaloRaw[kk]!=0 && kk==25) gCaloRaw[kk]->Draw("APL");
    //    //  for(int kk=8;kk<17;kk++){
    //    //    c1->cd(kk+1);
//    c1->cd(NCalo-kk);
//    if(gCaloRaw[kk]!=0 &&) gCaloRaw[kk]->Draw("APL");
//    //    gCaloDiff[kk]->SetLineColor(kRed);
//    //    if(gCaloDiff[kk]!=0) gCaloDiff[kk]->Draw("PLsame");
   
//  }
//  gCaloRaw[24]->Draw("APL");
//  c1->Update();
//  getchar();
  // c1->Update();
  Nrow=3;
  Ncol=3; 
  Int_t jj=0;
  TCanvas * c3= new TCanvas("CaloRecMon","CaloRecMon",1000,800);
  c3->Divide(Nrow,Ncol); 
  for(int kk=0;kk<NCalo;kk++){
    //    c3->cd(NCalo-kk);
    std::cout<<"plot "<<kk<<" "<<gCaloReco[kk]<<std::endl;
    if(gCaloReco[kk]!=0) {
      c3->cd(jj+1);
      gCaloReco[kk]->Draw("APL");
      jj++;
    }
  }
  c3->Update();
  //  getchar();
//
// TCanvas * c2=new TCanvas("TrigMon","TrigMon",800,600);
//  //  c2->Divide(1,NTrig); 
//  for(int kk=0;kk<NTrig;kk++){
//    //    c2->cd(kk+1);
//    if(kk==0){
//      gCaloTrigRaw[kk]->Draw("APL");
//    }else{
//      gCaloTrigRaw[kk]->Draw("PLsame");
////    }
//    gPad->Modified();
//    gCaloTrigRaw[kk]->SetMinimum(0.);
//    gCaloTrigRaw[kk]->SetMaximum(4096.);
//  for(int ll=0;ll<NCalo;ll++){
//    if(gCaloRaw[ll]!=0){
//      gCaloRaw[ll]->SetMarkerColor(ll);
//      gCaloRaw[ll]->Draw("PLsame");
//    }
//  }
//    c2->Update();
//  } 
}


void Histo::DrawCalo(Int_t NTrig, Int_t NCalo)
{
  printf("Drawing Calorimeter histograms\n");
  Int_t Nrow=5;
  Int_t Ncol=5;

  TCanvas * c4= new TCanvas("CaloPed","CaloPed",800,600);
  c4->Divide(Nrow,Ncol); 
  for(int kk=0;kk<NCalo;kk++){
    c4->cd(25-kk);
    if(hPedCalo!=0) hPedCalo[kk]->Draw();
    c4->Update();
  }

  TCanvas * c5= new TCanvas("QCh","QCh",800,600);
  c5->Divide(Nrow,Ncol); 
  for(int kk=0;kk<NCalo;kk++){
    c5->cd(25-kk);
    gPad->SetLogy();
    if(hQCh!=0){
      hQCh[kk]->SetLineColor(kBlack);
      hQCh[kk]->SetFillColor(kRed);
      hQCh[kk]->Draw();
    }
    c5->Update();
  }

  TCanvas * c6= new TCanvas("QTot","QTot",800,600);
  c6->Divide(1,2);
  gPad->SetLogy();
  c6->cd(1);
  hQTot->SetLineColor(kBlack);
  hQTot->SetFillColor(kRed);
  hQTot->Draw();
  c6->cd(2);
  hECALPos->Draw("colz");
  c6->Update();

  TCanvas * c7= new TCanvas("QVertCh","QVertCh",800,600);
  c7->Divide(Nrow,Ncol); 
  for(int kk=0;kk<NCalo;kk++){
    c7->cd(25-kk);
    gPad->SetLogy();
    if(hQVertCh!=0){
      hQVertCh[kk]->SetLineColor(kBlack);
      hQVertCh[kk]->SetFillColor(kRed);
      hQVertCh[kk]->Draw();
    }
    c7->Update();
  }

  TCanvas * c8= new TCanvas("QVert2Ch","QVert2Ch",800,600);
  c8->Divide(Nrow,Ncol); 
  for(int kk=0;kk<NCalo;kk++){
    c8->cd(25-kk);
    gPad->SetLogy();
    if(hQVert2Ch!=0){
      hQVert2Ch[kk]->SetLineColor(kBlack);
      hQVert2Ch[kk]->SetFillColor(kRed);
      hQVert2Ch[kk]->Draw();
    }
    c8->Update();
  }

  TCanvas * c9= new TCanvas("QAllVertCh","QAllVertCh",800,600);
  c9->Divide(Nrow,Ncol); 
  for(int kk=0;kk<NCalo;kk++){
    c9->cd(25-kk);
    gPad->SetLogy();
    if(hQAllVertCh!=0){
      hQAllVertCh[kk]->SetLineColor(kBlack);
      hQAllVertCh[kk]->SetFillColor(kRed);
      hQAllVertCh[kk]->Draw();
    }
    c9->Update();
  }


  TCanvas * c10= new TCanvas("Q3maxCh","Q3maxCh",800,600);
  c10->Divide(Nrow,Ncol); 
  for(int kk=0;kk<NCalo;kk++){
    c10->cd(25-kk);
    gPad->SetLogy();
    if(hQ3maxCh!=0){
      hQ3maxCh[kk]->SetLineColor(kBlack);
      hQ3maxCh[kk]->SetFillColor(kRed);
      hQ3maxCh[kk]->Draw();
    }
    c10->Update();
  }


}

void Histo::DrawTarg(Int_t Ntrig, Int_t NCal)
{

}

Int_t Histo::Fill1D(const char* name,Double_t var)
{
  TH1D* histo=(TH1D*)hListCal->FindObject(name);
  histo->Fill(var);
  return 0;
}

Int_t Histo::Fill2D(const char* name,Double_t var,Double_t var1)
{
  TH2D* histo=(TH2D*)hListCal->FindObject(name);
  histo->Fill(var,var1);
  return 0;
}

Int_t Histo::FillGraph(const char* name,Int_t Nch, Int_t Nsam,Double_t *var,Double_t *var1)
{
  char gName[10];
  sprintf(gName,"Ch%d",Nch);
  if (strcmp(name,"Calo")==0) {
    if(Nch<32){
      gCaloRaw[Nch] = new TGraphErrors(Nsam,var,var1);
      gCaloRaw[Nch]->SetTitle(gName);
    }else{
      printf("Index out of range %d",Nch);
      return -1;
    }
  }

  if (strcmp(name,"CaloReco")==0) {
    if(Nch<32){
      gCaloReco[Nch] = new TGraphErrors(Nsam,var,var1);
      gCaloReco[Nch]->SetTitle(gName);
    }else{
      printf("Index out of range %d",Nch);
      return -1;
    }
  }

  if (strcmp(name,"Diff")==0) {
    if(Nch<32){
      gCaloDiff[Nch] = new TGraphErrors(Nsam,var,var1);
      gCaloDiff[Nch] ->SetTitle(gName);
    }else{
      printf("Index out of range %d",Nch);
      return -1;
    }
  }


  char gTrgName[10];
  sprintf(gTrgName,"Trg%d",Nch);
  if (strcmp(name,"CaloTrig")==0) {
    if(Nch<4){
      gCaloTrigRaw[Nch] = new TGraphErrors(Nsam,var,var1);
      gCaloTrigRaw[Nch]->SetTitle(gTrgName);
    }else{
      printf("Index out of range %d",Nch);
      return -1;
    }
  }
  return 0;
}


Int_t Histo::KillGraph(){
  for(int kk=0;kk<32;kk++){delete gCaloRaw[kk]; }
  for(int kk=0;kk<32;kk++){delete gCaloReco[kk];}
  for(int kk=0;kk<4;kk++){delete gCaloTrigRaw[kk];}
}


//Costruttore
//#ifdef Histo_cxx
Histo::Histo()
{
 
  fileOut  = new TFile("outCosmic.root", "RECREATE");
  //  printf("Calling Init histograms ");
  InitHisto();
}
//
Histo::~Histo()
{
  fileOut->Close();
//  printf("Closing Init histograms ");
}

