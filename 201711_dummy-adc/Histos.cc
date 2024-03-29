#include"Histos.hh"

#include"Universe.hh"
#include<iomanip>

extern int gBoardID;


  void
Histos::CreateHistos()
{
  //const Universe& uni=Universe::GetInstance();
  std::string name, title, base;
  TObject* tmptobj;


    int board_i=0;
    for(int chan_i=0;chan_i<fNChanMax;++chan_i){
      std::stringstream chan_i_ss;
      chan_i_ss<<"_"<< std::setfill('0') << std::setw(4) <<gBoardID<<"_ch_"<< std::setfill('0') << std::setw(2) <<chan_i;
      std::string chan_i_s=chan_i_ss.str();
      base="OscCumulative"        ;name=base+chan_i_s; title=name+";Samples;Values [ADU]"; tmptobj=hist2f_ChanOscCum               [board_i][chan_i]=new TH2F(name.c_str(),title.c_str(),1024,0-.5,1024-.5,500,3500,4000); fAllObj.emplace(base,tmptobj);
      base="OscCumulativeT0"      ;name=base+chan_i_s; title=name+";Samples;Values [ADU]"; tmptobj=hist2f_ChanOscCumT0             [board_i][chan_i]=new TH2F(name.c_str(),title.c_str(),1024,0-.5,1024-.5,500,3500,4000); fAllObj.emplace(base,tmptobj);


      base="SigmaSampBySamp"      ;name=base+chan_i_s; title=name+";Values [ADU]"        ; tmptobj=hist1f_ChanSigmaSampBySamp      [board_i][chan_i]=new TH1F(name.c_str(),title.c_str(),400,0,30                       ); fAllObj.emplace(base,tmptobj);
      base="SigmaSampBySampT0"    ;name=base+chan_i_s; title=name+";Values [ADU]"        ; tmptobj=hist1f_ChanSigmaSampBySampT0    [board_i][chan_i]=new TH1F(name.c_str(),title.c_str(),400,0,30                       ); fAllObj.emplace(base,tmptobj);

      base="AmplFluctSampBySamp"  ;name=base+chan_i_s; title=name+" samp 0..1023;Values [ADU]"        ; tmptobj=hist1f_ChanAmplFluctSampBySamp  [board_i][chan_i]=new TH1F(name.c_str(),title.c_str(),500,0,500                      ); fAllObj.emplace(base,tmptobj);
      base="AmplFluctSampBySampT0";name=base+chan_i_s; title=name+" samp 0..1023;Values [ADU]"        ; tmptobj=hist1f_ChanAmplFluctSampBySampT0[board_i][chan_i]=new TH1F(name.c_str(),title.c_str(),500,0,500                      ); fAllObj.emplace(base,tmptobj);

      base="PedestalsMean"        ;name=base+chan_i_s; title=name+" samp 0..995;Pedestal mean [ADU]" ; tmptobj=hist1f_ChanPedestalsMean        [board_i][chan_i]=new TH1F(name.c_str(),title.c_str(),1000,3500,4000                 ); fAllObj.emplace(base,tmptobj);
      base="PedestalsRMS"         ;name=base+chan_i_s; title=name+" samp 0..995;Pedestal RMS [ADU]"  ; tmptobj=hist1f_ChanPedestalsRMS         [board_i][chan_i]=new TH1F(name.c_str(),title.c_str(),400,0,200                      ); fAllObj.emplace(base,tmptobj);

      base="SlopeFitA"            ;name=base+chan_i_s; title=name+" samp 0..995 const;[ADU]"         ; tmptobj=hist1f_ChanSlopeFitA            [board_i][chan_i]=new TH1F(name.c_str(),title.c_str(),400,3500,4000                  ); fAllObj.emplace(base,tmptobj);
      base="SlopeFitB"            ;name=base+chan_i_s; title=name+" samp 0..995 slope;[ADU]"         ; tmptobj=hist1f_ChanSlopeFitB            [board_i][chan_i]=new TH1F(name.c_str(),title.c_str(),400,-.1,.10                    ); fAllObj.emplace(base,tmptobj);
      base="SlopeFitRMS"          ;name=base+chan_i_s; title=name+" samp 0..995;[ADU]"               ; tmptobj=hist1f_ChanSlopeFitRMS          [board_i][chan_i]=new TH1F(name.c_str(),title.c_str(),400,0,200                      ); fAllObj.emplace(base,tmptobj);
      base="OscCumulative3d"      ;name=base+chan_i_s; title=name+";SamplesT0Cor;Samples"             ; tmptobj=hist3f_ChanOscCum3d             [board_i][chan_i]=new TH3F(name.c_str(),title.c_str(),128,0,1024,128,0,1024,100,3500,4000          ); fAllObj.emplace(base,tmptobj);
      //base="OscCumulative2d"      ;name=base+chan_i_s; title=name+";SamplesT0Cor;Samples"; tmptobj=hist2f_ChanOscCum2d             [board_i][chan_i]=new TH2F(name.c_str(),title.c_str(),128,0,1024,128,0,1024          ); fAllObj.emplace(base,tmptobj);
      //base="MaxAmplFluctuation"   ;name=base+chan_i_s; title=name+";Values [ADU]"        ; tmptobj=hist1f_ChanMaxAmplFluct         [board_i][chan_i]=new TH1F(name.c_str(),title.c_str(),400,0,400                      ); fAllObj.emplace(base,tmptobj);
      //base="SampleBySample"       ;name=base+chan_i_s; title=name+";Samples;Values [ADU]"; tmptobj=hist2f_ChanSampleBySample       [board_i][chan_i]=new TH2F(name.c_str(),title.c_str(),102,0-.5,1024-.5,100,0,400     ); fAllObj.emplace(base,tmptobj);
    }

    for(int trig_i=0;trig_i<fNTrigMax;++trig_i){
      std::stringstream trig_i_ss;
      trig_i_ss<<"_"<< std::setfill('0') << std::setw(4) <<gBoardID<<"_tr_"<< std::setfill('0') << std::setw(1) <<trig_i;
      std::string trig_i_s=trig_i_ss.str();


        base="OscCumulative"        ;name=base+trig_i_s; title=name+";Samples;Values [ADU]"             ; tmptobj=hist2f_TrigOscCum               [board_i][trig_i]=new TH2F(name.c_str(),title.c_str(),1024,0-.5,1024-.5,500,-5000,5000); fAllObj.emplace(base,tmptobj);
        base="OscCumulativeT0"      ;name=base+trig_i_s; title=name+";Samples;Values [ADU]"             ; tmptobj=hist2f_TrigOscCumT0             [board_i][trig_i]=new TH2F(name.c_str(),title.c_str(),1024,0-.5,1024-.5,500,-5000,5000); fAllObj.emplace(base,tmptobj);


        base="SigmaSampBySamp"      ;name=base+trig_i_s; title=name+";Values [ADU]"                     ; tmptobj=hist1f_TrigSigmaSampBySamp      [board_i][trig_i]=new TH1F(name.c_str(),title.c_str(),400,0,30                       ); fAllObj.emplace(base,tmptobj);
        base="SigmaSampBySampT0"    ;name=base+trig_i_s; title=name+";Values [ADU]"                     ; tmptobj=hist1f_TrigSigmaSampBySampT0    [board_i][trig_i]=new TH1F(name.c_str(),title.c_str(),400,0,30                       ); fAllObj.emplace(base,tmptobj);

        base="AmplFluctSampBySamp"  ;name=base+trig_i_s; title=name+" samp 0..1023;Values [ADU]"        ; tmptobj=hist1f_TrigAmplFluctSampBySamp  [board_i][trig_i]=new TH1F(name.c_str(),title.c_str(),500,0,500                      ); fAllObj.emplace(base,tmptobj);
        base="AmplFluctSampBySampT0";name=base+trig_i_s; title=name+" samp 0..1023;Values [ADU]"        ; tmptobj=hist1f_TrigAmplFluctSampBySampT0[board_i][trig_i]=new TH1F(name.c_str(),title.c_str(),500,0,500                      ); fAllObj.emplace(base,tmptobj);

        base="PedestalsMean"        ;name=base+trig_i_s; title=name+" samp 0..995;Pedestal mean [ADU]"  ; tmptobj=hist1f_TrigPedestalsMean        [board_i][trig_i]=new TH1F(name.c_str(),title.c_str(),1000,3500,4000                 ); fAllObj.emplace(base,tmptobj);
        base="PedestalsRMS"         ;name=base+trig_i_s; title=name+" samp 0..995;Pedestal RMS [ADU]"   ; tmptobj=hist1f_TrigPedestalsRMS         [board_i][trig_i]=new TH1F(name.c_str(),title.c_str(),400,0,200                      ); fAllObj.emplace(base,tmptobj);

        base="SlopeFitA"            ;name=base+trig_i_s; title=name+" samp 0..995 const;[ADU]"          ; tmptobj=hist1f_TrigSlopeFitA            [board_i][trig_i]=new TH1F(name.c_str(),title.c_str(),400,3500,4000                  ); fAllObj.emplace(base,tmptobj);
        base="SlopeFitB"            ;name=base+trig_i_s; title=name+" samp 0..995 slope;[ADU]"          ; tmptobj=hist1f_TrigSlopeFitB            [board_i][trig_i]=new TH1F(name.c_str(),title.c_str(),400,-.1,.10                    ); fAllObj.emplace(base,tmptobj);
        base="SlopeFitRMS"          ;name=base+trig_i_s; title=name+" samp 0..995;[ADU]"                ; tmptobj=hist1f_TrigSlopeFitRMS          [board_i][trig_i]=new TH1F(name.c_str(),title.c_str(),400,0,200                      ); fAllObj.emplace(base,tmptobj);
      //base="OscCumulative3d"      ;name=base+trig_i_s; title=name+";SamplesT0Cor;Samples"             ; tmptobj=hist3f_TrigOscCum3d             [board_i][trig_i]=new TH3F(name.c_str(),title.c_str(),128,0,1024,128,0,1024,100,3500,4000          ); fAllObj.emplace(base,tmptobj);
      //base="MaxAmplFluctuation"   ;name=base+trig_i_s; title=name+";Values [ADU]"                     ; tmptobj=hist1f_TrigMaxAmplFluct         [board_i][trig_i]=new TH1F(name.c_str(),title.c_str(),400,0,400                      ); fAllObj.emplace(base,tmptobj);
      //base="SampleBySample"       ;name=base+trig_i_s; title=name+";Samples;Values [ADU]"             ; tmptobj=hist2f_TrigSampleBySample       [board_i][trig_i]=new TH2F(name.c_str(),title.c_str(),102,0-.5,1024-.5,100,0,400     ); fAllObj.emplace(base,tmptobj);
    }

    std::stringstream board_i_ss;
    board_i_ss<<"_"<< std::setfill('0') << std::setw(4) <<gBoardID;
    std::string board_i_s=board_i_ss.str();

    name="TrigSigPedMean"+board_i_s;title=name+" multi evt stability" ;tmptobj=hist1f_TrigSigPedMean =new TH1F(name.c_str(),title.c_str(),100,0,3   ); fAllObj.emplace("",tmptobj);
    name="TrigSigPedSig" +board_i_s;title=name+" inside evt stability";tmptobj=hist1f_TrigSigPedSig  =new TH1F(name.c_str(),title.c_str(),400,0,10  ); fAllObj.emplace("",tmptobj);
    name="ChanSigPedMean"+board_i_s;title=name+" multi evt stability" ;tmptobj=hist1f_ChanSigPedMean =new TH1F(name.c_str(),title.c_str(),100,0,3   ); fAllObj.emplace("",tmptobj);
    name="ChanSigPedSig" +board_i_s;title=name+" inside evt stability";tmptobj=hist1f_ChanSigPedSig  =new TH1F(name.c_str(),title.c_str(),400,0,10  ); fAllObj.emplace("",tmptobj);
    name="ChanOscSigY"   +board_i_s;title=name                        ;tmptobj=hist1f_ChanOscSigY    =new TH1F(name.c_str(),title.c_str(),400,0,40  ); fAllObj.emplace("",tmptobj);

}
