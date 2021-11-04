#include"Analyse.hh"


#include"Universe.hh"
#include"exec_options.hh"

#include"utlMessageBus.hh"

#include<TFile.h>
#include<TH1F.h>
#include<TH2F.h>

#include<sstream>
#include<math.h>


#include <json/json.h>
#include<fstream>



void SubDetector::Analyse() {
  for(int i=0;i<fChan.size()-1;++i){
    for(int k=0;k<fChan[i+1]->fPeakRanges.size();++k){
      for(int l=0;l<fChan[i  ]->fPeakRanges.size();++l){
        const double ampl = sqrt(fChan[i]->fPhEAbs[l] * fChan[i+1]->fPhEAbs[k]);

        hist2f_TimeDiffMaxValue         [i]->Fill((fChan[i+1]->fTimeMaxVal            [k] - fChan[i]->fTimeMaxVal            [l])/2.5/*ns*/,ampl);
        hist2f_TimeDiffMeanTime         [i]->Fill((fChan[i+1]->fTimeMean              [k] - fChan[i]->fTimeMean              [l])/2.5/*ns*/,ampl);
        hist2f_TimeDiffMeanTime2        [i]->Fill((fChan[i+1]->fTimeMean2             [k] - fChan[i]->fTimeMean2             [l])/2.5/*ns*/,ampl);
        hist2f_TimeDiffMeanTimeAbs      [i]->Fill((fChan[i+1]->fTimeMeanAbs           [k] - fChan[i]->fTimeMeanAbs           [l])/2.5/*ns*/,ampl);
        hist2f_TimeDiff2080LeadTrailCros[i]->Fill((fChan[i+1]->fTime2080LeadTrailCross[k] - fChan[i]->fTime2080LeadTrailCross[l])/2.5/*ns*/,ampl);
        hist2f_TimeDiff2080LeadZeroCros [i]->Fill((fChan[i+1]->fTime2080LeadZeroCross [k] - fChan[i]->fTime2080LeadZeroCross [l])/2.5/*ns*/,ampl);
        hist2f_TimeDiff2080Lead50       [i]->Fill((fChan[i+1]->fTime2080LeadMid       [k] - fChan[i]->fTime2080LeadMid       [l])/2.5/*ns*/,ampl);
        hist2f_TimeDiffHalfMaxValue     [i]->Fill((fChan[i+1]->fTimeHalfMax           [k] - fChan[i]->fTimeHalfMax           [l])/2.5/*ns*/,ampl);
        hist2f_TimeDiff01MaxValue       [i]->Fill((fChan[i+1]->fTime01Max             [k] - fChan[i]->fTime01Max             [l])/2.5/*ns*/,ampl);
        hist2f_TimeDiff02MaxValue       [i]->Fill((fChan[i+1]->fTime02Max             [k] - fChan[i]->fTime02Max             [l])/2.5/*ns*/,ampl);
        hist2f_TimeDiffIntegral         [i]->Fill((fChan[i+1]->fTimeIntegral          [k] - fChan[i]->fTimeIntegral          [l])/2.5/*ns*/,ampl);
      }
    }

    for(auto i_it=fChan[i+1]->fTSpeTimes.begin();i_it!=fChan[i+1]->fTSpeTimes.end();i_it++){
      for(auto j_it=fChan[i]->fTSpeTimes.begin();j_it!=fChan[i]->fTSpeTimes.end();j_it++){
        hist1f_TimeTSpectrum[i]->Fill((*i_it)-(*j_it));
      }
    }
  }

}



