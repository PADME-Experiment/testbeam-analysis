#include<string>
#include<sstream>
#include<vector>

void ProcFile(const TFile& f,TFile& out, const ::std::string& fn){
  out.cd();
  ((TDirectory*)out.mkdir(fn.c_str()))->cd();
  for(int i=0;i<16;++i){
    ::std::stringstream ssSingle;
    ::std::stringstream ssDouble;
    ssSingle<<"PhElectrAbsSinglePartBeam_ch_"<<i;
    ssDouble<<"PhElectrAbsDoublePartBeam_ch_"<<i;
    TH1F* h1_single=dynamic_cast<TH1F*>(f.FindObjectAny(ssSingle.str().c_str()));
    TH1F* h1_double=dynamic_cast<TH1F*>(f.FindObjectAny(ssDouble.str().c_str()));
    if(h1_single){
      TFitResultPtr r1=h1_single->Fit("gaus","S");
      const double* ar1=r1.Get()->GetParams();

      TFitResultPtr r2=h1_single->Fit("gaus","SL","",ar1[1]-ar1[2],ar1[1]+ar1[2]);
      const double* ar2=r2.Get()->GetParams();

      TFitResultPtr r3=h1_single->Fit("gaus","SL","",ar2[1]-ar2[2],ar2[1]+ar2[2]);
      const double* ar3=r3.Get()->GetParams();
      const double* err=r3.Get()->GetErrors();
      cerr<<fn<<" "<< i<<" single "<<ar3[1]<<"  "<<err[1]<<"  "<<ar3[2]<<"  "<<err[2]<<std::endl;
      h1_single->Write();
    }
    if(h1_double){
      TFitResultPtr r1=h1_double->Fit("gaus","S");
        const double* ar1=r1.Get()->GetParams();

        TFitResultPtr r2=h1_double->Fit("gaus","SL","",ar1[1]-ar1[2]*.7,ar1[1]+ar1[2]*1.4);
        const double* ar2=r2.Get()->GetParams();

        TFitResultPtr r3=h1_double->Fit("gaus","SL","",ar2[1]-ar2[2]*.7,ar2[1]+ar2[2]*1.4);
        const double* ar3=r3.Get()->GetParams();
      const double* err=r3.Get()->GetErrors();
      cerr<<fn<<" "<< i<<" double "<<ar3[1]<<"  "<<err[1]<<"  "<<ar3[2]<<"  "<<err[2]<<std::endl;
      h1_double->Write();
    }
  }
}


int Post(){
  ::std::vector<::std::string> files;
  //files.push_back("run_611");
  files.push_back("run_612");
  files.push_back("run_613");
  files.push_back("run_614");
  files.push_back("run_615");
  files.push_back("run_616");
  files.push_back("run_617");
  files.push_back("run_618");
  files.push_back("run_619");
  files.push_back("run_620");
  files.push_back("run_621");
  files.push_back("run_622");
  files.push_back("run_623");
  files.push_back("run_624");
  files.push_back("run_625");
  files.push_back("run_626");
  files.push_back("run_627");


  TFile out("out.root","recreate");
  for(auto fni=files.begin();fni!=files.end();++fni){
    auto fn=*fni;
    cout<<fn<<std::endl;
    TFile f(("/data/georgieff/padme-raw/TB201704/"+fn+".lst.root").c_str(),"READ");
    ProcFile(f,out,fn);
  }
  out.Write();
  out.Close();
  return 0;
}
