#include"exec_options.hh"


ExecutableOptions& ExecutableOptions::GetInstance(){
  static ExecutableOptions a;
  return a;
}




ExecutableOptions::ExecutableOptions():
  fVerbosity(5),
  fNEvtToProcess(-1)
{}
void ExecutableOptions::Parse(int argc,char **argv) {
  int c;

  std::vector<std::string> inputLists;

  // Parse options
  while ((c = getopt (argc, argv, "c:i:o:l:n:V:vqh")) != -1) {
    switch (c) {
      case 'c': fCellCalDatFile=optarg;
                break;
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
      case 'h': fprintf(stdout,"\nReadTest [-i input root file] [-o otput root file] [-v verbosity] [-h]\n\n");
                fprintf(stdout,"  -i: define an input file in root format\n");
                fprintf(stdout,"  -0: define an otput file in root format\n");
                fprintf(stdout,"  -n: define number of events to read from input file (0: all events)\n");
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
