#include"Analyse.hh"

#include<fstream>
#include<iterator>
#include<stdio.h>
#include<typeinfo>

#include "TRawEvent.hh"
#include"utlMessageBus.hh"
#include"Histos.hh"


#include"H9500.hh"
#include"R6427.hh"
#include"DummyChannel.hh"
#include"TerminatedChannel.hh"

#include"VCalorimeterChannel.hh"
#include"BTFCalorimeterChannel.hh"
#include"BaF2CalorimeterChannel.hh"

  void
Analyse::LinksNames()
{
  fLinkRO2DetCh[eROCh::eX1    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX2    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX3    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX4    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX5    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX6    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX7    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eX8    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY1    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY2    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY3    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY4    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY5    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY6    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY7    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eY8    ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eH1    ]=eDetCh::eVBD;
  fLinkRO2DetCh[eROCh::eH2    ]=eDetCh::eVTD;
  fLinkRO2DetCh[eROCh::eH3    ]=eDetCh::eVTU;
  fLinkRO2DetCh[eROCh::eH4    ]=eDetCh::eD2;
  fLinkRO2DetCh[eROCh::eH5    ]=eDetCh::eVBU;
  fLinkRO2DetCh[eROCh::eH6    ]=eDetCh::eD6;
  fLinkRO2DetCh[eROCh::eH7    ]=eDetCh::eD4;
  fLinkRO2DetCh[eROCh::eH8    ]=eDetCh::eD8;
  fLinkRO2DetCh[eROCh::eCalo  ]=eDetCh::eCalo;
  fLinkRO2DetCh[eROCh::eTerm  ]=eDetCh::NC;
  fLinkRO2DetCh[eROCh::eAntena]=eDetCh::NC;

  fROChNames[eROCh::eX1    ]="00_X1";
  fROChNames[eROCh::eX2    ]="01_X2";
  fROChNames[eROCh::eX3    ]="02_X3";
  fROChNames[eROCh::eX4    ]="03_X4";
  fROChNames[eROCh::eX5    ]="04_X5";
  fROChNames[eROCh::eX6    ]="05_X6";
  fROChNames[eROCh::eX7    ]="06_X7";
  fROChNames[eROCh::eX8    ]="07_X8_D1Al";
  fROChNames[eROCh::eY1    ]="08_Y1_D2";
  fROChNames[eROCh::eY2    ]="09_Y2";
  fROChNames[eROCh::eY3    ]="10_Y3";
  fROChNames[eROCh::eY4    ]="11_Y4";
  fROChNames[eROCh::eY5    ]="12_Y5";
  fROChNames[eROCh::eY6    ]="13_Y6_D4";
  fROChNames[eROCh::eY7    ]="14_Y7";
  fROChNames[eROCh::eY8    ]="15_Y8";
  fROChNames[eROCh::eH1    ]="16_H1";
  fROChNames[eROCh::eH2    ]="17_H2";
  fROChNames[eROCh::eH3    ]="18_H3";
  fROChNames[eROCh::eH4    ]="19_H4";
  fROChNames[eROCh::eH5    ]="20_H5";
  fROChNames[eROCh::eH6    ]="21_H6";
  fROChNames[eROCh::eH7    ]="22_H7";
  fROChNames[eROCh::eH8    ]="23_H8";
  fROChNames[eROCh::eCalo  ]="Calorimeter";
  fROChNames[eROCh::eTerm  ]="Terminated";
  fROChNames[eROCh::eAntena]="Antena";

  for(auto it=fLinkRO2DetCh.begin();it!=fLinkRO2DetCh.end();++it){
    fLinkDet2ROCh.emplace(it->second,it->first);
  }
  //fROChNames
  //fDetChNames

}
  void
