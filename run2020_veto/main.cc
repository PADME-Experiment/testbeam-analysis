#include"exec_options.hh"



#include<exception>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"



#include "TH1F.h"
#include "TH2F.h"
#include "TDirectory.h"
#include<sstream>
#include<string>


#include<vector>
#include<queue>
#include<deque>
#include<algorithm>
#include<string>
#include<iostream>
#include<cctype>
#include <fstream>
#include<typeinfo>
#include<unistd.h>

#include"fwkException.hh"
#include"utlMessageBus.hh"
#include"utlConfigParser.hh"




#include"Analyse.hh"


int main(int argc, char* argv[]){
  try{

    ExecutableOptions& exeopt=ExecutableOptions::GetInstance();
    exeopt.Parse(argc,argv);
    utl::MessageBus& mb=utl::MessageBus::GetInstance();
    mb.SetVerbosity(exeopt.GetVerbosity());
    mb.SetLogFile(exeopt.GetLogFile());

    Analyse anl;
    anl.SetNEvtToProcess(exeopt.GetNEvtToProcess());

    for(auto file_it=exeopt.GetInputFilesBegin();file_it!=exeopt.GetInputFilesEnd();++file_it){
      std::string& filename=*file_it;
      if(access(filename.c_str(),R_OK)==0){
        INFO("Processing '"+filename+"'");
        anl.Process(filename);
      }else{
        WARNING("Skip! File not found/accessable '"+filename+"'");
      }
    }
    anl.Finalize();



  }
  catch(const ExecutableOptions_exception& e){
    INFO("throwing "+e.GetType());
    ERROR(e.GetWhat());
    return 1;
  }
  catch(const fwk::Exception& e){
    INFO("throwing "+typeid(e).name());
    ERROR(e.GetWhat());
    return 1;
  }
  catch(std::exception){
    ERROR("uncathced std::exception");
    throw;
  }
  catch(...){
    ERROR("uncathced exception");
    throw;
  }

}
