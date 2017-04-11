#ifndef _SiPM_hh_
#define _SiPM_hh_
#include"VPMTChannel.hh"
class SiPM:public VPMTChannel{
  public:
    SiPM(){
      fType="SiPM";
      fGain=11.6; //E5
      fFireThreshold=12;//7;
      fSignalRangeBegin  =100;
      fSignalRangeEnd    =500;
      fNoiseRangeBegin=550;
      fNoiseRangeEnd=950;
      fPedestalRangeBegin=550;
      fPedestalRangeEnd  =950;
      //fNoiseRangeEnd     =fNoiseRangeBegin+fSignalRangeEnd-fSignalRangeBegin;
    }
};
#endif
