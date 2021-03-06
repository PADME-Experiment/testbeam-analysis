#include"Analyse.hh"

#include<fstream>
#include<iterator>
#include<stdio.h>
#include<typeinfo>

#include "TRawEvent.hh"
#include"utlMessageBus.hh"
#include"Histos.hh"


#include"SiPM.hh"
#include"DummyChannel.hh"
#include"TerminatedChannel.hh"

#include"VCalorimeterChannel.hh"
#include"BTFCalorimeterChannel.hh"
#include"BaF2CalorimeterChannel.hh"

  void
Analyse::HWInit()
{
  //fRunNumber;
  fSignalChannels [Universe::eROCh::eB1S1    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB1S2    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB1S3    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB1S4    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB2S1    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB2S2    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB2S3    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB2S4    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB3S1    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB3S2    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB3S3    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB3S4    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB4S1    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB4S2    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB4S3    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eB4S4    ]=new SiPM                 ();
  fSignalChannels [Universe::eROCh::eBTFCalo ]=new BTFCalorimeterChannel();
  fTriggerChannels[0 ]=new TriggerChannel        ();
  fTriggerChannels[1 ]=new TriggerChannel        ();
  fTriggerChannels[2 ]=new TriggerChannel        ();
  fTriggerChannels[3 ]=new TriggerChannel        ();

  fTriggerChannels[0]->SetName("Trig1");
  fTriggerChannels[1]->SetName("Trig2");
  fTriggerChannels[2]->SetName("Trig3");
  fTriggerChannels[3]->SetName("Trig4");

  fSignalChannels [Universe::eROCh::eB1S1    ]->SetGain(4*5.15);
  fSignalChannels [Universe::eROCh::eB1S2    ]->SetGain(4*5.15);
  fSignalChannels [Universe::eROCh::eB1S3    ]->SetGain(4*5.15);
  fSignalChannels [Universe::eROCh::eB1S4    ]->SetGain(4*5.15);
  fSignalChannels [Universe::eROCh::eB2S1    ]->SetGain(4*5.15);
  fSignalChannels [Universe::eROCh::eB2S2    ]->SetGain(4*5.15);
  fSignalChannels [Universe::eROCh::eB2S3    ]->SetGain(4*5.15);
  fSignalChannels [Universe::eROCh::eB2S4    ]->SetGain(4*5.15);
  fSignalChannels [Universe::eROCh::eB3S1    ]->SetGain(4*5.15);
  fSignalChannels [Universe::eROCh::eB3S2    ]->SetGain(4*5.15);
  fSignalChannels [Universe::eROCh::eB3S3    ]->SetGain(4*5.15);
  fSignalChannels [Universe::eROCh::eB3S4    ]->SetGain(4*5.15);
  fSignalChannels [Universe::eROCh::eB4S1    ]->SetGain(4*2.31);
  fSignalChannels [Universe::eROCh::eB4S2    ]->SetGain(4*2.31);
  fSignalChannels [Universe::eROCh::eB4S3    ]->SetGain(4*2.31);
  fSignalChannels [Universe::eROCh::eB4S4    ]->SetGain(4*2.31);


}

  void
Analyse::HWDestr()
{
  for(auto it=fSignalChannels.begin();it!=fSignalChannels.end();++it)    delete it->second;
  for(auto it=fTriggerChannels.rbegin();it!=fTriggerChannels.rend();++it)delete it->second;
  fSignalChannels .clear();
  fTriggerChannels.clear();
}

  void