Analyse::HWInit()
{
  //fRunNumber;
  fSignalChannels [eROCh::eX1    ]=new H9500                 ();
  fSignalChannels [eROCh::eX2    ]=new H9500                 ();
  fSignalChannels [eROCh::eX3    ]=new H9500                 ();
  fSignalChannels [eROCh::eX4    ]=new H9500                 ();
  fSignalChannels [eROCh::eX5    ]=new H9500                 ();
  fSignalChannels [eROCh::eX6    ]=new H9500                 ();
  fSignalChannels [eROCh::eX7    ]=new H9500                 ();
  fSignalChannels [eROCh::eX8    ]=new H9500                 ();
  fSignalChannels [eROCh::eY1    ]=new H9500                 ();
  fSignalChannels [eROCh::eY2    ]=new H9500                 ();
  fSignalChannels [eROCh::eY3    ]=new H9500                 ();
  fSignalChannels [eROCh::eY4    ]=new H9500                 ();
  fSignalChannels [eROCh::eY5    ]=new H9500                 ();
  fSignalChannels [eROCh::eY6    ]=new H9500                 ();
  fSignalChannels [eROCh::eY7    ]=new H9500                 ();
  fSignalChannels [eROCh::eY8    ]=new H9500                 ();
  fSignalChannels [eROCh::eH1    ]=new R6427                 ();
  fSignalChannels [eROCh::eH2    ]=new R6427                 ();
  fSignalChannels [eROCh::eH3    ]=new R6427                 ();
  fSignalChannels [eROCh::eH4    ]=new R6427                 ();
  fSignalChannels [eROCh::eH5    ]=new R6427                 ();
  fSignalChannels [eROCh::eH6    ]=new R6427                 ();
  fSignalChannels [eROCh::eH7    ]=new R6427                 ();
  fSignalChannels [eROCh::eH8    ]=new R6427                 ();
  fSignalChannels [eROCh::eCalo  ]=new BTFCalorimeterChannel();
  //fSignalChannels [eROCh::eTerm  ]=new TerminatedChannel     ();
  //fSignalChannels [eROCh::eAntena]=new DummyChannel          ();
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

        if(true
            &&int(chii.GetPhEAbs())/5==int(chjj.GetPhEAbs())/5
            &&fSignalChannels[eROCh::eCalo]->HasOnePhEExact()
            //&&!fSignalChannels[eROCh::eVTU]->IsFired()
            //&&!fSignalChannels[eROCh::eVTD]->IsFired()
            //&&!fSignalChannels[eROCh::eVBU]->IsFired()
            //&&!fSignalChannels[eROCh::eVBD]->IsFired()
            //&&sigii.IsFired()
            //&&sigjj.IsFired()
          ){
          fHists.hist2f_TimeDiffMeanTime         [ii][jj]->Fill((chii.GetTimeMean              () - chjj.GetTimeMean              ())/5./*ns*/,sqrt(chii.GetPhE()*chii.GetPhE()+chjj.GetPhE()*chjj.GetPhE()));
          fHists.hist2f_TimeDiffMeanTime2        [ii][jj]->Fill((chii.GetTimeMean2             () - chjj.GetTimeMean2             ())/5./*ns*/,sqrt(chii.GetPhE()*chii.GetPhE()+chjj.GetPhE()*chjj.GetPhE()));
          fHists.hist2f_TimeDiffMeanTimeAbs      [ii][jj]->Fill((chii.GetTimeMeanAbs           () - chjj.GetTimeMeanAbs           ())/5./*ns*/,sqrt(chii.GetPhE()*chii.GetPhE()+chjj.GetPhE()*chjj.GetPhE()));
          fHists.hist2f_TimeDiff2080LeadTrailCros[ii][jj]->Fill((chii.GetTime2080LeadTrailCross() - chjj.GetTime2080LeadTrailCross())/5./*ns*/,sqrt(chii.GetPhE()*chii.GetPhE()+chjj.GetPhE()*chjj.GetPhE()));
          fHists.hist2f_TimeDiff2080LeadZeroCros [ii][jj]->Fill((chii.GetTime2080LeadZeroCross () - chjj.GetTime2080LeadZeroCross ())/5./*ns*/,sqrt(chii.GetPhE()*chii.GetPhE()+chjj.GetPhE()*chjj.GetPhE()));
          fHists.hist2f_TimeDiff2080Lead50       [ii][jj]->Fill((chii.GetTime2080LeadMid       () - chjj.GetTime2080LeadMid       ())/5./*ns*/,sqrt(chii.GetPhE()*chii.GetPhE()+chjj.GetPhE()*chjj.GetPhE()));
          fHists.hist2f_TimeDiffHalfMaxValue     [ii][jj]->Fill((chii.GetTimeHalfMax           () - chjj.GetTimeHalfMax           ())/5./*ns*/,sqrt(chii.GetPhE()*chii.GetPhE()+chjj.GetPhE()*chjj.GetPhE()));
          fHists.hist2f_TimeDiffMaxValue         [ii][jj]->Fill((chii.GetTimeMaxVal            () - chjj.GetTimeMaxVal            ())/5./*ns*/,sqrt(chii.GetPhE()*chii.GetPhE()+chjj.GetPhE()*chjj.GetPhE()));
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
          fHists.hist1f_PhElectr[ii]->Fill(chii.GetPhE());
          fHists.hist1f_PhElectrAbs[ii]->Fill(chii.GetPhEAbs());
          for(auto sigjj_it=std::next(sigii_it);sigjj_it!=fSignalChannels.end();++sigjj_it){
            VPMTChannel&chjj= *sigjj_it->second;
            int jj=int(sigjj_it->first);
            fHists.hist2f_PhElectrChCor[ii][jj]->Fill(chii.GetPhE(),chjj.GetPhE());
            //fHists.hist2f_PhElectrChCorT0Fix[ii][jj]->Fill(pheallchT0Fix[ii],pheallchT0Fix[jj]);
          }
        }
      }
    }
  void
    Analyse::MakeFFT()
    {
      static int nfilled=0;
      if( true
          //&&chan[16].HasOnePhEExact()
          &&nfilled<0//100
        ){
        nfilled++;
        for(auto sigii_it=fSignalChannels.begin();sigii_it!=fSignalChannels.end();++sigii_it){
          int ch_i=int(sigii_it->first);
          VPMTChannel& ch=*sigii_it->second;
          std::ofstream of("fft/"+ch.GetName()+"-"+std::to_string(nfilled));
          of<<"sig"<<std::endl;
          for(unsigned s=0;s<1024;++s){
            of<<ch.GetValT0Ped(s)<<std::endl;;
          }
          for(int cut=0;cut<512;++cut){
            std::cout<<nfilled<<"   "<<cut<<std::endl;
            std::cout<<ch_i<<std::endl;
            of<<std::endl;
            of<<std::endl;
            ch.FFTLowPass(cut);
            of<<"f_{max}="<<int(100*(5000.*(512-cut)/1024))/100<<"MHz ("<<cut<<")"<<std::endl;
            for(unsigned s=0;s<1024;++s){
              of<<ch.GetValT0PedLowPass(s)<<std::endl;;
              //fHists.hist2f_SignalStudy       [ch_i]->SetBinContent(s+1,nfilled,-ch.GetValT0Ped(s));
              //fHists.hist2f_SignalStudyLowPass[ch_i]->SetBinContent(s+1,nfilled,-ch.GetValT0PedLowPass(s));
              //fHists.hist2f_PedestalsStudy[ch_i]->SetBinContent(s+1,nfilled,-chan[ch_i].GetValT0Ped(s));
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







      //#pragma omp parallel
      //#pragma omp  for
      //  for(int ch_i=8;ch_i<16;++ch_i){
      //    if(
      //        chan[16].HasOnePhEExact()&&
      //        (ch_i== 8||chan[ 8].IsFired())       &&
      //        (ch_i== 9||chan[ 9].IsFired())       &&
      //        (ch_i==10||chan[10].IsFired())       &&
      //        (ch_i==11||chan[11].IsFired())       &&
      //        (ch_i==12||chan[12].IsFired())       &&
      //        (ch_i==13||chan[13].IsFired())       &&
      //        (ch_i==14||chan[14].IsFired())       &&
      //        (ch_i==15||chan[15].IsFired())
      //      ){
      //      fHists.hist1f_PhElectrEff  [ch_i]->Fill(chan[ch_i].     GetPhE());
      //      fHists.hist1f_PhElectrNoise[ch_i]->Fill(chan[ch_i].GetPhENoise());
      //      fHists.hist1f_PhElectrAbsEff  [ch_i]->Fill(chan[ch_i].     GetPhEAbs());
      //      fHists.hist1f_PhElectrAbsNoise[ch_i]->Fill(chan[ch_i].GetPhENoiseAbs());
      //    }
      //  }
      //
      //
      //
      //
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
          ch.CalcTimeCharge();
        }
      }
    }
  void
    Analyse::Process(std::string infile)
    {
      std::stringstream info;
      info <<fNEvtToProcess<<"  "<<fNEvtProcessed;
      INFO(info.str());
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
      printf("TTree RawEvents contains %d events\tfilename %s\n",nevt,infile.c_str());

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
        if(iev%100==0){
          fprintf(stderr,"\rGlob(%d%%, %d/%d) File(%d%%, %d/%d) Run nr %d Event nr %d ADC boards %d    ",
              fNEvtProcessed*100/fNEvtToProcess,
              fNEvtProcessed,fNEvtToProcess,
              iev*100/nevt,
              iev,nevt,
              rawEv->GetRunNumber(),rawEv->GetEventNumber(),nBoards);
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

        if(nTrg!=4) { WARNING("nTrg!=4  "+std::to_string(int(nTrg))); continue;}
        if(nChn!=27){ WARNING("nChn!=27 "+std::to_string(int(nChn))); continue;}

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
          if(c>nChn){ERROR("c>nChn");continue;}
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
