#include"Histos.hh"
  void
Histos::CreateHistos()
{
  std::string name, title;
  TObject* tmptobj;

  for(int slope_i=0;slope_i<gSqNoiseSlopes;++slope_i){
    for(int noise_i=0;noise_i<gSqNoiseNoises;++noise_i){
      std::stringstream noise_ss;noise_ss<<GExpStep(noise_i);
      std::stringstream slope_ss;slope_ss<<GExpStep(slope_i);

      name           ="SqNoiseOsc_slope_"+slope_ss.str()+"_noise_"+noise_ss.str(); title=name;
      tmptobj  =hist2f_SqNoiseOsc      [slope_i][noise_i]=new TGraph(1024);
      ((TGraph*)tmptobj)->SetName(name.c_str());
      ((TGraph*)tmptobj)->SetTitle(title.c_str());
      ((TGraph*)tmptobj)->SetMarkerStyle(7);
      ((TGraph*)tmptobj)->SetMarkerColor(2);
      ((TGraph*)tmptobj)->SetMarkerSize(2);

      fAllObj.emplace("SqNoiseOsc",tmptobj);

      name           ="SqNoiseIntrSlope_slope_"+slope_ss.str()+"_noise_"+noise_ss.str(); title=name;
      tmptobj  =hist1f_SqNoiseIntrSlope[slope_i][noise_i]=new TH1F(name.c_str(),title.c_str(),800,130-.5,170-.5);
      fAllObj.emplace("SqNoiseIntrSlope",tmptobj);

      name           ="SqNoiseIntrThres_slope_"+slope_ss.str()+"_noise_"+noise_ss.str(); title=name;
      tmptobj  =hist1f_SqNoiseIntrThres[slope_i][noise_i]=new TH1F(name.c_str(),title.c_str(),800,130-.5,170-.5);
      fAllObj.emplace("SqNoiseIntrThres",tmptobj);

      name           ="SqNoiseDiffSlope_slope_"+slope_ss.str()+"_noise_"+noise_ss.str(); title=name;
      tmptobj  =hist1f_SqNoiseDiffSlope[slope_i][noise_i]=new TH1F(name.c_str(),title.c_str(),600,-30-.5,30-.5);
      fAllObj.emplace("SqNoiseDiffSlope",tmptobj);

      name           ="SqNoiseDiffThres_slope_"+slope_ss.str()+"_noise_"+noise_ss.str(); title=name;
      tmptobj  =hist1f_SqNoiseDiffThres[slope_i][noise_i]=new TH1F(name.c_str(),title.c_str(),600,-30-.5,30-.5);
      fAllObj.emplace("SqNoiseDiffThres",tmptobj);
    }
  }


  for(int sine_i=0;sine_i<gNSines;++sine_i){
    for(int noise_i=0;noise_i<gSqNoiseNoises;++noise_i){
      std::stringstream noise_ss;noise_ss<<GExpStep(noise_i);
      std::stringstream sine_ss;sine_ss<<GExpStep(sine_i)+1;

      name           ="SineOsc_sine_"+sine_ss.str()+"_noise_"+noise_ss.str(); title=name;
      tmptobj  =hist2f_SineOsc      [sine_i][noise_i]=new TGraph(1024);
      ((TGraph*)tmptobj)->SetName(name.c_str());
      ((TGraph*)tmptobj)->SetTitle(title.c_str());
      ((TGraph*)tmptobj)->SetMarkerStyle(7);
      ((TGraph*)tmptobj)->SetMarkerColor(2);
      ((TGraph*)tmptobj)->SetMarkerSize(2);
      fAllObj.emplace("SineOsc",tmptobj);
      name           ="SineIntrSlope_sine_"+sine_ss.str()+"_noise_"+noise_ss.str(); title=name;
      tmptobj  =hist1f_SineIntrSlope[sine_i][noise_i]=new TH1F(name.c_str(),title.c_str(),800,130-.5,170-.5);
      fAllObj.emplace("SineIntrSlope",tmptobj);

      name           ="SineIntrThres_sine_"+sine_ss.str()+"_noise_"+noise_ss.str(); title=name;
      tmptobj  =hist1f_SineIntrThres[sine_i][noise_i]=new TH1F(name.c_str(),title.c_str(),800,130-.5,170-.5);
      fAllObj.emplace("SineIntrThres",tmptobj);

      name           ="SineDiffSlope_sine_"+sine_ss.str()+"_noise_"+noise_ss.str(); title=name;
      tmptobj  =hist1f_SineDiffSlope[sine_i][noise_i]=new TH1F(name.c_str(),title.c_str(),600,-30-.5,30-.5);
      fAllObj.emplace("SineDiffSlope",tmptobj);

      name           ="SineDiffThres_sine_"+sine_ss.str()+"_noise_"+noise_ss.str(); title=name;
      tmptobj  =hist1f_SineDiffThres[sine_i][noise_i]=new TH1F(name.c_str(),title.c_str(),600,-30-.5,30-.5);
      fAllObj.emplace("SineDiffThres",tmptobj);

      name           ="SineIntrFFTPhase_sine_"+sine_ss.str()+"_noise_"+noise_ss.str(); title=name;
      tmptobj  =hist1f_SineIntrFFTPhase[sine_i][noise_i]=new TH1F(name.c_str(),title.c_str(),800,-10,10);
      fAllObj.emplace("SineIntrFFTPhase",tmptobj);

      name           ="SineDiffFFTPhase_sine_"+sine_ss.str()+"_noise_"+noise_ss.str(); title=name;
      tmptobj  =hist2f_SineDiffFFTPhase[sine_i][noise_i]=new TH2F(name.c_str(),title.c_str(),600,-1,1,500,-5,5);
      fAllObj.emplace("SineDiffFFTPhase",tmptobj);
    }
  }










  name="TriggerDiffSine"; title=name;
  tmptobj=hist1f_TrigDiffSine=new TH1F(name.c_str(),title.c_str(),2000,-100-.5,100-.5);
  fAllObj.emplace("TrigDiff",tmptobj);



  name="TriggerPhyDif"; title=name;
  tmptobj=hist2f_phy_dif=new TH2F(name.c_str(),title.c_str(),150,600,0,330,4,4);
  fAllObj.emplace("",tmptobj);

}
