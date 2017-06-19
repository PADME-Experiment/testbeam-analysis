



void superimpose(){

  TFile* f1 = new TFile("/home/daq/DigiDaq/TestBeamOld/figures/TOT_Q_run540_10pC.root");
  TFile* f2 = new TFile("/home/daq/DigiDaq/TestBeamOld/figures/TOT_Q_run540_central_10pC.root");


  TH1D* h1 = (TH1D*)f1->Get("Total Charge run 540");//->FindObject("hQTot");//->FindObject("Total Charge run 540");
  TH1D* h2 = (TH1D*)f2->Get("Total Charge run 540");


  TCanvas* Canv = new TCanvas("","",800,800);
  Canv->SetLogy();

  //h1->SetLineColor(kBlack);
  h1->Draw();
  //h2->SetLineColor(kBlue);
  h2->Draw("SAME");

}