void SubDetector::CreateHistos(Histos& hist){

  if(fIsHistDone) return;
  fIsHistDone=true;

  //INFO("create histos");


  std::string name, title;
  TObject* tmptobj;
  std::string lab=";ns;PhE[X]*PhE[Y]";

  hist.GotoDir(fDetName+"_TimeDiffMaxValue");

  for(int i=0;i<fChan.size()-1;i++){
    std::stringstream ss;


    ss<<"_ch"<<i+1<<"_ch"<<i;
    //INFO(ss.str());
    std::string a;

    a="TimeDiffMaxValue"         ;hist.GotoDir(fDetName+"_"+a);hist2f_TimeDiffMaxValue         .push_back( new TH2F((fDetName+"_"+a+ss.str()).c_str(),(a+ss.str()+lab).c_str()          ,320,-40-.5,40-.5,200,-20,780));
    a="TimeDiffMeanTime"         ;hist.GotoDir(fDetName+"_"+a);hist2f_TimeDiffMeanTime         .push_back( new TH2F((fDetName+"_"+a+ss.str()).c_str(),(a+ss.str()+lab).c_str()          ,320,-40-.5,40-.5,200,-20,780));
    a="TimeDiffMeanTime2"        ;hist.GotoDir(fDetName+"_"+a);hist2f_TimeDiffMeanTime2        .push_back( new TH2F((fDetName+"_"+a+ss.str()).c_str(),(a+ss.str()+lab).c_str()          ,320,-40-.5,40-.5,200,-20,780));
    a="TimeDiffMeanTimeAbs"      ;hist.GotoDir(fDetName+"_"+a);hist2f_TimeDiffMeanTimeAbs      .push_back( new TH2F((fDetName+"_"+a+ss.str()).c_str(),(a+ss.str()+lab).c_str()          ,320,-40-.5,40-.5,200,-20,780));
    a="TimeDiff2080LeadTrailCros";hist.GotoDir(fDetName+"_"+a);hist2f_TimeDiff2080LeadTrailCros.push_back( new TH2F((fDetName+"_"+a+ss.str()).c_str(),(a+ss.str()+lab).c_str()          ,320,-40-.5,40-.5,200,-20,780));
    a="TimeDiff2080LeadZeroCros" ;hist.GotoDir(fDetName+"_"+a);hist2f_TimeDiff2080LeadZeroCros .push_back( new TH2F((fDetName+"_"+a+ss.str()).c_str(),(a+ss.str()+lab).c_str()          ,320,-40-.5,40-.5,200,-20,780));
    a="TimeDiff2080Lead50"       ;hist.GotoDir(fDetName+"_"+a);hist2f_TimeDiff2080Lead50       .push_back( new TH2F((fDetName+"_"+a+ss.str()).c_str(),(a+ss.str()+lab).c_str()          ,320,-40-.5,40-.5,200,-20,780));
    a="TimeDiffHalfMaxValue"     ;hist.GotoDir(fDetName+"_"+a);hist2f_TimeDiffHalfMaxValue     .push_back( new TH2F((fDetName+"_"+a+ss.str()).c_str(),(a+ss.str()+lab).c_str()          ,320,-40-.5,40-.5,200,-20,780));
    a="TimeDiff01MaxValue"       ;hist.GotoDir(fDetName+"_"+a);hist2f_TimeDiff01MaxValue       .push_back( new TH2F((fDetName+"_"+a+ss.str()).c_str(),(a+ss.str()+lab).c_str()          ,320,-40-.5,40-.5,200,-20,780));
    a="TimeDiff02MaxValue"       ;hist.GotoDir(fDetName+"_"+a);hist2f_TimeDiff02MaxValue       .push_back( new TH2F((fDetName+"_"+a+ss.str()).c_str(),(a+ss.str()+lab).c_str()          ,320,-40-.5,40-.5,200,-20,780));
    a="TimeDiffIntegral"         ;hist.GotoDir(fDetName+"_"+a);hist2f_TimeDiffIntegral         .push_back( new TH2F((fDetName+"_"+a+ss.str()).c_str(),(a+ss.str()+lab).c_str()          ,320,-40-.5,40-.5,200,-20,780));
    a="TimeDiffTSpectrum"        ;hist.GotoDir(fDetName+"_"+a);hist1f_TimeTSpectrum            .push_back( new TH1F((fDetName+"_"+a+ss.str()).c_str(),(a+ss.str()+lab).c_str()          ,320,-40-.5,40-.5));
  }

  //SUCCESS("create histos "+std::to_string(fAllObj.size()));
}









