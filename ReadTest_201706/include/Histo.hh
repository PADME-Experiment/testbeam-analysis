#ifndef Histo_h
#define Histo_h

#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TList.h"
#include <TTree.h>

#include "TEveManager.h"
#include "TEveBrowser.h"
#include "TGFrame.h"
#include "TGTab.h"
#include<iostream>
//#include <vector>


class Histo {
  TRootBrowser * GetMainWindow() { return fMainWindow; }
  TCanvas * AddCanvasTab(TString);
  TCanvas * AddCanvas(TString);

public :
  //  Histo();
  ~Histo();
  static Histo* GetInstance();
  //  NTEvent  myEvt;

  void WriteHisto();
  void InitMonitor();

  void DrawChannels(Int_t,Int_t);

  void DrawCalo(Int_t,Int_t);
  void DrawTarg(Int_t,Int_t);

  TH1D* Get1DHisto(const char* name){return (TH1D*)hListCal->FindObject(name);}; 
  TH2D* Get2DHisto(const char* name){return (TH2D*)hListCal->FindObject(name);};
  TGraphErrors* GetGraph(const char* name){return (TGraphErrors*)hListCal->FindObject(name);};
  TFile * GetFile(){return (TFile *)fileOut;};

  Int_t Fill1D(const char* ,Double_t );
  Int_t Fill2D(const char* ,Double_t ,Double_t);
  Int_t FillGraph(const char* ,Int_t, Int_t ,Double_t *,Double_t *);
  Int_t KillGraph();

private:
  void InitHisto();
private:
  TFile *fileOut;
  TList* hListCal;  
  TGraphErrors* gCaloRaw[32];
  TGraphErrors* gCaloTrigRaw[4];

  TGraphErrors* gCaloReco[32];
  TGraphErrors* gCaloDiff[32];
  TGraphErrors* gCaloTrigReco[4];

  TH1D ** hPedCalo;
  TH1D ** hPedMean;
  TH1D ** hQPedCalo;
  TH1D ** hPedTarg;
  TH1D ** hRMS100;
  TH1D ** hQCh;
  TH1D ** hQVertCh;
  TH1D ** hQVert2Ch;
  TH1D ** hQAllVertCh;
  TH1D ** hQ3maxCh;
  TH1D ** hTCh;
  TH1D ** hTTrig;
  TProfile **hQPedCaloProf;

  //  TH1D * hQCal;

  TH1D * hNCry;
  TH1D * hNTCry;
  TH2D * hNCol;
  TH1D * hQTotZS;
  TH1D * hQTot;
  TH1D * hQTotCal;
  TH1D * hQTotWP;
  TH1D * hQTotNoCut;
  TH1D * hQTot2cry;

  TH2D * hECALPos;
  TH2D * hECALPosZS;
  TH2D * hECALPosZS1e;
  TH2D ** hSigAmplitudes;

  TH2D * hMeanvsNevt;
  TH2D * hRMSvsNevt;
  TH2D * hQtotVsNevt;

  TH1D * hTT0_TT1;
  TH1D * hTT2_TT3;
  TH1D * hTevRes;

  TH1D ** hPedRMSCalo;
  TH1D ** hPedRMSTarg;

  static Histo* fInstance;
  
public:
  Int_t NCalo;
  Int_t NTrigCalo;
  //  NTEvent  myEvt;
  TTree *ntupl;

protected:
  Histo();

  TRootBrowser * fMainWindow;
  TGMainFrame *  fMainTabFrame;
  TGTab *        fMainTab;
  //  vector<TCanvas*> fCanvases;  
};
#endif
