#ifndef _VCalorimeterChannel_hh_
#define _VCalorimeterChannel_hh_
#include"VPMTChannel.hh"
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
    virtual void SetVoltage(unsigned i){fGain=i;}
  protected:
    //int fNParticles;
};
#endif
