#ifndef _Analyse_hh_
#define _Analyse_hh_ 0

#include"exec_options.hh"
#include"Universe.hh"

#include<string>
#include<map>
#include<unordered_map>


#include <TSpectrum.h>

#include <TRawEvent.hh>


#include"Histos.hh"
#include"VPMTChannel.hh"
#include"TriggerChannel.hh"

#include"SiPM.hh"
#include"V1742.hh"





class Analyse{
  public:
  private:
    //Histos       fHists;
    unsigned int fNEvtToProcess;
    unsigned int fNEvtProcessed;
    int          fRunNumber;
  public:
    Analyse():
      //fHists(ExecutableOptions::GetInstance().GetOutputRootFile()),
      fNEvtToProcess(-1),
      fNEvtProcessed(0),
      fRunNumber(-1)
  {
    }
    ~Analyse(){}
    void SetNEvtToProcess(unsigned int i){fNEvtToProcess=i;}
    void Process(std::string infile);
    void Finalize();

    SiPM& PVetoMap(unsigned int ch);
    SiPM& HVetoMap(unsigned int ch);
    SiPM& EVetoMap(unsigned int ch);
    //SiPM& SACMap(unsigned int ch);

  private:
    void HWInit();

    void FitCellPedestals();

    void Fill();
    void AnalyseAndFill(){
      Fill();
      //FillPhEDistr();
      //FillGraphTrends();
      //FillTimes();
      //FillHistos();
      FillOscCumulatives();
      //MakeFFT();
    }
    //void PrepareChannelsForAnal();
    //void FillHistos();
    //void FillGraphTrends();
    void FillOscCumulatives();
    //void FillPhEDistr();
    //void FillTimes();
    //void MakeFFT();

    //std::map<Universe::eROCh,VPMTChannel   *> fSignalChannels;
    //std::map<unsigned char,TriggerChannel*> fTriggerChannels;






};

#endif
