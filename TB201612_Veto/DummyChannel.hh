#ifndef _DummyChannel_hh_
#define _DummyChannel_hh_
#include"VPMTChannel.hh"
class DummyChannel:public VPMTChannel{
  public:
    DummyChannel(){
      fType="DummyChannel";
      fSignalRange={400,550}; fNoiseRange={25,175};
      fPedestalRange={1,180};
      fOnePheRange={150,300};
      fFired=false;
    }
};
#endif
