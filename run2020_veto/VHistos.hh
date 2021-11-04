#ifndef _VHistos_hh_
#define _VHistos_hh_ 0

#include<sstream>
#include<string>
#include<map>

#include"TH1F.h"
#include"TH2F.h"
#include"TFile.h"
#include"TDirectory.h"

class VHistos{
  public:
    VHistos(){
      throw;
      //CreateHistos();
    }
    virtual ~VHistos(){
      //WriteHistos();
      //DeleteHistos();
    }
    virtual void CreateHistos()=0;
    void WriteHistos(const std::string& fn){
      TFile* outRootFileP=new TFile(fn.c_str(),"recreate");
      WriteHistos(outRootFileP);
      outRootFileP->Write();
      outRootFileP->Close();
      delete outRootFileP;
    }
    void WriteHistos(TFile* outRootFileP){
      INFO("start");
      TDirectory* fileDir=outRootFileP;
      //std::stringstream chan_i_ss;
      fileDir->cd();
      std::string curdirname;
      int tmp=0;
      for(auto obj_it=fAllObj.begin();obj_it!=fAllObj.end();++obj_it){
        std::stringstream ss;
        ss<<obj_it->first<<"   "<<obj_it->second;
        INFO(ss.str());
        INFO(std::to_string(tmp++)+"/"+std::to_string(fAllObj.size()));
        if(curdirname!=obj_it->first){
          curdirname=obj_it->first;
          fileDir->mkdir(curdirname.c_str())->cd();
        }
        if(curdirname.size()==0)fileDir->cd();
        TH1*hist=dynamic_cast<TH1*>(obj_it->second);

        if(hist!=nullptr&&hist->GetEntries()==0)continue;
        INFO("write"+obj_it->second->GetName());
        //INFO(std::to_string(hist->GetEntries()));
        INFO("write!");
        obj_it->second->Write();
      }
      INFO("stop");
    }

    void DeleteHistos(){
      INFO("kur");
      for(auto obj_it=fAllObj.begin();obj_it!=fAllObj.end();++obj_it){
        std::stringstream ss;
        ss<<obj_it->first<<"/"<<obj_it->second->GetName();
        delete obj_it->second;
        SUCCESS(ss.str());
      }
    }
  protected:
    std::multimap<std::string,TObject*>fAllObj;
};
#endif
