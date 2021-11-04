#ifndef _BTFCalorimeterChannel_hh_
#define _BTFCalorimeterChannel_hh_
#include"VCalorimeterChannel.hh"
class BTFCalorimeterChannel:public VCalorimeterChannel{
  public:
    BTFCalorimeterChannel(){
      fGain=6.009615;
      fSignalRangeBegin  =420;
      fSignalRangeEnd    =580;
      fNoiseRangeBegin   =100;
      fNoiseRangeEnd     =210;
      fOneParticleRangeBegin=35;
      fOneParticleRangeEnd  =58;
    }
    void SetVoltage(unsigned v){
      switch (v){
        case 900: fGain=100;break;
        default:throw "unknown voltage";
      }
    }
};
#endif
