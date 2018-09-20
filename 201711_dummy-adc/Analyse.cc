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
  fSignalChannels [0 ]=new DummyChannel();
  fSignalChannels [1 ]=new DummyChannel();
  fSignalChannels [2 ]=new DummyChannel();
  fSignalChannels [3 ]=new DummyChannel();
  fSignalChannels [4 ]=new DummyChannel();
  fSignalChannels [5 ]=new DummyChannel();
  fSignalChannels [6 ]=new DummyChannel();
  fSignalChannels [7 ]=new DummyChannel();
  fSignalChannels [8 ]=new DummyChannel();
  fSignalChannels [9 ]=new DummyChannel();
  fSignalChannels [10]=new DummyChannel();
  fSignalChannels [11]=new DummyChannel();
  fSignalChannels [12]=new DummyChannel();
  fSignalChannels [13]=new DummyChannel();
  fSignalChannels [14]=new DummyChannel();
  fSignalChannels [15]=new DummyChannel();
  fSignalChannels [16]=new DummyChannel();
  fSignalChannels [17]=new DummyChannel();
  fSignalChannels [18]=new DummyChannel();
  fSignalChannels [19]=new DummyChannel();
  fSignalChannels [20]=new DummyChannel();
  fSignalChannels [21]=new DummyChannel();
  fSignalChannels [22]=new DummyChannel();
  fSignalChannels [23]=new DummyChannel();
  fSignalChannels [24]=new DummyChannel();
  fSignalChannels [25]=new DummyChannel();
  fSignalChannels [26]=new DummyChannel();
  fSignalChannels [27]=new DummyChannel();
  fSignalChannels [28]=new DummyChannel();
  fSignalChannels [29]=new DummyChannel();
  fSignalChannels [30]=new DummyChannel();
  fSignalChannels [31]=new DummyChannel();
  fTriggerChannels[0 ]=new DummyChannel();
  fTriggerChannels[1 ]=new DummyChannel();
  fTriggerChannels[2 ]=new DummyChannel();
  fTriggerChannels[3 ]=new DummyChannel();

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
Analyse::FillOscCumulatives()
{
}





  void
Analyse::FillHistos()
{
}


  void
