#ifndef _H9500_hh_
#define _H9500_hh_
#include"VPMTChannel.hh"
class H9500:public VPMTChannel{
  public:
    H9500(){
      fType="H9500";
      fGain=6.5; //E5
      fFireThreshold=11;//6;
      fSignalRangeBegin  =330;
      fSignalRangeEnd    =420;
      fNoiseRangeEnd     =fNoiseRangeBegin+fSignalRangeEnd-fSignalRangeBegin;
    }

};
#endif
