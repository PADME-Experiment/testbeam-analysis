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




#include"Histos.hh"
#include"Analyse.hh"


class ExecutableOptions_exception:public fwk::Exception{
  public:
    ExecutableOptions_exception(){SetType(*this);}
    ExecutableOptions_exception& NoInputFiles(){fWhat+="No input files were set. "; return *this;}
    ExecutableOptions_exception& NoOutputRootFiles(){fWhat+="No output root file set. "; return *this;}
    ExecutableOptions_exception& FileListNotFound(const std::string&s){fWhat+="Filelist '"+s+"' cannot be accessed. "; return *this;}
    ExecutableOptions_exception& UnknownParameter(char c){fWhat+="Parameter '-"+std::to_string(c)+"' is unknown. "; return *this;}
    ExecutableOptions_exception& UnknownParameter(const std::string&s){fWhat+="Parameter '--"+s+"' is unknown. "; return *this;}
    ExecutableOptions_exception& OnePerLineExpected(const std::string&s){fWhat+="On line '"+s+"' only a single file is expected. "; return *this;}
    ExecutableOptions_exception& InvalidNumberConvertion(const std::string&s){
      fWhat+="Parameter '--"+s+"' cannot be converted to int. "; return *this;}
    ExecutableOptions_exception& InvalidArg_n_(){fWhat+="Invalid arg of -n. "; return *this;}


};


class ExecutableOptions{
  public:
    ExecutableOptions(int argc,char **argv);
    typedef std::deque<std::string> input_files_list_t;
    input_files_list_t::iterator GetInputFilesBegin(){return fInputFiles.begin();}
    input_files_list_t::iterator GetInputFilesEnd  (){return fInputFiles.end  ();}
    int GetVerbosity(){return fVerbosity;}
    std::string& GetLogFile(){return fLogFile;}
    std::string& GetOutputRootFile(){return fOutputRootFile;}
    unsigned int GetNEvtToProcess()const{return fNEvtToProcess;}
    unsigned int GetNFreqToCancel()const{return fNFreqToCancelFFT;}
  private:
    input_files_list_t fInputFiles;
    int fVerbosity;
    unsigned int fNEvtToProcess;
    unsigned int fNFreqToCancelFFT;
    std::string fLogFile;
    std::string fOutputRootFile;
};
ExecutableOptions::ExecutableOptions(int argc,char **argv):
  fVerbosity(5),
    fNEvtToProcess(-1)
    {
    int c;

    std::vector<std::string> inputLists;

    // Parse options
    while ((c = getopt (argc, argv, "i:o:l:n:F:V:vqh")) != -1) {
      switch (c) {
        case 'o': fOutputRootFile=optarg;
                  break;
        case 'i': fInputFiles.push_back(optarg);
                  //fprintf(stdout,"Set input data file to '%s'\n",optarg);
                  break;
        case 'l': inputLists.push_back(optarg);
                  break;
        case 'n': if ( sscanf(optarg,"%u",&fNEvtToProcess) != 1 )
                    throw ExecutableOptions_exception().InvalidArg_n_().InvalidNumberConvertion(optarg);
                  break;
        case 'v': ++fVerbosity;
                  break;
        case 'V': fLogFile=optarg;
                  break;
        case 'q': fVerbosity=0;
                  break;
        case 'F': if ( sscanf(optarg,"%u",&fNFreqToCancelFFT) != 1 )
                    throw ExecutableOptions_exception().InvalidArg_n_().InvalidNumberConvertion(optarg);
                  break;
        case 'h': fprintf(stdout,"\nReadTest [-i input root file] [-o otput root file] [-v verbosity] [-h]\n\n");
                  fprintf(stdout,"  -i: define an input file in root format\n");
                  fprintf(stdout,"  -0: define an otput file in root format\n");
                  fprintf(stdout,"  -n: define number of events to read from input file (0: all events)\n");
                  fprintf(stdout,"  -F: FFT number of frequency to cancel\n");
                  fprintf(stdout,"  -v: increase verbose level\n");
                  fprintf(stdout,"  -h: show this help message and exit\n\n");
        case '?': if (optopt == 'v') {
                    // verbose with no argument: just enable at minimal level
                    break;
                  } else if (optopt == 'i' || optopt == 'l' || optopt == 'o')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                  else if (isprint(optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                  else
                    fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
                  exit(1);
        default:
                  throw ExecutableOptions_exception().UnknownParameter(c);
      }
    }
    for(auto list_it=inputLists.begin();list_it!=inputLists.end();++list_it){
      utl::ConfigParser filelist(*list_it);
      //filelist.Print();
      auto& dflt=filelist.GetGroup("Default");
      for(auto fline_it=dflt.begin();fline_it!=dflt.end();++fline_it){
        const std::string& line=fline_it->first;
        if(fline_it->second.size()>0)throw ExecutableOptions_exception().OnePerLineExpected(line);
        fInputFiles.push_back(line);
      }
    }
    if(fInputFiles.size()==0) throw ExecutableOptions_exception().NoInputFiles();
    if(fOutputRootFile.size()==0) throw ExecutableOptions_exception().NoOutputRootFiles();
  }

int main(int argc, char* argv[]){
  try{
    ExecutableOptions exeopt(argc,argv);
    utl::MessageBus& mb=utl::MessageBus::GetInstance();
    mb.SetVerbosity(exeopt.GetVerbosity());
    mb.SetLogFile(exeopt.GetLogFile());

    Analyse anl(exeopt.GetOutputRootFile());
    anl.SetNEvtToProcess(exeopt.GetNEvtToProcess());
    anl.SetNFreqToCancel(exeopt.GetNFreqToCancel());

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
