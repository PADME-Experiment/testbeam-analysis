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
//  fSignalChannels [Universe::eROCh::eB5S1    ]=new SiPM                 ();
//  fSignalChannels [Universe::eROCh::eB5S2    ]=new SiPM                 ();
//  fSignalChannels [Universe::eROCh::eB5S3    ]=new SiPM                 ();
//  fSignalChannels [Universe::eROCh::eB5S4    ]=new SiPM                 ();
  fTriggerChannels[0 ]=new TriggerChannel        ();
  fTriggerChannels[1 ]=new TriggerChannel        ();
  fTriggerChannels[2 ]=new TriggerChannel        ();
  fTriggerChannels[3 ]=new TriggerChannel        ();

  fTriggerChannels[0]->SetName("Trig1");
  fTriggerChannels[1]->SetName("Trig2");
  fTriggerChannels[2]->SetName("Trig3");
  fTriggerChannels[3]->SetName("Trig4");
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
Analyse::FillOscCumulatives(){
  //if(
  //    !fSignalChannels[Universe::eROCh::eCalo]->IsSinglePartBeam()
  //    ||fSignalChannels[Universe::eROCh::eH3]->IsFired() //VTU
  //    ||fSignalChannels[Universe::eROCh::eY4]->IsFired()
  //    ||fSignalChannels[Universe::eROCh::eH5]->IsFired() //VBU
  //    ||fSignalChannels[Universe::eROCh::eX5]->IsFired()
  //    ||fSignalChannels[Universe::eROCh::eH2]->IsFired() //VTD
  //    ||fSignalChannels[Universe::eROCh::eY5]->IsFired()
  //    ||fSignalChannels[Universe::eROCh::eH1]->IsFired() //VBD
  //    ||fSignalChannels[Universe::eROCh::eX4]->IsFired()
  //  )return;
  static int nfilled=0;
  //if(nfilled++>1000)return;
#pragma omp parallel
  for(auto sig_it=fSignalChannels.begin();sig_it!=fSignalChannels.end();++sig_it){
#pragma omp single nowait
    {
      unsigned int chan_i=int(sig_it->first);
      VPMTChannel& ch=*sig_it->second;
      fHists.hist1f_Pedestals[chan_i]->Fill(ch.GetPedestal());
      for(UShort_t s=0;s<1024;s++){
        fHists.hist2f_OscCum[chan_i]->Fill(s,ch.GetVal(s));
        fHists.hist2f_OscCumT0Fixed[chan_i]->Fill(s,ch.GetValT0Ped(s));
        if(nfilled<100)
          fHists.hist2f_SignalStudy       [chan_i]->SetBinContent(s+1,nfilled,-ch.GetValT0Ped(s));
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
      fHists.graph_AbsSumSamp_Time[ii]->SetPoint(graphpointnum,graphpointnum,chii.GetAllSampAbsSum());
      fHists.graph_RMSSamp_Time   [ii]->SetPoint(graphpointnum,graphpointnum,chii.GetAllSampRMS());
      fHists.graph_MinSamp_Time   [ii]->SetPoint(graphpointnum,graphpointnum,chii.GetAllSampMin());
      fHists.graph_MaxSamp_Time   [ii]->SetPoint(graphpointnum,graphpointnum,chii.GetAllSampMax());
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

        if(true||true
            //&&int(chii.GetPhEAbs())/5==int(chjj.GetPhEAbs())/5
            &&int(chii.GetPhEAbs())+5>int(chjj.GetPhEAbs())
            &&int(chii.GetPhEAbs())-5<int(chjj.GetPhEAbs())
            //&&fSignalChannels[Universe::eROCh::eCalo]->IsSinglePartBeam()
            //&&!fSignalChannels[Universe::eROCh::eH3]->IsFired() //VTU
            //&&!fSignalChannels[Universe::eROCh::eY4]->IsFired()
            //&&!fSignalChannels[Universe::eROCh::eH5]->IsFired() //VBU
            //&&!fSignalChannels[Universe::eROCh::eX5]->IsFired()
            //&&!fSignalChannels[Universe::eROCh::eH2]->IsFired() //VTD
            //&&!fSignalChannels[Universe::eROCh::eY5]->IsFired()
            //&&!fSignalChannels[Universe::eROCh::eH1]->IsFired() //VBD
            //&&!fSignalChannels[Universe::eROCh::eX4]->IsFired()
            &&chii.IsFired()
            &&chjj.IsFired()
          ){
          fHists.hist2f_PhElectrChCorAbsSinglePartBeamVetoed[ii][jj]->Fill(chii.GetPhEAbs(),chjj.GetPhEAbs());

          fHists.hist2f_PhElectrChCorFFTAbsSinglePartBeamVetoed[ii][jj]->Fill(chii.GetPhEAbsLowPass(),chjj.GetPhEAbsLowPass());
          fHists.hist2f_TimeDiffMeanTimeFFT      [ii][jj]->Fill((chii.GetTimeMeanLowPass       () - chjj.GetTimeMeanLowPass       ())/5./*ns*/,sqrt(chii.GetPhEAbsLowPass()*chii.GetPhEAbsLowPass()+chjj.GetPhEAbsLowPass()*chjj.GetPhEAbsLowPass()));
          fHists.hist2f_TimeDiffMeanTimeFFTAbs   [ii][jj]->Fill((chii.GetTimeMeanAbsLowPass    () - chjj.GetTimeMeanAbsLowPass    ())/5./*ns*/,sqrt(chii.GetPhEAbsLowPass()*chii.GetPhEAbsLowPass()+chjj.GetPhEAbsLowPass()*chjj.GetPhEAbsLowPass()));

          fHists.hist2f_TimeDiffMeanTime         [ii][jj]->Fill((chii.GetTimeMean              () - chjj.GetTimeMean              ())/5./*ns*/,sqrt(chii.GetPhEAbs()*chii.GetPhEAbs()+chjj.GetPhEAbs()*chjj.GetPhEAbs()));
          fHists.hist2f_TimeDiffMeanTime2        [ii][jj]->Fill((chii.GetTimeMean2             () - chjj.GetTimeMean2             ())/5./*ns*/,sqrt(chii.GetPhEAbs()*chii.GetPhEAbs()+chjj.GetPhEAbs()*chjj.GetPhEAbs()));
          fHists.hist2f_TimeDiffMeanTimeAbs      [ii][jj]->Fill((chii.GetTimeMeanAbs           () - chjj.GetTimeMeanAbs           ())/5./*ns*/,sqrt(chii.GetPhEAbs()*chii.GetPhEAbs()+chjj.GetPhEAbs()*chjj.GetPhEAbs()));
          fHists.hist2f_TimeDiff2080LeadTrailCros[ii][jj]->Fill((chii.GetTime2080LeadTrailCross() - chjj.GetTime2080LeadTrailCross())/5./*ns*/,sqrt(chii.GetPhEAbs()*chii.GetPhEAbs()+chjj.GetPhEAbs()*chjj.GetPhEAbs()));
          fHists.hist2f_TimeDiff2080LeadZeroCros [ii][jj]->Fill((chii.GetTime2080LeadZeroCross () - chjj.GetTime2080LeadZeroCross ())/5./*ns*/,sqrt(chii.GetPhEAbs()*chii.GetPhEAbs()+chjj.GetPhEAbs()*chjj.GetPhEAbs()));
          fHists.hist2f_TimeDiff2080Lead50       [ii][jj]->Fill((chii.GetTime2080LeadMid       () - chjj.GetTime2080LeadMid       ())/5./*ns*/,sqrt(chii.GetPhEAbs()*chii.GetPhEAbs()+chjj.GetPhEAbs()*chjj.GetPhEAbs()));
          fHists.hist2f_TimeDiffHalfMaxValue     [ii][jj]->Fill((chii.GetTimeHalfMax           () - chjj.GetTimeHalfMax           ())/5./*ns*/,sqrt(chii.GetPhEAbs()*chii.GetPhEAbs()+chjj.GetPhEAbs()*chjj.GetPhEAbs()));
          fHists.hist2f_TimeDiffMaxValue         [ii][jj]->Fill((chii.GetTimeMaxVal            () - chjj.GetTimeMaxVal            ())/5./*ns*/,sqrt(chii.GetPhEAbs()*chii.GetPhEAbs()+chjj.GetPhEAbs()*chjj.GetPhEAbs()));
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
      if(true
          //&&fSignalChannels[Universe::eROCh::eCalo]->IsSinglePartBeam()
        ){
        fHists.hist1f_PhElectrAbsSinglePartBeam[ii]->Fill(chii.GetPhEAbs());
      }
      for(auto sigjj_it=std::next(sigii_it);sigjj_it!=fSignalChannels.end();++sigjj_it){
        VPMTChannel&chjj= *sigjj_it->second;
        int jj=int(sigjj_it->first);
        fHists.hist2f_PhElectrChCor[ii][jj]->Fill(chii.GetPhE(),chjj.GetPhE());
        fHists.hist2f_PhElectrChCorAbs[ii][jj]->Fill(chii.GetPhEAbs(),chjj.GetPhEAbs());
        if(true
            //&&fSignalChannels[Universe::eROCh::eCalo]->IsSinglePartBeam()
          ){
          fHists.hist2f_PhElectrChCorAbsSinglePartBeam[ii][jj]->Fill(chii.GetPhEAbs(),chjj.GetPhEAbs());
        }
      }
    }
  }
}
  void
Analyse::MakeFFT()
{
  //if(
  //    !fSignalChannels[Universe::eROCh::eCalo]->IsSinglePartBeam()
  //    ||fSignalChannels[Universe::eROCh::eH3]->IsFired() //VTU
  //    ||fSignalChannels[Universe::eROCh::eY4]->IsFired()
  //    ||fSignalChannels[Universe::eROCh::eH5]->IsFired() //VBU
  //    ||fSignalChannels[Universe::eROCh::eX5]->IsFired()
  //    ||fSignalChannels[Universe::eROCh::eH2]->IsFired() //VTD
  //    ||fSignalChannels[Universe::eROCh::eY5]->IsFired()
  //    ||fSignalChannels[Universe::eROCh::eH1]->IsFired() //VBD
  //    ||fSignalChannels[Universe::eROCh::eX4]->IsFired()
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
    if(sigii_it->second->IsFired())
      for(auto sigjj_it=std::next(sigii_it);sigjj_it!=fSignalChannels.end();++sigjj_it){
        if(sigjj_it->second->IsFired()){
          int jj=int(sigjj_it->first);
          fHists.hist2f_CorrMatrix->Fill(ii,jj);
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
          //&&fSignalChannels[Universe::eROCh::eCalo]->IsSinglePartBeam()
          //&&!fSignalChannels[Universe::eROCh::eH3]->IsFired() //VTU
          //&&!fSignalChannels[Universe::eROCh::eY4]->IsFired()
          //&&!fSignalChannels[Universe::eROCh::eH5]->IsFired() //VBU
          //&&!fSignalChannels[Universe::eROCh::eX5]->IsFired()
          //&&!fSignalChannels[Universe::eROCh::eH2]->IsFired() //VTD
          //&&!fSignalChannels[Universe::eROCh::eY5]->IsFired()
          //&&!fSignalChannels[Universe::eROCh::eH1]->IsFired() //VBD
          //&&!fSignalChannels[Universe::eROCh::eX4]->IsFired()

          //&&(ii==int(Universe::eROCh::eX1)||ii==int(Universe::eROCh::eH4)||//D2
          //  (fSignalChannels[Universe::eROCh::eX1]->IsFired()&&
          //   fSignalChannels[Universe::eROCh::eH4]->IsFired()))
          //&&(ii==int(Universe::eROCh::eX6)||ii==int(Universe::eROCh::eH7)||//D4
          //  (fSignalChannels[Universe::eROCh::eX6]->IsFired()&&
          //   fSignalChannels[Universe::eROCh::eH7]->IsFired()))
          //&&(ii==int(Universe::eROCh::eX3)||ii==int(Universe::eROCh::eH6)||//D6
          //  (fSignalChannels[Universe::eROCh::eX3]->IsFired()&&
          //   fSignalChannels[Universe::eROCh::eH6]->IsFired()))
          //&&(ii==int(Universe::eROCh::eX8)||ii==int(Universe::eROCh::eH8)||//D8
          //  (fSignalChannels[Universe::eROCh::eX8]->IsFired()&&
          //   fSignalChannels[Universe::eROCh::eH8]->IsFired()))

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
      ch.FFTLowPass(200);
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
