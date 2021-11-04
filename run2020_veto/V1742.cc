#include"V1742.hh"
#include"Universe.hh"

#include"utlMessageBus.hh"

#include<TH1F.h>
#include<TH2F.h>

#include<sstream>






V1742::V1742():
  fNEvtsProcessed(0),
  fIsHistDone(false) {
  }

void V1742::SetBoard(TADCBoard* adcB){
  Universe& u = Universe::GetInstance();
  fADCBoard=adcB;
  UChar_t nTrg = adcB->GetNADCTriggers();
  UChar_t nChn = adcB->GetNADCChannels();


  for(UChar_t t=0;t<nTrg;t++){
    auto trg= adcB->ADCTrigger(t);
    fTrig.emplace_back();
    fTrig.rbegin()->SetSamples(trg->GetNSamples(), trg->GetSamplesArray());
    fTrig.rbegin()->CalcT0();

    fTrig.rbegin()->SetStartIndexCell((unsigned short)adcB->ADCTrigger(t)->GetStartIndexCell());
  }
  for(UChar_t c=0;c<nChn;++c){
    //fChan.emplace_back();
    auto chn=adcB->ADCChannel(c);
    fChan[c].SetSamples(chn->GetNSamples(), chn->GetSamplesArray());

    fChan[c].SetStartIndexCell((unsigned short)adcB->ADCTrigger(int(c/8))->GetStartIndexCell());

    fChan[c].SetPedestalCalibration(u.fADCCellCallDat[adcB->GetBoardId()][c]);
  }
  PrepareForAnal();
}





void V1742::PrepareForAnal(){
#pragma omp parallel
#pragma omp  for
  for(unsigned ch=0;ch<
fADCBoard->GetNADCChannels()
    ;++ch){
    //fChan[ch].SetStartIndexCell(fTrig[ch/8].GetStartIndexCell());


    fChan[ch].CalcPedestal();
    fChan[ch].SetT0(fTrig[ch/8].GetT0());
    fChan[ch].CalcTimeCharge();
  }
}



void V1742::Analyse(){
  //static int tttt =0;
  //INFO(std::to_string(tttt));
  if(fNEvtsProcessed>4000)return;
  fNEvtsProcessed++;
  for(unsigned int ch_i=0;ch_i<
fADCBoard->GetNADCChannels()
    ;++ch_i){
    {
      //INFO(std::to_string(ch_i));
      auto chan=GetChan(ch_i);
      //hist1f_SigPedestals[ch_i]->Fill(chan.GetPedestal());
      //hist1f_IndexCell[ch_i]->Fill(chan.GetStartIndexCell());

      for(uint128_t t=0;t<1000;++t){
        //hist2f_OscCum[ch_i]->Fill(t,chan.GetSamp(t));
        //hist2f_OscCumT0Fixed[ch_i]->Fill(t,chan.GetValT0Ped(t));
        const int p  = (t+chan.GetStartIndexCell())%1024;
        const int Cp = chan.GetSampNoCellPedCor(t);
        auto &sums = cap_sums[ch_i][p];
        const long long uint128_t = 
        sums.n   += 1;
        sums.t   += t;
        sums.t2  += t*t;
        sums.t3  += t*t*t;
        sums.t4  += t*t*t*t;
        sums.t5  += t*t*t*t*t;
        sums.t6  += t*t*t*t*t*t;
        sums.t7  += t*t*t*t*t*t*t;
        sums.t8  += t*t*t*t*t*t*t*t;
        sums.t9  += t*t*t*t*t*t*t*t*t;
        sums.t10 += t*t*t*t*t*t*t*t*t*t;
        sums.Cp  += Cp;
        sums.tCp += t*Cp;
        sums.t2Cp+= t*t*Cp;
        sums.t3Cp+= t*t*t*Cp;
        sums.t4Cp+= t*t*t*t*Cp;
        sums.t5Cp+= t*t*t*t*t*Cp;

        const int Ct = chan.GetSampNoCellPedCor(t);
        const int Ctcal = chan.GetSamp(t);

        hist2f_Pedestal_cal_cell  [ch_i]->Fill(p, Ctcal);
        hist2f_Pedestal_nocal_cell[ch_i]->Fill(p, Ct);
        hist2f_Pedestal_cal_time  [ch_i]->Fill(t, Ctcal);
        hist2f_Pedestal_nocal_time[ch_i]->Fill(t, Ct);

        //hist2f_PedestalCell[ch_i]->Fill(
        //    (t+chan.GetStartIndexCell())%1024,
        //    chan.GetSampNoCellPedCor(t)
        //    );
        //hist2f_Pedestal[ch_i]->Fill(t, chan.GetSamp(t));
        //hist2f_PedestalNoCellPedCor[ch_i]->Fill(t, chan.GetSampNoCellPedCor(t));





        if(p>27)continue;
        if(ch_i==12) hist2f_Cells_time[p]->Fill(t, Ct);
        //hist2f_PedestalStudy[ch_i]->SetBinContent(t+1,fNEvtsProcessed,chan.GetSamp(t));
        //hist2f_PedestalStudyCell[ch_i]->Fill(p, fNEvtsProcessed,chan.GetSamp(t));
        //std::stringstream info;
        //info 
        //<< (t+1024-chan.GetStartIndexCell())%1024+1<<"  "
        //<< t<< " "
        //<<chan.GetStartIndexCell()<<"  "
        //<< fNEvtsProcessed<<"  "
        //<<chan.GetSamp(t);
        //  INFO(info.str());
      }
      //INFO(std::to_string(ch_i));
    }
  }
}


