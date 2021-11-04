#ifndef _Histos_hh_
#define _Histos_hh_ 0

#include<sstream>
#include<string>
#include<map>

#include"TH1F.h"
#include"TH2F.h"
#include"TGraph.h"
#include"TFile.h"
#include"TDirectory.h"
#include"TTree.h"


#include"utlMessageBus.hh"


class Histos{
  private:
    const static int fNChanMax=32*6;
    const static int fNTrigMax=4*6;
    std::string fOutRootFileName;

  public:
    TH2F* hist2f_OscCum     [fNChanMax/32][32];
    //TH2F* hist2f_SignalStudy[fNChanMax/32][fNChanMax%32];
    //TH2F* hist2f_TrigCum    [fNTrigMax/4 ][fNTrigMax%4 ];

  private:
    std::multimap<std::string,TObject*>fAllObj;

  public:
    Histos(const std::string& fn){
      fOutRootFileName = fn;
      CreateHistos();
      SUCCESS("create histos");
    }

    ~Histos(){
      WriteHistos();
      DeleteHistos();
    }

    void CreateHistos();
    void AddToFile(const std::string& dirname, TObject* obj){fAllObj.emplace(dirname,obj);}
    void WriteHistos(){
      TFile* outRootFileP=new TFile(fOutRootFileName.c_str(),"recreate");
      TDirectory* fileDir=outRootFileP;
      std::stringstream chan_i_ss;
      fileDir->cd();
      std::string curdirname;
      for(auto obj_it=fAllObj.begin();obj_it!=fAllObj.end();++obj_it){
        if(curdirname!=obj_it->first){
          curdirname=obj_it->first;
          fileDir->mkdir(curdirname.c_str())->cd();
        }
        if(curdirname.size()==0)fileDir->cd();
        TH1*hist=dynamic_cast<TH1*>(obj_it->second);
        if(hist!=nullptr&&hist->GetEntries()==0)continue;
        obj_it->second->Write();
      }
      outRootFileP->Write();
      outRootFileP->Close();
      delete outRootFileP;
    }

    void DeleteHistos(){
      for(auto obj_it=fAllObj.begin();obj_it!=fAllObj.end();++obj_it){
        delete obj_it->second;
      }
    }
};
#endif