Universe& Universe::GetInstance(){
  static Universe a;
  return a;
}

Universe::Universe():
  fHist(ExecutableOptions::GetInstance().fOutputRootFile),
  fIsMappingDone(false)
{

  std::string caldatjson = ExecutableOptions::GetInstance().GetCellCalDatFile();
  if(caldatjson.size()==0){
     INFO("No Cell CalDat used");
     return;
  }
  INFO("read Cell CalDat from "+caldatjson);

  Json::Value caldat;
  std::ifstream caldat_file(caldatjson.c_str(), std::ifstream::binary);
  caldat_file >>caldat;
  for(auto it=caldat.begin();it!=caldat.end();it++){
    for(int ch=0;ch<32;++ch){
      for(int cell=0;cell<1024;++cell){
        fADCCellCallDat[std::atoi(it.key().asString().c_str())][ch][cell][0]=
          caldat[it.key().asString()][ch][cell][0].asDouble();
        fADCCellCallDat[std::atoi(it.key().asString().c_str())][ch][cell][1]=
          caldat[it.key().asString()][ch][cell][1].asDouble();
        fADCCellCallDat[std::atoi(it.key().asString().c_str())][ch][cell][2]=
          caldat[it.key().asString()][ch][cell][2].asDouble();
        fADCCellCallDat[std::atoi(it.key().asString().c_str())][ch][cell][3]=
          caldat[it.key().asString()][ch][cell][3].asDouble();
        fADCCellCallDat[std::atoi(it.key().asString().c_str())][ch][cell][4]=
          caldat[it.key().asString()][ch][cell][4].asDouble();
        fADCCellCallDat[std::atoi(it.key().asString().c_str())][ch][cell][5]=
          caldat[it.key().asString()][ch][cell][5].asDouble();
      }
    }
  }
}


void Universe::Map(){
  if(fIsMappingDone)return;
  fIsMappingDone=true;
  WARNING("this should be called once");
  //MapPVeto();
  //MapEVeto();
  //MapHEPVeto();
  //MapSAC();



  //fPVeto.CreateHistos(fHist);
  //fEVeto.CreateHistos(fHist);
  //fHVeto.CreateHistos(fHist);
  //fSAC.CreateHistos(fHist);
  for(auto map_it=fADCBoards.begin();map_it!=fADCBoards.end();map_it++){
    map_it->second.CreateHistos(fHist);
  }
}














