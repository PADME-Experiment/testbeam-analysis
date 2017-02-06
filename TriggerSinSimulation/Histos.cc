#include"Histos.hh"
  void
Histos::CreateHistos()
{
  std::string name, title;
  name="ChannelOccupacy"; title=name;
  TObject* tmptobj;

  for(int ii=0;ii<2;++ii){
    std::stringstream chan_i_ss;
    chan_i_ss<<ii;
    name="TriggerCum_ch_"+chan_i_ss.str(); title=name;
    tmptobj=hist2f_TrigCum[ii]=new TH2F(name.c_str(),title.c_str(),1024,0-.5,1024-.5,3000,-3000-.5,3000-.5);

    fAllObj.emplace("TrigCum",tmptobj);
    name="TriggerIntrSlope_ch_"+chan_i_ss.str(); title=name;
    tmptobj=hist1f_TrigIntrSlope[ii]=new TH1F(name.c_str(),title.c_str(),2000,130-.5,150-.5);
    fAllObj.emplace("TrigIntr",tmptobj);
    name="TriggerIntrThres_ch_"+chan_i_ss.str(); title=name;
    tmptobj=hist1f_TrigIntrThres[ii]=new TH1F(name.c_str(),title.c_str(),2000,130-.5,150-.5);
    fAllObj.emplace("TrigIntr",tmptobj);
  }
  name="TriggerDiffSlope"; title=name;
  tmptobj=hist1f_TrigDiffSlope=new TH1F(name.c_str(),title.c_str(),2000,-100-.5,100-.5);
  fAllObj.emplace("TrigDiff",tmptobj);
  name="TriggerDiffThres"; title=name;
  tmptobj=hist1f_TrigDiffThres=new TH1F(name.c_str(),title.c_str(),2000,-100-.5,100-.5);
  fAllObj.emplace("TrigDiff",tmptobj);
  name="TriggerDiffSine"; title=name;
  tmptobj=hist1f_TrigDiffSine=new TH1F(name.c_str(),title.c_str(),2000,-100-.5,100-.5);
  fAllObj.emplace("TrigDiff",tmptobj);



  name="TriggerPhyDif"; title=name;
  tmptobj=hist2f_phy_dif=new TH2F(name.c_str(),title.c_str(),150,600,0,330,4,4);
  fAllObj.emplace("",tmptobj);

}
