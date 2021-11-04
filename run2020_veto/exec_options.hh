#ifndef _EXECUTABLE_OPTIONS_HH_
#define _EXECUTABLE_OPTIONS_HH_ 0

#include"fwkException.hh"
#include"utlMessageBus.hh"
#include"utlConfigParser.hh"

#include<sstream>
#include<string>


#include<vector>
#include<queue>
#include<deque>
#include<algorithm>
#include<iostream>
#include<cctype>
#include <fstream>
#include<typeinfo>
#include<unistd.h>

#include<exception>


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
static ExecutableOptions& GetInstance();
    void Parse(int argc,char **argv);
    typedef std::deque<std::string> input_files_list_t;
    input_files_list_t::iterator GetInputFilesBegin(){return fInputFiles.begin();}
    input_files_list_t::iterator GetInputFilesEnd  (){return fInputFiles.end  ();}
    int GetVerbosity(){return fVerbosity;}
    std::string& GetLogFile(){return fLogFile;}
    std::string& GetOutputRootFile(){return fOutputRootFile;}
    std::string& GetCellCalDatFile(){return fCellCalDatFile;}
    unsigned int GetNEvtToProcess()const{return fNEvtToProcess;}
  private:
    ExecutableOptions();
    ExecutableOptions(const ExecutableOptions&)=delete;
    void operator=(const ExecutableOptions&)=delete;

    public:

    input_files_list_t fInputFiles;
    int fVerbosity;
    unsigned int fNEvtToProcess;
    std::string fLogFile;
    std::string fOutputRootFile;
    std::string fCellCalDatFile;
};



#endif