void V1742::CreateHistos(Histos& hist){
  if(fIsHistDone) return;
  fIsHistDone=true;

  //INFO("create histos");

  std::string lab;

  for(int i=0;i<32;i++){

    std::stringstream ss_p;
    ss_p<<"_"<<"cap_"<<i;

    std::stringstream ss;
    ss<<"_"<<"ch"<<i;

    //INFO(ss.str());

    std::string brdID=std::to_string(fADCBoard->GetBoardId());
    std::string a;

    //a="_IndexCell"        ;hist.GotoDir("b"+brdID+a);hist1f_IndexCell         .push_back( new TH1F(("b"+brdID+a+ss.str()).c_str(),(a+ss.str()+lab).c_str(),1025,0-.5,1024-.5));

    lab=";Cell ID";
    a="_Pedestal_cal_Cell"              ;hist.GotoDir("b"+brdID+a);hist2f_Pedestal_cal_cell    .push_back( new TH2S(("b"+brdID+a+ss.str()).c_str(),(a+ss.str()+lab).c_str(),1024,0-.5,1024-.5,800,3300-.5,4100-.5));
    a="_Pedestal_nocal_Cell"            ;hist.GotoDir("b"+brdID+a);hist2f_Pedestal_nocal_cell  .push_back( new TH2S(("b"+brdID+a+ss.str()).c_str(),(a+ss.str()+lab).c_str(),1024,0-.5,1024-.5,800,3300-.5,4100-.5));
    lab=";Time [samples]";
    a="_Pedestal_cal_time"              ;hist.GotoDir("b"+brdID+a);hist2f_Pedestal_cal_time    .push_back( new TH2S(("b"+brdID+a+ss.str()).c_str(),(a+ss.str()+lab).c_str(),1024,0-.5,1024-.5,800,3300-.5,4100-.5));
    a="_Pedestal_nocal_time"            ;hist.GotoDir("b"+brdID+a);hist2f_Pedestal_nocal_time  .push_back( new TH2S(("b"+brdID+a+ss.str()).c_str(),(a+ss.str()+lab).c_str(),1024,0-.5,1024-.5,800,3300-.5,4100-.5));

    a="_ch12_Cells_time"                ;hist.GotoDir("b"+brdID+"cells_time");hist2f_Cells_time.push_back( new TH2S(("b"+brdID+a+ss_p.str()).c_str(),(a+ss_p.str()+lab).c_str(),44,0-.5,1012-.5,800,3300-.5,4100-.5));

    //a="_SigPedestals"        ;hist.GotoDir("b"+brdID+a);hist1f_SigPedestals         .push_back( new TH1F(("b"+brdID+a+ss.str()).c_str(),(a+ss.str()+lab).c_str(),500,3500-.5,4000-.5));
    //a="_SignalStudy"         ;hist.GotoDir("b"+brdID+a);hist2f_SignalStudy          .push_back( new TH2F(("b"+brdID+a+ss.str()).c_str(),(a+ss.str()+lab).c_str(),1024,0-.5,1024-.5,100,-.5,100-.5));
    //a="_PedestalStudyCell"   ;hist.GotoDir("b"+brdID+a);hist2f_PedestalStudyCell    .push_back( new TH2F(("b"+brdID+a+ss.str()).c_str(),(a+ss.str()+lab).c_str(),1024,0-.5,1024-.5,100,-.5,100-.5));
    //a="_PedestalStudy"       ;hist.GotoDir("b"+brdID+a);hist2f_PedestalStudy        .push_back( new TH2F(("b"+brdID+a+ss.str()).c_str(),(a+ss.str()+lab).c_str(),1024,0-.5,1024-.5,100,-.5,100-.5));
  }


}
