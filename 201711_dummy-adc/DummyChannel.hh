#ifndef _DummyChannel_hh_
#define _DummyChannel_hh_
#include"VPMTChannel.hh"
class DummyChannel:public VPMTChannel{
  public:
    DummyChannel();
    void FitNoiseSlope();
    void CalcMeanRMS();

    void Process(){
      FitNoiseSlope();
      CalcMeanRMS();
    }

    Short_t GetSampT0Cor(int t)const {t-=fT0;t+=1024;t%=1024;return t>=0&&t<fNSamples?fSamples[t]:0;}
    Short_t CorT0(int t)const {t-=fT0;t+=1024;t%=1024;return t>=0&&t<fNSamples?t:0;}

  private:
    const int fMaxSample=995;
    double fLinSlope_a;
    double fLinSlope_b;
    double fLinSlope_rms;
    double fMean;
    double fRMS;
    public:
    double GetLinSlope_a  (){return fLinSlope_a;   }
    double GetLinSlope_b  (){return fLinSlope_b;   }
    double GetLinSlope_rms(){return fLinSlope_rms; }
    double GetMean        (){return fMean;         }
    double GetRMS         (){return fRMS;          }
};
#endif
