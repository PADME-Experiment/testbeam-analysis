#ifndef _Analyse_hh_
#define _Analyse_hh_ 0

#include<string>
#include<map>
#include<unordered_map>
#include"Histos.hh"
#include"VPMTChannel.hh"
#include"TriggerChannel.hh"
#include"Universe.hh"


class Analyse{
  public:
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

    void AnalyseAndFill(){
      PrepareChannelsForAnal();
      FillPhEDistr();
      FillTimes();
      FillHistos();
      FillOscCumulatives();
      //MakeFFT();
    }
    void PrepareChannelsForAnal();
    void FillHistos();
    void FillOscCumulatives();
    void FillPhEDistr();
    void FillTimes();
    void MakeFFT();

    std::map<Universe::eROCh,VPMTChannel   *> fSignalChannels;
    std::map<unsigned char,TriggerChannel*> fTriggerChannels;
};


#endif