Analyse::FillOscCumulatives()
{
  if(!fSignalChannels[Universe::eROCh::eBTFCalo]->IsFired())return;
  static int nfilled=0;
  if(nfilled++>100000)return;
#pragma omp parallel
  for(auto sig_it=fSignalChannels.begin();sig_it!=fSignalChannels.end();++sig_it){
#pragma omp single nowait
    {
      unsigned int chan_i=int(sig_it->first);
      VPMTChannel& ch=*sig_it->second;
      fHists.hist1f_Pedestals[chan_i]->Fill(ch.GetPedestal());
      for(UShort_t s=0;s<1024;++s){
        fHists.hist2f_OscCum[chan_i]->Fill(s,ch.GetVal(s));
        fHists.hist2f_OscCumT0Fixed[chan_i]->Fill(s,ch.GetValT0Ped(s));
        if(nfilled<100) fHists.hist2f_SignalStudy[chan_i]->SetBinContent(s+1,nfilled,-ch.GetValT0Ped(s));
      }
    }
  }
  for(unsigned short t=0;t<4;++t){
    TriggerChannel& trig=*fTriggerChannels[t];
    for(UShort_t s=0;s<trig.GetNSamples();s++){
      fHists.hist1f_TrigJitter[t]->Fill(fTriggerChannels[t]->GetT0());
      fHists.hist2f_TrigCum[t]->Fill(s,fTriggerChannels[t]->GetSamp(s));
      fHists.hist2f_TrigCumT0Fixed[t]->Fill(s,fTriggerChannels[t]->GetSampT0Cor(s));
    }
  }
}


  void
Analyse::FillGraphTrends()
{
  static int graphpointnum=0;
  graphpointnum++;
  for(auto sigii_it=fSignalChannels.begin();sigii_it!=fSignalChannels.end();++sigii_it){
    VPMTChannel&chii= *sigii_it->second;
    int ii=int(sigii_it->first);
    fHists.graph_AbsSumSamp_Time[ii]->Set(graphpointnum);
    fHists.graph_RMSSamp_Time   [ii]->Set(graphpointnum);
    fHists.graph_MinSamp_Time   [ii]->Set(graphpointnum);
    fHists.graph_MaxSamp_Time   [ii]->Set(graphpointnum);
    fHists.graph_PPStab_Time    [ii]->Set(graphpointnum);
    fHists.graph_AbsSumSamp_Time[ii]->SetPoint(graphpointnum,graphpointnum,chii.GetNoiseSampAbsSum());
    fHists.graph_RMSSamp_Time   [ii]->SetPoint(graphpointnum,graphpointnum,chii.GetNoiseSampRMS());
    fHists.graph_MinSamp_Time   [ii]->SetPoint(graphpointnum,graphpointnum,chii.GetNoiseSampMin());
    fHists.graph_MaxSamp_Time   [ii]->SetPoint(graphpointnum,graphpointnum,chii.GetNoiseSampMax());
    fHists.hist1f_RMSSamp       [ii]->Fill    (                           -chii.GetNoiseSampRMS());
    fHists.graph_PPStab_Time    [ii]->SetPoint(graphpointnum,graphpointnum,chii.GetNoiseSampMax());
    fHists.hist1f_PPStab        [ii]->Fill    (                            chii.GetNoiseSampMax());
  }
}

  void
