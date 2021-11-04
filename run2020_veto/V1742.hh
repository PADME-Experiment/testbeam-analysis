#ifndef _V1742_HH_
#define _V1742_HH_


#include"SiPM.hh"
#include"VPMTChannel.hh"
#include"TriggerChannel.hh"
#include"Histos.hh"

#include <TRawEvent.hh>

#include<TH1F.h>
#include<TH2F.h>


#include<map>
#include<vector>

typedef unsigned __int128 uint128_t;

struct lin_reg_sums_t{
  lin_reg_sums_t():
  n    (0),
  t    (0),
  t2   (0),
  t3   (0),
  t4   (0),
  t5   (0),
  t6   (0),
  t7   (0),
  t8   (0),
  t9   (0),
  t10  (0),
  Cp   (0),
  tCp  (0),
  t2Cp (0),
  t3Cp (0),
  t4Cp (0),
  t5Cp (0)
  {}
  uint16_t  n    ;
  uint64_t  t    ;
  uint64_t  t2   ;
  uint64_t  t3   ;
  uint128_t t4   ;
  uint128_t t5   ;
  uint128_t t6   ;
  uint128_t t7   ;
  uint128_t t8   ;
  uint128_t t9   ;
  uint128_t t10  ;
  uint64_t  Cp   ;
  uint64_t  tCp  ;
  uint64_t  t2Cp ;
  uint128_t t3Cp ;
  uint128_t t4Cp ;
  uint128_t t5Cp ;
};

class V1742{
  private:
    TADCBoard* fADCBoard;
    bool fIsHistDone;
    int fNEvtsProcessed;
  public:
    void CreateHistos(Histos& hist);
    void Analyse();
    V1742();
    ~V1742(){ }
    void SetBoard(TADCBoard* adcB);

    SiPM& GetChan(const int ch){return fChan[ch];}
    void SetTrig(const int t, TADCTrigger* trg){
    }

    void PrepareForAnal();
    std::vector<TriggerChannel> fTrig;
  private:
    //std::vector<SiPM> fChan;
    SiPM fChan[32];
    std::vector<int> fPeaks;


    //static void CellConfig();


  public:
    lin_reg_sums_t cap_sums[32][1024];
    //std::vector<TH1F*> hist1f_IndexCell           ;
    std::vector<TH2S*> hist2f_Pedestal_cal_cell  ;
    std::vector<TH2S*> hist2f_Pedestal_nocal_cell;
    std::vector<TH2S*> hist2f_Pedestal_cal_time  ;
    std::vector<TH2S*> hist2f_Pedestal_nocal_time;
    std::vector<TH2S*> hist2f_Cells_time         ;
    //std::vector<TH1F*> hist1f_SigPedestals        ;
    //std::vector<TH2F*> hist2f_SignalStudy         ;
    //std::vector<TH2F*> hist2f_PedestalStudyCell   ;
    //std::vector<TH2F*> hist2f_PedestalStudy       ;


};
#endif
