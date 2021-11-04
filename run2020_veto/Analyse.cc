#include"Analyse.hh"

#include"V1742.hh"

#include"Histos.hh"

#include"TRawEvent.hh"
#include"utlMessageBus.hh"


#include"SiPM.hh"
#include"DummyChannel.hh"
#include"TerminatedChannel.hh"

#include"VCalorimeterChannel.hh"
#include"BTFCalorimeterChannel.hh"
#include"BaF2CalorimeterChannel.hh"

#include<fstream>
#include<iterator>
#include<stdio.h>
#include<typeinfo>






  void
Analyse::HWInit()
{
  //fADCBoards.clear();
}


  void
Analyse::Fill()
{
  Universe& u = Universe::GetInstance();
  for(int i=0;i<96;++i)     if(u.fEVeto.GetChan(i).IsFired()){
    for(int j=i; j<96; ++j) if(u.fEVeto.GetChan(j).IsFired())  u.fHist.hist2f_CorrMatrix->Fill(i,j);
    for(int j=0; j<96; ++j) if(u.fPVeto.GetChan(j).IsFired())  u.fHist.hist2f_CorrMatrix->Fill(i,100+j);
    for(int j=0; j<32; ++j) if(u.fHVeto.GetChan(j).IsFired())  u.fHist.hist2f_CorrMatrix->Fill(i,200+j);
  }
  for(int i=0;i<96;++i)     if(u.fPVeto.GetChan(i).IsFired()){
    for(int j=i; j<96; ++j) if(u.fPVeto.GetChan(j).IsFired())  u.fHist.hist2f_CorrMatrix->Fill(100+i,100+j);
    for(int j=0; j<32; ++j) if(u.fHVeto.GetChan(j).IsFired())  u.fHist.hist2f_CorrMatrix->Fill(100+i,200+j);
  }
  for(int i=0;i<32;++i)     if(u.fHVeto.GetChan(i).IsFired()){
    for(int j=i; j<32; ++j) if(u.fHVeto.GetChan(j).IsFired())  u.fHist.hist2f_CorrMatrix->Fill(200+i,200+j);
  }



  //for(int i=0;i<32;++i){
  //    fHists.hist1f_PhElectr   [i]->Fill(PVetoMap(i+shift).GetPhE   ());
  //    fHists.hist1f_PhElectrAbs[i]->Fill(PVetoMap(i+shift).GetPhEAbs());
  //}



}

  void
