#include<set>
#include<iterator>
#include<stdio.h>
#ifndef _analyse_hh_
#define _analyse_hh_ 0



class SamplingChannel{
  public:
    SamplingChannel(){
      fT0=0;
    }
    SamplingChannel(UShort_t n,Short_t* arr){SamplingChannel(); SetNSamples(n); SetSamplesArr(arr);}
    void SetNSamples  (UShort_t n){fNSamples=n;}
    void SetSamplesArr(Short_t* arr){fSamples=arr;}
    void SetSamples(UShort_t n,Short_t* arr){SetNSamples(n); SetSamplesArr(arr);}
    int  GetT0()const {return fT0;}
    void SetT0(int t){fT0=t;}
    Short_t GetSampT0Cor(int t)const {t-=fT0;return t>=0&&t<fNSamples?fSamples[t]:0;}
    Short_t GetSamp     (int t)const {       return t>=0&&t<fNSamples?fSamples[t]:0;}
    UShort_t GetNSamples()const{return fNSamples;}
  protected:
    Short_t* fSamples;  ///< [ADU]
    UShort_t fNSamples;
    int fT0;
};

class TriggerChannel: public SamplingChannel{
  public:
    void CalcT0(){
      for(unsigned s=0;s<fNSamples/2;++s){ if(fSamples[s]>1500)fT0=167-s; }
    }
};
class PMTChannel:public SamplingChannel{
  public:
    bool IsFired()const{return fFired;}
    void CalcPedestal(){/*{{{*/
      if(
          fPedestalRange.first>=fNSamples||
          fPedestalRange.second>=fNSamples||
          fPedestalRange.second-fPedestalRange.first<5
        ){
        fPedestal=0;
        return;
      }
      // multiset pedestal
      std::multiset<Short_t> peds (&fSamples[fPedestalRange.first],&fSamples[fPedestalRange.second]);
      auto pedp=peds.begin();
      std::advance(pedp,peds.size()*.50); // median
      fPedestal=*pedp;
      fValues.resize(fNSamples);
      for(int i=0;i<fNSamples;++i) fValues[i]=(fSamples[i]-fPedestal)/4096.;
      //FFTLowPass();//uses fPedestal
      //for(int i=0;i<fNSamples;++i) fValues[i]=(fValues[i]-fPedestal)/4096.;
      // multiset pedestal
    }/*}}}*/
    Short_t GetPedestal()const{return fPedestal;}
    Short_t GetSampT0PedCor(int t)const {t-=fT0;return t>=0&&t<fNSamples?fSamples[t]-fPedestal:0;}
    double GetValT0Ped(int t)const{t-=fT0;return t>=0&&t<fNSamples?fValues[t]:0;}
    double GetVal     (int t)const{       return t>=0&&t<fNSamples?fValues[t]:0;}

    double GetTimeMeanAbs           ()const{return fTimeMeanAbs;}
    double GetTimeMean2             ()const{return fTimeMean2;}
    double GetTimeMean              ()const{return fTimeMean;}
    double GetTimeMaxVal            ()const{return fTimeMaxVal;}
    double GetTime2080LeadTrailCross()const{return fTime2080LeadTrailCross;}
    double GetTime2080LeadZeroCross ()const{return fTime2080LeadZeroCross;}
    double GetTime2080LeadMid       ()const{return fTime2080LeadMid;}
    double GetTimeHalfMax           ()const{return fTimeHalfMax;}
    bool   HasOnePhEExact           ()const{return fPhE>fOnePheRange.first&&fPhE<fOnePheRange.second;}

