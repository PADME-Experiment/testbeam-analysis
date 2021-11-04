#include"VPMTChannel.hh"
#include"Universe.hh"

#include<set> //std::multiset
#include<cmath>
#include<iostream>

#include<gsl/gsl_fft_halfcomplex_float.h>
#include<gsl/gsl_fft_real_float.h>


    void VPMTChannel::CalcPeaksTSpectrum(){
      //Universe::GetInstance().fHist.GotoDir("tsp");
      //TH1D* H1 = new TH1D("h1","h1",1000,0.,1000.);
      //double arr[1026];
      //double min=5000;
      //double max=0;
      //for(int i=0; i<1024;++i){
      //  if(min>fSamples[i])min=fSamples[i];
      //  if(max<fSamples[i])max=fSamples[i];
      //}
      //for(int i=0; i<1024;++i){
      //    arr[i+1]=(max-fSamples[i])/4096;//(max-min);
      //}
      //arr[1]=1;


      //H1->SetContent(arr);
      //TSpectrum *tsp=new TSpectrum(10);
      //Int_t nfound = tsp->Search(H1);
      //fTSpeTimes.clear();
      //for(Int_t ll=0;ll<nfound;ll++){
      //  Double_t xp   =tsp->GetPositionX()[ll];
      //  Double_t yp   =tsp->GetPositionY()[ll];
      //  fTSpeTimes.push_back(xp+fT0);
      //}
      //static int nfil=0;
      //if(nfil++<100) H1->Write();
      //delete H1;
      //delete tsp;
    }



  void
VPMTChannel::CalcPedestal()
{
  if(
      fPedestalRangeBegin>=fNSamples||
      fPedestalRangeEnd>=fNSamples||
      fPedestalRangeEnd-fPedestalRangeBegin<5
    ){
    fPedestal=0;
    return;
  }
  // multiset pedestal
  std::multiset<Short_t> peds (&fSamples[fPedestalRangeBegin],&fSamples[fPedestalRangeEnd]); //FIXME: use GetSamp as it has per cell pedestal calibration
  auto pedp=peds.begin();
  std::advance(pedp,peds.size()*.50); // median
  fPedestal=*pedp;
  fValues.resize(fNSamples);
  for(int i=0;i<fNSamples;++i) fValues[i]=(GetSamp(i)-fPedestal)/4096.;
  // multiset pedestal
}

void VPMTChannel::CalcPZFilter(){
  fValuesPZcorrected.clear();
  fValuesPZcorrected.resize(fNSamples);
  double r1=392;
  double r2=104;
  double c=0.1426;
  double integral=0;
  double ic[1024];
  ic[0]=GetValT0Ped(0)/r2;
  for(unsigned val_i=1;val_i<1024;++val_i){
    const double normcor_sample=GetValT0Ped(val_i);
    integral+=ic[val_i-1];
    ic[val_i]=normcor_sample/r2-((r1+r2)/(c*r1*r2))*integral;
    fValuesPZcorrected[val_i]=-(normcor_sample-integral/c);
  }
}

  void