Analyse::FitCellPedestals()
{



  Universe& u = Universe::GetInstance();

  std::ofstream outF_linreg("caldat-linreg.json", std::ios_base::trunc);
  outF_linreg.precision(40);
  outF_linreg<<"{"<<std::endl;
  for(auto b_it=u.fADCBoards.begin();b_it!=u.fADCBoards.end();b_it++){
    outF_linreg<<'"'<<b_it->first<<"\": ["<<std::endl; // adcb
    for(int ch=0; ch<32; ch++){
      outF_linreg<<"["<<std::endl; //channels
      for(int cell=0; cell<1024;cell++){
        TH1D* cellped=b_it->second.hist2f_Pedestal_nocal_cell[ch]->ProjectionY("", cell+1, cell+1);
        const int median=cellped->GetBinLowEdge(cellped->GetMaximumBin());

        auto &summ = b_it->second.cap_sums[ch][cell];
        outF_linreg
          <<"{"
          <<"\"n\": "      <<summ.n    <<", "
          <<"\"t\": "      <<summ.t    <<", "
          <<"\"t2\": "     <<summ.t2   <<", "
          <<"\"t3\": "     <<summ.t3   <<", "
          <<"\"t4\": "     <<(long double)summ.t4   <<", "
          <<"\"t5\": "     <<(long double)summ.t5   <<", "
          <<"\"t6\": "     <<(long double)summ.t6   <<", "
          <<"\"t7\": "     <<(long double)summ.t7   <<", "
          <<"\"t8\": "     <<(long double)summ.t8   <<", "
          <<"\"t9\": "     <<(long double)summ.t9   <<", "
          <<"\"t10\": "    <<(long double)summ.t10  <<", "
          <<"\"Cp\": "     <<summ.Cp   <<", "
          <<"\"tCp\": "    <<summ.tCp  <<", "
          <<"\"t2Cp\": "   <<summ.t2Cp <<", "
          <<"\"t3Cp\": "   <<(long double)summ.t3Cp <<", "
          <<"\"t4Cp\": "   <<(long double)summ.t4Cp <<", "
          <<"\"t5Cp\": "   <<(long double)summ.t5Cp <<", "
          <<"\"MPV\": " <<median
          <<"}";
        if(cell<1023){
          outF_linreg<<","<<std::endl;
        }else{
          outF_linreg<<std::endl;
        }
      }
      if(ch<31){ //channels
        outF_linreg<<"],"<<std::endl;
      }else{
        outF_linreg<<"]"<<std::endl;
      }
    }
    if(b_it->first != u.fADCBoards.rbegin()->first){
      outF_linreg<<"],"<<std::endl;
    }else{
      outF_linreg<<"]"<<std::endl;
    }
  }
  outF_linreg<<"}"<<std::endl;
  outF_linreg<<std::flush;





  //std::ofstream outF("caldat-new.json", std::ios_base::trunc);
  //outF<<"{"<<std::endl;
  //for(auto b_it=u.fADCBoards.begin();b_it!=u.fADCBoards.end();b_it++){

  //  long double vals[32][1024];

  //  for(unsigned ch=0;ch<32;++ch){
  //    for(unsigned cell=0;cell<1024;++cell){
  //      TH1D* cellped=b_it->second.hist2f_PedestalCell[ch]->ProjectionY("", cell+1, cell+1);
  //      vals[ch][cell]=cellped->GetBinLowEdge(cellped->GetMaximumBin())+.55;
  //      //vals[ch][cell]=cellped->GetMean()+.5;
  //    }
  //  }

  //  for(unsigned ch=0;ch<32;++ch){
  //    long double mean=0;
  //    for(unsigned cell=0;cell<1024;++cell) mean+=vals[ch][cell];
  //    mean/=1024;
  //    for(unsigned cell=0;cell<1024;++cell) vals[ch][cell]-=mean;
  //  }

  //  outF<<'"'<<b_it->first<<"\": ["<<std::endl;


  //  for(unsigned ch=0;ch<32;++ch){
  //    outF<<"[";
  //    for(unsigned cell=0;cell<1024;++cell){
  //      outF<<floor(vals[ch][cell]);
  //      if(cell<1023) outF<<", ";
  //    }
  //    if(ch<31){
  //      outF<<"],"<<std::endl;
  //    }else{
  //      outF<<"]"<<std::endl;
  //    }
  //  }

  //  if(b_it->first != u.fADCBoards.rbegin()->first){
  //    outF<<"],"<<std::endl;
  //  }else{
  //    outF<<"]"<<std::endl;
  //  }
  //}

  //outF<<"}"<<std::endl;
  //outF<<std::flush;





  //int vals[32][1024];
  //for(unsigned ch=0;ch<32;++ch){
  //  for(unsigned cell=0;cell<1024;++cell){
  //    TH1D* cellped=fHists.hist2f_PedestalCell[ch]->ProjectionY("", cell+2, cell+2);
  //    vals[ch][cell]=cellped->GetBinCenter(cellped->GetMaximumBin());
  //  }
  //}
  //for(unsigned ch=0;ch<32;++ch){
  //  int mean=0;
  //  for(unsigned cell=0;cell<1024;++cell) mean+=vals[ch][cell];
  //  mean/=1024;
  //  for(unsigned cell=0;cell<1024;++cell) vals[ch][cell]-=mean;
  //}



  //std::ofstream outF("caldat.cc_", std::ios_base::app);
  ////outF<<"void V1742::CellConfig(){"<<std::endl;

  //for(unsigned ch=0;ch<32;++ch){
  //  for(unsigned cell=0;cell<1024;++cell){
  //    outF<<"  fCalDat[12" /*boardID*/<<"]["<<ch<<"]["<<cell<<"]="<< vals[ch][cell] <<";"<<std::endl;
  //  }
  //}
  ////outF<<"}"<<std::endl;
  //outF<<std::flush;
}


  void
