#ifndef _R6427_hh_
#define _R6427_hh_
#include"VPMTChannel.hh"
class R6427:public VPMTChannel{
  public:
    R6427(){
      fType="R6427";
      fGain=5;//11.6; //E5
      fFireThreshold=7;
      fSignalRangeBegin  =400;
      fSignalRangeEnd    =550;
      fNoiseRangeBegin   =200;
      fNoiseRangeEnd     =350;
    }
};
#endif
