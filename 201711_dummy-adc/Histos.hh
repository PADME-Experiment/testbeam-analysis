#ifndef _Histos_hh_
#define _Histos_hh_ 0

#include<sstream>
#include<string>
#include<map>

#include"TH1F.h"
#include"TH2F.h"
#include"TGraph.h"
#include"TFile.h"
#include"TDirectory.h"
#include"TTree.h"

class Histos{
  private:
    static const int fNChanMax=32;
    static const int fNTrigMax=4;
    static const int fNBoards=1;
    std::string fOutRootFileName;

  public:
   TH1F* hist1f_TrigSigPedMean;
   TH1F* hist1f_TrigSigPedSig ;
   TH1F* hist1f_ChanSigPedMean;
   TH1F* hist1f_ChanSigPedSig ;
    TH2F* hist2f_ChanOscCum           [fNBoards][fNChanMax];
    TH2F* hist2f_ChanOscCumT0         [fNBoards][fNChanMax];
    TH1F* hist1f_ChanSigmaSampBySamp  [fNBoards][fNChanMax];
    TH1F* hist1f_ChanSigmaSampBySampT0[fNBoards][fNChanMax];
    TH1F* hist1f_ChanAmplFluctSampBySamp  [fNBoards][fNChanMax];
    TH1F* hist1f_ChanAmplFluctSampBySampT0[fNBoards][fNChanMax];
    TH1F* hist1f_ChanPedestalsMean    [fNBoards][fNChanMax];
    TH1F* hist1f_ChanPedestalsRMS     [fNBoards][fNChanMax];
    TH1F* hist1f_ChanSlopeFitA        [fNBoards][fNChanMax];
    TH1F* hist1f_ChanSlopeFitB        [fNBoards][fNChanMax];
    TH1F* hist1f_ChanSlopeFitRMS      [fNBoards][fNChanMax];
    //TH2F* hist2f_ChanOscCum2d         [fNBoards][fNChanMax];
    //TH1F* hist1f_ChanMaxAmplFluct     [fNBoards][fNChanMax];
    //TH2F* hist2f_ChanSampleBySample   [fNBoards][fNChanMax];

    TH2F* hist2f_TrigOscCum                [fNBoards][fNTrigMax];
    TH2F* hist2f_TrigOscCumT0              [fNBoards][fNTrigMax];
    TH1F* hist1f_TrigSigmaSampBySamp       [fNBoards][fNTrigMax];
    TH1F* hist1f_TrigSigmaSampBySampT0     [fNBoards][fNTrigMax];
    TH1F* hist1f_TrigAmplFluctSampBySamp   [fNBoards][fNTrigMax];
    TH1F* hist1f_TrigAmplFluctSampBySampT0 [fNBoards][fNTrigMax];
    TH1F* hist1f_TrigPedestalsMean         [fNBoards][fNTrigMax];
    TH1F* hist1f_TrigPedestalsRMS          [fNBoards][fNTrigMax];
    TH1F* hist1f_TrigSlopeFitA             [fNBoards][fNTrigMax];
    TH1F* hist1f_TrigSlopeFitB             [fNBoards][fNTrigMax];
    TH1F* hist1f_TrigSlopeFitRMS           [fNBoards][fNTrigMax];
    //TH2F* hist2f_TrigOscCum2d              [fNBoards][fNTrigMax];
    //TH1F* hist1f_TrigMaxAmplFluct          [fNBoards][fNTrigMax];
    //TH2F* hist2f_TrigSampleBySample        [fNBoards][fNTrigMax];












  private:
    std::multimap<std::string,TObject*>fAllObj;

  public:
    Histos(const std::string& fn){
      fOutRootFileName = fn;
      CreateHistos();
    }

  public:
    ~Histos(){
      WriteHistos();
      DeleteHistos();
    }

    void CreateHistos();
    void AddToFile(const std::string& dirname, TObject* obj){fAllObj.emplace(dirname,obj);}
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
