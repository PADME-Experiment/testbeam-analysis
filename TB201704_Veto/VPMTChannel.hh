#ifndef _VPMTChannel_hh_
#define _VPMTChannel_hh_
#include<utility>
#include<vector>
#include"utlMessageBus.hh"
#include"VSamplingChannel.hh"
class VPMTChannel:public VSamplingChannel{
  public:
    VPMTChannel():
      fGain              (1),
      fSignalRangeBegin  (0),
      fSignalRangeEnd    (0),
      fNoiseRangeBegin   (50),
      fNoiseRangeEnd     (49),
      fPedestalRangeBegin(30),
      fPedestalRangeEnd  (100) {}
    virtual ~VPMTChannel(){}
  public:
    bool IsFired()const{return fPhEAbs>fFireThreshold;}
    void CalcPedestal();

    Short_t GetPedestal()const{return fPedestal;}
    //Short_t GetSampT0PedCor   (int t)const{t-=fT0;return t>=0&&t<fNSamples?fSamples[t]-fPedestal:0;}
    double  GetValT0Ped       (int t)const{t-=fT0;return t>=0&&t<fNSamples?fValues[t]:0;}
    double  GetVal            (int t)const{       return t>=0&&t<fNSamples?fValues[t]:0;}
    double  GetValT0PedLowPass(int t)const{t-=fT0;return t>=0&&t<int(fValuesLowPass.size())?fValuesLowPass[t]:0;}
    //double  GetValT0PedCorLowPass(int t)const{t-=fT0;return t>=0&&t<int(fValuesLowPass.size())?fValuesLowPass[t]-fPedestal:0;}
    double  GetValLowPass     (int t)const{       return t>=0&&t<int(fValuesLowPass.size())?fValuesLowPass[t]:0;}

    double  GetTimeMeanAbs           ()const{return fTimeMeanAbs;}
    double  GetTimeMean2             ()const{return fTimeMean2;}
    double  GetTimeMean              ()const{return fTimeMean;}
    double  GetTimeMaxVal            ()const{return fTimeMaxVal;}
    double  GetTime2080LeadTrailCross()const{return fTime2080LeadTrailCross;}
    double  GetTime2080LeadZeroCross ()const{return fTime2080LeadZeroCross;}
    double  GetTime2080LeadMid       ()const{return fTime2080LeadMid;}
    double  GetTimeHalfMax           ()const{return fTimeHalfMax;}
    double  GetTime01Max           ()const{return fTime01Max;}
    double  GetTime02Max           ()const{return fTime02Max;}
    //double  GetTimePol4    (double v)const{return 

    double  GetTimeIntegral      ()const{return fTimeIntegral;}
    double  GetTimeMeanAbsLowPass()const{return fTimeMeanAbsLowPass;}
    double  GetTimeMeanLowPass   ()const{return fTimeMeanLowPass;   }
    double  GetPhELowPass        ()const{return fPhELowPass;        }
    double  GetPhEAbsLowPass     ()const{return fPhEAbsLowPass;     }
    bool    IsSinglePartBeam     ()const{return fOneParticleRangeBegin<fPhEAbs&&fPhEAbs<fOneParticleRangeEnd;}
    bool    IsDoublePartBeam     ()const{return fTwoParticleRangeBegin<fPhEAbs&&fPhEAbs<fTwoParticleRangeEnd;}

    double GetPhE        ()const{return fPhE;}
    double GetPhEAbs     ()const{return fPhEAbs;}
    double GetPhENoise   ()const{return fPhENoise;}
    double GetPhENoiseAbs()const{return fPhENoiseAbs;}
    double GetValMax     ()const{return fValMax;}

    double GetAllSampMean  ()const{return fAllSampMean  ;}
    double GetAllSampRMS   ()const{return fAllSampRMS   ;}
    double GetAllSampMin   ()const{return fAllSampMin   ;}
    double GetAllSampMax   ()const{return fAllSampMax   ;}
    double GetAllSampAbsSum()const{return fAllSampAbsSum;}

    double GetNoiseSampMean  ()const{return fNoiseSampMean  ;}
    double GetNoiseSampRMS   ()const{return fNoiseSampRMS   ;}
    double GetNoiseSampMin   ()const{return fNoiseSampMin   ;}
    double GetNoiseSampMax   ()const{return fNoiseSampMax   ;}
    double GetNoiseSampAbsSum()const{return fNoiseSampAbsSum;}


    void CalcTimeCharge();
    void   SetGain(double g){fGain=g;}
    //const std::pair<unsigned, unsigned>& GetPedestalRange()const {return fPedestalRange;}
  public:
    //void FFTLowPass(){
    //  FFTLowPass(4);
    //}
    void FFTLowPass(double nFreqToWipe /**<0..NSamples/2*/){
      WARNING(__func__+std::to_string(nFreqToWipe));
      return FFTLowPassGSL(nFreqToWipe);
      //return FFTLowPassMy(nFreqToWipe);
    }
  protected:

    void FFTLowPassGSL(double);
    void FFTLowPassMy (double);
  protected:
    double fAllSampMean;
    double fAllSampRMS;
    double fAllSampMin;
    double fAllSampMax;
    double fAllSampAbsSum;

    double fNoiseSampMean;
    double fNoiseSampRMS;
    double fNoiseSampMin;
    double fNoiseSampMax;
    double fNoiseSampAbsSum;

    double fTimeMeanAbsLowPass;
    double fTimeMeanLowPass;
    double fTimeMeanAbs;
    double fTimeMean2;
    double fTimeMean;
    double fTimeMaxVal;
    double fTime2080LeadTrailCross;
    double fTime2080LeadZeroCross;
    double fTime2080LeadMid;
    double fTimeHalfMax;
    double fTime01Max;
    double fTime02Max;
    double fTimeIntegral;

    double fPhE,fPhE2;
    double fPhEAbs;
    double fPhELowPass;
    double fPhEAbsLowPass;
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
    unsigned int fOneParticleRangeBegin ;
    unsigned int fOneParticleRangeEnd   ;
    unsigned int fTwoParticleRangeBegin ;
    unsigned int fTwoParticleRangeEnd   ;
    double fFireThreshold;

    //std::pair<unsigned,unsigned> fSignalRange;
    //std::pair<unsigned,unsigned> fNoiseRange;
    //std::pair<unsigned,unsigned> fPedestalRange;
    //std::pair<double,double> fOnePheRange;
};
#endif
