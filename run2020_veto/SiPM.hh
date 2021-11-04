#ifndef _SiPM_hh_
#define _SiPM_hh_
#include"VPMTChannel.hh"
class SiPM:public VPMTChannel{
  public:
    SiPM(){
      fType="SiPM";
      fGain=25;//overwiritten in Analyse.cc
      fFireThreshold=15;//7;
      fSignalRangeBegin  =300;
      fSignalRangeEnd    =900;
      fNoiseRangeBegin   =50;
      fNoiseRangeEnd     =250;
      //fPedestalRangeBegin=50;
      //fPedestalRangeEnd  =400;
      //fNoiseRangeEnd     =fNoiseRangeBegin+fSignalRangeEnd-fSignalRangeBegin;
    }
};
#endif
