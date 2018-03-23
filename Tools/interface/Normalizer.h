#ifndef PANDACORE_TOOLS_NORMALIZER
#define PANDACORE_TOOLS_NORMALIZER

#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"
#include "TString.h"
#include "TH1F.h"
#include "Common.h"
#include "TreeTools.h"
#include "BranchAdder.h"

/**
 * \brief Normalizes a tree
 *
 * Given an input weight, class adds an output weight
 * that is calculated as in_weight*xsec/total_events
 */
class Normalizer:
  protected FormulaBranchAdder
{
public:
    Normalizer():
      histName("hDTotalMCWeight") 
      { 
        formula = "mcWeight";
        treeName = "events";
        newBranchName = "normalizedWeight";
      }
    ~Normalizer() { }

    /**
     * \param t input tree
     * \param totalEvents total number of events for this process
     * \param xsec cross-section for this process
     * \brief Normalizes the tree given total weight of events and 
     * cross-section
     */
    void NormalizeTree(TTree *t, double totalEvts_, double xsec_);

    /**
     * \param fpath path to input file 
     * \param xsec cross-section for this process
     * \brief Reads an input file and picks up the tree to normalize
     * as well as a histogram containing the weight of events
     */
    void NormalizeTree(TString fpath, double xsec_);

    TString histName; /**< name of histogram containing MC weights */
    bool isFloat = true;
    int histBin = 1; /**< if > 0, use that bin. if < 0, use the integral **/ 

protected:
  float getValue() override;
  double xsec;
  double totalEvts;
};
#endif
