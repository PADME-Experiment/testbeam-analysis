#ifndef _VPMTChannel_hh_
#define _VPMTChannel_hh_
#include<utility>
#include<vector>
#include"VSamplingChannel.hh"
class VPMTChannel:public VSamplingChannel{
  public:
  VPMTChannel():
  fSignalRangeBegin  (0),
  fSignalRangeEnd    (0),
  fNoiseRangeBegin   (50),
  fNoiseRangeEnd     (0),
  fPedestalRangeBegin(30),
  fPedestalRangeEnd  (250) {}
    virtual ~VPMTChannel(){}
  public:
    bool IsFired()const{return fFired;}
    void CalcPedestal();

    Short_t GetPedestal()const{return fPedestal;}
    Short_t GetSampT0PedCor   (int t)const{t-=fT0;return t>=0&&t<fNSamples?fSamples[t]-fPedestal:0;}
    double  GetValT0Ped       (int t)const{t-=fT0;return t>=0&&t<fNSamples?fValues[t]:0;}
    double  GetVal            (int t)const{       return t>=0&&t<fNSamples?fValues[t]:0;}
    double  GetValT0PedLowPass(int t)const{t-=fT0;return t>=0&&t<int(fValuesLowPass.size())?fValuesLowPass[t]:0;}
    double  GetValLowPass     (int t)const{       return t>=0&&t<int(fValuesLowPass.size())?fValuesLowPass[t]:0;}

    double  GetTimeMeanAbs           ()const{return fTimeMeanAbs;}
    double  GetTimeMean2             ()const{return fTimeMean2;}
    double  GetTimeMean              ()const{return fTimeMean;}
    double  GetTimeMaxVal            ()const{return fTimeMaxVal;}
    double  GetTime2080LeadTrailCross()const{return fTime2080LeadTrailCross;}
    double  GetTime2080LeadZeroCross ()const{return fTime2080LeadZeroCross;}
    double  GetTime2080LeadMid       ()const{return fTime2080LeadMid;}
    double  GetTimeHalfMax           ()const{return fTimeHalfMax;}
    bool    HasOnePhEExact           ()const{return fPhEAbs>fOnePheRange.first&&fPhEAbs<fOnePheRange.second;}

    double GetPhE        ()const{return fPhE;}
    double GetPhEAbs     ()const{return fPhEAbs;}
    double GetPhENoise   ()const{return fPhENoise;}
    double GetPhENoiseAbs()const{return fPhENoiseAbs;}
    double GetValMax     ()const{return fValMax;}

    void CalcTimeCharge();
    void   SetGain(double g){fGain=g;}
    //const std::pair<unsigned, unsigned>& GetPedestalRange()const {return fPedestalRange;}
  public:
    //void FFTLowPass(){
    //  FFTLowPass(4);
    //}
    void FFTLowPass(double nFreqToWipe /**<0..NSamples/2*/);
  protected:
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
    std::vector<float> fValuesLowPass; /// [mV]

    unsigned int fSignalRangeBegin   ;
    unsigned int fSignalRangeEnd     ;
    unsigned int fNoiseRangeBegin    ;
    unsigned int fNoiseRangeEnd      ;
    unsigned int fPedestalRangeBegin ;
    unsigned int fPedestalRangeEnd   ;

    std::pair<unsigned,unsigned> fSignalRange;
    std::pair<unsigned,unsigned> fNoiseRange;
    std::pair<unsigned,unsigned> fPedestalRange;
    bool fFired;
    std::pair<double,double> fOnePheRange;
};
#endif
