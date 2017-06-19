#ifndef _DummyChannel_hh_
#define _DummyChannel_hh_
#include"VPMTChannel.hh"
class DummyChannel:public VPMTChannel{
  public:
    DummyChannel(){
      fType="DummyChannel";
      fSignalRangeBegin  =330;
      fSignalRangeEnd    =420;
      fNoiseRangeEnd     =fNoiseRangeBegin+fSignalRangeEnd-fSignalRangeBegin;
    }
};
#endif
