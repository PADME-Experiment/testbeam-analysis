#ifndef _TerminatedChannel_hh_
#define _TerminatedChannel_hh_
#include"VPMTChannel.hh"
class TerminatedChannel:public VPMTChannel{
  public:
    TerminatedChannel(){
      fType="TerminatedChannel";
      fSignalRange={400,550}; fNoiseRange={25,175};
      fPedestalRange={1,180};
      fOnePheRange={150,300};
      fFired=false;
    }
};
#endif
