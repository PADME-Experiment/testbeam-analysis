#ifndef _Universe_hh_
#define _Universe_hh_ 0

#include"exec_options.hh"
//#include"VHistos.hh"
#include"Histos.hh"
#include"Analyse.hh"
#include"SiPM.hh"
#include"V1742.hh"


#include"utlMessageBus.hh"

#include<TH2F.h>
#include<TH1F.h>
#include<TH2F.h>
#include<TFile.h>


#include<sstream>
#include<string>
#include<vector>
#include<map>


struct SubDetector{
  std::string fDetName;
  void push_back(SiPM*s){fChan.push_back(s);}
  void CreateHistos(Histos& hist);
  void clear(){fChan.clear();}
  SubDetector():
    fIsHistDone(false)
  {
    //CreateHistos();
  }
  virtual ~SubDetector(){
    //DeleteHistos();
  }
  SiPM& GetChan(int ch){return *fChan[ch];}


  void Analyse();


  private:
  std::vector<SiPM*> fChan;
  bool fIsHistDone;



  std::vector<TH2F*> hist2f_TimeDiffMaxValue           ;
  std::vector<TH2F*> hist2f_TimeDiffHalfMaxValue       ;
  std::vector<TH2F*> hist2f_TimeDiff02MaxValue         ;
  std::vector<TH2F*> hist2f_TimeDiff01MaxValue         ;
  std::vector<TH2F*> hist2f_TimeDiff2080LeadTrailCros  ;
  std::vector<TH2F*> hist2f_TimeDiff2080LeadZeroCros   ;
  std::vector<TH2F*> hist2f_TimeDiff2080Lead50         ;
  std::vector<TH2F*> hist2f_TimeDiffMeanTime           ;
  std::vector<TH2F*> hist2f_TimeDiffMeanTime2          ;
  std::vector<TH2F*> hist2f_TimeDiffMeanTimeAbs        ;
  std::vector<TH2F*> hist2f_TimeDiffMeanTimeFFT        ;
  std::vector<TH2F*> hist2f_TimeDiffMeanTimeFFTAbs     ;
  std::vector<TH2F*> hist2f_TimeDiffIntegral           ;
  std::vector<TH1F*> hist1f_TimeTSpectrum              ;


};


struct EVeto: SubDetector{
  EVeto() {
    fDetName="EVeto";
  }
  virtual ~EVeto(){}
};

struct PVeto: SubDetector{
  PVeto() {
    fDetName="PVeto";
  }
  virtual ~PVeto(){}
};

struct HVeto: SubDetector{
  HVeto() {
    fDetName="HVeto";
  }
  virtual ~HVeto(){}
};

struct SAC: SubDetector{
  SAC() {
    fDetName="SAC";
  }
  virtual ~SAC(){}
};

struct Universe{

  static Universe& GetInstance();
  ~Universe(){}
  EVeto fEVeto;
  PVeto fPVeto;
  HVeto fHVeto;
  SAC fSAC;
  Histos fHist;
  std::map<unsigned int, V1742> fADCBoards;
  std::map<unsigned int, double[32][1024][6]> fADCCellCallDat;
  //VHistos fHistos;
  void Map();
  void Reset(){
    //fEVeto.clear();
    //fPVeto.clear();
    //fHVeto.clear();
  }
  private:
  void MapPVeto();
  void MapEVeto();
  void MapHEPVeto();
  void MapSAC();
  bool fIsMappingDone;
  Universe();
  Universe(const Universe&) = delete;
  void operator=(const Universe&) = delete;

};

#endif