void Universe::MapEVeto(){
  fEVeto.push_back(&fADCBoards[24].GetChan( 3));   // 0     1
  fEVeto.push_back(&fADCBoards[24].GetChan( 2));   // 1     2
  fEVeto.push_back(&fADCBoards[24].GetChan( 1));   // 2     3
  fEVeto.push_back(&fADCBoards[24].GetChan( 0));   // 3     4
  fEVeto.push_back(&fADCBoards[24].GetChan( 7));   // 4     5
  fEVeto.push_back(&fADCBoards[24].GetChan( 6));   // 5     6
  fEVeto.push_back(&fADCBoards[24].GetChan( 5));   // 6     7
  fEVeto.push_back(&fADCBoards[24].GetChan( 4));   // 7     8
  fEVeto.push_back(&fADCBoards[24].GetChan(11));   // 8     9
  fEVeto.push_back(&fADCBoards[24].GetChan(10));   // 9     10
  fEVeto.push_back(&fADCBoards[24].GetChan( 9));   // 10    11
  fEVeto.push_back(&fADCBoards[24].GetChan( 8));   // 11    12
  fEVeto.push_back(&fADCBoards[24].GetChan(15));   // 12    13
  fEVeto.push_back(&fADCBoards[24].GetChan(14));   // 13    14
  fEVeto.push_back(&fADCBoards[24].GetChan(13));   // 14    15
  fEVeto.push_back(&fADCBoards[24].GetChan(12));   // 15    16
  fEVeto.push_back(&fADCBoards[24].GetChan(19));   // 16    17
  fEVeto.push_back(&fADCBoards[24].GetChan(18));   // 17    18
  fEVeto.push_back(&fADCBoards[24].GetChan(17));   // 18    19
  fEVeto.push_back(&fADCBoards[24].GetChan(16));   // 19    20
  fEVeto.push_back(&fADCBoards[24].GetChan(23));   // 20    21
  fEVeto.push_back(&fADCBoards[24].GetChan(22));   // 21    22
  fEVeto.push_back(&fADCBoards[24].GetChan(21));   // 22    23
  fEVeto.push_back(&fADCBoards[24].GetChan(20));   // 23    24
  fEVeto.push_back(&fADCBoards[24].GetChan(27));   // 24    25
  fEVeto.push_back(&fADCBoards[24].GetChan(26));   // 25    26
  fEVeto.push_back(&fADCBoards[24].GetChan(25));   // 26    27
  fEVeto.push_back(&fADCBoards[24].GetChan(24));   // 27    28
  fEVeto.push_back(&fADCBoards[24].GetChan(31));   // 28    29
  fEVeto.push_back(&fADCBoards[24].GetChan(30));   // 29    30
  fEVeto.push_back(&fADCBoards[24].GetChan(29));   // 30    31
  fEVeto.push_back(&fADCBoards[24].GetChan(28));   // 31    32
  fEVeto.push_back(&fADCBoards[25].GetChan( 3));   // 32    33
  fEVeto.push_back(&fADCBoards[25].GetChan( 2));   // 33    34
  fEVeto.push_back(&fADCBoards[25].GetChan( 1));   // 34    35
  fEVeto.push_back(&fADCBoards[25].GetChan( 0));   // 35    36
  fEVeto.push_back(&fADCBoards[25].GetChan( 7));   // 36    37
  fEVeto.push_back(&fADCBoards[25].GetChan( 6));   // 37    38
  fEVeto.push_back(&fADCBoards[25].GetChan( 5));   // 38    39
  fEVeto.push_back(&fADCBoards[25].GetChan( 4));   // 39    40
  fEVeto.push_back(&fADCBoards[25].GetChan(11));   // 40    41
  fEVeto.push_back(&fADCBoards[25].GetChan(10));   // 41    42
  fEVeto.push_back(&fADCBoards[25].GetChan( 9));   // 42    43
  fEVeto.push_back(&fADCBoards[25].GetChan( 8));   // 43    44
  fEVeto.push_back(&fADCBoards[25].GetChan(15));   // 44    45
  fEVeto.push_back(&fADCBoards[25].GetChan(14));   // 45    46
  fEVeto.push_back(&fADCBoards[25].GetChan(13));   // 46    47
  fEVeto.push_back(&fADCBoards[25].GetChan(12));   // 47    48
  fEVeto.push_back(&fADCBoards[25].GetChan(19));   // 48    49
  fEVeto.push_back(&fADCBoards[25].GetChan(18));   // 49    50
  fEVeto.push_back(&fADCBoards[25].GetChan(17));   // 50    51
  fEVeto.push_back(&fADCBoards[25].GetChan(16));   // 51    52
  fEVeto.push_back(&fADCBoards[25].GetChan(23));   // 52    53
  fEVeto.push_back(&fADCBoards[25].GetChan(22));   // 53    54
  fEVeto.push_back(&fADCBoards[25].GetChan(21));   // 54    55
  fEVeto.push_back(&fADCBoards[25].GetChan(20));   // 55    56
  fEVeto.push_back(&fADCBoards[25].GetChan(27));   // 56    57
  fEVeto.push_back(&fADCBoards[25].GetChan(26));   // 57    58
  fEVeto.push_back(&fADCBoards[25].GetChan(25));   // 58    59
  fEVeto.push_back(&fADCBoards[25].GetChan(24));   // 59    60
  fEVeto.push_back(&fADCBoards[25].GetChan(31));   // 60    61
  fEVeto.push_back(&fADCBoards[25].GetChan(30));   // 61    62
  fEVeto.push_back(&fADCBoards[25].GetChan(29));   // 62    63
  fEVeto.push_back(&fADCBoards[25].GetChan(28));   // 63    64
  fEVeto.push_back(&fADCBoards[26].GetChan( 3));   // 64    65
  fEVeto.push_back(&fADCBoards[26].GetChan( 2));   // 65    66
  fEVeto.push_back(&fADCBoards[26].GetChan( 1));   // 66    67
  fEVeto.push_back(&fADCBoards[26].GetChan( 0));   // 67    68
  fEVeto.push_back(&fADCBoards[26].GetChan( 7));   // 68    69
  fEVeto.push_back(&fADCBoards[26].GetChan( 6));   // 69    70
  fEVeto.push_back(&fADCBoards[26].GetChan( 5));   // 70    71
  fEVeto.push_back(&fADCBoards[26].GetChan( 4));   // 71    72
  fEVeto.push_back(&fADCBoards[26].GetChan(11));   // 72    73
  fEVeto.push_back(&fADCBoards[26].GetChan(10));   // 73    74
  fEVeto.push_back(&fADCBoards[26].GetChan( 9));   // 74    75
  fEVeto.push_back(&fADCBoards[26].GetChan( 8));   // 75    76
  fEVeto.push_back(&fADCBoards[26].GetChan(15));   // 76    77
  fEVeto.push_back(&fADCBoards[26].GetChan(14));   // 77    78
  fEVeto.push_back(&fADCBoards[26].GetChan(13));   // 78    79
  fEVeto.push_back(&fADCBoards[26].GetChan(12));   // 79    80
  fEVeto.push_back(&fADCBoards[26].GetChan(19));   // 80    81
  fEVeto.push_back(&fADCBoards[26].GetChan(18));   // 81    82
  fEVeto.push_back(&fADCBoards[26].GetChan(17));   // 82    83
  fEVeto.push_back(&fADCBoards[26].GetChan(16));   // 83    84
  fEVeto.push_back(&fADCBoards[26].GetChan(23));   // 84    85
  fEVeto.push_back(&fADCBoards[26].GetChan(22));   // 85    86
  fEVeto.push_back(&fADCBoards[26].GetChan(21));   // 86    87
  fEVeto.push_back(&fADCBoards[26].GetChan(20));   // 87    88
  fEVeto.push_back(&fADCBoards[26].GetChan(27));   // 88    89
  fEVeto.push_back(&fADCBoards[26].GetChan(26));   // 89    90
  fEVeto.push_back(&fADCBoards[26].GetChan(25));   // 90    91
  fEVeto.push_back(&fADCBoards[26].GetChan(24));   // 91    92
  fEVeto.push_back(&fADCBoards[26].GetChan(31));   // 92    93
  fEVeto.push_back(&fADCBoards[26].GetChan(30));   // 93    94
  fEVeto.push_back(&fADCBoards[26].GetChan(29));   // 94    95
  fEVeto.push_back(&fADCBoards[26].GetChan(28));   // 95    96
}



