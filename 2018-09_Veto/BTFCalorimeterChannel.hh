#ifndef _BTFCalorimeterChannel_hh_
#define _BTFCalorimeterChannel_hh_
#include"VCalorimeterChannel.hh"
class BTFCalorimeterChannel:public VCalorimeterChannel{
  public:
    BTFCalorimeterChannel(){
      fGain=6.009615;

      fSignalRangeBegin  =450;
      fSignalRangeEnd    =700;
      fNoiseRangeBegin=100;
      fNoiseRangeEnd=350;
      fPedestalRangeBegin=100;
      fPedestalRangeEnd  =350;



      //fSignalRangeBegin  =430;
      //fSignalRangeEnd    =600;
      //fNoiseRangeEnd     =fNoiseRangeBegin+fSignalRangeEnd-fSignalRangeBegin;
      fOneParticleRangeBegin=62;//50-12;
      fOneParticleRangeEnd  =115;//50+12;
      fTwoParticleRangeBegin=180;
      fTwoParticleRangeEnd  =250;
      fFireThreshold=32;
    }
    void SetVoltage(unsigned v){
      switch (v){
        case 900: fGain=100;break;
        default:throw "unknown voltage";
      }
    }
};
#endif