VPMTChannel::CalcTimeCharge()
{
  fAllSampMean   =0;
  fAllSampRMS    =0;
  fAllSampMin    =9999;
  fAllSampMax    =-9999;
  fAllSampAbsSum =0;
  for(unsigned val_i=0;val_i<1024;++val_i){
    const double normcor_sample=GetValT0Ped(val_i);
    fAllSampAbsSum+=abs(normcor_sample);
    fAllSampMean+=normcor_sample;
    fAllSampRMS +=normcor_sample*normcor_sample;
    fAllSampMin =(fAllSampMin>normcor_sample?normcor_sample:fAllSampMin);
    fAllSampMax =(fAllSampMax<normcor_sample?normcor_sample:fAllSampMax);
  }
  fAllSampRMS=(fAllSampRMS/1024-fAllSampMean*fAllSampMean)/1024;
  fAllSampMean/=1024;


  fNoiseSampMean   =0;
  fNoiseSampRMS    =0;
  fNoiseSampMin    =9999;
  fNoiseSampMax    =-9999;
  fNoiseSampAbsSum =0;
  for(unsigned val_i=0;val_i<400;++val_i){
    const double normcor_sample=GetValT0Ped(val_i);
    fNoiseSampAbsSum+=abs(normcor_sample);
    fNoiseSampMean+=normcor_sample;
    fNoiseSampRMS +=normcor_sample*normcor_sample;
    fNoiseSampMin =(fNoiseSampMin>normcor_sample?normcor_sample:fNoiseSampMin);
    fNoiseSampMax =(fNoiseSampMax<normcor_sample?normcor_sample:fNoiseSampMax);
  }
  fNoiseSampRMS=(fNoiseSampRMS/1024-fNoiseSampMean*fNoiseSampMean)/1024;
  fNoiseSampMean/=1024;



  ClearTimes();
  CalcPZFilter();


  //calculate peak ranges
  for(int i=0;i<fValuesPZcorrected.size();++i){


    if(fValuesPZcorrected[i]<.005)continue; // 5 mV threshod
    int countAboveThr=0;
    int countBelowThr=0;
    int start=i;
    while(1){
      if(
          (i<=1023&&fValuesPZcorrected[i  ]>=0.005)|| // 5 mV threshold
          (i<=1022&&fValuesPZcorrected[i+1]>=0.005)||
          (i<=1021&&fValuesPZcorrected[i+2]>=0.005)
        ){
        countAboveThr++;
        i++;
      }else{
        break;
      }
    }
    if(countAboveThr<15)break;
    int stop=i;
    while(1){
      if(
          (i<=1023&&fValuesPZcorrected[i  ]<0.005)|| // 5 mV threshold
          (i<=1022&&fValuesPZcorrected[i+1]<0.005)||
          (i<=1021&&fValuesPZcorrected[i+2]<0.005)
        ){
        countBelowThr++;
        i++;
      }else{
        break;
      }
    }
    if(countBelowThr<5)break;
    fPeakRanges.emplace_back(start,stop);
  }

  double PhENoise     =0;
  double PhENoiseAbs  =0;



  for(unsigned val_i=fNoiseRangeBegin;val_i<fNoiseRangeEnd;++val_i){
    PhENoise+=GetValT0Ped(val_i);
    PhENoiseAbs+=-std::abs(GetValT0Ped(val_i));
  }



  for(auto sigrange_it=fPeakRanges.begin();sigrange_it!=fPeakRanges.end();sigrange_it++){
    double PhE          =0;
    double PhE2         =0;
    double PhEAbs       =0;
    double PhELowPass   =0;
    double PhEAbsLowPass=0;
    double ValMax       =0;
    double TimeMaxVal   =0;

    double TimeMean          =0;
    double TimeMean2         =0;
    double TimeMeanAbs       =0;
    double TimeMeanLowPass   =0;
    double TimeMeanAbsLowPass=0;
    double TimeIntegral      =0;

    for(unsigned val_i=sigrange_it->first;val_i<sigrange_it->second;++val_i){
      const double normcor_sample=GetValT0Ped(val_i);
      PhE   +=normcor_sample;
      PhE2  +=normcor_sample*normcor_sample;
      PhEAbs+=-std::abs(normcor_sample);
      TimeMean +=val_i*normcor_sample;
      TimeMean2+=val_i*normcor_sample*normcor_sample;
      TimeMeanAbs+=val_i*(-std::abs(normcor_sample));
      PhELowPass        +=(                GetValT0PedLowPass(val_i));
      PhEAbsLowPass     +=(      -std::abs(GetValT0PedLowPass(val_i)));
      TimeMeanLowPass   +=val_i*(          GetValT0PedLowPass(val_i));
      TimeMeanAbsLowPass+=val_i*(-std::abs(GetValT0PedLowPass(val_i)));
      if(ValMax>normcor_sample){
        ValMax=normcor_sample;
        TimeMaxVal=val_i;
      }
    }
    TimeMean /=PhE ;
    TimeMean2/=PhE2;
    TimeMeanAbs/=PhEAbs;
    TimeMeanLowPass   /=PhELowPass   ;
    TimeMeanAbsLowPass/=PhEAbsLowPass;
    // fGain*1e5
    PhE          *=-250/fGain;//-41.6/fGain;
    PhEAbs       *=-250/fGain;//-41.6/fGain;
    PhENoise     *=-250/fGain;//-41.6/fGain;
    PhENoiseAbs  *=-250/fGain;//-41.6/fGain;
    PhELowPass   *=-250/fGain;//-41.6/fGain;
    PhEAbsLowPass*=-250/fGain;//-41.6/fGain;


    fPhE          .push_back(PhE          );
    fPhE2         .push_back(PhE2         );
    fPhEAbs       .push_back(PhEAbs       );
    fPhENoise     .push_back(PhENoise     );
    fPhENoiseAbs  .push_back(PhENoiseAbs  );
    fPhELowPass   .push_back(PhELowPass   );
    fPhEAbsLowPass.push_back(PhEAbsLowPass);
    fValMax       .push_back(ValMax       );
    fTimeMaxVal   .push_back(TimeMaxVal   );


    fTimeMean          .push_back(TimeMean          );
    fTimeMean2         .push_back(TimeMean2         );
    fTimeMeanAbs       .push_back(TimeMeanAbs       );
    fTimeMeanLowPass   .push_back(TimeMeanLowPass   );
    fTimeMeanAbsLowPass.push_back(TimeMeanAbsLowPass);



    double summall=0;
    double summtmp=0;
    for(unsigned val_i=sigrange_it->first;val_i<sigrange_it->second;++val_i){
      const double normcor_sample=GetValT0Ped(val_i);
      summall+=normcor_sample;
    }
    for(unsigned val_i=sigrange_it->first;val_i<sigrange_it->second;++val_i){
      const double normcor_sample=GetValT0Ped(val_i);
      summtmp+=normcor_sample;
      if(summtmp<=summall*.115){ // best results
        TimeIntegral=val_i;
        break;
      }
    }
    fTimeIntegral.push_back(TimeIntegral);



    double y10=ValMax*.1;
    double y20=ValMax*.2;
    double y50=ValMax*.5;
    double y80=ValMax*.8;
    double xl10=-999990;
    double xl20=-999990;
    double xl50=-999990;
    double xl80=-999990;
    double xt20=-999990;
    double xt80=-999990;



    for(UShort_t val_i=TimeMaxVal;val_i>=sigrange_it->first;--val_i){
      const double normcor_sample=GetValT0Ped(val_i);
      if(normcor_sample<y10)xl10=val_i;
      if(normcor_sample<y20)xl20=val_i;
      if(normcor_sample<y50)xl50=val_i;
      if(normcor_sample<y80)xl80=val_i;
    }
    for(UShort_t val_i=TimeMaxVal;val_i<sigrange_it->second;val_i++){
      const double normcor_sample=GetValT0Ped(val_i);
      if(normcor_sample<y20)xt20=val_i;
      if(normcor_sample<y80)xt80=val_i;
    }

    double Time2080LeadTrailCross=(xl20*xt80-xt20*xl80)/(xl20-xl80+xt80-xt20);
    double Time2080LeadMid       =(xl80-xl20)/2+xl20;
    double Time2080LeadZeroCross =-y20*(xl80-xl20)/(y80-y20)+xl20;
    double TimeHalfMax           =xl50;
    double Time01Max             =xl10;
    double Time02Max             =xl20;
    fTime2080LeadTrailCross.push_back(Time2080LeadTrailCross);
    fTime2080LeadMid       .push_back(Time2080LeadMid       );
    fTime2080LeadZeroCross .push_back(Time2080LeadZeroCross );
    fTimeHalfMax           .push_back(TimeHalfMax           );
    fTime01Max             .push_back(Time01Max             );
    fTime02Max             .push_back(Time02Max             );

  }// sigrange_it



  //CalcPeaksTSpectrum();
}


  void