void Universe::MapSAC(){
  fSAC.push_back(&fADCBoards[27].GetChan(1 ));
  fSAC.push_back(&fADCBoards[27].GetChan(2 ));
  fSAC.push_back(&fADCBoards[27].GetChan(3 ));
  fSAC.push_back(&fADCBoards[27].GetChan(4 ));
  fSAC.push_back(&fADCBoards[27].GetChan(5 ));
  fSAC.push_back(&fADCBoards[27].GetChan(6 ));
  fSAC.push_back(&fADCBoards[27].GetChan(7 ));
  fSAC.push_back(&fADCBoards[27].GetChan(8 ));
  fSAC.push_back(&fADCBoards[27].GetChan(9 ));
  fSAC.push_back(&fADCBoards[27].GetChan(10));
  fSAC.push_back(&fADCBoards[27].GetChan(11));
  fSAC.push_back(&fADCBoards[27].GetChan(12));
  fSAC.push_back(&fADCBoards[27].GetChan(13));
  fSAC.push_back(&fADCBoards[27].GetChan(14));
  fSAC.push_back(&fADCBoards[27].GetChan(15));
  fSAC.push_back(&fADCBoards[27].GetChan(16));
  fSAC.push_back(&fADCBoards[27].GetChan(17));
  fSAC.push_back(&fADCBoards[27].GetChan(18));
  fSAC.push_back(&fADCBoards[27].GetChan(19));
  fSAC.push_back(&fADCBoards[27].GetChan(20));
  fSAC.push_back(&fADCBoards[27].GetChan(21));
  fSAC.push_back(&fADCBoards[27].GetChan(22));
  fSAC.push_back(&fADCBoards[27].GetChan(23));
  fSAC.push_back(&fADCBoards[27].GetChan(24));
  fSAC.push_back(&fADCBoards[27].GetChan(25));
}