Analyse::FillTimes()
{
#pragma omp parallel
  for(auto sigii_it=fSignalChannels.begin();sigii_it!=fSignalChannels.end();++sigii_it){
#pragma omp single nowait
    {
      VPMTChannel&chii= *sigii_it->second;
      int ii=int(sigii_it->first);
      for(auto sigjj_it=std::next(sigii_it);sigjj_it!=fSignalChannels.end();++sigjj_it){
        VPMTChannel&chjj= *sigjj_it->second;
        int jj=int(sigjj_it->first);

        if(true //||false
            //&&int(chii.GetPhEAbs())+5>int(chjj.GetPhEAbs())
            //&&int(chii.GetPhEAbs())-5<int(chjj.GetPhEAbs())
            &&fSignalChannels[Universe::eROCh::eBTFCalo]->IsSinglePartBeam()
            &&chii.IsFired()
            &&chjj.IsFired()
          ){
          fHists.hist2f_PhElectrChCorAbsSinglePartBeamVetoed[ii][jj]->Fill(chii.GetPhEAbs(),chjj.GetPhEAbs());


          fHists.hist2f_PhElectrChCorFFTAbsSinglePartBeamVetoed[ii][jj]->Fill(chii.GetPhEAbsLowPass(),chjj.GetPhEAbsLowPass());
          fHists.hist2f_TimeDiffMeanTimeFFT      [ii][jj]->Fill((chii.GetTimeMeanLowPass       () - chjj.GetTimeMeanLowPass       ())/5./*ns*/,sqrt((chii.GetPhEAbsLowPass()*chii.GetPhEAbsLowPass()+chjj.GetPhEAbsLowPass()*chjj.GetPhEAbsLowPass())/2.));
          fHists.hist2f_TimeDiffMeanTimeFFTAbs   [ii][jj]->Fill((chii.GetTimeMeanAbsLowPass    () - chjj.GetTimeMeanAbsLowPass    ())/5./*ns*/,sqrt((chii.GetPhEAbsLowPass()*chii.GetPhEAbsLowPass()+chjj.GetPhEAbsLowPass()*chjj.GetPhEAbsLowPass())/2.));

          //double iijjampl=sqrt((chii.GetPhEAbs()*chii.GetPhEAbs()+chjj.GetPhEAbs()*chjj.GetPhEAbs())/2.);
          double iijjampl=(sqrt(chii.GetPhEAbs())+sqrt(chjj.GetPhEAbs()))/2.; iijjampl*=iijjampl;
          fHists.hist2f_TimeDiffMeanTime         [ii][jj]->Fill((chii.GetTimeMean              () - chjj.GetTimeMean              ())/5./*ns*/,iijjampl);
          fHists.hist2f_TimeDiffMeanTime2        [ii][jj]->Fill((chii.GetTimeMean2             () - chjj.GetTimeMean2             ())/5./*ns*/,iijjampl);
          fHists.hist2f_TimeDiffMeanTimeAbs      [ii][jj]->Fill((chii.GetTimeMeanAbs           () - chjj.GetTimeMeanAbs           ())/5./*ns*/,iijjampl);
          fHists.hist2f_TimeDiff2080LeadTrailCros[ii][jj]->Fill((chii.GetTime2080LeadTrailCross() - chjj.GetTime2080LeadTrailCross())/5./*ns*/,iijjampl);
          fHists.hist2f_TimeDiff2080LeadZeroCros [ii][jj]->Fill((chii.GetTime2080LeadZeroCross () - chjj.GetTime2080LeadZeroCross ())/5./*ns*/,iijjampl);
          fHists.hist2f_TimeDiff2080Lead50       [ii][jj]->Fill((chii.GetTime2080LeadMid       () - chjj.GetTime2080LeadMid       ())/5./*ns*/,iijjampl);
          fHists.hist2f_TimeDiffHalfMaxValue     [ii][jj]->Fill((chii.GetTimeHalfMax           () - chjj.GetTimeHalfMax           ())/5./*ns*/,iijjampl);
          fHists.hist2f_TimeDiff01MaxValue     [ii][jj]->Fill((chii.GetTime01Max           () - chjj.GetTime01Max           ())/5./*ns*/,iijjampl);
          fHists.hist2f_TimeDiff02MaxValue     [ii][jj]->Fill((chii.GetTime02Max           () - chjj.GetTime02Max           ())/5./*ns*/,iijjampl);
          fHists.hist2f_TimeDiffMaxValue         [ii][jj]->Fill((chii.GetTimeMaxVal            () - chjj.GetTimeMaxVal            ())/5./*ns*/,iijjampl);
          fHists.hist2f_TimeDiffIntegral         [ii][jj]->Fill((chii.GetTimeIntegral          () - chjj.GetTimeIntegral          ())/5./*ns*/,iijjampl);
        }
      }
    }
  }
}


  void
