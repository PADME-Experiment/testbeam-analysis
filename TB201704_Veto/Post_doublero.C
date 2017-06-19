#include<string>
#include<sstream>
#include<vector>

//void ProcFile(const TFile& f,TFile& out, const ::std::string& fn)
void ProcFile(const TFile& f,const ::std::string& fn){
  std::vector<std::string> histnames;
  histnames.push_back("lightCollectionRTO_0_11");
  histnames.push_back("lightCollectionRTO_1_10");
  histnames.push_back("lightCollectionRTO_2_9");
  histnames.push_back("lightCollectionRTO_3_8");

  for(auto fni=histnames.begin();fni!=histnames.end();++fni){
    auto histn=*fni;
    TH1F* h1_single=dynamic_cast<TH1F*>(f.FindObjectAny(histn.c_str()));
    if(h1_single){
      cerr<<fn<<"  " << histn<<" "<<h1_single->GetMean()<<std::endl;
    }
  }
}


int Post_doublero(){
  ::std::vector<::std::string> files;
  files.push_back("run_624");
  files.push_back("run_625");
  files.push_back("run_626");
  files.push_back("run_627");


  //TFile out("out.root","recreate");
  for(auto fni=files.begin();fni!=files.end();++fni){
    auto fn=*fni;
    TFile f((""+fn+"-tmp.root").c_str(),"READ");
    //ProcFile(f,out,fn);
    ProcFile(f,fn);
  }
  return 0;
}
