#ifndef _BTFCalorimeterChannel_hh_
#define _BTFCalorimeterChannel_hh_
#include"VCalorimeterChannel.hh"
class BTFCalorimeterChannel:public VCalorimeterChannel{
  public:
    BTFCalorimeterChannel(){
      fGain=2.5;//6.009615;

      fSignalRangeBegin  =500;//450;
      fSignalRangeEnd    =660;//700;
      fNoiseRangeBegin   =100;
      fNoiseRangeEnd     =360;
      //fPedestalRangeBegin=100;
      //fPedestalRangeEnd  =350;



      //fSignalRangeBegin  =430;
      //fSignalRangeEnd    =600;
      //fNoiseRangeEnd     =fNoiseRangeBegin+fSignalRangeEnd-fSignalRangeBegin;
      fOneParticleRangeBegin=80;//50-12;
      fOneParticleRangeEnd  =290;//50+12;
      fTwoParticleRangeBegin=350;
      fTwoParticleRangeEnd  =520;
      fFireThreshold=50;
    }
    void SetVoltage(unsigned v){
      switch (v){
        case 900: fGain=100;break;
        default:throw "unknown voltage";
      }
    }
};
#endif