Analyse::DummyChannelAnalyse()
{
  for(auto it=fSignalChannels.begin();it!=fSignalChannels.end();++it){
    DummyChannel* ch=dynamic_cast<DummyChannel*>(it->second);
    int ch_i=it->first;
    if(ch==nullptr){ERROR("not a dummychannel");continue;}
    ch->Process();
    //TH2F tmphist("tt","",128,0,1024,128,0,1024);
    for(int i=0;i<1024;++i){
      fHists.hist2f_ChanOscCum           [0][ch_i]->Fill(i,ch->GetSamp(i));
      fHists.hist2f_ChanOscCumT0         [0][ch_i]->Fill(i,ch->GetSampT0Cor(i));
      fHists.hist3f_ChanOscCum3d         [0][ch_i]->Fill(double(ch->CorT0(i)),double(i),ch->GetSamp(i));
      //tmphist.Fill(double(ch->CorT0(i)),double(i));
    }
    //fHists.hist2f_ChanOscCum2d         [0][ch_i]->Divide( fHists.hist2f_ChanOscCum2d         [0][ch_i], &tmphist);
    fHists.hist1f_ChanPedestalsMean    [0][ch_i]->Fill(ch->GetMean        ());
    fHists.hist1f_ChanPedestalsRMS     [0][ch_i]->Fill(ch->GetRMS         ());
    fHists.hist1f_ChanSlopeFitA        [0][ch_i]->Fill(ch->GetLinSlope_a  ());
    fHists.hist1f_ChanSlopeFitB        [0][ch_i]->Fill(ch->GetLinSlope_b  ());
    fHists.hist1f_ChanSlopeFitRMS      [0][ch_i]->Fill(ch->GetLinSlope_rms());
  }



  for(auto it=fTriggerChannels.rbegin();it!=fTriggerChannels.rend();++it){
    DummyChannel* ch=dynamic_cast<DummyChannel*>(it->second);
    int ch_i=it->first;
    if(ch==nullptr){ERROR("not a dummychannel");continue;}
    ch->Process();
    //TH2F tmphist("tt","",128,0,1024,128,0,1024);
    for(int i=0;i<1024;++i){
      //INFO(std::to_string(double(ch->GetSamp(i))));
      fHists.hist2f_TrigOscCum           [0][ch_i]->Fill(i,ch->GetSamp(i));
      fHists.hist2f_TrigOscCumT0         [0][ch_i]->Fill(i,ch->GetSampT0Cor(i));
      //fHists.hist2f_TrigOscCum2d         [0][ch_i]->Fill(double(ch->CorT0(i)),double(i),ch->GetSamp(i)-ch->GetMean());
      //tmphist.Fill(double(ch->CorT0(i)),double(i));
    }
    //fHists.hist2f_TrigOscCum2d         [0][ch_i]->Divide(
    //fHists.hist2f_TrigOscCum2d         [0][ch_i], &tmphist);
    fHists.hist1f_TrigPedestalsMean    [0][ch_i]->Fill(ch->GetMean        ());
    fHists.hist1f_TrigPedestalsRMS     [0][ch_i]->Fill(ch->GetRMS         ());
    fHists.hist1f_TrigSlopeFitA        [0][ch_i]->Fill(ch->GetLinSlope_a  ());
    fHists.hist1f_TrigSlopeFitB        [0][ch_i]->Fill(ch->GetLinSlope_b  ());
    fHists.hist1f_TrigSlopeFitRMS      [0][ch_i]->Fill(ch->GetLinSlope_rms());
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
    int nBoardsRead=0;
    for(UChar_t b=0;b<1&&nBoardsRead<nBoards;b++){ //nBoards

      // Show board info
      TADCBoard* adcB = rawEv->ADCBoard(b);
      if(adcB==nullptr){WARNING("board number "+std::to_string(b)+" does not exist. SKIP!");continue;}
      nBoards++;
      UChar_t nTrg = adcB->GetNADCTriggers();
      UChar_t nChn = adcB->GetNADCChannels();
      if(nTrg!=4)ERROR("nTrig!=4");
      if(nChn!=32)ERROR("nChn!=32");
      //if(verbose>2){
      //  printf("\tBoard %u Board Id %u LVDS %u Status %u GMsk 0x%1x EvtCnt %u Time %u ActMsk 0x%08x AccMsk 0x%08x #Trg %u #Chn %u\n",
      //      b,adcB->GetBoardId(),adcB->GetLVDSPattern(),adcB->GetStatus(),adcB->GetGroupMask(),adcB->GetEventCounter(),
      //      adcB->GetEventTimeTag(),adcB->GetActiveChannelMask(),adcB->GetAcceptedChannelMask(),nTrg,nChn);
      //  }

      //if(nTrg!=3) { WARNING("nTrg!=3  "+std::to_string(int(nTrg))); continue;}
      //if(nChn!=17){ WARNING("nChn!=17 "+std::to_string(int(nChn))); continue;}

      // Loop over triggers
#pragma omp parallel
#pragma omp  for
      for(UChar_t t=0;t<nTrg;t++){
        TADCTrigger* trg = adcB->ADCTrigger(t);
        //INFO("tring "+std::to_string(int(t)));
        fTriggerChannels[t]->SetSamples(trg->GetNSamples(),trg->GetSamplesArray());
        fTriggerChannels[t]->SetT0(trg->GetStartIndexCell());
        //fTriggerChannels[t]->CalcT0();
      } //end trigger for

#pragma omp parallel
      for(auto sig_it=fSignalChannels.begin();sig_it!=fSignalChannels.end();++sig_it)
#pragma omp single nowait
      {
        UChar_t c=int(sig_it->first);
        //if(c>nChn){ERROR("c>nChn c="+std::to_string(c));continue;}
        auto& ch=*sig_it->second;
        TADCChannel* chn = adcB->ADCChannel(c);
        //INFO("chan "+std::to_string(int(c)));
        ch.SetSamples(chn->GetNSamples(),chn->GetSamplesArray());
        ch.SetT0(fTriggerChannels[c/8]->GetT0());
      } //end channel for
    } //end boards for




    DummyChannelAnalyse();


    // Clear event
    rawEv->Clear("C");

  } //end event for

  delete rawEv;
  delete bRawEv;
  delete tRawEv;

  fRawEv->Close();
  delete fRawEv;
}

  void