Analyse::FillPhEDistr()
{
#pragma omp parallel
  for(auto sigii_it=fSignalChannels.begin();sigii_it!=fSignalChannels.end();++sigii_it){
#pragma omp single nowait
    {
      VPMTChannel&chii= *sigii_it->second;
      int ii=int(sigii_it->first);
      fHists.hist1f_MaxValueDistr[ii]->Fill(chii.GetValMax());
      fHists.hist1f_MeanTimeDistribution[ii]->Fill(chii.GetTimeMean());
      fHists.hist2f_MeanTimeDistribution_Charge[ii]->Fill(chii.GetTimeMean(),chii.GetPhE());
      fHists.hist2f_MeanTimeDistributionAbs_Charge[ii]->Fill(chii.GetTimeMeanAbs(),chii.GetPhEAbs());
      fHists.hist1f_PhElectr[ii]->Fill(chii.GetPhE());
      fHists.hist1f_PhElectrAbs[ii]->Fill(chii.GetPhEAbs());
      if(fSignalChannels[Universe::eROCh::eBTFCalo]->IsSinglePartBeam()
        ){
        //fHists.hist1f_PhElectrAbsSinglePartBeam[ii]->Fill(chii.GetPhEAbs());
        fHists.hist1f_PhElectrAbsSinglePartBeam[ii]->Fill(chii.GetPhE());
      }
      if(fSignalChannels[Universe::eROCh::eBTFCalo]->IsDoublePartBeam())
        fHists.hist1f_PhElectrAbsDoublePartBeam[ii]->Fill(chii.GetPhE());
      for(auto sigjj_it=std::next(sigii_it);sigjj_it!=fSignalChannels.end();++sigjj_it){
        VPMTChannel&chjj= *sigjj_it->second;
        int jj=int(sigjj_it->first);
        fHists.hist2f_PhElectrChCor[ii][jj]->Fill(chii.GetPhE(),chjj.GetPhE());
        fHists.hist2f_PhElectrChCorAbs[ii][jj]->Fill(chii.GetPhEAbs(),chjj.GetPhEAbs());
        if(fSignalChannels[Universe::eROCh::eBTFCalo]->IsSinglePartBeam()
          ){
          fHists.hist2f_PhElectrChCorAbsSinglePartBeam[ii][jj]->Fill(chii.GetPhE(),chjj.GetPhE());
        }
      }
    }
  }
  if(fSignalChannels[Universe::eROCh::eBTFCalo]->IsSinglePartBeam()){
    double a[]={
      fSignalChannels[(Universe::eROCh) 0]->GetPhE(),
      fSignalChannels[(Universe::eROCh) 1]->GetPhE(),
      fSignalChannels[(Universe::eROCh) 2]->GetPhE(),
      fSignalChannels[(Universe::eROCh) 3]->GetPhE(),
    };
    double b[]={
      fSignalChannels[(Universe::eROCh)11]->GetPhE(),
      fSignalChannels[(Universe::eROCh)10]->GetPhE(),
      fSignalChannels[(Universe::eROCh) 9]->GetPhE(),
      fSignalChannels[(Universe::eROCh) 8]->GetPhE(),
    };
    if(
        ( // at least 3 of 4 scintillators are fired
         (fSignalChannels[(Universe::eROCh) 4]->IsFired()?1:0)+
         (fSignalChannels[(Universe::eROCh) 5]->IsFired()?1:0)+
         (fSignalChannels[(Universe::eROCh) 6]->IsFired()?1:0)+
         (fSignalChannels[(Universe::eROCh) 7]->IsFired()?1:0)
        )>3&&
        (
         (fSignalChannels[(Universe::eROCh)12]->IsFired()?1:0)+
         (fSignalChannels[(Universe::eROCh)13]->IsFired()?1:0)+
         (fSignalChannels[(Universe::eROCh)14]->IsFired()?1:0)+
         (fSignalChannels[(Universe::eROCh)15]->IsFired()?1:0)
        )>3
      ){
      int i=0;
      fHists.hist1f_lightCollectRto[i]->Fill((b[i]<1e-8?0:log(b[i]))-(a[i]<1e-8?0:log(a[i])));i++;
      fHists.hist1f_lightCollectRto[i]->Fill((b[i]<1e-8?0:log(b[i]))-(a[i]<1e-8?0:log(a[i])));i++;
      fHists.hist1f_lightCollectRto[i]->Fill((b[i]<1e-8?0:log(b[i]))-(a[i]<1e-8?0:log(a[i])));i++;
      fHists.hist1f_lightCollectRto[i]->Fill((b[i]<1e-8?0:log(b[i]))-(a[i]<1e-8?0:log(a[i])));i++;
    }
  }
}
  void
