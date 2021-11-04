#include"DummyChannel.hh"
#include<cmath>

DummyChannel::DummyChannel()
{
  fType="DummyChannel";
  fSignalRangeBegin  =330;
  fSignalRangeEnd    =420;
  fNoiseRangeEnd     =fNoiseRangeBegin+fSignalRangeEnd-fSignalRangeBegin;
  fFireThreshold=-1000000;

  fPedestalRangeBegin=0;
  fPedestalRangeEnd  =1023;
}

  void
DummyChannel::FitNoiseSlope()
{
  double s=0;
  double sx=0;
  double sxx=0;
  double sxy=0;
  double sy=0;
  for(int x=0;x<fMaxSample;++x){
    s+=1;
    sxy+=x*fSamples[x];
    sy+=fSamples[x];
    sx+=x;
    sxx+=x*x;
  }
  double delta=s*sxx-sx*sx;
  double a=(sxx*sy-sx*sxy)/delta;
  double b=(s*sxy-sx*sy)/delta;
  long double rms=0;
  for(int x=0;x<fMaxSample;++x){
    rms+=(a+b*x-fSamples[x])*(a+b*x-fSamples[x]);
  }
  rms=sqrt(rms);
  fLinSlope_a=a;
  fLinSlope_b=b;
  fLinSlope_rms=rms;
}

  void
DummyChannel::CalcMeanRMS()
{
  fMean=0;
  fRMS=0;
  long double rms=0;
  for(int x=0;x<fMaxSample;++x){
    fMean+=fSamples[x];
  }
  fMean/=fMaxSample;
  for(int x=0;x<fMaxSample;++x){
    rms+=(fSamples[x]-fMean)*(fSamples[x]-fMean);
  }
  fRMS=sqrt(rms);
}
