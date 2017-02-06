#ifndef _Histos_hh_
#define _Histos_hh_ 0

#include<sstream>
#include<map>

#include"TH1F.h"
#include"TH2F.h"
#include"TFile.h"
#include"TDirectory.h"
#include"TTree.h"

class Histos{
  private:
    std::string fOutRootFileName;




  public:
    TH2F* hist2f_TrigCum[2];
    TH1F* hist1f_TrigIntrSlope[2];
    TH1F* hist1f_TrigIntrThres[2];
    TH1F* hist1f_TrigDiffSlope;
    TH1F* hist1f_TrigDiffThres;
    TH1F* hist1f_TrigDiffSine;
    TH2F* hist2f_phy_dif;



  private:
    std::multimap<std::string,TObject*>fAllObj;

  public:
    Histos(const std::string& fn){
      fOutRootFileName = fn;
      CreateHistos();
    }

    ~Histos(){
      WriteHistos();
      DeleteHistos();
    }

    void CreateHistos();
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
