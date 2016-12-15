#ifndef _BaF2CalorimeterChannel_hh_
#define _BaF2CalorimeterChannel_hh_
#include"VCalorimeterChannel.hh"
class BaF2CalorimeterChannel:public VCalorimeterChannel{
  public:
    BaF2CalorimeterChannel(){
      fGain=1;

      fFired=false;
    }
};
#endif
