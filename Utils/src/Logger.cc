#include "../interface/Logger.h"

Logger logger; 

Logger::RType::RType(TString n, TString c, FILE* f) : name(n), color(c), fhandle(f) 
{
  pad = "";
  for (int i = n.Length(); i != 9; ++i)
    pad += " ";
}

Logger::Logger(TString name) :
  _isatty(isatty(fileno(stdout))),
  _fhandle(_isatty ? stdout : stderr),
  _name(name),
  _info("INFO", "32m", _fhandle),
  _debug("DEBUG", "36m", _fhandle),
  _warning("WARNING", "91m", stderr),
  _error("ERROR", "41m\033[1;37m", stderr) 
{
  if (_isatty)  
    _tmpl = "\033[0;%s%s\033[0m%s [%-"+TString::Format("%i",MAXLOGGERLEN)+"s]: %s%s";
  else
    _tmpl = "%s%s [%-"+TString::Format("%i",MAXLOGGERLEN)+"s]: %s%s";
}

void Logger::_report(const RType& r, TString title, const TString& msg, const TString& n) const 
{ 
  title = _name+title; 
  if (title.Length() > MAXLOGGERLEN) {
    title = "..." + title(title.Length()-MAXLOGGERLEN+3,
                           title.Length());
  }
  if (_isatty) {
    fprintf(
      r.fhandle,
      "%s",
      Form(_tmpl,
           r.color.Data(), r.name.Data(), r.pad.Data(), title.Data(), msg.Data(), n.Data()));
  } else {
    fprintf(
      r.fhandle,
      "%s",
      Form(_tmpl,
           r.name.Data(), r.pad.Data(), title.Data(), msg.Data(), n.Data()));
  }
}