void Universe::MapHEPVeto(){
  fHVeto.push_back(&fADCBoards[13].GetChan(15));
  fHVeto.push_back(&fADCBoards[13].GetChan(14));
  fHVeto.push_back(&fADCBoards[13].GetChan(13));
  fHVeto.push_back(&fADCBoards[13].GetChan(12));
  fHVeto.push_back(&fADCBoards[13].GetChan(11));
  fHVeto.push_back(&fADCBoards[13].GetChan(10));
  fHVeto.push_back(&fADCBoards[13].GetChan( 9));
  fHVeto.push_back(&fADCBoards[13].GetChan( 8));
  fHVeto.push_back(&fADCBoards[13].GetChan( 7));
  fHVeto.push_back(&fADCBoards[13].GetChan( 6));
  fHVeto.push_back(&fADCBoards[13].GetChan( 5));
  fHVeto.push_back(&fADCBoards[13].GetChan( 4));
  fHVeto.push_back(&fADCBoards[13].GetChan( 3));
  fHVeto.push_back(&fADCBoards[13].GetChan( 2));
  fHVeto.push_back(&fADCBoards[13].GetChan( 1));
  fHVeto.push_back(&fADCBoards[13].GetChan( 0));
  fHVeto.push_back(&fADCBoards[13].GetChan(28));
  fHVeto.push_back(&fADCBoards[13].GetChan(29));
  fHVeto.push_back(&fADCBoards[13].GetChan(30));
  fHVeto.push_back(&fADCBoards[13].GetChan(31));
  fHVeto.push_back(&fADCBoards[13].GetChan(24));
  fHVeto.push_back(&fADCBoards[13].GetChan(25));
  fHVeto.push_back(&fADCBoards[13].GetChan(26));
  fHVeto.push_back(&fADCBoards[13].GetChan(27));
  fHVeto.push_back(&fADCBoards[13].GetChan(20));
  fHVeto.push_back(&fADCBoards[13].GetChan(21));
  fHVeto.push_back(&fADCBoards[13].GetChan(22));
  fHVeto.push_back(&fADCBoards[13].GetChan(23));
  fHVeto.push_back(&fADCBoards[13].GetChan(16));
  fHVeto.push_back(&fADCBoards[13].GetChan(17));
  fHVeto.push_back(&fADCBoards[13].GetChan(18));
  fHVeto.push_back(&fADCBoards[13].GetChan(19));
}



