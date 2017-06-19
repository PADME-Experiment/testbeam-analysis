#ifndef _TerminatedChannel_hh_
#define _TerminatedChannel_hh_
#include"VPMTChannel.hh"
class TerminatedChannel:public VPMTChannel{
  public:
    TerminatedChannel(){
      fType="TerminatedChannel";
      fSignalRangeBegin  =330;
      fSignalRangeEnd    =420;
      fNoiseRangeEnd     =fNoiseRangeBegin+fSignalRangeEnd-fSignalRangeBegin;
    }
};
#endif
