#ifndef PHEADER
#define PHEADER

#include "PandaCore/Utils/interface/Logger.h"

typedef void (Logger::*printfn) (const char *, const char *, const char *) const;

Logger logger; 

void log(int argc, char **argv, printfn f)
{
  TString name = "shell", report = "";
  bool is_name = false; 
  for (int iA=1; iA!=argc; ++iA) {
      std::string this_arg = argv[iA];
      if (this_arg=="-n") {
          is_name = true;
          continue;
      }
      if (is_name) {
          name = this_arg;
          is_name = false;
          continue;
      }
      report += this_arg;
      report += " ";
  }

  (logger.*f)(name.Data(),report.Data(),"\n");
}


#endif
