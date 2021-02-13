#include "TH2D.h"
#include <iostream>
#include <math.h>
//macro to compare pt and eta from ak4/8 1 to 2
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
TCanvas * pT4_vs = new TCanvas("pT4_vs","pT4_vs", 800, 800);
TH2D * h_pT_vs;
signal_region->GetObject("Kin_AK8/pT_AK4_1_vs_pT_AK4_2_S2_5p0", h_pT_vs);//add ending for parameter
//pT4_vs -> SetLogy();
h_pT_vs -> GetZaxis()->SetTitle("Event Density");
h_pT_vs->GetZaxis()->SetTitleOffset(1.5);
h_pT_vs->GetZaxis()->RotateTitle(180);

//h_pT_vs->GetZaxis()->ChangeLabel(9,90,-1,-1,-1,-1,"Events");
//h_pT_vs->GetZaxis()->SetTitleOffset(1.4);
h_pT_vs ->GetXaxis()->SetRangeUser(0,2500);
h_pT_vs ->GetYaxis()->SetRangeUser(0,2500);
h_pT_vs -> GetYaxis()->SetTitle("p_{T} AK4_{2} [GeV/c^{2}]");
h_pT_vs ->GetXaxis()->SetTitle("p_{T} AK4_{1} [GeV/c^{2}]");
h_pT_vs -> SetTitle("p_{T} AK4_{1} vs p_{T} AK4_{2}");
h_pT_vs -> Draw("COLZ");
pT4_vs ->SetRightMargin(0.15);
pT4_vs->SetLeftMargin(0.15);
pT4_vs -> SaveAs(".pdf");

//gROOT->SetBatch();
//__________________________________________________________AK4_eta_vs
TCanvas * eta4_vs = new TCanvas("eta4_vs","eta4_vs", 800, 800);
TH2D * h_eta_vs;
signal_region->GetObject("Kin_AK8/eta_AK4_1_vs_eta_AK4_2_S2_5p0", h_eta_vs);//add ending for parameter
//eta4_vs -> SetLogy();
h_eta_vs -> GetZaxis()->SetTitle("Event Density");
h_eta_vs->GetZaxis()->SetTitleOffset(1.8);
h_eta_vs->GetZaxis()->RotateTitle(180);
h_eta_vs ->GetXaxis()->SetRangeUser(-5,5);
h_eta_vs  ->GetYaxis()->SetRangeUser(-5,5);
h_eta_vs -> GetYaxis()->SetTitle("#eta AK4_{2}");
h_eta_vs ->GetXaxis()->SetTitle("#eta AK4_{1}");
h_eta_vs -> SetTitle("#eta AK4_{1} vs #eta AK4_{2}");
h_eta_vs -> Draw("COLZ");
eta4_vs ->SetRightMargin(0.19);
eta4_vs -> SaveAs(".pdf");

//________________________________________________________compare AK8
TFile * signal = new TFile("/nfs/dust/cms/user/loemkerj/bachelor/CMSSW_10_2_16/src/UHH2/aQGCVVjjhadronic/SignalRegion/uhh2.AnalysisModuleRunner.MC.MC_aQGC_ZZjj_hadronic_2016v3.root","READ");
gStyle -> SetOptStat(0);
//__________________________________________________________AK8_pT_vs
TCanvas * pT8_vs = new TCanvas("pT8_vs","pT8_vs", 800, 800);
TH2D * h_pT;
signal->GetObject("Kin_AK8/pT_AK8_1_vs_pT_AK8_2_S2_5p0", h_pT);//add ending for parameter
//pT8_vs -> SetLogy();
h_pT -> GetZaxis()->SetTitle("Event Density");
h_pT->GetZaxis()->SetTitleOffset(1.5);
h_pT->GetZaxis()->RotateTitle(180);
h_pT ->GetXaxis()->SetRangeUser(0,4500);
h_pT  ->GetYaxis()->SetRangeUser(0,4500);
h_pT -> GetYaxis()->SetTitle("p_{T} AK8_{2} [GeV/c^{2}]");
h_pT ->GetXaxis()->SetTitle("p_{T} AK8_{1} [GeV/c^{2}]");
h_pT -> SetTitle("p_{T} AK8_{1} vs p_{T} AK8_{2}");
h_pT -> Draw("COLZ");
pT8_vs ->SetRightMargin(0.15);
pT8_vs ->SetLeftMargin(0.15);
pT8_vs -> SaveAs(".pdf");
//__________________________________________________________AK4_eta_vs
TCanvas * eta8_vs = new TCanvas("eta8_vs","eta8_vs", 800, 800);
TH2D * h_eta;
signal->GetObject("Kin_AK8/eta_AK8_1_vs_eta_AK8_2_S2_5p0", h_eta);//add ending for parameter
//eta8_vs -> SetLogy();
h_eta -> GetZaxis()->SetTitle("Event Density");
h_eta->GetZaxis()->SetTitleOffset(1.8);
h_eta->GetZaxis()->RotateTitle(180);
h_eta ->GetXaxis()->SetRangeUser(-3,3);
h_eta ->GetYaxis()->SetRangeUser(-3,3);
h_eta -> GetYaxis()->SetTitle("#eta AK8_{2}");
h_eta ->GetXaxis()->SetTitle("#eta AK8_{1}");
h_eta -> SetTitle("#eta AK8_{1} vs #eta AK8_{2}");
h_eta -> Draw("COLZ");
eta8_vs ->SetRightMargin(0.19);
eta8_vs -> SaveAs(".pdf");
}