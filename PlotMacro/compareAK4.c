#include "TH2D.h"
#include <iostream>
#include <math.h>
//macro to compare pt and eta from ak4 1 to 2
//repeat this for the ones without Mjj cut...should be in another directory...No they wont, because the EFT applies only after the cut
//repeat for the ones without EFT once with and without Mjj Ak4 cut
// -> legend ass well
/*  Different cuts
    Kin_AK8;
    Kin_AK4_N_cut;
    Kin_AK4_deta_cut;
*/
void compareAK4(){
gStyle -> SetOptStat(0);
//gROOT->SetBatch();
TFile * signal_region = new TFile("/nfs/dust/cms/user/loemkerj/bachelor/CMSSW_10_2_16/src/UHH2/aQGCVVjjhadronic/SignalRegion/uhh2.AnalysisModuleRunner.MC.MC_aQGC_ZZjj_hadronic_2016v3.root","READ");
gStyle -> SetOptStat(0);
//__________________________________________________________AK4_pT_vs
TCanvas * pT4_vs = new TCanvas("pT4_vs","pT4_vs", 500, 500);

TH2D * h_pT_vs;
signal_region->GetObject("Kin_AK8/pT_AK4_1_vs_pT_AK4_2_S2_5p0", h_pT_vs);//add ending for parameter

//pT4_vs -> SetLogy();
//h_pT_vs -> GetXaxis()->SetRangeUser(0,2500);
h_pT_vs -> GetYaxis()->SetTitle("p_{T} AK4_{2} [GeV/c^{2}]");
h_pT_vs ->GetXaxis()->SetTitle("p_{T} AK4_{1} [GeV/c^{2}]");
h_pT_vs -> SetTitle("p_{T} AK4_{1} vs p_{T} AK4_{2}");
//h_pT_vs -> SetLineColor(kBlack);
//h_pT_vs -> Rebin(2);
h_pT_vs -> Draw("COLZ");
//gPad -> BuildLegend();
pT4_vs -> SaveAs(" NoOppositeEtaCutpT4.pdf");
//__________________________________________________________AK4_eta_vs
TCanvas * eta4_vs = new TCanvas("eta4_vs","eta4_vs", 500, 500);

TH2D * h_eta_vs;
signal_region->GetObject("Kin_AK8/eta_AK4_1_vs_eta_AK4_2_S2_5p0", h_eta_vs);//add ending for parameter
//eta4_vs -> SetLogy();
//h_pT_vs -> GetXaxis()->SetRangeUser(0,2500);
h_eta_vs -> GetYaxis()->SetTitle("#eta AK4_{2}");
h_eta_vs ->GetXaxis()->SetTitle("#eta AK4_{1}");
h_eta_vs -> SetTitle("#eta AK4_{1} vs #eta AK4_{2}");
//h_eta_vs -> SetLineColor(kBlack);
//h_eta_vs -> Rebin(2);
h_eta_vs -> Draw("COLZ");
//gPad -> BuildLegend();
eta4_vs -> SaveAs(" NoOppositeEtaCuteta4.pdf");
}