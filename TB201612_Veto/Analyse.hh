#ifndef _Analyse_hh_
#define _Analyse_hh_ 0

#include<string>
#include<map>
#include<unordered_map>
#include"Histos.hh"
#include"VPMTChannel.hh"
#include"TriggerChannel.hh"


class Analyse{
  public:
    enum class eROCh{
      eFirst=0,
      eX1=0,
      eX2,
      eX3,
      eX4,
      eX5,
      eX6,
      eX7,
      eX8,
      eY1,
      eY2,
      eY3,
      eY4,
      eY5,
      eY6,
      eY7,
      eY8,
      eH1,
      eH2,
      eH3,
      eH4,
      eH5,
      eH6,
      eH7,
      eH8,
      eCalo  ,
      eTerm  ,
      eAntena,
      eLast
    };
    enum class eDetCh{
      eFirst=0,
      eVTU, eVBU, eVTD, eVBD,
      eD1,eD2,eD3,eD4,eD5,eD6,eD7,eD8,
      eCalo,
      eLast,
      NC
    };
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
    void LinksNames();
    void HWInit();
    void HWDestr();

    void AnalyseAndFill(){
      PrepareChannelsForAnal();
      FillPhEDistr();
      FillTimes();
      //FillOscCumulatives();
    }
    void PrepareChannelsForAnal();
    void FillHistos();
    void FillOscCumulatives();
    void FillPhEDistr();
    void FillTimes();
    void MakeFFT();

    std::map<eROCh,VPMTChannel   *> fSignalChannels;
    std::map<unsigned char,TriggerChannel*> fTriggerChannels;
    std::map     <eROCh,eDetCh>  fLinkRO2DetCh;
    std::multimap<eDetCh,eROCh>  fLinkDet2ROCh;
    std::map<eROCh , std::string>fROChNames;
    std::map<eDetCh, std::string>fDetChNames;
};

#endif
