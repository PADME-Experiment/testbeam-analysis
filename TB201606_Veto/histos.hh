#ifndef _histos_hh_
#define _histos_hh_ 0


class Histos{
  private:
    const static int fNChanMax=17;
    const static int fNTrigMax=4;
    std::string fOutRootFileName;

  public:
    TH2F* hist2f_OscCum[fNChanMax];
    TH2F* hist2f_OscCumT0Fixed[fNChanMax];
    TH1F* hist1f_Pedestals[fNChanMax];
    TH2F* hist2f_PedestalsStudy[fNChanMax];
    TH1F* hist1f_PhElectr[fNChanMax];
    TH1F* hist1f_PhElectrAbs[fNChanMax];
    TH1F* hist1f_PhElectrEff[fNChanMax];
    TH1F* hist1f_PhElectrNoise[fNChanMax];
    TH1F* hist1f_PhElectrAbsEff[fNChanMax];
    TH1F* hist1f_PhElectrAbsNoise[fNChanMax];
    TH1F* hist1f_PhElectrT0Fix[fNChanMax];
    TH1F* hist1f_MaxValueDistr[fNChanMax];
    TH2F* hist2f_PhElectrChCor[fNChanMax][fNChanMax];
    TH2F* hist2f_PhElectrChCorT0Fix[fNChanMax][fNChanMax];

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


    //MaxValue
    //HalfMaxValue
    //2080LeadTrailCros
    //2080LeadZeroCros
    //2080Lead50
    //MeanTime

    TH1F* hist1f_MeanTimeDistribution[fNChanMax];
    TH2F* hist2f_MeanTimeDistribution_Charge[fNChanMax];
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





  public:
    Histos(const std::string& fn){
      fOutRootFileName = fn;
      ZerofyHistos();
      CreateHistos();
    }


    ~Histos(){
      WriteHistos();
      DeleteHistos();
      ZerofyHistos();
    }

    void ZerofyHistos(){
      for(int ii=0;ii<fNTrigMax;++ii){
        hist1f_TrigJitter[ii]=NULL;
        hist2f_TrigCum[ii]=NULL;
        hist2f_TrigCumT0Fixed[ii]=NULL;
      }

      hist2F_ChanneOccupancy=NULL;
      for(int ii=0;ii<fNChanMax;++ii){
        hist2f_OscCum[ii]=NULL;
        hist2f_OscCumT0Fixed[ii]=NULL;
        hist1f_Pedestals[ii]=NULL;
        hist2f_PedestalsStudy[ii]=NULL;
        hist1f_PhElectr[ii]=NULL;
        hist1f_PhElectrAbs[ii]=NULL;
        hist1f_PhElectrEff[ii]=NULL;
        hist1f_PhElectrNoise[ii]=NULL;
        hist1f_PhElectrAbsEff[ii]=NULL;
        hist1f_PhElectrAbsNoise[ii]=NULL;
        hist1f_PhElectrT0Fix[ii]=NULL;
        hist1f_MaxValueDistr[ii]=NULL;
        hist1f_MeanTimeDistribution[ii]=NULL;

        hist1f_TimeMaxValue             [ii]=NULL;
        hist1f_TimeHalfMaxValue         [ii]=NULL;
        hist1f_Time2080LeadTrailCros    [ii]=NULL;
        hist1f_Time2080LeadZeroCros     [ii]=NULL;
        hist1f_Time2080Lead50           [ii]=NULL;

        hist2f_TimeMaxValue_Phe16[ii]=NULL;
        hist2f_TimeHalfMaxValue_Phe16[ii]=NULL;
        hist2f_Time2080LeadTrailCros_Phe16[ii]=NULL;
        hist2f_Time2080LeadZeroCros_Phe16[ii]=NULL;
        hist2f_Time2080Lead50_Phe16[ii]=NULL;
        hist2f_TimeMean_Phe16[ii]=NULL;

        hist2f_TimeCor2080LeadTrailCros_2080LeadZeroCros[ii]=NULL;
        hist2f_TimeCor2080LeadTrailCros_2080Lead50[ii]=NULL;
        hist2f_TimeCor2080LeadTrailCros_MeanTime[ii]=NULL;
        hist2f_TimeCor2080LeadTrailCros_MaxValue[ii]=NULL;
        hist2f_TimeCor2080LeadTrailCros_HalfMaxValue[ii]=NULL;
        hist2f_TimeCorMaxValue_HalfMaxValue[ii]=NULL;
        hist2f_TimeCorMeanTime_MaxValue[ii]=NULL;
        hist2f_TimeCorMeanTime_HalfMaxValue[ii]=NULL;
        hist2f_TimeCorMeanTime_2080Lead50[ii]=NULL;
        hist2f_TimeCorMeanTime_2080LeadZeroCros[ii]=NULL;


        hist2f_MeanTimeDistribution_Charge[ii]=NULL;
        for(int jj=0;jj<fNChanMax;++jj){
          hist2f_PhElectrChCor[ii][jj]=NULL;
          hist2f_PhElectrChCorT0Fix[ii][jj]=NULL;
          hist1f_MeanTimeChanDif[ii][jj]=NULL;
          hist2f_MeanTimeChanDif_Charge[ii][jj]=NULL;
          hist2f_TimeLead50Dif_Charge[ii][jj]=NULL;


          hist2f_TimeDiffMaxValue                    [ii][jj]=NULL;;
          hist2f_TimeDiffHalfMaxValue                [ii][jj]=NULL;;
          hist2f_TimeDiff2080LeadTrailCros           [ii][jj]=NULL;;
          hist2f_TimeDiff2080LeadZeroCros            [ii][jj]=NULL;;
          hist2f_TimeDiff2080Lead50                  [ii][jj]=NULL;;
          hist2f_TimeDiffMeanTime                    [ii][jj]=NULL;;
          hist2f_TimeDiffMeanTime2                   [ii][jj]=NULL;;
          hist2f_TimeDiffMeanTimeAbs                 [ii][jj]=NULL;;

        }
      }
      hist2f_CorrMatrix=NULL;
    }