Analyse::FillOscCumulatives()
{
  //static int nfilled=0;
  //if(nfilled++>10000)return;
  //for(unsigned int ch_i=0;ch_i<25;++ch_i){
  //  {
  //        //&& b!=10
  //        //&& b!=11
  //        //&& b!=12
  //        //&& b!=13
  //        //&& b!=24
  //        //&& b!=25
  //        //&& b!=26
  //        //&& b!=27 //SAC
  //    auto chan=fADCBoards[12/*boardID*/].GetChan(ch_i);
  //    fHists.hist1f_SigPedestals[ch_i]->Fill(chan.GetPedestal());
  //    for(UShort_t s=0;s<1024;++s){
  //      //fHists.hist2f_OscCum[ch_i]->Fill(s,chan.GetSamp(s));
  //      //fHists.hist2f_OscCumT0Fixed[ch_i]->Fill(s,chan.GetValT0Ped(s));
  //      if(nfilled<100) fHists.hist2f_PedestalStudy[ch_i]->SetBinContent(s+1,nfilled,chan.GetSamp(s));
  //      if(nfilled<100){
  //        fHists.hist2f_PedestalStudyCell[ch_i]->SetBinContent(
  //            (s+1024+chan.GetStartIndexCell())%1024+1, nfilled,chan.GetSamp(s));
  //        //std::stringstream info;
  //        //info 
  //        //<< (s+1024-chan.GetStartIndexCell())%1024+1<<"  "
  //        //<< s<< " "
  //        //<<chan.GetStartIndexCell()<<"  "
  //        //<< nfilled<<"  "
  //        //<<chan.GetSamp(s);
  //        //  INFO(info.str());
  //      }
  //      fHists.hist2f_PedestalCell[ch_i]->Fill(
  //          (s+1024+chan.GetStartIndexCell())%1024+1,chan.GetSampNoCellPedCor(s));
  //      fHists.hist2f_Pedestal[ch_i]->Fill( s+1,chan.GetSamp(s));
  //      fHists.hist2f_PedestalNoCellPedCor[ch_i]->Fill( s+1,chan.GetSampNoCellPedCor(s));
  //    }
  //  }
  //}
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

    //INFO("TTT"+std::to_string(int(rawEv->GetNADCBoards())));


    HWInit();


    // Loop over boards
    for(UChar_t b=0;b<((UChar_t)rawEv->GetNADCBoards());b++){ //nBoards
      if(1
          && false
          && b!=0
          //&& b!=10
          //&& b!=11
          //&& b!=12
          //&& b!=13
          //&& b!=24
          && b!=25
          //&& b!=26
          && b!=27 //SAC
        )continue;

      // Show board info
      TADCBoard* adcB = rawEv->ADCBoard(b);
      Universe::GetInstance().fADCBoards[b].SetBoard(adcB);
    } //end boards for

    Universe& u = Universe::GetInstance();

    u.Map();

    for(auto b_it=u.fADCBoards.begin();b_it!=u.fADCBoards.end();b_it++){
      b_it->second.Analyse();
    }
    //u.fEVeto.Analyse();
    //u.fPVeto.Analyse();
    //u.fHVeto.Analyse();






    //AnalyseAndFill();  //corel matrix


    Universe::GetInstance().Reset();
    // Clear event
    rawEv->Clear("C");

  } //end event for
  //HWDestr();

  delete rawEv;
  delete bRawEv;
  delete tRawEv;

  fRawEv->Close();
  delete fRawEv;
}

  void
Analyse::Finalize()
{
  FitCellPedestals();

  Universe::GetInstance().fHist.Write();

}
