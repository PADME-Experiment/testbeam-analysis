#ifndef _VCalorimeterChannel_hh_
#define _VCalorimeterChannel_hh_
#include"VPMTChannel.hh"
#include<cmath>
class VCalorimeterChannel:public VPMTChannel{
  public:
    virtual~VCalorimeterChannel(){}
    VCalorimeterChannel(){
      //fGain=1;
      //fSignalRange={400,550}; fNoiseRange={25,175};
      //fPedestalRange={1,180};
      //fOnePheRange={150,300};
      //fFired=false;
    }
    //int GetNParticles(){return fNParticles;}
    //int GetNPart(){return round((fPhEAbs[0]-fOfs)/fMult);}
  protected:
    double fMult;
    double fOfs;
    //int fNParticles;
};
#endif
