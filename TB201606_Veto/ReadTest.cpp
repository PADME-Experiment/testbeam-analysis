#include<exception>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

#include "TRawEvent.hh"


#include "TH1F.h"
#include "TH2F.h"
#include "TDirectory.h"
#include<sstream>
#include<string>


#include<vector>
#include<algorithm>
#include<string>
#include<iostream>
#include<cctype>
#include <fstream>



int verbose = 0;
int nevents = 0;


#include"histos.hh"
#include"analyse.hh"


class ExceptSynopsis:public std::runtime_error{
  public:
    ExceptSynopsis(auto a):runtime_error(a){}
    ExceptSynopsis(const std::string&opt,const std::string&val):
      runtime_error("Error while processing option '"+opt+"'. Invalid parameter'"+val+"'"){}
};

int main(int argc, char* argv[]){
  int c;
  char tmpchar[500];
  std::string outputRootFN="t.root";

  std::vector<std::string> inputFiles,inputLists;
  std::string tmpstring;

  // Parse options
  try{
    while ((c = getopt (argc, argv, "i:n:v:ho:")) != -1) {
      switch (c) {
        case 'o': outputRootFN=optarg;
                  break;
        case 'i':
                  tmpstring=optarg;inputFiles.push_back(tmpstring);
                  fprintf(stdout,"Set input data file to '%s'\n",tmpstring.c_str());
                  break;
        case 'l':
                  tmpstring=optarg;inputLists.push_back(tmpstring);
                  break;
        case 'n':
                  if ( sscanf(optarg,"%d",&nevents) != 1 ) throw ExceptSynopsis("-n",optarg);
                  break;
        case 'v':
                  if ( sscanf(optarg,"%d",&verbose) != 1 ) throw ExceptSynopsis("-v",optarg);
                  break;
        case 'h':
                  fprintf(stdout,"\nReadTest [-i input root file] [-o otput root file] [-v verbosity] [-h]\n\n");
                  fprintf(stdout,"  -i: define an input file in root format\n");
                  fprintf(stdout,"  -0: define an otput file in root format\n");
                  fprintf(stdout,"  -n: define number of events to read from input file (0: all events)\n");
                  fprintf(stdout,"  -v: define verbose level\n");
                  fprintf(stdout,"  -h: show this help message and exit\n\n");
                  return 0;// exit(0);
        case '?':
                  if (optopt == 'v') {
                    // verbose with no argument: just enable at minimal level
                    verbose = 1;
                    break;
                  } else if (optopt == 'i' || optopt == 'l' || optopt == 'o')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                  else if (isprint(optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                  else
                    fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
                  exit(1);
        default:
                  throw ExceptSynopsis("Parameter error");
      }
    }
  }
    catch(const ExceptSynopsis& e){
      std::cerr << "Synopsis exception"<<std::endl;
      std::cerr << e.what()<<std::endl;;
      return 1;
    }




    for(unsigned int i=0;i<inputLists.size();++i){
      std::ifstream list(inputLists[i].c_str(),std::ifstream::in);
      if(!list.is_open())continue;
      std::cerr<<"proc list "<<inputLists[i]<<std::endl;
      while(!list.eof()){
        //list>>tmpstring;
        list.getline((char*)tmpchar,500,'\n');
        tmpstring=tmpchar;
        tmpstring.erase(std::remove(tmpstring.begin(),tmpstring.end(),' '),tmpstring.end());
        if(tmpstring.find_first_of('#')!=std::string::npos)
          tmpstring.erase(tmpstring.find_first_of('#'),tmpstring.length()); // # comment char
        if(tmpstring.size()>0)
          inputFiles.push_back(tmpstring);
      }
    }





    Analyse anl(outputRootFN);

    for(std::vector<std::string>::iterator if_it=inputFiles.begin();
        if_it!=inputFiles.end();
        ++if_it){
      std::string& filename=*if_it;
      std::cerr<<"Processing \""<<filename<<"\""<<std::endl;
      anl.Process(filename);
    }
    anl.Finalize();

}
