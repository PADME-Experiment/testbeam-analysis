#include"VPMTChannel.hh"

#include<set> //std::multiset
#include<cmath>
#include<iostream>

#include<gsl/gsl_fft_halfcomplex_float.h>
#include<gsl/gsl_fft_real_float.h>

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
  std::multiset<Short_t> peds (&fSamples[fPedestalRangeBegin],&fSamples[fPedestalRangeEnd]);
  auto pedp=peds.begin();
  std::advance(pedp,peds.size()*.50); // median
  fPedestal=*pedp;
  fValues.resize(fNSamples);
  for(int i=0;i<fNSamples;++i) fValues[i]=(fSamples[i]-fPedestal)/4096.;
  // multiset pedestal
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





  fPhE =0;
  fPhE2=0;
  fPhEAbs=0;
  fPhENoise=0;
  fPhENoiseAbs=0;
  fValMax=100;
  fTimeMean=0;
  fTimeMean2=0;
  fTimeMeanAbs=0;
  fPhELowPass        =0;
  fPhEAbsLowPass     =0;
  fTimeMeanLowPass   =0;
  fTimeMeanAbsLowPass=0;
  for(unsigned val_i=fNoiseRangeBegin;val_i<fNoiseRangeEnd;++val_i){
    fPhENoise+=GetValT0Ped(val_i);
    fPhENoiseAbs+=-std::abs(GetValT0Ped(val_i));
  }
  for(unsigned val_i=fSignalRangeBegin;val_i<fSignalRangeEnd;++val_i){
    const double normcor_sample=GetValT0Ped(val_i);
    fPhE   +=normcor_sample;
    fPhE2  +=normcor_sample*normcor_sample;
    fPhEAbs+=-std::abs(normcor_sample);
    fTimeMean +=val_i*normcor_sample;
    fTimeMean2+=val_i*normcor_sample*normcor_sample;
    fTimeMeanAbs+=val_i*(-std::abs(normcor_sample));
    fPhELowPass        +=(                GetValT0PedLowPass(val_i));
    fPhEAbsLowPass     +=(      -std::abs(GetValT0PedLowPass(val_i)));
    fTimeMeanLowPass   +=val_i*(          GetValT0PedLowPass(val_i));
    fTimeMeanAbsLowPass+=val_i*(-std::abs(GetValT0PedLowPass(val_i)));
    if(fValMax>normcor_sample){
      fValMax=normcor_sample;
      fTimeMaxVal=val_i;
    }
  }
  fTimeMean /=fPhE ;
  fTimeMean2/=fPhE2;
  fTimeMeanAbs/=fPhEAbs;
  fTimeMeanLowPass   /=fPhELowPass   ;
  fTimeMeanAbsLowPass/=fPhEAbsLowPass;
  // fGain*1e5
  fPhE        *=-250/fGain;//-41.6/fGain;
  fPhEAbs     *=-250/fGain;//-41.6/fGain;
  fPhENoise   *=-250/fGain;//-41.6/fGain;
  fPhENoiseAbs*=-250/fGain;//-41.6/fGain;
  fPhELowPass   *=-250/fGain;//-41.6/fGain;
  fPhEAbsLowPass*=-250/fGain;//-41.6/fGain;
  //fFired=fPhE>15;


  double summall=0;
  double summtmp=0;
  for(unsigned val_i=fSignalRangeBegin;val_i<fSignalRangeEnd;++val_i){
    const double normcor_sample=GetValT0Ped(val_i);
    summall+=normcor_sample;
  }
  for(unsigned val_i=fSignalRangeBegin;val_i<fSignalRangeEnd;++val_i){
    const double normcor_sample=GetValT0Ped(val_i);
    summtmp+=normcor_sample;
    if(summtmp<=summall*.115){ // best results
      fTimeIntegral=val_i;
      break;
    }
  }



  double y10=fValMax*.1;
  double y20=fValMax*.2;
  double y50=fValMax*.5;
  double y80=fValMax*.8;
  double xl10=-999990;
  double xl20=-999990;
  double xl50=-999990;
  double xl80=-999990;
  double xt20=-999990;
  double xt80=-999990;



  for(UShort_t val_i=fTimeMaxVal;val_i>=fSignalRangeBegin;--val_i){
    const double normcor_sample=GetValT0Ped(val_i);
    if(normcor_sample<y10)xl10=val_i;
    if(normcor_sample<y20)xl20=val_i;
    if(normcor_sample<y50)xl50=val_i;
    if(normcor_sample<y80)xl80=val_i;
  }
  for(UShort_t val_i=fTimeMaxVal;val_i<fSignalRangeEnd;val_i++){
    const double normcor_sample=GetValT0Ped(val_i);
    if(normcor_sample<y20)xt20=val_i;
    if(normcor_sample<y80)xt80=val_i;
  }

  fTime2080LeadTrailCross=(xl20*xt80-xt20*xl80)/(xl20-xl80+xt80-xt20);
  fTime2080LeadMid=(xl80-xl20)/2+xl20;
  fTime2080LeadZeroCross=-y20*(xl80-xl20)/(y80-y20)+xl20;
  fTimeHalfMax=xl50;
  fTime01Max=xl10;
  fTime02Max=xl20;

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
