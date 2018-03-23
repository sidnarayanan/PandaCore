#ifndef PANDACORE_TOOLS_BranchAdder
#define PANDACORE_TOOLS_BranchAdder

#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"
#include "TString.h"
#include "TTreeFormula.h"
#include "Common.h"
#include "TreeTools.h"

/**
 * \brief Adds a branch to a tree
 *
 * Can be used to add a branch to a tree based on a generic formula
 * or based on a histogram
 */

// abstract class 
class BranchAdder {
public:
  BranchAdder() { }
  virtual ~BranchAdder() { }

  virtual void addBranch(TString fpath) { 
    TFile *f = TFile::Open(fpath);
    TTree *t = (TTree*)f->Get(treeName);
    addBranch(t);
    f->WriteTObject(t,treeName,"OVERWRITE");
    f->Close();
  }
  virtual void addBranch(TTree *t) = 0;

  TString newBranchName{"newBranch"};
  TString treeName{"events"};
  TString cut{"1==1"};
  float defaultValue{1};
  bool verbose{true};
  int reportFreq{10};

protected:
  void doAddBranch(TTree *t);
  virtual float getValue() = 0;
};


class FormulaBranchAdder: 
  public BranchAdder
{
public:
  FormulaBranchAdder() { }
  virtual ~FormulaBranchAdder() { delete tf; }

  virtual void addBranch(TTree *t) override;

  TString formula{"1"};
protected:
  virtual float getValue() override;

  TTreeFormula *tf{nullptr};
};


template <typename H>
class HBranchAdder:
  public BranchAdder
{
public:
  HBranchAdder() { }
  ~HBranchAdder() { delete tfX; delete tfY; }

  void addBranch(TTree *t) override;

  void setH(const TH1* h_);

  TString formulaX{"1"};
  TString formulaY{"1"};
protected:
  float getValue() override;

  H h;
  float xlo, xhi, ylo, yhi;
  TTreeFormula *tfX{nullptr};
  TTreeFormula *tfY{nullptr};
};

#endif
