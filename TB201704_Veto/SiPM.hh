#ifndef _SiPM_hh_
#define _SiPM_hh_
#include"VPMTChannel.hh"
class SiPM:public VPMTChannel{
  public:
    SiPM(){
      fType="SiPM";
      fGain=25;//overwiritten in Analyse.cc
      fFireThreshold=26;//7;
      fSignalRangeBegin  =450;
      fSignalRangeEnd    =800;
      fNoiseRangeBegin   =100;
      fNoiseRangeEnd     =450;
      //fPedestalRangeBegin=50;
      //fPedestalRangeEnd  =400;
      //fNoiseRangeEnd     =fNoiseRangeBegin+fSignalRangeEnd-fSignalRangeBegin;
    }
};
#endif
