#ifndef _Histos_hh_
#define _Histos_hh_ 0

#include"a.hh"

#include<sstream>
#include<map>

#include"TH1F.h"
#include"TH2F.h"
#include"TGraph.h"
#include"TFile.h"
#include"TDirectory.h"
#include"TTree.h"

class Histos{
  private:
    std::string fOutRootFileName;
  public:
    TH1F*   hist1f_SqNoiseIntrSlope[gSqNoiseSlopes][gSqNoiseNoises];
    TH1F*   hist1f_SqNoiseIntrThres[gSqNoiseSlopes][gSqNoiseNoises];
    TH1F*   hist1f_SqNoiseDiffSlope[gSqNoiseSlopes][gSqNoiseNoises];
    TH1F*   hist1f_SqNoiseDiffThres[gSqNoiseSlopes][gSqNoiseNoises];
    TGraph* hist2f_SqNoiseOsc      [gSqNoiseSlopes][gSqNoiseNoises];

    TH2F* hist1f_SqNoiseIntrSlopeSummary;
    TH2F* hist1f_SqNoiseIntrThresSummary;
    TH2F* hist1f_SqNoiseDiffSlopeSummary;
    TH2F* hist1f_SqNoiseDiffThresSummary;

    TH1F*   hist1f_SineIntrThres[gNSines][gSqNoiseNoises];
    TH1F*   hist1f_SineDiffThres[gNSines][gSqNoiseNoises];
    TH1F*   hist1f_SineIntrSlope[gNSines][gSqNoiseNoises];
    TH1F*   hist1f_SineDiffSlope[gNSines][gSqNoiseNoises];
    TH1F*   hist1f_SineIntrFFTPhase[gNSines][gSqNoiseNoises];
    TH2F*   hist2f_SineDiffFFTPhase[gNSines][gSqNoiseNoises];
    TGraph* hist2f_SineOsc[gNSines][gSqNoiseNoises];



    TH1F* hist1f_TrigDiffSine;
    TH2F* hist2f_phy_dif;



  private:
    std::multimap<std::string,TObject*>fAllObj;

  public:
    Histos(const std::string& fn) {
      fOutRootFileName = fn;
      CreateHistos();
    }

    ~Histos(){
      WriteHistos();
      DeleteHistos();
    }

    void CreateHistos();
    void WriteHistos(){
      TFile* outRootFileP=new TFile(fOutRootFileName.c_str(),"recreate");
      TDirectory* fileDir=outRootFileP;
      std::stringstream chan_i_ss;
      fileDir->cd();
      std::string curdirname;
      for(auto obj_it=fAllObj.begin();obj_it!=fAllObj.end();++obj_it){
        if(curdirname!=obj_it->first){
          curdirname=obj_it->first;
          fileDir->mkdir(curdirname.c_str())->cd();
        }
        if(curdirname.size()==0)fileDir->cd();
        TH1*hist=dynamic_cast<TH1*>(obj_it->second);
        if(hist!=nullptr&&hist->GetEntries()==0)continue;
        obj_it->second->Write();
      }
      outRootFileP->Write();
      outRootFileP->Close();
      delete outRootFileP;
    }

    void DeleteHistos(){
      for(auto obj_it=fAllObj.begin();obj_it!=fAllObj.end();++obj_it){
        delete obj_it->second;
      }
    }
};
#endif
