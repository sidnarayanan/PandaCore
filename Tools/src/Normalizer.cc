#include "../interface/Normalizer.h"

float Normalizer::getValue() 
{
    return xsec * tf->EvalInstance() / totalEvts; 
} 

void Normalizer::NormalizeTree(TTree *t, double totalEvts_, double xsec_) 
{
    xsec = xsec_;
    totalEvts = totalEvts_;

    addBranch(t);
}


void Normalizer::NormalizeTree(TString fpath, double xsec_) 
{
    TFile *fIn = TFile::Open(fpath,"UPDATE");
    TTree *t = (TTree*)fIn->Get(treeName.Data());
    TH1F *h = (TH1F*)fIn->Get(histName.Data());
    if (t==NULL || h==NULL) {
        PError("Normalizer::NormalizeTree",TString::Format("Could not normalize %s because tree=%p and hist=%p\n",fpath.Data(),t,h));
        return; 
    }
    NormalizeTree(t,h->Integral(),xsec_);
    fIn->WriteTObject(t,treeName.Data(),"overwrite");
    fIn->Close();
}
