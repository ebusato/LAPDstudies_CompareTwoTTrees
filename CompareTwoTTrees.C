#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooHistPdf.h"
#include "RooPlot.h"
using namespace RooFit ;


TH1F* GetTH1FromTTree(TTree* t, TString varName, TString cut, int color, int nBins, double min, double max)
{
  TString TH1Name("h_"+varName);
  TH1F* h = new TH1F(TH1Name.Data(), TH1Name.Data(), nBins, min, max);
  TString s(varName + ">>" + TH1Name);
  t->Draw(s.Data(), cut);
  h->Sumw2();
  h->SetLineColor(color);
  h->SetMarkerColor(color);
  h->Scale(1/h->Integral());
  return h;
}

// example :
//  root -l 'CompareTwoTTrees.C("~/godaq_rootfiles/analysis_v2.10.0/run67.root", "~/godaq_rootfiles/analysis_v2.10.0/run79.root", "NoPulses", "", 240, 0, 240)'
void CompareTwoTTrees(TString file1, TString file2, TString varName, TString cut, int nBins, double min, double max)
{
  TFile* f1 = new TFile(file1.Data(), "read");
  TFile* f2 = new TFile(file2.Data(), "read");
  TTree* t1 = (TTree*) f1->Get("tree");
  TTree* t2 = (TTree*) f2->Get("tree");
  TH1F* h1 = GetTH1FromTTree(t1, varName, cut, kBlack, nBins, min, max);
  TH1F* h2 = GetTH1FromTTree(t2, varName, cut, kRed, nBins, min, max);
  h1->Draw("e");
  h2->Draw("esame");
}
