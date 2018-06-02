#ifndef LOGGER_H
#define LOGGER_H

#include "TString.h"
#define MAXLOGGERLEN 30


class Logger {
public:
  Logger(TString name="");
  void info(const char *title, const char *msg, const char *n="\n") const {
    _report(_info, title, msg, n);
  }
  void debug(const char *title, const char *msg, const char *n="\n") const {
    _report(_debug, title, msg, n);
  }
  void warning(const char *title, const char *msg, const char *n="\n") const {
    _report(_warning, title, msg, n);
  }
  void error(const char *title, const char *msg, const char *n="\n") const {
    _report(_error, title, msg, n);
  }

private:
  struct RType {
    RType(TString n, TString c, FILE* f);
    TString name;
    TString color;
    TString pad;
    FILE *const fhandle;
  };
  void _report(const RType& r, TString title, const TString& msg, const TString& n) const;
  bool _isatty;
  FILE *const _fhandle;
  TString _name, _tmpl;
  RType _info, _debug, _warning, _error;
};

#endif
