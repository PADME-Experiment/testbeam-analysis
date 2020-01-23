#include"Histos.hh"

#include <iomanip>

  void
Histos::CreateHistos()
{
  std::string name, title;
  name="ChannelOccupacy"; title=name;
  TObject* tmptobj;

  //for(int ii=0;ii<fNTrigMax;++ii){
  //  std::stringstream chan_i_ss;
  //  chan_i_ss<<ii;


  //  name="TriggerCumulativeOscillogram_ch_"+chan_i_ss.str(); title=name;
  //  tmptobj=hist2f_TrigCum[ii]=new TH2F(name.c_str(),title.c_str(),1024,-.5,1023.5, 512,-5000,5000);
  //  fAllObj.emplace("TrigCumOsc",tmptobj);

  //}

  for(int board_i=0;board_i<fNChanMax/32;++board_i){
      SUCCESS(std::to_string(board_i)+"  "+std::to_string(fNChanMax%32));
    for(int ii=0;ii<32;++ii){
      SUCCESS(std::to_string(board_i)+"  "+std::to_string(ii));
      std::stringstream chan_i_ss,board_i_ss,veto_ss,pos_ss;

      board_i_ss<<"b"<<board_i;
      chan_i_ss<<"ch"<<ii;

      if(board_i<3){
        //pveto
        veto_ss<<"PVeto";
        pos_ss<<"pos"<< std::setfill('0') << std::setw(2)<<ii+1;
      }else{
        //eveto
        veto_ss<<"EVeto";
        pos_ss<<"pos"<< std::setfill('0') << std::setw(2)<<(ii/4)*4+(3-ii%4)+1; // Eveto has reversed channels 4-1, 8-5.....
      }




      name="CumulativeOscillogram_"+veto_ss.str()+"_"+pos_ss.str()+"_"+board_i_ss.str()+"_"+chan_i_ss.str();  title=name;
      tmptobj=hist2f_OscCum[board_i][ii]=new TH2F(name.c_str(),title.c_str(),1024,-.5,1023.5, 2048,0,4096) ;

      fAllObj.emplace(veto_ss.str()+"_"+board_i_ss.str(),tmptobj);

      //name ="SignalStudy_ch_"+chan_i_ss.str();  title=name+" "+uni.GetROName(ii);
      //tmptobj=hist2f_SignalStudy[ii]=new TH2F(name.c_str(),title.c_str(),1024,0-.5,1024-.5,100,-.5,100-.5);
      //fAllObj.emplace("StudySignal",tmptobj);

    }

  }
}
