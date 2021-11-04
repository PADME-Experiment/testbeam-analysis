#ifndef _TriggerChannel_hh_
#define _TriggerChannel_hh_
#include"VSamplingChannel.hh"
class TriggerChannel: public VSamplingChannel{
  public:
    TriggerChannel(){
      fType="Trigger";
    }
    void CalcT0(){
      for(unsigned s=0;s<fNSamples/2;++s){ if(fSamples[s]>1500)fT0=340-s; }
    }
};
#endif