    double GetPhE()const{return fPhE;}
    double GetPhEAbs()const{return fPhEAbs;}
    double GetPhENoise()const{return fPhENoise;}
    double GetPhENoiseAbs()const{return fPhENoiseAbs;}
    double GetValMax()const{return fValMax;}
    void CalcTimeCharge(){//{{{
      fPhE =0;
      fPhE2=0;
      fPhEAbs=0;
      fPhENoise=0;
      fPhENoiseAbs=0;
      fValMax=100;
      fTimeMean=0;
      fTimeMean2=0;
      fTimeMeanAbs=0;
      for(unsigned val_i=fNoiseRange.first;val_i<fNoiseRange.second;++val_i){
        fPhENoise+=GetValT0Ped(val_i);
        fPhENoiseAbs+=-std::abs(GetValT0Ped(val_i));
      }
      for(unsigned val_i=fSignalRange.first;val_i<fSignalRange.second;++val_i){
        const double normcor_sample=GetValT0Ped(val_i);
        fPhE   +=normcor_sample;
        fPhE2  +=normcor_sample*normcor_sample;
        fPhEAbs+=-std::abs(normcor_sample);
        fTimeMean +=val_i*normcor_sample;
        fTimeMean2+=val_i*normcor_sample*normcor_sample;
        fTimeMeanAbs+=val_i*(-std::abs(normcor_sample));
        if(fValMax>normcor_sample){
          fValMax=normcor_sample;
          fTimeMaxVal=val_i;
        }
      }
      fTimeMean /=fPhE ;
      fTimeMean2/=fPhE2;
      fTimeMeanAbs/=fPhEAbs;

      fPhE*=-41.6/fGain;
      fPhEAbs*=-41.6/fGain;
      fPhENoise*=-41.6/fGain;
      fPhENoiseAbs*=-41.6/fGain;
      fFired=fPhE>15;

      double y20=fValMax*.2;
      double y50=fValMax*.5;
      double y80=fValMax*.8;
      double xl20=-999990;
      double xl50=-999990;
      double xl80=-999990;
      double xt20=-999990;
      double xt80=-999990;



      for(UShort_t val_i=fTimeMaxVal;val_i>=fSignalRange.first;--val_i){
        const double normcor_sample=GetValT0Ped(val_i);
        if(normcor_sample<y20)xl20=val_i;
        if(normcor_sample<y50)xl50=val_i;
        if(normcor_sample<y80)xl80=val_i;
      }
      for(UShort_t val_i=fTimeMaxVal;val_i<fSignalRange.second;val_i++){
        const double normcor_sample=GetValT0Ped(val_i);
        if(normcor_sample<y20)xt20=val_i;
        if(normcor_sample<y80)xt80=val_i;
      }

      fTime2080LeadTrailCross=(xl20*xt80-xt20*xl80)/(xl20-xl80+xt80-xt20);
      fTime2080LeadMid=(xl80-xl20)/2+xl20;
      fTime2080LeadZeroCross=-y20*(xl80-xl20)/(y80-y20)+xl20;
      fTimeHalfMax=xl50;

    }//}}}
    void   SetGain(double g){fGain=g;}
    const std::pair<unsigned, unsigned>& GetPedestalRange()const {return fPedestalRange;}
  protected:
    void FFTLowPass(){/*{{{*/
      const unsigned nDat=fNSamples;
      const unsigned nFreq=2;
      const double df=-2*acos(-1.)/nDat;
      fValues.resize(nDat);
      std::vector<double> Re;Re.resize(nFreq);
      std::vector<double> Im;Im.resize(nFreq,0);
      for(unsigned f=0;f<nFreq;++f){
        for(unsigned t=0;t<nDat;++t){
          Re[f]+=fSamples[t]*cos(df*t*f);
          Im[f]+=fSamples[t]*sin(df*t*f);
        }
        //Re[0]-=Re[f]; //background subtraction
      }
      for(unsigned t=0;t<nDat;++t){
        fValues[t]=Re[0];
        for(unsigned f=1;f<nFreq;++f){
          fValues[t]+=2*(Re[f]*cos(df*t*f)+Im[f]*(sin(df*t*f)));
        }
        fValues[t]/=nDat;
      }
    }/*}}}*/
    double fTimeMeanAbs;
    double fTimeMean2;
    double fTimeMean;
    double fTimeMaxVal;
    double fTime2080LeadTrailCross;
    double fTime2080LeadZeroCross;
    double fTime2080LeadMid;
    double fTimeHalfMax;

    double fPhE,fPhE2;
    double fPhEAbs;
    double fPhENoise;
    double fPhENoiseAbs;
    double fValMax;
    double fGain;
    Short_t fPedestal;
    std::vector<float> fValues; /// [mV]
    std::pair<unsigned,unsigned> fSignalRange;
    std::pair<unsigned,unsigned> fNoiseRange;
    std::pair<unsigned,unsigned> fPedestalRange;
    bool fFired;
    std::pair<double,double> fOnePheRange;
};
class MAPMTChannel:public PMTChannel{
  public:
    MAPMTChannel(){
      fGain=1;
      //fSignalRange={200,450};
      fSignalRange={250,400}; fNoiseRange={25,175};
      fPedestalRange={1,200};
      fFired=false;
    }

};
class PhotonisChannel:public PMTChannel{
  public:
    PhotonisChannel(){
      fGain=1;
      fSignalRange={400,550}; fNoiseRange={25,175};
      fPedestalRange={1,180};
      fOnePheRange={150,300};
      fFired=false;
    }
};