Analyse::MakeFFT()
{
  //if(
  //  )return;
  Universe& uni=Universe::GetInstance();
  static int nfilled=0;
  if( true
      &&nfilled<100
    ){
    INFO("FFT nfilled "+std::to_string(nfilled));
    nfilled++;
    for(auto sigii_it=fSignalChannels.begin();sigii_it!=fSignalChannels.end();++sigii_it){
      int ch_i=int(sigii_it->first);
      VPMTChannel& ch=*sigii_it->second;
      std::ofstream of("fft/"+uni.GetROName(ch_i)+"-"+std::to_string(nfilled));
      of<<"sig"<<std::endl;
      for(unsigned s=0;s<1024;++s){
        of<<ch.GetValT0Ped(s)<<std::endl;;
      }
      for(int cut=0;cut<512;++cut) {
        std::cout<<nfilled<<"   "<<cut<<std::endl;
        std::cout<<ch_i<<std::endl;
        of<<std::endl;
        of<<std::endl;
        ch.FFTLowPass(cut);
        of<<"f_{max}="<<int(100*(5000.*(512-cut)/1024))/100<<"MHz ("<<cut<<")"<<std::endl;
        for(unsigned s=0;s<1024;++s){
          of<<ch.GetValT0PedLowPass(s)<<std::endl;;
          fHists.hist2f_SignalStudyLowPass[ch_i]->SetBinContent(s+1,nfilled,-ch.GetValT0PedLowPass(s));
          //fHists.hist2f_PedestalsStudy    [ch_i]->SetBinContent(s+1,nfilled,-ch.GetValT0Ped(s));
        }
      }
      of.flush();
      of.close();
    }
  }
}

  void
Analyse::FillHistos()
{
  for(auto sigii_it=fSignalChannels.begin();sigii_it!=fSignalChannels.end();++sigii_it){
    int ii=int(sigii_it->first);
    if(sigii_it->second->IsFired()){
      fHists.hist2f_CorrMatrix->Fill(ii,ii);
      for(auto sigjj_it=std::next(sigii_it);sigjj_it!=fSignalChannels.end();++sigjj_it){
        if(sigjj_it->second->IsFired()){
          int jj=int(sigjj_it->first);
          fHists.hist2f_CorrMatrix->Fill(ii,jj);
          fHists.hist2f_CorrMatrix->Fill(jj,ii);
        }
      }
    }
  }



#pragma omp parallel
  for(auto sigii_it=fSignalChannels.begin();sigii_it!=fSignalChannels.end();++sigii_it){
#pragma omp single nowait
    {
      VPMTChannel&chii= *sigii_it->second;
      int ii=int(sigii_it->first);
      if(true
          &&( // at least 2 of 4 scintillators are fired
            (fSignalChannels[(Universe::eROCh) 4]->IsFired()?1:0)+
            (fSignalChannels[(Universe::eROCh) 5]->IsFired()?1:0)+
            (fSignalChannels[(Universe::eROCh) 6]->IsFired()?1:0)+
            (fSignalChannels[(Universe::eROCh) 7]->IsFired()?1:0)
            )>2
          &&(
            (fSignalChannels[(Universe::eROCh)12]->IsFired()?1:0)+
            (fSignalChannels[(Universe::eROCh)13]->IsFired()?1:0)+
            (fSignalChannels[(Universe::eROCh)14]->IsFired()?1:0)+
            (fSignalChannels[(Universe::eROCh)15]->IsFired()?1:0)
            )>2
        ){
        fHists.hist1f_PhElectrEff     [ii]->Fill(chii.     GetPhE());
        fHists.hist1f_PhElectrNoise   [ii]->Fill(chii.GetPhENoise());
        fHists.hist1f_PhElectrAbsEff  [ii]->Fill(chii.     GetPhEAbs());
        fHists.hist1f_PhElectrAbsNoise[ii]->Fill(chii.GetPhENoiseAbs());
      }
    }
  }
}

  void
Analyse::PrepareChannelsForAnal()
{
#pragma omp parallel
  for(auto sig_it=fSignalChannels.begin();sig_it!=fSignalChannels.end();++sig_it){
#pragma omp single nowait
    {
      unsigned int chan_i=int(sig_it->first);
      VPMTChannel& ch=*sig_it->second;
      ch.CalcPedestal();
      ch.SetT0(fTriggerChannels[chan_i/8]->GetT0());
      //ch.FFTLowPass(200);
      ch.CalcTimeCharge();
    }
  }
}

  void