VPMTChannel::FFTLowPassGSL(double nFreqToWipe /**<0..NSamples/2*/)
{
  fValuesLowPass=fValues;
  if(nFreqToWipe<0||nFreqToWipe>=fNSamples/2){
    std::cerr
      <<"nFreqToWipe="
      <<nFreqToWipe
      <<" is out of range [0.."
      <<fNSamples/2
      <<"). Will do nothing!"
      <<std::endl;
    return;
  }
  const double pi=acos(-1);

  gsl_fft_real_float_radix2_transform(&fValuesLowPass[0],1,fNSamples);
  for(int fk=512;fk>512-nFreqToWipe;--fk){ //freq to kill
    fValuesLowPass[0]+=2*(
        fValuesLowPass[fk]*sin(2*pi*fk)+
        fValuesLowPass[fNSamples-fk]*(1-cos(-2*pi*fk))
        );
    fValuesLowPass[fk]=fValuesLowPass[fNSamples-fk]=0;
  }
  gsl_fft_halfcomplex_float_radix2_inverse(&fValuesLowPass[0],1,fNSamples);
}


  void
VPMTChannel::FFTLowPassMy(double nFreqToWipe /**<0..NSamples/2*/)
{
  if(nFreqToWipe<0||nFreqToWipe>=fNSamples/2){
    std::cerr
      <<"nFreqToWipe="
      <<nFreqToWipe
      <<" is out of range [0.."
      <<fNSamples/2
      <<"). Will do nothing!"
      <<std::endl;
    fValuesLowPass=fValues;
    return;
  }
  const unsigned nDat=fNSamples;
  const unsigned nFreq=nDat/2-nFreqToWipe;
  const double df=-2*acos(-1.)/nDat;
  fValuesLowPass.resize(nDat);
  std::vector<double> Re;Re.resize(nFreq);
  std::vector<double> Im;Im.resize(nFreq,0);
  for(unsigned f=0;f<nFreq;++f){
    for(unsigned t=0;t<nDat;++t){
      Re[f]+=fValues[t]*cos(df*t*f);
      Im[f]+=fValues[t]*sin(df*t*f);
    }
    //Re[0]-=Re[f]; //background subtraction
  }
  for(unsigned t=0;t<nDat;++t){
    fValuesLowPass[t]=Re[0];
    for(unsigned f=1;f<nFreq;++f){
      fValuesLowPass[t]+=2*(Re[f]*cos(df*t*f)+Im[f]*(sin(df*t*f)));
    }
    fValuesLowPass[t]/=nDat;
  }
}
