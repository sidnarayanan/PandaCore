#include "PandaCore/Tools/interface/Common.h"
#include "TChain.h"

#ifndef TREETOOLS_H
#define TREETOOLS_H

/** \file TreeTools.h
 * \brief Common functions for dealing with TTrees 
 */

//////////////////////////////////////////////////////////////////////////////////

/**
 * \param t input tree
 * \param s formula containing dependencies
 * \brief Figures out any substrings of s that are branch dependencies
 * and sets the status of those branches to 1
 */
void turnOnBranches(TTree*t,TString s);

//////////////////////////////////////////////////////////////////////////////////

#endif