void Universe::MapPVeto(){
  fPVeto.push_back(&fADCBoards[10].GetChan( 0));   // 0     1
  fPVeto.push_back(&fADCBoards[10].GetChan( 1));   // 1     2
  fPVeto.push_back(&fADCBoards[10].GetChan( 2));   // 2     3
  fPVeto.push_back(&fADCBoards[10].GetChan( 3));   // 3     4
  fPVeto.push_back(&fADCBoards[10].GetChan( 4));   // 4     5
  fPVeto.push_back(&fADCBoards[10].GetChan( 5));   // 5     6
  fPVeto.push_back(&fADCBoards[10].GetChan( 6));   // 6     7
  fPVeto.push_back(&fADCBoards[10].GetChan( 7));   // 7     8
  fPVeto.push_back(&fADCBoards[10].GetChan( 8));   // 8     9
  fPVeto.push_back(&fADCBoards[10].GetChan( 9));   // 9     10
  fPVeto.push_back(&fADCBoards[10].GetChan(10));   // 10    11
  fPVeto.push_back(&fADCBoards[10].GetChan(11));   // 11    12
  fPVeto.push_back(&fADCBoards[10].GetChan(12));   // 12    13
  fPVeto.push_back(&fADCBoards[10].GetChan(13));   // 13    14
  fPVeto.push_back(&fADCBoards[10].GetChan(14));   // 14    15
  fPVeto.push_back(&fADCBoards[10].GetChan(15));   // 15    16
  fPVeto.push_back(&fADCBoards[10].GetChan(16));   // 16    17
  fPVeto.push_back(&fADCBoards[10].GetChan(17));   // 17    18
  fPVeto.push_back(&fADCBoards[10].GetChan(18));   // 18    19
  fPVeto.push_back(&fADCBoards[10].GetChan(19));   // 19    20
  fPVeto.push_back(&fADCBoards[10].GetChan(20));   // 20    21
  fPVeto.push_back(&fADCBoards[10].GetChan(21));   // 21    22
  fPVeto.push_back(&fADCBoards[10].GetChan(22));   // 22    23
  fPVeto.push_back(&fADCBoards[10].GetChan(23));   // 23    24
  fPVeto.push_back(&fADCBoards[10].GetChan(24));   // 24    25
  fPVeto.push_back(&fADCBoards[10].GetChan(25));   // 25    26
  fPVeto.push_back(&fADCBoards[10].GetChan(26));   // 26    27
  fPVeto.push_back(&fADCBoards[10].GetChan(27));   // 27    28
  fPVeto.push_back(&fADCBoards[10].GetChan(28));   // 28    29
  fPVeto.push_back(&fADCBoards[10].GetChan(29));   // 29    30
  fPVeto.push_back(&fADCBoards[10].GetChan(30));   // 30    31
  fPVeto.push_back(&fADCBoards[10].GetChan(31));   // 31    32
  fPVeto.push_back(&fADCBoards[11].GetChan( 0));   // 32    33
  fPVeto.push_back(&fADCBoards[11].GetChan( 1));   // 33    34
  fPVeto.push_back(&fADCBoards[11].GetChan( 2));   // 34    35
  fPVeto.push_back(&fADCBoards[11].GetChan( 3));   // 35    36
  fPVeto.push_back(&fADCBoards[11].GetChan( 4));   // 36    37
  fPVeto.push_back(&fADCBoards[11].GetChan( 5));   // 37    38
  fPVeto.push_back(&fADCBoards[11].GetChan( 6));   // 38    39
  fPVeto.push_back(&fADCBoards[11].GetChan( 7));   // 39    40
  fPVeto.push_back(&fADCBoards[11].GetChan( 8));   // 40    41
  fPVeto.push_back(&fADCBoards[11].GetChan( 9));   // 41    42
  fPVeto.push_back(&fADCBoards[11].GetChan(10));   // 42    43
  fPVeto.push_back(&fADCBoards[11].GetChan(11));   // 43    44
  fPVeto.push_back(&fADCBoards[11].GetChan(12));   // 44    45
  fPVeto.push_back(&fADCBoards[11].GetChan(13));   // 45    46
  fPVeto.push_back(&fADCBoards[11].GetChan(14));   // 46    47
  fPVeto.push_back(&fADCBoards[11].GetChan(15));   // 47    48
  fPVeto.push_back(&fADCBoards[11].GetChan(16));   // 48    49
  fPVeto.push_back(&fADCBoards[11].GetChan(17));   // 49    50
  fPVeto.push_back(&fADCBoards[11].GetChan(18));   // 50    51
  fPVeto.push_back(&fADCBoards[11].GetChan(19));   // 51    52
  fPVeto.push_back(&fADCBoards[11].GetChan(20));   // 52    53
  fPVeto.push_back(&fADCBoards[11].GetChan(21));   // 53    54
  fPVeto.push_back(&fADCBoards[11].GetChan(22));   // 54    55
  fPVeto.push_back(&fADCBoards[11].GetChan(23));   // 55    56
  fPVeto.push_back(&fADCBoards[11].GetChan(24));   // 56    57
  fPVeto.push_back(&fADCBoards[11].GetChan(25));   // 57    58
  fPVeto.push_back(&fADCBoards[11].GetChan(26));   // 58    59
  fPVeto.push_back(&fADCBoards[11].GetChan(27));   // 59    60
  fPVeto.push_back(&fADCBoards[11].GetChan(28));   // 60    61
  fPVeto.push_back(&fADCBoards[11].GetChan(29));   // 61    62
  fPVeto.push_back(&fADCBoards[11].GetChan(30));   // 62    63
  fPVeto.push_back(&fADCBoards[11].GetChan(31));   // 63    64
  fPVeto.push_back(&fADCBoards[12].GetChan( 0));   // 64    65
  fPVeto.push_back(&fADCBoards[12].GetChan( 1));   // 65    66
  fPVeto.push_back(&fADCBoards[12].GetChan( 2));   // 66    67
  fPVeto.push_back(&fADCBoards[12].GetChan( 3));   // 67    68
  fPVeto.push_back(&fADCBoards[12].GetChan( 4));   // 68    69
  fPVeto.push_back(&fADCBoards[12].GetChan( 5));   // 69    70
  fPVeto.push_back(&fADCBoards[12].GetChan( 6));   // 70    71
  fPVeto.push_back(&fADCBoards[12].GetChan( 7));   // 71    72
  fPVeto.push_back(&fADCBoards[12].GetChan( 8));   // 72    73
  fPVeto.push_back(&fADCBoards[12].GetChan( 9));   // 73    74
  fPVeto.push_back(&fADCBoards[12].GetChan(10));   // 74    75
  fPVeto.push_back(&fADCBoards[12].GetChan(11));   // 75    76
  fPVeto.push_back(&fADCBoards[12].GetChan(12));   // 76    77
  fPVeto.push_back(&fADCBoards[12].GetChan(13));   // 77    78
  fPVeto.push_back(&fADCBoards[12].GetChan(14));   // 78    79
  fPVeto.push_back(&fADCBoards[12].GetChan(15));   // 79    80
  fPVeto.push_back(&fADCBoards[12].GetChan(16));   // 80    81
  fPVeto.push_back(&fADCBoards[12].GetChan(17));   // 81    82
  fPVeto.push_back(&fADCBoards[12].GetChan(18));   // 82    83
  fPVeto.push_back(&fADCBoards[12].GetChan(19));   // 83    84
  fPVeto.push_back(&fADCBoards[12].GetChan(20));   // 84    85
  fPVeto.push_back(&fADCBoards[12].GetChan(21));   // 85    86
  fPVeto.push_back(&fADCBoards[12].GetChan(22));   // 86    87
  fPVeto.push_back(&fADCBoards[12].GetChan(23));   // 87    88
  fPVeto.push_back(&fADCBoards[12].GetChan(24));   // 88    89
  fPVeto.push_back(&fADCBoards[12].GetChan(25));   // 89    90
  fPVeto.push_back(&fADCBoards[12].GetChan(26));   // 90    91
  fPVeto.push_back(&fADCBoards[12].GetChan(27));   // 91    92
  fPVeto.push_back(&fADCBoards[12].GetChan(28));   // 92    93
  fPVeto.push_back(&fADCBoards[12].GetChan(29));   // 93    94
  fPVeto.push_back(&fADCBoards[12].GetChan(30));   // 94    95
  fPVeto.push_back(&fADCBoards[12].GetChan(31));   // 95    96
}
