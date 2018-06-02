#include "../interface/Logger.h"

Logger logger; 

void Logger::_report(const RType& r, const char *title, const char *msg, const char *n) {
    if (_isatty) {
      fprintf(
        r.fhandle,
        "%s",
        Form("\033[0;%s%s\033[0m%s [%-30s]: %s%s",
             r.color.Data(), r.name.Data(), r.pad.Data(), (_name+title).Data(), msg, n));
    } else {
      fprintf(
        r.fhandle,
        "%s",
        Form("%s%s [%-30s]: %s%s",
             r.name.Data(), r.pad.Data(), (_name+title).Data(), msg, n));
    }
}