Analyse::Process(std::string infile)
{
  //std::stringstream info;
  //info <<fNEvtToProcess<<"  "<<fNEvtProcessed;
  //INFO(info.str());
  if(fNEvtToProcess<=fNEvtProcessed){
    INFO("fNEvtToProcess limit reached. SKIP!");
    return;
  }

  TFile* fRawEv = new TFile(infile.c_str());
  TTree* tRawEv = (TTree*)fRawEv->Get("RawEvents");
  TBranch* bRawEv = tRawEv->GetBranch("RawEvent");
  TRawEvent* rawEv = new TRawEvent();
  if(fRunNumber!=int(rawEv->GetRunNumber())){
    if(fRunNumber==-1){
      fRunNumber=rawEv->GetRunNumber();
    }else{
      std::cerr<<"RunNumber changes"<<std::endl;
      return;
    }
  }

  bRawEv->SetAddress(&rawEv);

  Int_t nevt = tRawEv->GetEntries();
  //printf("TTree RawEvents contains %d events\tfilename %s\n",nevt,infile.c_str());

  // Set number of events to read
  std::cerr<<std::endl;
  HWInit();
  for(Int_t iev=0;iev<nevt&&fNEvtProcessed<fNEvtToProcess;++iev,++fNEvtProcessed){

    // Read event
    //printf("Reading event %d\n",iev);
    bRawEv->GetEntry(iev);
    //printf("Event %d read\n",iev);

    // Show event header
    UChar_t nBoards = rawEv->GetNADCBoards();
    //int curEvtNum=rawEv->GetEventNumber();
    if(iev%200==0){
      std::stringstream info;
      info
        <<"Glob("
        <<fNEvtProcessed*100/fNEvtToProcess<<"% "
        <<fNEvtProcessed                   <<"/"
        <<fNEvtToProcess                   <<") "
        <<"File("
        <<iev*100/nevt<<"% "
        <<iev           <<"/"
        <<nevt          <<") ";
      INFO(info.str());
    }


    // Loop over boards
    //for(UChar_t b=0;b<1;b++){ //nBoards
    UChar_t b=0;

    // Show board info
    TADCBoard* adcB = rawEv->ADCBoard(b);
    UChar_t nTrg = adcB->GetNADCTriggers();
    UChar_t nChn = adcB->GetNADCChannels();
    //if(verbose>2){
    //  printf("\tBoard %u Board Id %u LVDS %u Status %u GMsk 0x%1x EvtCnt %u Time %u ActMsk 0x%08x AccMsk 0x%08x #Trg %u #Chn %u\n",
    //      b,adcB->GetBoardId(),adcB->GetLVDSPattern(),adcB->GetStatus(),adcB->GetGroupMask(),adcB->GetEventCounter(),
    //      adcB->GetEventTimeTag(),adcB->GetActiveChannelMask(),adcB->GetAcceptedChannelMask(),nTrg,nChn);
    //  }

    if(nTrg!=3) { WARNING("nTrg!=3  "+std::to_string(int(nTrg))); continue;}
    if(nChn!=17){ WARNING("nChn!=17 "+std::to_string(int(nChn))); continue;}

    // Loop over triggers
#pragma omp parallel
#pragma omp  for
    for(UChar_t t=0;t<nTrg;t++){
      TADCTrigger* trg = adcB->ADCTrigger(t);
      //INFO("tring "+std::to_string(int(t)));
      fTriggerChannels[t]->SetSamples(trg->GetNSamples(),trg->GetSamplesArray());
      fTriggerChannels[t]->CalcT0();
    } //end trigger for

    //#pragma omp parallel
    //#pragma omp for
    for(auto sig_it=fSignalChannels.begin();sig_it!=fSignalChannels.end();++sig_it){
      UChar_t c=int(sig_it->first);
      if(c>nChn){ERROR("c>nChn c="+std::to_string(c));continue;}
      VPMTChannel& ch=*sig_it->second;
      TADCChannel* chn = adcB->ADCChannel(c);
      //INFO("chan "+std::to_string(int(c)));
      ch.SetSamples(chn->GetNSamples(),chn->GetSamplesArray());
    } //end channel for
    //} //end boards for




    AnalyseAndFill();


    // Clear event
    rawEv->Clear("C");

  } //end event for
  HWDestr();

  delete rawEv;
  delete bRawEv;
  delete tRawEv;

  fRawEv->Close();
  delete fRawEv;
}

  void
Analyse::Finalize()
{
}
