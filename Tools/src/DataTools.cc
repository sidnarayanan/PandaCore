#include "../interface/DataTools.h"

bool matchTriggerName(std::string pattern, std::string name) {
  if (pattern.size() > name.size())
    return false;
  unsigned nC = pattern.size();
  for (unsigned iC=0; iC!=nC; ++iC) {
    if (pattern[iC] != name[iC])
      return false;
  }
  return true;
}

EraHandler::EraHandler(int year) 
{
  switch (year) 
  {
    case 2016: 
    {
      runBounds = {272007,
                   275657,
                   276315,
                   276831,
                   277772,
                   278820,
                   280919,
                   284045};
      eraNames = {"B","C","D","E","F","G","H"};
      bins = new Binner(runBounds);
      break;
    }
    case 2017:
    {
      runBounds = {297020,
                   299337,
                   302030,
                   303435,
                   304911,
                   306462};
      eraNames = {"B","C","D","E","F"};
      bins = new Binner(runBounds);
      break;
    }
    default :
    {
      logger.error("EraHandler",TString::Format("Year %i is not known",year));
    }
  }
}

TString EraHandler::getEra(int runNumber) 
{
  if (runNumber<runBounds[0]) {
    logger.error("EraHandler",
        TString::Format("Run number (%i) is less than first run (%i)",runNumber,(int)runBounds[0]));
    return "";
  }
  if (runNumber>runBounds.back()) {
    logger.error("EraHandler",
        TString::Format("Run number (%i) is greater than last run (%i)",runNumber,(int)runBounds.back()));
    return "";
  }
  unsigned int eraIdx = bins->bin(runNumber);
  return eraNames.at(eraIdx);
}
