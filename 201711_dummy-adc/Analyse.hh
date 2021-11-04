#ifndef _Analyse_hh_
#define _Analyse_hh_ 0

#include<string>
#include<map>
#include<unordered_map>
#include"Histos.hh"
#include"VPMTChannel.hh"
#include"TriggerChannel.hh"
#include"Universe.hh"

extern int gBoardID;

class Analyse{
  private:
    Histos       fHists;
    unsigned int fNEvtToProcess;
    unsigned int fNEvtProcessed;
    int          fRunNumber;
  public:
    Analyse(const std::string& ofn):
      fHists(ofn),
      fNEvtToProcess(-1),
      fNEvtProcessed(0),
      fRunNumber(-1)
  {}
    ~Analyse(){}
    void SetNEvtToProcess(unsigned int i){fNEvtToProcess=i;}
    void Process(std::string infile);
    void Finalize();
  private:
    void HWInit();
    void HWDestr();
    void DummyChannelAnalyse();

    void AnalyseAndFill(){
      FillHistos();
      FillOscCumulatives();
      //MakeFFT();
    }
    void FillHistos();
    void FillOscCumulatives();
    void MakeFFT();

    std::map<int,VSamplingChannel  *> fSignalChannels;
    std::map<unsigned char,VSamplingChannel*> fTriggerChannels;
};


#endif