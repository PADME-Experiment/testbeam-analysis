#include"Histos.hh"

#include"Universe.hh"
  void
Histos::CreateHistos()
{
  const Universe& uni=Universe::GetInstance();
  std::string name, title;
  name="ChannelOccupacy"; title=name;
  hist2F_ChanneOccupancy=new TH2F(name.c_str(),title.c_str(),16,1,9,3,1,4);
  TObject* tmptobj;

  for(int ii=0;ii<fNTrigMax;++ii){
    std::stringstream chan_i_ss;
    chan_i_ss<<ii;
    name="TriggerJitter_ch_"+chan_i_ss.str(); title=name;
    tmptobj=hist1f_TrigJitter[ii]=new TH1F(name.c_str(),title.c_str(),100,-250-.5,250-.5);
    fAllObj.emplace("TrigJitter",tmptobj);

    name="TriggerCumulativeOscillogram_ch_"+chan_i_ss.str(); title=name;
    tmptobj=hist2f_TrigCum[ii]=new TH2F(name.c_str(),title.c_str(),1024,-.5,1023.5, 512,-5000,5000);
    fAllObj.emplace("TrigCumOsc",tmptobj);

    name="TriggerCumulativeOscillogramT0Fixed_ch_"+chan_i_ss.str(); title=name;
    tmptobj=hist2f_TrigCumT0Fixed[ii]=new TH2F(name.c_str(),title.c_str(),1024,-.5,1023.5, 512,-5000,5000);
    fAllObj.emplace("TrigCumOscT0",tmptobj);
  }

  for(int ii=0;ii<fNChanMax;++ii){
    std::stringstream chan_i_ss;
    chan_i_ss<<ii;
    name="CumulativeOscillogram_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    tmptobj=hist2f_OscCum[ii]=new TH2F(name.c_str(),title.c_str(),1024,-.5,1023.5, 2048,-1,.1) ;
    fAllObj.emplace("SigCumOsc",tmptobj);
    name="CumulativeOscillogramT0Fixed_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    tmptobj=hist2f_OscCumT0Fixed[ii]=new TH2F(name.c_str(),title.c_str(),1024,-.5,1023.5, 4096,-1,.1) ;
    fAllObj.emplace("SigCumOscT0",tmptobj);
    name="Pedestals_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_Pedestals[ii]=new TH1F(name.c_str(),title.c_str(),500,3500-.5,4000-.5);
    fAllObj.emplace("SigPedestals",tmptobj);
    name ="PedestalsStudy_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    tmptobj=hist2f_PedestalsStudy[ii]=new TH2F(name.c_str(),title.c_str(),1024,0-.5,1024-.5,100,-.5,100-.5);
    fAllObj.emplace("StudyPedestal",tmptobj);
    name ="SignalStudy_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    tmptobj=hist2f_SignalStudy[ii]=new TH2F(name.c_str(),title.c_str(),1024,0-.5,1024-.5,100,-.5,100-.5);
    fAllObj.emplace("StudySignal",tmptobj);
    name ="SignalStudyLowPass_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    tmptobj=hist2f_SignalStudyLowPass[ii]=new TH2F(name.c_str(),title.c_str(),1024,0-.5,1024-.5,100,-.5,100-.5);
    fAllObj.emplace("StudySignalLowPass",tmptobj);
    name="PhElectr_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_PhElectr[ii]=new TH1F(name.c_str(),title.c_str(),512,-100,1500);
    fAllObj.emplace("PhElectr",tmptobj);
    name ="PhElectrAbs_ch_"+chan_i_ss.str(); title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_PhElectrAbs[ii]=new TH1F(name.c_str(),title.c_str(),512,-100,1500);
    fAllObj.emplace("PhElectrAbs",tmptobj);

    name ="PhElectrAbsSinglePartBeam_ch_"+chan_i_ss.str(); title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_PhElectrAbsSinglePartBeam[ii]=new TH1F(name.c_str(),title.c_str(),812,-50,1350);
    fAllObj.emplace("PhElectrAbsSinglePartBeam",tmptobj);
    name ="PhElectrAbsDoublePartBeam_ch_"+chan_i_ss.str(); title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_PhElectrAbsDoublePartBeam[ii]=new TH1F(name.c_str(),title.c_str(),812,-50,1350);
    fAllObj.emplace("PhElectrAbsDoublePartBeam",tmptobj);

    name ="PhElectrFFTAbsSinglePartBeam_ch_"+chan_i_ss.str(); title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_PhElectrFFTAbsSinglePartBeam[ii]=new TH1F(name.c_str(),title.c_str(),512,-50,550);
    fAllObj.emplace("PhElectrFFTAbsSinglePartBeam",tmptobj);

    name ="PhElectrEff_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_PhElectrEff[ii]=new TH1F(name.c_str(),title.c_str(),512,-150,1400);
    fAllObj.emplace("PhElectrEff",tmptobj);
    name ="PhElectrNoise_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_PhElectrNoise[ii]=new TH1F(name.c_str(),title.c_str(),512,-150,1400);
    fAllObj.emplace("PhElectrNoise",tmptobj);

    name ="PhElectrEffAbs_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_PhElectrAbsEff[ii]=new TH1F(name.c_str(),title.c_str(),512,-50,1400);
    fAllObj.emplace("PhElectrAbsEff",tmptobj);
    name ="PhElectrNoiseAbs_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_PhElectrAbsNoise[ii]=new TH1F(name.c_str(),title.c_str(),512,-50,1400);
    fAllObj.emplace("PhElectrAbsEff",tmptobj);

    name="PhElectrT0Fix_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_PhElectrT0Fix[ii]=new TH1F(name.c_str(),title.c_str(),512,-50,400);
    fAllObj.emplace("PhElectrT0Fix",tmptobj);

    name ="MaxValueDistr_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_MaxValueDistr[ii]=new TH1F(name.c_str(),title.c_str(),512,-1,.1);
    fAllObj.emplace("MaxValueDistr",tmptobj);

    name="MeanTimeDistr_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_MeanTimeDistribution[ii]=new TH1F(name.c_str(),title.c_str(),400,400,800);
    fAllObj.emplace("MeanTimeDistr",tmptobj);


    name="AbsSumSamp_Time_ch_"+chan_i_ss.str();  title=name;tmptobj=graph_AbsSumSamp_Time[ii]=new TGraph();((TGraph*)tmptobj)->SetNameTitle(name.c_str(),title.c_str());    fAllObj.emplace("StabAbsSumSamp_Time",tmptobj);
    name="RMS_Time_ch_"+chan_i_ss.str();  title=name;tmptobj=graph_RMSSamp_Time          [ii]=new TGraph();((TGraph*)tmptobj)->SetNameTitle(name.c_str(),title.c_str());    fAllObj.emplace("StabRMS_Time",tmptobj);
    name="MinSamp_Time_ch_"+chan_i_ss.str();  title=name;tmptobj=graph_MinSamp_Time      [ii]=new TGraph();((TGraph*)tmptobj)->SetNameTitle(name.c_str(),title.c_str());    fAllObj.emplace("StabMinSamp_Time",tmptobj);
    name="MaxSamp_Time_ch_"+chan_i_ss.str();  title=name;tmptobj=graph_MaxSamp_Time      [ii]=new TGraph();((TGraph*)tmptobj)->SetNameTitle(name.c_str(),title.c_str());    fAllObj.emplace("StabMaxSamp_Time",tmptobj);

    name="RMSSamp_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_RMSSamp[ii]=new TH1F(name.c_str(),title.c_str(),4000,0,0.01);
    fAllObj.emplace("StabRMS_Time",tmptobj);

    name="PPStab_Time_ch_"+chan_i_ss.str();  title=name;tmptobj=graph_PPStab_Time      [ii]=new TGraph();((TGraph*)tmptobj)->SetNameTitle(name.c_str(),title.c_str());    fAllObj.emplace("StabPeak_Peak_Samp_Time",tmptobj);

    name="PPStab_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    tmptobj=hist1f_PPStab[ii]=new TH1F(name.c_str(),title.c_str(),500,0,0.5);
    fAllObj.emplace("StabPeak_Peak_Samp_Time",tmptobj);

    //name ="TimeMaxValue_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    //tmptobj=hist1f_TimeMaxValue             [ii]=new TH1F(name.c_str(),title.c_str(),600,0,600);
    //fAllObj.emplace("TimeMaxValue",tmptobj);
    //name ="TimeHalfMaxValue_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    //tmptobj=hist1f_TimeHalfMaxValue         [ii]=new TH1F(name.c_str(),title.c_str(),600,0,600);
    //fAllObj.emplace("TimeHalfMaxValue",tmptobj);
    //name ="Time2080LeadTrailCros_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    //tmptobj=hist1f_Time2080LeadTrailCros    [ii]=new TH1F(name.c_str(),title.c_str(),600,0,600);
    //fAllObj.emplace("Time2080LeadTrailCros",tmptobj);
    //name ="Time2080LeadZeroCros_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    //tmptobj=hist1f_Time2080LeadZeroCros     [ii]=new TH1F(name.c_str(),title.c_str(),600,0,600);
    //fAllObj.emplace("Time2080LeadZeroCros",tmptobj);
    //name ="Time2080Lead50_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii); title=name+" "+uni.GetROName(ii);
    //tmptobj=hist1f_Time2080Lead50           [ii]=new TH1F(name.c_str(),title.c_str(),600,0,600);
    //fAllObj.emplace("Time2080Lead50",tmptobj);

    //name ="TimeCor2080LeadTrailCros_2080LeadZeroCros_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    //tmptobj=hist2f_TimeCor2080LeadTrailCros_2080LeadZeroCros[ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
    //fAllObj.emplace("TimeCor2080LeadTrailCros",tmptobj);
    //name ="TimeCor2080LeadTrailCros_2080Lead50_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    //tmptobj=hist2f_TimeCor2080LeadTrailCros_2080Lead50      [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
    //fAllObj.emplace("TimeCor2080LeadTrailCros",tmptobj);
    //name ="TimeCor2080LeadTrailCros_MeanTime_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    //tmptobj=hist2f_TimeCor2080LeadTrailCros_MeanTime        [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
    //fAllObj.emplace("TimeCor2080LeadTrailCros",tmptobj);
    //name ="TimeCor2080LeadTrailCros_MaxValue_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    //tmptobj=hist2f_TimeCor2080LeadTrailCros_MaxValue        [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
    //fAllObj.emplace("TimeCor2080LeadTrailCros",tmptobj);
    //name ="TimeCor2080LeadTrailCros_HalfMaxValue_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    //tmptobj=hist2f_TimeCor2080LeadTrailCros_HalfMaxValue    [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
    //fAllObj.emplace("TimeCor2080LeadTrailCros",tmptobj);
    //name ="TimeCorMaxValue_HalfMaxValue_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    //tmptobj=hist2f_TimeCorMaxValue_HalfMaxValue             [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
    //fAllObj.emplace("TimeCorMaxValue",tmptobj);
    //name ="TimeCorMeanTime_MaxValue_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    //tmptobj=hist2f_TimeCorMeanTime_MaxValue                 [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
    //fAllObj.emplace("TimeCorMeanTime",tmptobj);
    //name ="TimeCorMeanTime_HalfMaxValue_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    //tmptobj=hist2f_TimeCorMeanTime_HalfMaxValue             [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
    //fAllObj.emplace("TimeCorMeanTime",tmptobj);
    //name ="TimeCorMeanTime_2080Lead50_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    //tmptobj=hist2f_TimeCorMeanTime_2080Lead50               [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
    //fAllObj.emplace("TimeCorMeanTime",tmptobj);
    //name ="TimeCorMeanTime_2080LeadZeroCros_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    //tmptobj=hist2f_TimeCorMeanTime_2080LeadZeroCros        [ii]=new TH2F(name.c_str(),title.c_str(),600,0,600,600,0,600);
    //fAllObj.emplace("TimeCorMeanTime",tmptobj);

    name="MeanTimeDistr_Charge_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    tmptobj=hist2f_MeanTimeDistribution_Charge[ii]=new TH2F(name.c_str(),title.c_str(),512,0-.5,1024-.5,500,-50,800);
    fAllObj.emplace("MeanTimeDistr_Charge",tmptobj);
    name="MeanTimeDistrAbs_Charge_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
    tmptobj=hist2f_MeanTimeDistributionAbs_Charge[ii]=new TH2F(name.c_str(),title.c_str(),512,0-.5,1024-.5,600,-50,800);
    fAllObj.emplace("MeanTimeDistrAbs_Charge",tmptobj);

    for(int jj=ii+1;jj<fNChanMax;++jj){ //TODO
      std::stringstream chan_j_ss;
      chan_j_ss<<jj;
      name="PhElectrChCor_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj);
      tmptobj=hist2f_PhElectrChCor[ii][jj]=new TH2F(name.c_str(),title.c_str(),512,-50,1400,512,-50,1400);
      fAllObj.emplace("PhElectrChCor",tmptobj);
      name="PhElectrChCorAbs_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj);
      tmptobj=hist2f_PhElectrChCorAbs[ii][jj]=new TH2F(name.c_str(),title.c_str(),512,-50,1400,512,-50,1400);
      fAllObj.emplace("PhElectrChCorAbs",tmptobj);
      name="PhElectrChCorAbsSinglePartBeam_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj);
      tmptobj=hist2f_PhElectrChCorAbsSinglePartBeam[ii][jj]=new TH2F(name.c_str(),title.c_str(),512,-50,1400,512,-50,1400);
      fAllObj.emplace("PhElectrChCorAbsSinglePartBeam",tmptobj);
      name="PhElectrChCorAbsSinglePartBeamVetoed_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj);
      tmptobj=hist2f_PhElectrChCorAbsSinglePartBeamVetoed[ii][jj]=new TH2F(name.c_str(),title.c_str(),512,-50,400,1512,-50,1400);
      fAllObj.emplace("PhElectrChCorAbsSinglePartBeamVetoed",tmptobj);

      name="PhElectrChCorFFTAbsSinglePartBeamVetoed_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj);
      tmptobj=hist2f_PhElectrChCorFFTAbsSinglePartBeamVetoed[ii][jj]=new TH2F(name.c_str(),title.c_str(),512,-50,1400,512,-50,1400);
      fAllObj.emplace("PhElectrChCorFFTAbsSinglePartBeamVetoed",tmptobj);

      name="MeanTimeChanDif_"+chan_i_ss.str()+"-"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj);
      tmptobj=hist1f_MeanTimeChanDif[ii][jj]=new TH1F(name.c_str(),title.c_str(),1000,-400,400);
      fAllObj.emplace("MeanTimeChanDif",tmptobj);

      std::string lab=";ns;nPhe(13)/10";

      name ="TimeDiffMaxValue_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj)+lab;
      tmptobj=hist2f_TimeDiffMaxValue  [ii][jj]       =new TH2F(name.c_str(),title.c_str(),640,-80-.25,80-.25,350,-20,1000);
      fAllObj.emplace("TimeDiffMaxValue",tmptobj);

      name ="TimeDiffHalfMaxValue_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj)+lab;
      tmptobj=hist2f_TimeDiffHalfMaxValue   [ii][jj]  =new TH2F(name.c_str(),title.c_str(),640,-80-.25,80-.25,350,-20,1000);
      fAllObj.emplace("TimeDiffHalfMaxValue",tmptobj);

      name ="TimeDiff01MaxValue_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj)+lab;
      tmptobj=hist2f_TimeDiff01MaxValue   [ii][jj]  =new TH2F(name.c_str(),title.c_str(),640,-80-.25,80-.25,350,-20,1000);
      fAllObj.emplace("TimeDiff01MaxValue",tmptobj);
      name ="TimeDiff02MaxValue_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj)+lab;
      tmptobj=hist2f_TimeDiff02MaxValue   [ii][jj]  =new TH2F(name.c_str(),title.c_str(),640,-80-.25,80-.25,350,-20,1000);
      fAllObj.emplace("TimeDiff02MaxValue",tmptobj);

      name ="TimeDiff2080LeadTrailCros_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj)+lab;
      tmptobj=hist2f_TimeDiff2080LeadTrailCros[ii][jj]=new TH2F(name.c_str(),title.c_str(),640,-80-.25,80-.25,350,-20,1000);
      fAllObj.emplace("TimeDiff2080LeadTrailCros",tmptobj);
      name ="TimeDiff2080LeadZeroCros_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj)+lab;
      tmptobj=hist2f_TimeDiff2080LeadZeroCros[ii][jj] =new TH2F(name.c_str(),title.c_str(),640,-80-.25,80-.25,350,-20,1000);
      fAllObj.emplace("TimeDiff2080LeadZeroCros",tmptobj);
      name ="TimeDiff2080Lead50_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj)+lab;
      tmptobj=hist2f_TimeDiff2080Lead50   [ii][jj]    =new TH2F(name.c_str(),title.c_str(),640,-80-.25,80-.25,350,-20,1000);
      fAllObj.emplace("TimeDiff2080Lead50",tmptobj);
      name ="TimeDiffMeanTime_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj)+lab;
      tmptobj=hist2f_TimeDiffMeanTime      [ii][jj]   =new TH2F(name.c_str(),title.c_str(),640,-80-.25,80-.25,350,-20,1000);
      fAllObj.emplace("TimeDiffMeanTime",tmptobj);
      name ="TimeDiffMeanTime2_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj)+lab;
      tmptobj=hist2f_TimeDiffMeanTime2     [ii][jj]   =new TH2F(name.c_str(),title.c_str(),640,-80-.25,80-.25,350,-20,1000);
      fAllObj.emplace("TimeDiffMeanTime2",tmptobj);
      name ="TimeDiffMeanTimeAbs_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj)+lab;
      tmptobj=hist2f_TimeDiffMeanTimeAbs     [ii][jj]   =new TH2F(name.c_str(),title.c_str(),640,-80-.25,80-.25,350,-20,1000);
      fAllObj.emplace("TimeDiffMeanTimeAbs",tmptobj);

      name ="TimeDiffMeanTimeFFT_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj)+lab;
      tmptobj=hist2f_TimeDiffMeanTimeFFT     [ii][jj]   =new TH2F(name.c_str(),title.c_str(),640,-80-.25,80-.25,350,-20,1000);
      fAllObj.emplace("TimeDiffMeanTimeFFT",tmptobj);
      name ="TimeDiffMeanTimeFFTAbs_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj)+lab;
      tmptobj=hist2f_TimeDiffMeanTimeFFTAbs     [ii][jj]   =new TH2F(name.c_str(),title.c_str(),640,-80-.25,80-.25,350,-20,1000);
      fAllObj.emplace("TimeDiffMeanTimeFFTAbs",tmptobj);

      name=         "TimeDiffIntegral_"+chan_i_ss.str()+"_"+chan_j_ss.str(); title=name+uni.GetROName(ii)+" "+uni.GetROName(jj)+lab;
      tmptobj=hist2f_TimeDiffIntegral[ii][jj]   =new TH2F(name.c_str(),title.c_str(),640,-80-.25,80-.25,350,-20,1000);
      fAllObj.emplace("TimeDiffIntegral",tmptobj);




    }
  }
  name ="lightCollectionRTO_0_11"; title=name+";ln(FibSc)-ln(Scint)";
  tmptobj=hist1f_lightCollectRto[0]=new TH1F(name.c_str(),title.c_str(),500,-10,10);
  fAllObj.emplace("LightCollectionRatio",tmptobj);
  name ="lightCollectionRTO_1_10"; title=name+";ln(FibSc)-ln(Scint)";
  tmptobj=hist1f_lightCollectRto[1]=new TH1F(name.c_str(),title.c_str(),500,-10,10);
  fAllObj.emplace("LightCollectionRatio",tmptobj);
  name ="lightCollectionRTO_2_9"; title=name+";ln(FibSc)-ln(Scint)";
  tmptobj=hist1f_lightCollectRto[2]=new TH1F(name.c_str(),title.c_str(),500,-10,10);
  fAllObj.emplace("LightCollectionRatio",tmptobj);
  name ="lightCollectionRTO_3_8"; title=name+";ln(FibSc)-ln(Scint)";
  tmptobj=hist1f_lightCollectRto[3]=new TH1F(name.c_str(),title.c_str(),500,-10,10);
  fAllObj.emplace("LightCollectionRatio",tmptobj);





  name ="CorrMatrix"; title=name;
  tmptobj=hist2f_CorrMatrix=new TH2F(name.c_str(),title.c_str(),fNChanMax,-.5,fNChanMax-.5,fNChanMax,-.5,fNChanMax-.5);
  fAllObj.emplace("",tmptobj);

}
