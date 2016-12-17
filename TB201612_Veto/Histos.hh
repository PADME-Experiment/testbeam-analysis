#ifndef _Histos_hh_
#define _Histos_hh_ 0

#include<sstream>
#include<map>

#include"TH1F.h"
#include"TH2F.h"
#include"TFile.h"
#include"TDirectory.h"
#include"TTree.h"

class Histos{
  private:
    const static int fNChanMax=27;
    const static int fNTrigMax=4;
    std::string fOutRootFileName;

  public:
    TH2F* hist2f_OscCum[fNChanMax];
    TH2F* hist2f_OscCumT0Fixed[fNChanMax];
    TH1F* hist1f_Pedestals[fNChanMax];
    TH2F* hist2f_PedestalsStudy[fNChanMax];
    TH2F* hist2f_SignalStudy       [fNChanMax];
    TH2F* hist2f_SignalStudyLowPass[fNChanMax];
    TH1F* hist1f_PhElectr[fNChanMax];
    TH1F* hist1f_PhElectrAbs[fNChanMax];
    TH1F* hist1f_PhElectrAbsSinglePartBeam[fNChanMax];
    TH1F* hist1f_PhElectrEff[fNChanMax];
    TH1F* hist1f_PhElectrNoise[fNChanMax];
    TH1F* hist1f_PhElectrAbsEff[fNChanMax];
    TH1F* hist1f_PhElectrAbsNoise[fNChanMax];
    TH1F* hist1f_PhElectrT0Fix[fNChanMax];
    TH1F* hist1f_MaxValueDistr[fNChanMax];
    TH2F* hist2f_PhElectrChCor[fNChanMax][fNChanMax];
    TH2F* hist2f_PhElectrChCorAbs[fNChanMax][fNChanMax];
    TH2F* hist2f_PhElectrChCorAbsSinglePartBeam[fNChanMax][fNChanMax];
    TH2F* hist2f_PhElectrChCorAbsSinglePartBeamVetoed[fNChanMax][fNChanMax];

    TH1F* hist1f_TrigJitter[fNTrigMax];
    TH2F* hist2f_TrigCum[fNTrigMax];
    TH2F* hist2f_TrigCumT0Fixed[fNTrigMax];
    TH2F* hist2f_CorrMatrix;


    TH1F* hist1f_TimeMaxValue[fNChanMax];
    TH1F* hist1f_TimeHalfMaxValue[fNChanMax];
    TH1F* hist1f_Time2080LeadTrailCros[fNChanMax];
    TH1F* hist1f_Time2080LeadZeroCros[fNChanMax];
    TH1F* hist1f_Time2080Lead50[fNChanMax];

    TH2F* hist2f_TimeMaxValue_Phe16[fNChanMax];
    TH2F* hist2f_TimeHalfMaxValue_Phe16[fNChanMax];
    TH2F* hist2f_Time2080LeadTrailCros_Phe16[fNChanMax];
    TH2F* hist2f_Time2080LeadZeroCros_Phe16[fNChanMax];
    TH2F* hist2f_Time2080Lead50_Phe16[fNChanMax];
    TH2F* hist2f_TimeMean_Phe16[fNChanMax];

    TH2F* hist2f_TimeCor2080LeadTrailCros_2080LeadZeroCros[fNChanMax];
    TH2F* hist2f_TimeCor2080LeadTrailCros_2080Lead50[fNChanMax];
    TH2F* hist2f_TimeCor2080LeadTrailCros_MeanTime[fNChanMax];
    TH2F* hist2f_TimeCor2080LeadTrailCros_MaxValue[fNChanMax];
    TH2F* hist2f_TimeCor2080LeadTrailCros_HalfMaxValue[fNChanMax];
    TH2F* hist2f_TimeCorMaxValue_HalfMaxValue[fNChanMax];
    TH2F* hist2f_TimeCorMeanTime_MaxValue[fNChanMax];
    TH2F* hist2f_TimeCorMeanTime_HalfMaxValue[fNChanMax];
    TH2F* hist2f_TimeCorMeanTime_2080Lead50[fNChanMax];
    TH2F* hist2f_TimeCorMeanTime_2080LeadZeroCros[fNChanMax];

    TH1F* hist1f_MeanTimeDistribution[fNChanMax];
    TH2F* hist2f_MeanTimeDistribution_Charge[fNChanMax];
    TH2F* hist2f_MeanTimeDistributionAbs_Charge[fNChanMax];
    TH1F* hist1f_MeanTimeChanDif[fNChanMax][fNChanMax];
    TH2F* hist2F_ChanneOccupancy;
    TH2F* hist2f_MeanTimeChanDif_Charge[fNChanMax][fNChanMax];
    TH2F* hist2f_TimeLead50Dif_Charge[fNChanMax][fNChanMax];

    TH2F* hist2f_TimeDiffMaxValue           [fNChanMax][fNChanMax];
    TH2F* hist2f_TimeDiffHalfMaxValue       [fNChanMax][fNChanMax];
    TH2F* hist2f_TimeDiff2080LeadTrailCros  [fNChanMax][fNChanMax];
    TH2F* hist2f_TimeDiff2080LeadZeroCros   [fNChanMax][fNChanMax];
    TH2F* hist2f_TimeDiff2080Lead50         [fNChanMax][fNChanMax];
    TH2F* hist2f_TimeDiffMeanTime           [fNChanMax][fNChanMax];
    TH2F* hist2f_TimeDiffMeanTime2          [fNChanMax][fNChanMax];
    TH2F* hist2f_TimeDiffMeanTimeAbs        [fNChanMax][fNChanMax];




  private:
    std::multimap<std::string,TObject*>fAllObj;

  public:
    Histos(const std::string& fn){
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
