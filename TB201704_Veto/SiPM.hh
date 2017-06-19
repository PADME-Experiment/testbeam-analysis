#ifndef _SiPM_hh_
#define _SiPM_hh_
#include"VPMTChannel.hh"
class SiPM:public VPMTChannel{
  public:
    SiPM(){
      fType="SiPM";
      fGain=25;//11.6; //E5
      fFireThreshold=30;//7;
      fSignalRangeBegin  =450;
      fSignalRangeEnd    =800;
      fNoiseRangeBegin=50;
      fNoiseRangeEnd=400;
      fPedestalRangeBegin=50;
      fPedestalRangeEnd  =400;
      //fNoiseRangeEnd     =fNoiseRangeBegin+fSignalRangeEnd-fSignalRangeBegin;
    }
};
#endif
