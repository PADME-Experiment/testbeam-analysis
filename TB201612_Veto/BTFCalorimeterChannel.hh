#ifndef _BTFCalorimeterChannel_hh_
#define _BTFCalorimeterChannel_hh_
#include"VCalorimeterChannel.hh"
class BTFCalorimeterChannel:public VCalorimeterChannel{
  public:
    BTFCalorimeterChannel(){
      fGain=1;
      fSignalRangeBegin  =430;
      fSignalRangeEnd    =600;
      fNoiseRangeEnd     =fNoiseRangeBegin+fSignalRangeEnd-fSignalRangeBegin;
fOnePheRange={40,60};
      fFired=false;
    }
    void SetVoltage(unsigned v){
      switch (v){
        case 900: fGain=100;break;
        default:throw "unknown voltage";
      }
    }
};
#endif