class Analyse{

  const int fNSampPedestalCalc=180;
  const double fSamplingTimeStep= 1./5e9; //5GHz
  const double fMAPMTGain= 6e5; // @900V
  const double fDAQInputImpedance=50; // Ohm
  const double fElementaryCharge=-1.6e-19;
  const double fMAPMTCoef=fSamplingTimeStep*fMAPMTGain/fElementaryCharge/fDAQInputImpedance;
  //const int fIntegralMAPMTRange[2]={200,500};
  const int fIntegralMAPMTRange[2]={200,450};//{250,375};
  const int fIntegralMAPMTRange16[2]={400,540};
  const double fNPhElectrThr=12; //PhE

  Histos* fHistosP;

  public:
  Analyse(const std::string& ofn){fHistosP=new Histos(ofn);}
  ~Analyse(){delete fHistosP;}
  void Process(std::string infile);
  void Finalize();
};

void Analyse::Process(std::string infile){
  Histos& hist=*fHistosP;

  TFile* fRawEv = new TFile(infile.c_str());
  TTree* tRawEv = (TTree*)fRawEv->Get("RawEvents");
  TBranch* bRawEv = tRawEv->GetBranch("RawEvent");
  TRawEvent* rawEv = new TRawEvent();
  bRawEv->SetAddress(&rawEv);

  Int_t nevt = tRawEv->GetEntries();
  printf("TTree RawEvents contains %d events\tfilename %s\n",nevt,infile.c_str());

  // Set number of events to read
  Int_t ntoread = nevt;
  if (nevents && nevents<nevt) ntoread = nevents;


  printf("Reading the first %d events\n",ntoread);
  for(Int_t iev=0;iev<ntoread;iev++){


    // Read event
    //printf("Reading event %d\n",iev);
    bRawEv->GetEntry(iev);
    //printf("Event %d read\n",iev);

    // Show event header
    UChar_t nBoards = rawEv->GetNADCBoards();

    if(verbose>0){
      printf("Event %d Run nr %d Event nr %d ADC boards %d\n",
          iev,rawEv->GetRunNumber(),rawEv->GetEventNumber(),nBoards);
    }else{
      if(iev%100==0)
        fprintf(stderr,"%d%% Event %d Run nr %d Event nr %d ADC boards %d\r",iev*100/ntoread,
            iev,rawEv->GetRunNumber(),rawEv->GetEventNumber(),nBoards);
    }

    if(iev==0){
      for(UChar_t b=0;b<nBoards;b++){ //nBoards
        TADCBoard* adcB0 = rawEv->ADCBoard(b);
        printf("\n\n\n\nboard %d %d\n\n\n\n",b,adcB0->GetBoardId());
      }
    }

    // Loop over boards
    for(UChar_t b=0;b<1;b++){ //nBoards

      // Show board info
      TADCBoard* adcB = rawEv->ADCBoard(b);
      UChar_t nTrg = adcB->GetNADCTriggers();
      UChar_t nChn = adcB->GetNADCChannels();
      if(verbose>2)
        printf("\tBoard %u Board Id %u LVDS %u Status %u GMsk 0x%1x EvtCnt %u Time %u ActMsk 0x%08x AccMsk 0x%08x #Trg %u #Chn %u\n",
            b,adcB->GetBoardId(),adcB->GetLVDSPattern(),adcB->GetStatus(),adcB->GetGroupMask(),adcB->GetEventCounter(),
            adcB->GetEventTimeTag(),adcB->GetActiveChannelMask(),adcB->GetAcceptedChannelMask(),nTrg,nChn);


      TriggerChannel trig[4];
      // Loop over triggers
#pragma omp parallel
#pragma omp  for
      for(UChar_t t=0;t<nTrg;t++){
        TADCTrigger* trg = adcB->ADCTrigger(t);
        trig[t].SetSamples(trg->GetNSamples(),trg->GetSamplesArray());
        trig[t].CalcT0();

        for(UShort_t s=0;s<trg->GetNSamples();s++){
          hist.hist1f_TrigJitter[t]->Fill(trig[t].GetT0());
          //hist.hist2f_TrigCum[t]->Fill(s,trig[t].GetSamp(s));
          hist.hist2f_TrigCumT0Fixed[t]->Fill(s,trig[t].GetSampT0Cor(s));
        }
      } //end trigger for




      PMTChannel chan[nChn];
      // Loop over channels
#pragma omp parallel
#pragma omp for
      for(UChar_t c=0;c<nChn;c++){
        if(c>16)continue;
        TADCChannel* chn = adcB->ADCChannel(c);
        PMTChannel& ch=chan[c];
        ch=c<16?MAPMTChannel():c==16?PhotonisChannel():PMTChannel();
        ch.SetSamples(chn->GetNSamples(),chn->GetSamplesArray());
        ch.CalcPedestal();
        ch.SetT0(trig[c/8].GetT0());
        ch.SetGain( //1 //1
            c==8 ?0.9442707333*0.9905454853    //0.93534311177123537049
            : c==9 ?1.138643573 *1.023798109   //0.93534311177123537049
            : c==10?0.8840603595*0.9976260231  //1.165741136862403457
            : c==11?0.8019266101*0.9574429782  //0.88196162062834130445
            : c==12?0.9830511799*0.9992501964  //0.76779900187197419982
            : c==13?1.003189779 *1.006550073   //0.98231408458632673236
            : c==14?1.360235371 *1.077406706   //1.009760745285303867
            : c==15?1.000365233 *1.007981892   //1.465526710453797926
            :1);

        ch.CalcTimeCharge();

        hist.hist1f_Pedestals[c]->Fill(chan[c].GetPedestal());


        for(UShort_t s=0;s<chn->GetNSamples();s++){
          //hist.hist2f_OscCum[c]->Fill(s,ch.GetVal(s));
          hist.hist2f_OscCumT0Fixed[c]->Fill(s,ch.GetValT0Ped(s));
        }



        hist.hist1f_MeanTimeDistribution[c]->Fill(ch.GetTimeMean());

        hist.hist2f_MeanTimeDistribution_Charge[c]->Fill(ch.GetTimeMean(),ch.GetPhE());
        hist.hist1f_PhElectr[c]->Fill(ch.GetPhE());
        hist.hist1f_PhElectrAbs[c]->Fill(ch.GetPhEAbs());

        //               comm     Y          X
        const double pos8=c==16?1:c<8?8-c%8:16-c+.5;
        const double pos2=c==16?3:c<8?1    :2;

        if(ch.IsFired())
          hist.hist2F_ChanneOccupancy->Fill(pos8,pos2);

      } //end channel for




      for(int chan_i=0;chan_i<nChn;++chan_i){
        PMTChannel& ch=chan[chan_i];
        hist.hist1f_MaxValueDistr[chan_i]->Fill(ch.GetValMax());
      }
      for(int ii=0;ii<nChn;++ii)
        for(int jj=ii+1;jj<nChn;++jj){
          hist.hist2f_PhElectrChCor[ii][jj]->Fill(chan[ii].GetPhE(),chan[jj].GetPhE());
          //hist.hist2f_PhElectrChCorT0Fix[ii][jj]->Fill(pheallchT0Fix[ii],pheallchT0Fix[jj]);
        }

      for(int ii=0;ii<nChn;++ii)
        if(chan[ii].IsFired())
          for(int jj=ii+1;jj<nChn;++jj)
            if(chan[jj].IsFired())
              hist.hist2f_CorrMatrix->Fill(ii,jj);



      static int nfilled=0;
      if( true
          &&chan[16].HasOnePhEExact()
          &&nfilled<100
        ){
        nfilled++;
        for(int ch_i=0;ch_i<=16;++ch_i){
          for(unsigned s=0;s<1024;++s){
            hist.hist2f_PedestalsStudy[ch_i]->SetBinContent(s+1,nfilled,-chan[ch_i].GetValT0Ped(s));
          }
        }
      }



      if( chan[16].HasOnePhEExact()) for(int ch_i=8;ch_i<16;++ch_i) for(int ch_j=ch_i+1;ch_j<16;++ch_j){
        const PMTChannel& chani=chan[ch_i];
        const PMTChannel& chanj=chan[ch_j];
        if(chani.IsFired()&&chanj.IsFired())
          if( int(chani.GetPhE())/5==int(chanj.GetPhE())/5){
            hist.hist2f_TimeDiffMeanTime           [ch_i][ch_j]         ->Fill((chani.GetTimeMean              () - chanj.GetTimeMean              ())/5./*ns*/,sqrt(chani.GetPhE()*chani.GetPhE()+chanj.GetPhE()*chanj.GetPhE()));
            hist.hist2f_TimeDiffMeanTime2          [ch_i][ch_j]         ->Fill((chani.GetTimeMean2             () - chanj.GetTimeMean2             ())/5./*ns*/,sqrt(chani.GetPhE()*chani.GetPhE()+chanj.GetPhE()*chanj.GetPhE()));
            hist.hist2f_TimeDiffMeanTimeAbs        [ch_i][ch_j]         ->Fill((chani.GetTimeMeanAbs           () - chanj.GetTimeMeanAbs           ())/5./*ns*/,sqrt(chani.GetPhE()*chani.GetPhE()+chanj.GetPhE()*chanj.GetPhE()));
            hist.hist2f_TimeDiff2080LeadTrailCros  [ch_i][ch_j]         ->Fill((chani.GetTime2080LeadTrailCross() - chanj.GetTime2080LeadTrailCross())/5./*ns*/,sqrt(chani.GetPhE()*chani.GetPhE()+chanj.GetPhE()*chanj.GetPhE()));
            hist.hist2f_TimeDiff2080LeadZeroCros   [ch_i][ch_j]         ->Fill((chani.GetTime2080LeadZeroCross () - chanj.GetTime2080LeadZeroCross ())/5./*ns*/,sqrt(chani.GetPhE()*chani.GetPhE()+chanj.GetPhE()*chanj.GetPhE()));
            hist.hist2f_TimeDiff2080Lead50         [ch_i][ch_j]         ->Fill((chani.GetTime2080LeadMid       () - chanj.GetTime2080LeadMid       ())/5./*ns*/,sqrt(chani.GetPhE()*chani.GetPhE()+chanj.GetPhE()*chanj.GetPhE()));
            hist.hist2f_TimeDiffHalfMaxValue       [ch_i][ch_j]         ->Fill((chani.GetTimeHalfMax           () - chanj.GetTimeHalfMax           ())/5./*ns*/,sqrt(chani.GetPhE()*chani.GetPhE()+chanj.GetPhE()*chanj.GetPhE()));
            hist.hist2f_TimeDiffMaxValue           [ch_i][ch_j]         ->Fill((chani.GetTimeMaxVal            () - chanj.GetTimeMaxVal            ())/5./*ns*/,sqrt(chani.GetPhE()*chani.GetPhE()+chanj.GetPhE()*chanj.GetPhE()));
          }
      }

#pragma omp parallel
#pragma omp  for
      for(int ch_i=8;ch_i<16;++ch_i){
        if(
            chan[16].HasOnePhEExact()&&
            (ch_i== 8||chan[ 8].IsFired())       &&
            (ch_i== 9||chan[ 9].IsFired())       &&
            (ch_i==10||chan[10].IsFired())       &&
            (ch_i==11||chan[11].IsFired())       &&
            (ch_i==12||chan[12].IsFired())       &&
            (ch_i==13||chan[13].IsFired())       &&
            (ch_i==14||chan[14].IsFired())       &&
            (ch_i==15||chan[15].IsFired())
          ){
          hist.hist1f_PhElectrEff  [ch_i]->Fill(chan[ch_i].     GetPhE());
          hist.hist1f_PhElectrNoise[ch_i]->Fill(chan[ch_i].GetPhENoise());
          hist.hist1f_PhElectrAbsEff  [ch_i]->Fill(chan[ch_i].     GetPhEAbs());
          hist.hist1f_PhElectrAbsNoise[ch_i]->Fill(chan[ch_i].GetPhENoiseAbs());
        }
      }



    } //end board for

    // Clear event
    rawEv->Clear("C");

  } //end event for

  delete rawEv;
  delete bRawEv;
  delete tRawEv;

  fRawEv->Close();
  delete fRawEv;
}
void Analyse::Finalize(){
  Histos& hist=*fHistosP;
  for(int ch_i=8;ch_i<16;++ch_i){
    std::cout
      <<"int "<<ch_i<<"  "
      <<hist.hist1f_PhElectrEff[ch_i]->Integral(
          hist.hist1f_PhElectrEff[ch_i]->FindBin(15),
          hist.hist1f_PhElectrEff[ch_i]->GetNbinsX())
      <<" / "
      <<hist.hist1f_PhElectrEff[ch_i]->GetEntries()

      <<" eff "
      <<100.*
      hist.hist1f_PhElectrEff[ch_i]->Integral(
          hist.hist1f_PhElectrEff[ch_i]->FindBin(15),
          hist.hist1f_PhElectrEff[ch_i]->GetNbinsX())
      /
      hist.hist1f_PhElectrEff[ch_i]->GetEntries()
      <<std::endl;
  }
}
#endif
