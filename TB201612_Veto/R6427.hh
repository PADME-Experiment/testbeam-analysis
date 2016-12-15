#ifndef _R6427_hh_
#define _R6427_hh_
#include"VPMTChannel.hh"
class R6427:public VPMTChannel{
  public:
    R6427(){
      fType="R6427";
      fGain=1;
      fFireThreshold=14;
      fSignalRangeBegin  =400;
      fSignalRangeEnd    =600;
      fNoiseRangeEnd     =fNoiseRangeBegin+fSignalRangeEnd-fSignalRangeBegin;
    }
};
#endif
