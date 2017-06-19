#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TChain.h"


void DrawChain(/*TChain* Chain1*/){


  TChain* Chain1 = new TChain("NTU");
  Chain1->Add("/home/daq/DigiDaq/TestBeamOld/ntu815.root");
  TChain* Chain2 = new TChain("NTU");
  Chain2->Add("/home/daq/DigiDaq/TestBeamOld/ntu816.root");

  TCanvas* C1 = new TCanvas("C1","C1",800,800);
  C1->SetLogy();


  TH1D* Hist1 = new TH1D("Qspectrum1","Qspectrum1",3100,-400,12000);
  TH1D* Hist2 = new TH1D("Qspectrum2","Qspectrum2",3100,-400,12000);

  Chain1->Draw("QtotCal","IsPositron&&(!IsSaturated)&&sqrt((Xcluster+1)**2+(Ycluster+1)**2)<0.7","goff");

  double* Var1 = Chain1->GetV1();
  int nev1 = Chain1->GetSelectedRows();

  for(int ii=0;ii<nev1;ii++){
    Hist1->Fill(Var1[ii]);
  }


  Chain2->Draw("QtotCal","IsPositron&&(!IsSaturated)&&sqrt((Xcluster+1)**2+(Ycluster+1)**2)<0.7","goff");

  double* Var2 = Chain2->GetV1();
  int nev2 = Chain2->GetSelectedRows();

  for(int ii=0;ii<nev2;ii++){
    Hist2->Fill(Var2[ii]);
  }


  Hist1->Draw();
  Hist1->GetXaxis()->SetTitle("Charge [pC]");
  Hist1->Fit("gaus","","",1600,2250);

  Hist2->Draw("SAME");
  Hist2->SetLineColor(kRed);
  Hist2->Fit("gaus","","",1600,2250);



}
