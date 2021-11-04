#include"Analyse.hh"

#include<fstream>
#include<iterator>
#include<stdio.h>
#include<typeinfo>

#include "TRawEvent.hh"
#include"utlMessageBus.hh"
#include"Histos.hh"


  void
Analyse::HWInit()
{
}

  void
Analyse::HWDestr()
{
}

  void
Analyse::FillOscCumulatives()
{
}


  void
Analyse::FillGraphTrends()
{
}

  void
Analyse::FillTimes()
{
}


  void
Analyse::FillPhEDistr()
{
}
  void
Analyse::MakeFFT()
{
}

  void
Analyse::FillHistos()
{
}

  void
Analyse::PrepareChannelsForAnal()
{
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
    //INFO(std::to_string(nBoards)+" boards found");
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


    int boardSecN=-1;
    // Loop over boards
    for(UChar_t b=0;b<26;b++){ //nBoards
      //if(
      //    b!=10 &&
      //    b!=11 &&
      //    b!=12 &&
      //    b!=24 &&
      //    b!=25 &&
      //    b!=26
      //  ) continue;

      // Show board info
      TADCBoard* adcB = rawEv->ADCBoard(b);
      if(adcB==NULL)continue;
      if(
         adcB->GetBoardId()!=10 &&
         adcB->GetBoardId()!=11 &&
         adcB->GetBoardId()!=12 &&
         adcB->GetBoardId()!=24 &&
         adcB->GetBoardId()!=25 &&
         adcB->GetBoardId()!=26
        ) continue;


      //INFO(std::string("BoardId ")+std::to_string(int(adcB->GetBoardId()))+ "    BoardSN  "+ std::to_string(int(adcB->GetBoardSN())));


      //INFO("processing board "+ std::to_string(int(b)));
      boardSecN++;
      UChar_t nTrg = adcB->GetNADCTriggers();
      UChar_t nChn = adcB->GetNADCChannels();

      //if(nTrg!=3) { WARNING("nTrg!=3  "+std::to_string(int(nTrg))); continue;}
      //if(nChn!=17){ WARNING("nChn!=17 "+std::to_string(int(nChn))); continue;}

      //// Loop over triggers
      //for(UChar_t t=0;t<nTrg;t++){
      //  TADCTrigger* trg = adcB->ADCTrigger(t);
      //  //INFO("tring "+std::to_string(int(t)));
      //  fTriggerChannels[t]->SetSamples(trg->GetNSamples(),trg->GetSamplesArray());
      //  fTriggerChannels[t]->CalcT0();
      //} //end trigger for

      for(int ch_i=0;ch_i<nChn;++ch_i){
        TADCChannel* chn = adcB->ADCChannel(ch_i);

        int nSamp=chn->GetNSamples();
        auto array=chn->GetSamplesArray();
        //INFO(std::to_string(boardSecN)+"  "+std::to_string(ch_i));

        for(UShort_t s=0;s<nSamp;++s){
          fHists.hist2f_OscCum[boardSecN][ch_i]->Fill(s,array[s]);
        }
      } //end channel for
    } //end boards for

    //AnalyseAndFill();


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
