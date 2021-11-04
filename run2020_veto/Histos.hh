#ifndef _Histos_hh_
#define _Histos_hh_ 0


#include"utlMessageBus.hh"

#include"TH1F.h"
#include"TH2F.h"
#include"TGraph.h"
#include"TFile.h"
#include"TDirectory.h"
#include"TTree.h"

#include<sstream>
#include<string>
#include<map>




class Histos{
  private:
    const static int fNBoardsMax=7;
    const static int fNChanMax=32;
    const static int fNTrigMax=4;
    std::string fOutRootFileName;

  public:
    TH2F* hist2f_CorrMatrix;

    //    TH1F* hist1f_SigPedestals      [fNChanMax];
    //
    //    TH2F* hist2f_PedestalCell      [fNChanMax];
    //    TH2F* hist2f_Pedestal          [fNChanMax];
    //    TH2F* hist2f_PedestalNoCellPedCor[fNChanMax];
    //    TH2F* hist2f_SignalStudy       [fNChanMax];
    //    TH2F* hist2f_PedestalStudyCell [fNChanMax];
    //    TH2F* hist2f_PedestalStudy[fNChanMax];
    //    //TH2F* hist2f_SignalStudyLowPass[fNChanMax];
    //
    //
    //    TH2F* hist2f_EVeto_OscCum                [3 * 32];
    //    TH2F* hist2f_EVeto_OscCumT0Fixed         [3 * 32];
    //    TH1F* hist1f_EVeto_TrigJitter            [3 * 4];
    //    TH2F* hist2f_EVeto_TrigCum               [3 * 4];
    //    TH2F* hist2f_EVeto_TrigCumT0Fixed        [3 * 4];
    //
    //    TH2F* hist2f_PVeto_OscCum                [3 * 32];
    //    TH2F* hist2f_PVeto_OscCumT0Fixed         [3 * 32];
    //    TH1F* hist1f_PVeto_TrigJitter            [3 * 4];
    //    TH2F* hist2f_PVeto_TrigCum               [3 * 4];
    //    TH2F* hist2f_PVeto_TrigCumT0Fixed        [3 * 4];
    //
    //    TH2F* hist2f_HVeto_OscCum                [1 * 32];
    //    TH2F* hist2f_HVeto_OscCumT0Fixed         [1 * 32];
    //    TH1F* hist1f_HVeto_TrigJitter            [1 * 4];
    //    TH2F* hist2f_HVeto_TrigCum               [1 * 4];
    //    TH2F* hist2f_HVeto_TrigCumT0Fixed        [1 * 4];
    //
    //    TH2F* hist2f_OscCum[fNChanMax];
    //    TH2F* hist2f_OscCumT0Fixed[fNChanMax];
    //    TH1F* hist1f_PhElectr[fNChanMax];
    //    TH1F* hist1f_PhElectrAbs[fNChanMax];
    //    TH1F* hist1f_PhElectrAbsSinglePartBeam[fNChanMax];
    //    TH1F* hist1f_PhElectrAbsDoublePartBeam[fNChanMax];
    //    TH1F* hist1f_PhElectrFFTAbsSinglePartBeam[fNChanMax];
    //    TH1F* hist1f_PhElectrEff[fNChanMax];
    //    TH1F* hist1f_PhElectrNoise[fNChanMax];
    //    TH1F* hist1f_PhElectrAbsEff[fNChanMax];
    //    TH1F* hist1f_PhElectrAbsNoise[fNChanMax];
    //    TH1F* hist1f_PhElectrT0Fix[fNChanMax];
    //    TH1F* hist1f_MaxValueDistr[fNChanMax];
    //    TH2F* hist2f_PhElectrChCor[fNChanMax][fNChanMax];
    //    TH2F* hist2f_PhElectrChCorAbs[fNChanMax][fNChanMax];
    //    TH2F* hist2f_PhElectrChCorAbsSinglePartBeam[fNChanMax][fNChanMax];
    //    TH2F* hist2f_PhElectrChCorAbsSinglePartBeamVetoed[fNChanMax][fNChanMax];
    //    TH2F* hist2f_PhElectrChCorFFTAbsSinglePartBeamVetoed[fNChanMax][fNChanMax];
    //
    //    TH1F* hist1f_TrigJitter[fNTrigMax];
    //    TH2F* hist2f_TrigCum[fNTrigMax];
    //    TH2F* hist2f_TrigCumT0Fixed[fNTrigMax];
    //
    //
    //    TH1F* hist1f_TimeMaxValue[fNChanMax];
    //    TH1F* hist1f_TimeHalfMaxValue[fNChanMax];
    //    TH1F* hist1f_Time2080LeadTrailCros[fNChanMax];
    //    TH1F* hist1f_Time2080LeadZeroCros[fNChanMax];
    //    TH1F* hist1f_Time2080Lead50[fNChanMax];
    //
    //    TH2F* hist2f_TimeMaxValue_Phe16[fNChanMax];
    //    TH2F* hist2f_TimeHalfMaxValue_Phe16[fNChanMax];
    //    TH2F* hist2f_Time2080LeadTrailCros_Phe16[fNChanMax];
    //    TH2F* hist2f_Time2080LeadZeroCros_Phe16[fNChanMax];
    //    TH2F* hist2f_Time2080Lead50_Phe16[fNChanMax];
    //    TH2F* hist2f_TimeMean_Phe16[fNChanMax];
    //
    //    TH2F* hist2f_TimeCor2080LeadTrailCros_2080LeadZeroCros[fNChanMax];
    //    TH2F* hist2f_TimeCor2080LeadTrailCros_2080Lead50[fNChanMax];
    //    TH2F* hist2f_TimeCor2080LeadTrailCros_MeanTime[fNChanMax];
    //    TH2F* hist2f_TimeCor2080LeadTrailCros_MaxValue[fNChanMax];
    //    TH2F* hist2f_TimeCor2080LeadTrailCros_HalfMaxValue[fNChanMax];
    //    TH2F* hist2f_TimeCorMaxValue_HalfMaxValue[fNChanMax];
    //    TH2F* hist2f_TimeCorMeanTime_MaxValue[fNChanMax];
    //    TH2F* hist2f_TimeCorMeanTime_HalfMaxValue[fNChanMax];
    //    TH2F* hist2f_TimeCorMeanTime_2080Lead50[fNChanMax];
    //    TH2F* hist2f_TimeCorMeanTime_2080LeadZeroCros[fNChanMax];
    //
    //    TH1F* hist1f_MeanTimeDistribution[fNChanMax];
    //    TH2F* hist2f_MeanTimeDistribution_Charge[fNChanMax];
    //    TH2F* hist2f_MeanTimeDistributionAbs_Charge[fNChanMax];
    //    TH1F* hist1f_MeanTimeChanDif[fNChanMax][fNChanMax];
    //    TH2F* hist2F_ChanneOccupancy;
    //    TH2F* hist2f_MeanTimeChanDif_Charge[fNChanMax][fNChanMax];
    //    TH2F* hist2f_TimeLead50Dif_Charge[fNChanMax][fNChanMax];
    //
    //    TH2F* hist2f_TimeDiffMaxValue           [fNChanMax][fNChanMax];
    //    TH2F* hist2f_TimeDiffHalfMaxValue       [fNChanMax][fNChanMax];
    //    TH2F* hist2f_TimeDiff02MaxValue         [fNChanMax][fNChanMax];
    //    TH2F* hist2f_TimeDiff01MaxValue         [fNChanMax][fNChanMax];
    //    TH2F* hist2f_TimeDiff2080LeadTrailCros  [fNChanMax][fNChanMax];
    //    TH2F* hist2f_TimeDiff2080LeadZeroCros   [fNChanMax][fNChanMax];
    //    TH2F* hist2f_TimeDiff2080Lead50         [fNChanMax][fNChanMax];
    //    TH2F* hist2f_TimeDiffMeanTime           [fNChanMax][fNChanMax];
    //    TH2F* hist2f_TimeDiffMeanTime2          [fNChanMax][fNChanMax];
    //    TH2F* hist2f_TimeDiffMeanTimeAbs        [fNChanMax][fNChanMax];
    //    TH2F* hist2f_TimeDiffMeanTimeFFT        [fNChanMax][fNChanMax];
    //    TH2F* hist2f_TimeDiffMeanTimeFFTAbs     [fNChanMax][fNChanMax];
    //    TH2F* hist2f_TimeDiffIntegral           [fNChanMax][fNChanMax];
    //
    //    TGraph* graph_AbsSumSamp_Time[fNChanMax];
    //    TGraph* graph_RMSSamp_Time   [fNChanMax];
    //    TGraph* graph_MinSamp_Time   [fNChanMax];
    //    TGraph* graph_MaxSamp_Time   [fNChanMax];
    //    TH1F*   hist1f_RMSSamp       [fNChanMax];
    //    TGraph* graph_PPStab_Time    [fNChanMax];
    //    TH1F*   hist1f_PPStab        [fNChanMax];
    //    TH1F*   hist1f_lightCollectRto[4];




  private:
    TFile* fRootFileP;
  public:
    //std::multimap<std::string,TObject*>fAllObj;

  public:
    Histos(const std::string& fn){
      fOutRootFileName = fn;

      fRootFileP=new TFile(fn.c_str(),"recreate");
      fRootFileP->cd();
      std::string name, title;

      name ="CorrMatrix"; title=name;
      //hist2f_CorrMatrix=new TH2F(name.c_str(),title.c_str(), 300,-.5,300-.5, 300,-.5,300-.5);
      CreateHistos();
      //hist2f_CorrMatrix->Fill(3, 3);
      //fRootFileP->Write();
    }


    void Write(){
      fRootFileP->Write();
    }


    ~Histos(){
      fRootFileP->Close();
      delete fRootFileP;
    }

    void CreateHistos();

    void GotoDir(const std::string& dir){
      //INFO("goto "+dir);
      TDirectory* fileDir=fRootFileP;
      fileDir->cd();
      fileDir=fileDir->mkdir(dir.c_str(),"", true);
      fileDir->cd();
    }


};
#endif