Analyse::Finalize()
{
  for(auto it=fSignalChannels.begin();it!=fSignalChannels.end();++it){
    DummyChannel* ch=dynamic_cast<DummyChannel*>(it->second);
    int ch_i=it->first;
    if(ch==nullptr){ERROR("not a dummychannel");}
    else{
      double min=1e9;
      double max=-1e9;

      for(int bin_i=1;bin_i<=1024;++bin_i){
        TH1D* proj  =fHists.hist2f_ChanOscCum  [0][ch_i]->ProjectionY("nont0",bin_i,bin_i);
        TH1D* projt0=fHists.hist2f_ChanOscCumT0[0][ch_i]->ProjectionY("t0",bin_i,bin_i);

        double cmin  =proj  ->GetBinCenter(proj  ->FindFirstBinAbove());
        double cmax  =proj  ->GetBinCenter(proj  ->FindLastBinAbove() );
        double cmint0=projt0->GetBinCenter(projt0->FindFirstBinAbove());
        double cmaxt0=projt0->GetBinCenter(projt0->FindLastBinAbove() );
        //proj->GetMinimumAndMaximum  (cmin  ,cmax);
        //projt0->GetMinimumAndMaximum(cmint0,cmaxt0);

        fHists.hist1f_ChanSigmaSampBySamp  [0][ch_i]->Fill(proj  ->GetRMS());
        fHists.hist1f_ChanSigmaSampBySampT0[0][ch_i]->Fill(projt0->GetRMS());

        fHists.hist1f_ChanAmplFluctSampBySamp  [0][ch_i]->Fill(cmax-cmin    );
        fHists.hist1f_ChanAmplFluctSampBySampT0[0][ch_i]->Fill(cmaxt0-cmint0);
        if(min>cmin)min=cmin;
        if(max<cmax)min=cmax;
      }
      //fHists.hist1f_ChanMaxAmplFluct     [0][ch_i]->Fill(max-min);

      fHists.hist1f_ChanSigPedMean->Fill(fHists.hist1f_ChanPedestalsMean[0][ch_i]->GetRMS());
      fHists.hist1f_ChanSigPedSig ->Fill(fHists.hist1f_ChanPedestalsRMS [0][ch_i]->GetRMS());
      fHists.hist1f_ChanOscSigY   ->Fill(fHists.hist2f_ChanOscCum       [0][ch_i]->GetRMS(2));
    }
  }





  for(auto it=fTriggerChannels.begin();it!=fTriggerChannels.end();++it){
    DummyChannel* ch=dynamic_cast<DummyChannel*>(it->second);
    int ch_i=it->first;
    if(ch==nullptr){ERROR("not a dummychannel");}
    else{
      double min=1e9;
      double max=-1e9;

      for(int bin_i=1;bin_i<=1024;++bin_i){
        TH1D* proj  =fHists.hist2f_TrigOscCum  [0][ch_i]->ProjectionY("nont0",bin_i,bin_i);
        TH1D* projt0=fHists.hist2f_TrigOscCumT0[0][ch_i]->ProjectionY("t0",bin_i,bin_i);

        double cmin  =proj  ->GetBinCenter(proj  ->FindFirstBinAbove());
        double cmax  =proj  ->GetBinCenter(proj  ->FindLastBinAbove() );
        double cmint0=projt0->GetBinCenter(projt0->FindFirstBinAbove());
        double cmaxt0=projt0->GetBinCenter(projt0->FindLastBinAbove() );
        //proj->GetMinimumAndMaximum  (cmin  ,cmax);
        //projt0->GetMinimumAndMaximum(cmint0,cmaxt0);

        fHists.hist1f_TrigSigmaSampBySamp  [0][ch_i]->Fill(proj  ->GetRMS());
        fHists.hist1f_TrigSigmaSampBySampT0[0][ch_i]->Fill(projt0->GetRMS());

        fHists.hist1f_TrigAmplFluctSampBySamp  [0][ch_i]->Fill(cmax-cmin    );
        fHists.hist1f_TrigAmplFluctSampBySampT0[0][ch_i]->Fill(cmaxt0-cmint0);
        if(min>cmin)min=cmin;
        if(max<cmax)min=cmax;
      }
      //fHists.hist1f_TrigMaxAmplFluct     [0][ch_i]->Fill(max-min);

      fHists.hist1f_TrigSigPedMean->Fill(fHists.hist1f_TrigPedestalsMean[0][ch_i]->GetRMS());
      fHists.hist1f_TrigSigPedSig ->Fill(fHists.hist1f_TrigPedestalsRMS [0][ch_i]->GetRMS());
    }
  }





  HWDestr();
}