    void CreateHistos(){
      std::string name, title;
      name="ChannelOccupacy"; title=name;
      hist2F_ChanneOccupancy=new TH2F(name.c_str(),title.c_str(),16,1,9,3,1,4);

      for(int ii=0;ii<fNTrigMax;++ii){
        std::stringstream chan_i_ss;
        chan_i_ss<<ii;
        name="TriggerJitter_ch_"+chan_i_ss.str(); title=name;
        hist1f_TrigJitter[ii]=new TH1F(name.c_str(),title.c_str(),100,-50-.5,50-.5);

        name="TriggerCumulativeOscillogram_ch_"+chan_i_ss.str(); title=name;
        hist2f_TrigCum[ii]=new TH2F(name.c_str(),title.c_str(),1024,-.5,1023.5, 512,-5000,5000);

        name="TriggerCumulativeOscillogramT0Fixed_ch_"+chan_i_ss.str(); title=name;
        hist2f_TrigCumT0Fixed[ii]=new TH2F(name.c_str(),title.c_str(),1024,-.5,1023.5, 512,-5000,5000);
      }

      for(int ii=0;ii<fNChanMax;++ii){
        std::stringstream chan_i_ss;
        chan_i_ss<<ii;
        name="CumulativeOscillogram_ch_"+chan_i_ss.str(); title=name;
        hist2f_OscCum[ii]=new TH2F(name.c_str(),title.c_str(),1024,-.5,1023.5, 2048,-1,.1) ;
        name="CumulativeOscillogramT0Fixed_ch_"+chan_i_ss.str(); title=name;
        hist2f_OscCumT0Fixed[ii]=new TH2F(name.c_str(),title.c_str(),1024,-.5,1023.5, 512,-1,.1) ;
        name="Pedestals_ch_"+chan_i_ss.str(); title=name;
        hist1f_Pedestals[ii]=new TH1F(name.c_str(),title.c_str(),500,3500-.5,4000-.5);
        name ="PedestalsStudy_ch_"+chan_i_ss.str(); title=name;
        hist2f_PedestalsStudy[ii]=new TH2F(name.c_str(),title.c_str(),1024,0-.5,1024-.5,100,-.5,100-.5);
        name="PhElectr_ch_"+chan_i_ss.str(); title=name;
        hist1f_PhElectr[ii]=new TH1F(name.c_str(),title.c_str(),512,-50,400*(ii==16?20:1));
        name ="PhElectrAbs_ch_"+chan_i_ss.str(); title=name;
        hist1f_PhElectrAbs[ii]=new TH1F(name.c_str(),title.c_str(),512,-50,400*(ii==16?20:1));

        name ="PhElectrEff_ch_"+chan_i_ss.str(); title=name;
        hist1f_PhElectrEff[ii]=new TH1F(name.c_str(),title.c_str(),5120,-50,400*(ii==16?20:1));
        name ="PhElectrNoise_ch_"+chan_i_ss.str(); title=name;
        hist1f_PhElectrNoise[ii]=new TH1F(name.c_str(),title.c_str(),5120,-50,400*(ii==16?20:1));

        name ="PhElectrAbsEff_ch_"+chan_i_ss.str(); title=name;
        hist1f_PhElectrAbsEff[ii]=new TH1F(name.c_str(),title.c_str(),5120,-50,400*(ii==16?20:1));
        name ="PhElectrAbsNoise_ch_"+chan_i_ss.str(); title=name;
        hist1f_PhElectrAbsNoise[ii]=new TH1F(name.c_str(),title.c_str(),5120,-50,400*(ii==16?20:1));

        name="PhElectrT0Fix_ch_"+chan_i_ss.str(); title=name;
        hist1f_PhElectrT0Fix[ii]=new TH1F(name.c_str(),title.c_str(),512,-50,400*(ii==16?20:1));

        name ="MaxValueDistr_ch_"+chan_i_ss.str(); title=name;
        hist1f_MaxValueDistr[ii]=new TH1F(name.c_str(),title.c_str(),512,-1,.1);

        name="MeanTimeDistr_ch_"+chan_i_ss.str(); title=name;
        hist1f_MeanTimeDistribution[ii]=new TH1F(name.c_str(),title.c_str(),600,0,600);

        name ="TimeMaxValue_ch_"+chan_i_ss.str(); title=name;
        hist1f_TimeMaxValue             [ii]=new TH1F(name.c_str(),title.c_str(),600,0,600);
        name ="TimeHalfMaxValue_ch_"+chan_i_ss.str(); title=name;
        hist1f_TimeHalfMaxValue         [ii]=new TH1F(name.c_str(),title.c_str(),600,0,600);
        name ="Time2080LeadTrailCros_ch_"+chan_i_ss.str(); title=name;
        hist1f_Time2080LeadTrailCros    [ii]=new TH1F(name.c_str(),title.c_str(),600,0,600);
        name ="Time2080LeadZeroCros_ch_"+chan_i_ss.str(); title=name;
        hist1f_Time2080LeadZeroCros     [ii]=new TH1F(name.c_str(),title.c_str(),600,0,600);
        name ="Time2080Lead50_ch_"+chan_i_ss.str(); title=name;
        hist1f_Time2080Lead50           [ii]=new TH1F(name.c_str(),title.c_str(),600,0,600);

        name ="TimeMaxValue_Phe16_ch_"+chan_i_ss.str(); title=name;
        hist2f_TimeMaxValue_Phe16          [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="TimeHalfMaxValue_Phe16_ch_"+chan_i_ss.str(); title=name;
        hist2f_TimeHalfMaxValue_Phe16      [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="Time2080LeadTrailCros_Phe16_ch_"+chan_i_ss.str(); title=name;
        hist2f_Time2080LeadTrailCros_Phe16 [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="Time2080LeadZeroCros_Phe16_ch_"+chan_i_ss.str(); title=name;
        hist2f_Time2080LeadZeroCros_Phe16  [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="Time2080Lead50_Phe16_ch_"+chan_i_ss.str(); title=name;
        hist2f_Time2080Lead50_Phe16        [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="TimeMean_Phe16_ch_"+chan_i_ss.str(); title=name;
        hist2f_TimeMean_Phe16              [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);

        name ="TimeCor2080LeadTrailCros_2080LeadZeroCros_ch_"+chan_i_ss.str(); title=name;
        hist2f_TimeCor2080LeadTrailCros_2080LeadZeroCros[ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="TimeCor2080LeadTrailCros_2080Lead50_ch_"+chan_i_ss.str(); title=name;
        hist2f_TimeCor2080LeadTrailCros_2080Lead50      [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="TimeCor2080LeadTrailCros_MeanTime_ch_"+chan_i_ss.str(); title=name;
        hist2f_TimeCor2080LeadTrailCros_MeanTime        [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="TimeCor2080LeadTrailCros_MaxValue_ch_"+chan_i_ss.str(); title=name;
        hist2f_TimeCor2080LeadTrailCros_MaxValue        [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="TimeCor2080LeadTrailCros_HalfMaxValue_ch_"+chan_i_ss.str(); title=name;
        hist2f_TimeCor2080LeadTrailCros_HalfMaxValue    [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="TimeCorMaxValue_HalfMaxValue_ch_"+chan_i_ss.str(); title=name;
        hist2f_TimeCorMaxValue_HalfMaxValue             [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="TimeCorMeanTime_MaxValue_ch_"+chan_i_ss.str(); title=name;
        hist2f_TimeCorMeanTime_MaxValue                 [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="TimeCorMeanTime_HalfMaxValue_ch_"+chan_i_ss.str(); title=name;
        hist2f_TimeCorMeanTime_HalfMaxValue             [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="TimeCorMeanTime_2080Lead50_ch_"+chan_i_ss.str(); title=name;
        hist2f_TimeCorMeanTime_2080Lead50               [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
        name ="TimeCorMeanTime_2080LeadZeroCros_ch_"+chan_i_ss.str(); title=name;
        hist2f_TimeCorMeanTime_2080LeadZeroCros        [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);

        name="MeanTimeDistr_Charge_ch_"+chan_i_ss.str(); title=name;
        hist2f_MeanTimeDistribution_Charge[ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,500,0,500);

        for(int jj=0;jj<fNChanMax;++jj){
          std::stringstream chan_j_ss;
          chan_j_ss<<jj;
          name="MeanTimeChanDif_charge_"+chan_i_ss.str()+"-"+chan_j_ss.str()+"_charge_"+chan_i_ss.str(); title=name;
          hist2f_MeanTimeChanDif_Charge[ii][jj]=new TH2F(name.c_str(),title.c_str(),1000,-400,400,500,0,500);
          ///home/georgieff/git/padme-fw/GG-analyser

          name ="TimeLead50Dif_charge_"+chan_i_ss.str()+"-"+chan_j_ss.str()+"_charge_"+chan_i_ss.str(); title=name;
          hist2f_TimeLead50Dif_Charge[ii][jj]=new TH2F(name.c_str(),title.c_str(),1000,-400,400,500,0,500);
        }
        for(int jj=ii+1;jj<fNChanMax;++jj){
          std::stringstream chan_j_ss;
          chan_j_ss<<jj;
          name="PhElectrChCor_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name;
          hist2f_PhElectrChCor[ii][jj]=new TH2F(name.c_str(),title.c_str(),512,-50,400,512,-50,400*(jj==16?20:1));
          name="PhElectrChCorT0Fix_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name;
          hist2f_PhElectrChCorT0Fix[ii][jj]=new TH2F(name.c_str(),title.c_str(),512,-50,400,512,-50,400*(jj==16?20:1));


          name="MeanTimeChanDif_"+chan_i_ss.str()+"-"+chan_j_ss.str(); title=name;
          hist1f_MeanTimeChanDif[ii][jj]=new TH1F(name.c_str(),title.c_str(),1000,-400,400);

          std::string lab=";ns;nPhe(13)/10";

          name ="TimeDiffMaxValue_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+lab;
          hist2f_TimeDiffMaxValue  [ii][jj]       =new TH2F(name.c_str(),title.c_str(),320,-80-.25,80-.25,200,-20,500);
          name ="TimeDiffHalfMaxValue_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+lab;
          hist2f_TimeDiffHalfMaxValue   [ii][jj]  =new TH2F(name.c_str(),title.c_str(),320,-80-.25,80-.25,200,-20,500);
          name ="TimeDiff2080LeadTrailCros_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+lab;
          hist2f_TimeDiff2080LeadTrailCros[ii][jj]=new TH2F(name.c_str(),title.c_str(),320,-80-.25,80-.25,200,-20,500);
          name ="TimeDiff2080LeadZeroCros_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+lab;
          hist2f_TimeDiff2080LeadZeroCros[ii][jj] =new TH2F(name.c_str(),title.c_str(),320,-80-.25,80-.25,200,-20,500);
          name ="TimeDiff2080Lead50_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+lab;
          hist2f_TimeDiff2080Lead50   [ii][jj]    =new TH2F(name.c_str(),title.c_str(),320,-80-.25,80-.25,200,-20,500);
          name ="TimeDiffMeanTime_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+lab;
          hist2f_TimeDiffMeanTime      [ii][jj]   =new TH2F(name.c_str(),title.c_str(),320,-80-.25,80-.25,200,-20,500);
          name ="TimeDiffMeanTime2_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+lab;
          hist2f_TimeDiffMeanTime2     [ii][jj]   =new TH2F(name.c_str(),title.c_str(),320,-80-.25,80-.25,200,-20,500);
          name ="TimeDiffMeanTimeAbs_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+lab;
          hist2f_TimeDiffMeanTimeAbs     [ii][jj]   =new TH2F(name.c_str(),title.c_str(),320,-80-.25,80-.25,200,-20,500);


        }
      }
      name ="CorrMatrix"; title=name;
      hist2f_CorrMatrix=new TH2F(name.c_str(),title.c_str(),fNChanMax,-.5,fNChanMax-.5,fNChanMax,-.5,fNChanMax-.5);

    }

    void WriteHistos(){
      TFile* outRootFileP=new TFile(fOutRootFileName.c_str(),"recreate");
      TDirectory* fileDir=outRootFileP;
      std::stringstream chan_i_ss;
      //chan_i_ss<<chan_i;
      //std::string dirName="chan_"+chan_i_ss.str();
      std::string dirName;

      dirName="OscCum";

      TDirectory* dir;

      fileDir->cd();
      hist2f_CorrMatrix->Write();

      dir=fileDir->mkdir("TrigJitter"); dir->cd();
      for(int ii=0;ii<fNTrigMax;++ii) hist1f_TrigJitter[ii]->Write();

      dir=fileDir->mkdir("TrigCum"); dir->cd();
      for(int ii=0;ii<fNTrigMax;++ii) hist2f_TrigCum[ii]->Write();

      dir=fileDir->mkdir("TrigCumT0Fixed"); dir->cd();
      for(int ii=0;ii<fNTrigMax;++ii) hist2f_TrigCumT0Fixed[ii]->Write();

      dir=fileDir->mkdir("Pedestals"); dir->cd();
      for(int ii=0;ii<fNChanMax;++ii) hist1f_Pedestals[ii]->Write();
      dir=fileDir->mkdir("PedestalsStudy"); dir->cd();
      for(int ii=0;ii<fNChanMax;++ii) hist2f_PedestalsStudy[ii]->Write();

      dir=fileDir->mkdir("OscCum"); dir->cd();
      for(int ii=0;ii<fNChanMax;++ii) hist2f_OscCum[ii]->Write();

      dir=fileDir->mkdir("OscCumT0Fixed"); dir->cd();
      for(int ii=0;ii<fNChanMax;++ii) hist2f_OscCumT0Fixed[ii]->Write();

      //dir=fileDir->mkdir("PhElectrT0Fix"); dir->cd();
      //for(int ii=0;ii<fNChanMax;++ii) hist1f_PhElectrT0Fix[ii]->Write();

      dir=fileDir->mkdir("MaxValueDistr"); dir->cd();
      for(int ii=0;ii<fNChanMax;++ii) hist1f_MaxValueDistr[ii]->Write();

      dir=fileDir->mkdir("PhElectr"); dir->cd();
      for(int ii=0;ii<fNChanMax;++ii) hist1f_PhElectr[ii]->Write();
      dir=fileDir->mkdir("PhElectrAbs"); dir->cd();
      for(int ii=0;ii<fNChanMax;++ii) hist1f_PhElectrAbs[ii]->Write();
      dir=fileDir->mkdir("PhElectrChCor"); dir->cd();
      for(int ii=0;ii<fNChanMax;++ii) for(int jj=ii+1;jj<fNChanMax;++jj) hist2f_PhElectrChCor[ii][jj]->Write();
      dir=fileDir->mkdir("PhElectrEff"); dir->cd();
      for(int ii=0;ii<fNChanMax;++ii) hist1f_PhElectrEff[ii]->Write();
      dir=fileDir->mkdir("PhElectrNoise"); dir->cd();
      for(int ii=0;ii<fNChanMax;++ii) hist1f_PhElectrNoise[ii]->Write();
      dir=fileDir->mkdir("PhElectrAbsEff"); dir->cd();
      for(int ii=0;ii<fNChanMax;++ii) hist1f_PhElectrAbsEff[ii]->Write();
      dir=fileDir->mkdir("PhElectrAbsNoise"); dir->cd();
      for(int ii=0;ii<fNChanMax;++ii) hist1f_PhElectrAbsNoise[ii]->Write();

      dir=fileDir->mkdir("TimeDiffMaxValue"          ); dir->cd();  for(int ii=8;ii<16;++ii) for(int jj=ii+1;jj<16;++jj) hist2f_TimeDiffMaxValue              [ii][jj]->Write();
      dir=fileDir->mkdir("TimeDiffHalfMaxValue"      ); dir->cd();  for(int ii=8;ii<16;++ii) for(int jj=ii+1;jj<16;++jj) hist2f_TimeDiffHalfMaxValue          [ii][jj]->Write();
      dir=fileDir->mkdir("TimeDiff2080LeadTrailCros" ); dir->cd();  for(int ii=8;ii<16;++ii) for(int jj=ii+1;jj<16;++jj) hist2f_TimeDiff2080LeadTrailCros     [ii][jj]->Write();
      dir=fileDir->mkdir("TimeDiff2080LeadZeroCros"  ); dir->cd();  for(int ii=8;ii<16;++ii) for(int jj=ii+1;jj<16;++jj) hist2f_TimeDiff2080LeadZeroCros      [ii][jj]->Write();
      dir=fileDir->mkdir("TimeDiff2080Lead50"        ); dir->cd();  for(int ii=8;ii<16;++ii) for(int jj=ii+1;jj<16;++jj) hist2f_TimeDiff2080Lead50            [ii][jj]->Write();
      dir=fileDir->mkdir("TimeDiffMeanTime"          ); dir->cd();  for(int ii=8;ii<16;++ii) for(int jj=ii+1;jj<16;++jj) hist2f_TimeDiffMeanTime              [ii][jj]->Write();
      dir=fileDir->mkdir("TimeDiffMeanTime2"         ); dir->cd();  for(int ii=8;ii<16;++ii) for(int jj=ii+1;jj<16;++jj) hist2f_TimeDiffMeanTime2             [ii][jj]->Write();
      dir=fileDir->mkdir("TimeDiffMeanTimeAbs"       ); dir->cd();  for(int ii=8;ii<16;++ii) for(int jj=ii+1;jj<16;++jj) hist2f_TimeDiffMeanTimeAbs             [ii][jj]->Write();


      //dir=fileDir->mkdir("PhElectrChCorT0Fix"); dir->cd();
      //for(int ii=0;ii<fNChanMax;++ii) for(int jj=ii+1;jj<fNChanMax;++jj) hist2f_PhElectrChCorT0Fix[ii][jj]->Write();


      //dir=fileDir->mkdir("MeanTimeDistr"); dir->cd();
      //for(int ii=0;ii<fNChanMax;++ii) hist1f_MeanTimeDistribution[ii]->Write();

      //dir=fileDir->mkdir("TimeMaxValue"); dir->cd();
      //for(int ii=0;ii<fNChanMax;++ii) hist1f_TimeMaxValue[ii]           ->Write();
      //dir=fileDir->mkdir("TimeHalfMaxValue"); dir->cd();
      //for(int ii=0;ii<fNChanMax;++ii) hist1f_TimeHalfMaxValue[ii]       ->Write();
      //dir=fileDir->mkdir("Time2080LeadTrailCros"); dir->cd();
      //for(int ii=0;ii<fNChanMax;++ii) hist1f_Time2080LeadTrailCros[ii]  ->Write();
      //dir=fileDir->mkdir("Time2080LeadZeroCros"); dir->cd();
      //for(int ii=0;ii<fNChanMax;++ii) hist1f_Time2080LeadZeroCros[ii]   ->Write();
      //dir=fileDir->mkdir("Time2080Lead50"); dir->cd();
      //for(int ii=0;ii<fNChanMax;++ii) hist1f_Time2080Lead50[ii]         ->Write();


      //dir=fileDir->mkdir("TimeMaxValue_Phe16"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_TimeMaxValue_Phe16[ii]->Write();
      //dir=fileDir->mkdir("TimeHalfMaxValue_Phe16"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_TimeHalfMaxValue_Phe16[ii]->Write();
      //dir=fileDir->mkdir("Time2080LeadTrailCros_Phe16"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_Time2080LeadTrailCros_Phe16[ii]->Write();
      //dir=fileDir->mkdir("Time2080LeadZeroCros_Phe16"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_Time2080LeadZeroCros_Phe16[ii]->Write();
      //dir=fileDir->mkdir("Time2080Lead50_Phe16"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_Time2080Lead50_Phe16[ii]->Write();
      //dir=fileDir->mkdir("TimeMean_Phe16"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_TimeMean_Phe16[ii]->Write();

      //dir=fileDir->mkdir("TimeCor2080LeadTrailCros_2080LeadZeroCros"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_TimeCor2080LeadTrailCros_2080LeadZeroCros[ii]->Write();
      //dir=fileDir->mkdir("TimeCor2080LeadTrailCros_2080Lead50"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_TimeCor2080LeadTrailCros_2080Lead50[ii]->Write();
      //dir=fileDir->mkdir("TimeCor2080LeadTrailCros_MeanTime"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_TimeCor2080LeadTrailCros_MeanTime[ii]->Write();
      //dir=fileDir->mkdir("TimeCor2080LeadTrailCros_MaxValue"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_TimeCor2080LeadTrailCros_MaxValue[ii]->Write();
      //dir=fileDir->mkdir("TimeCor2080LeadTrailCros_HalfMaxValue"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_TimeCor2080LeadTrailCros_HalfMaxValue[ii]->Write();
      //dir=fileDir->mkdir("TimeCorMaxValue_HalfMaxValue"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_TimeCorMaxValue_HalfMaxValue[ii]->Write();
      //dir=fileDir->mkdir("TimeCorMeanTime_MaxValue"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_TimeCorMeanTime_MaxValue[ii]->Write();
      //dir=fileDir->mkdir("TimeCorMeanTime_HalfMaxValue"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_TimeCorMeanTime_HalfMaxValue[ii]->Write();
      //dir=fileDir->mkdir("TimeCorMeanTime_2080Lead50"); dir->cd(); for(int ii=0;ii<fNChanMax;++ii) hist2f_TimeCorMeanTime_2080Lead50[ii]->Write();
      //dir=fileDir->mkdir("TimeCorMeanTime_2080LeadZeroCros"); dir->cd();
      //for(int ii=0;ii<fNChanMax;++ii) hist2f_TimeCorMeanTime_2080LeadZeroCros[ii]->Write();

      //dir=fileDir->mkdir("MeanTimeDistr_Charge"); dir->cd();
      //for(int ii=0;ii<fNChanMax;++ii) hist2f_MeanTimeDistribution_Charge[ii]->Write();

      //dir=fileDir->mkdir("MeanTimeChanDif"); dir->cd();
      //for(int ii=0;ii<fNChanMax;++ii) for(int jj=ii+1;jj<fNChanMax;++jj) hist1f_MeanTimeChanDif[ii][jj]->Write();

      //dir=fileDir->mkdir("MeanTimeChanDif_Charge"); dir->cd();
      //for(int ii=0;ii<fNChanMax;++ii) for(int jj=0;jj<fNChanMax;++jj) hist2f_MeanTimeChanDif_Charge[ii][jj]->Write();

      //dir=fileDir->mkdir("TimeLead50Dif_charge"); dir->cd();
      //for(int ii=0;ii<fNChanMax;++ii) for(int jj=0;jj<fNChanMax;++jj) hist2f_TimeLead50Dif_Charge[ii][jj]->Write();

      fileDir->cd();
      hist2F_ChanneOccupancy->Write();

      outRootFileP->Write();
      outRootFileP->Close();
      delete outRootFileP;
    }
    void DeleteHistos(){
      for(int ii=0;ii<fNTrigMax;++ii){
        delete hist1f_TrigJitter[ii];
        delete hist2f_TrigCum[ii];
        delete hist2f_TrigCumT0Fixed[ii];
      }

      for(int ii=0;ii<fNChanMax;++ii){
        delete hist1f_Pedestals[ii];
        delete hist2f_PedestalsStudy[ii];
        delete hist2f_OscCum[ii];
        delete hist2f_OscCumT0Fixed[ii];
        delete hist1f_PhElectr[ii];
        delete hist1f_PhElectrAbs[ii];
        delete hist1f_PhElectrEff[ii];
        delete hist1f_PhElectrNoise[ii];
        delete hist1f_PhElectrAbsEff[ii];
        delete hist1f_PhElectrAbsNoise[ii];
        delete hist1f_PhElectrT0Fix[ii];
        delete hist1f_MaxValueDistr[ii];

        delete hist1f_MeanTimeDistribution[ii];

        delete hist1f_TimeMaxValue[ii];
        delete hist1f_TimeHalfMaxValue[ii];
        delete hist1f_Time2080LeadTrailCros[ii];
        delete hist1f_Time2080LeadZeroCros[ii];
        delete hist1f_Time2080Lead50[ii];

        delete hist2f_TimeMaxValue_Phe16[ii];
        delete hist2f_TimeHalfMaxValue_Phe16[ii];
        delete hist2f_Time2080LeadTrailCros_Phe16[ii];
        delete hist2f_Time2080LeadZeroCros_Phe16[ii];
        delete hist2f_Time2080Lead50_Phe16[ii];
        delete hist2f_TimeMean_Phe16[ii];

        delete hist2f_TimeCor2080LeadTrailCros_2080LeadZeroCros[ii];
        delete hist2f_TimeCor2080LeadTrailCros_2080Lead50[ii];
        delete hist2f_TimeCor2080LeadTrailCros_MeanTime[ii];
        delete hist2f_TimeCor2080LeadTrailCros_MaxValue[ii];
        delete hist2f_TimeCor2080LeadTrailCros_HalfMaxValue[ii];
        delete hist2f_TimeCorMaxValue_HalfMaxValue[ii];
        delete hist2f_TimeCorMeanTime_MaxValue[ii];
        delete hist2f_TimeCorMeanTime_HalfMaxValue[ii];
        delete hist2f_TimeCorMeanTime_2080Lead50[ii];
        delete hist2f_TimeCorMeanTime_2080LeadZeroCros[ii];

        delete hist2f_MeanTimeDistribution_Charge[ii];
        for(int jj=ii+1;jj<fNChanMax;++jj){
          delete hist2f_PhElectrChCor[ii][jj];
          delete hist2f_PhElectrChCorT0Fix[ii][jj];
          delete hist1f_MeanTimeChanDif[ii][jj];

          delete hist2f_TimeDiffMaxValue              [ii][jj];
          delete hist2f_TimeDiffHalfMaxValue          [ii][jj];
          delete hist2f_TimeDiff2080LeadTrailCros     [ii][jj];
          delete hist2f_TimeDiff2080LeadZeroCros      [ii][jj];
          delete hist2f_TimeDiff2080Lead50            [ii][jj];
          delete hist2f_TimeDiffMeanTime              [ii][jj];
          delete hist2f_TimeDiffMeanTime2             [ii][jj];
          delete hist2f_TimeDiffMeanTimeAbs           [ii][jj];
        }
        for(int jj=0;jj<fNChanMax;++jj){
          delete hist2f_MeanTimeChanDif_Charge[ii][jj];
          delete hist2f_TimeLead50Dif_Charge[ii][jj];
        }
      }
      delete hist2f_CorrMatrix;
      delete hist2F_ChanneOccupancy;
    }
};
#endif
