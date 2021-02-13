//make sure you focus on 4TeV max! 
//-Rebin, Rescale would be nice...
//overlay S2,T1,M1 plots pT and mass
//do it all again for VV selection
//!!!eta is -5 to 5for AK8!
//set binning
//setup the fit to extract signal for pT, invMass
#include "TH1F.h"
#include <iostream>
#include <math.h>

void comparePlot(){
gStyle -> SetOptStat(0);
gROOT->SetBatch();
TFile * signal_region = new TFile("/nfs/dust/cms/user/loemkerj/bachelor/CMSSW_10_2_16/src/UHH2/aQGCVVjjhadronic/SignalRegion/uhh2.AnalysisModuleRunner.MC.MC_aQGC_ZZjj_hadronic_2016v3.root","READ");
//________________________________________________________*************SelectionCriteria************AK4uhh2.AnalysisModuleRunner.MC.MC_QCD.root
//________________________________________________________pT-Hists
//plot them all in old code and then implement it here

TCanvas * pT4 = new TCanvas("pT4","pT4", 400, 400);

TH1F * h_SM4;
signal_region->GetObject("Kin_AK8/pT_AK4_12_S2_0p0", h_SM4);
TH1F * h_S24;
signal_region->GetObject("Kin_AK8/pT_AK4_12_S2_5p0", h_S24);
TH1F * h_M14;
signal_region->GetObject("Kin_AK8/pT_AK4_12_M1_0p70", h_M14);
TH1F * h_T14;
signal_region->GetObject("Kin_AK8/pT_AK4_12_T1_0p5", h_T14);
// book<TH1F>(AK4_pT_hist_name, "p_{T}^{leading AK4 jets} [GeV/c^{2}]", 40 ,0 ,4000);
pT4 -> SetLogy();
h_SM4 -> GetXaxis()->SetRangeUser(0,2500);
h_SM4 -> GetYaxis()->SetTitle("Events");
h_SM4 ->GetXaxis()->SetTitle("[GeV/c^{2}]");
h_SM4 -> SetTitle("p_{T} leading AK4 jets");
h_SM4 -> SetLineColor(kBlack);
h_SM4 -> Draw("H");
h_SM4 -> Rebin(2);
h_S24 -> GetXaxis()->SetRangeUser(0,2500);
h_S24 -> SetTitle("S2_{5p0}");
h_S24 -> SetLineColor(kBlue);
h_S24 -> Rebin(2);
//h_S24 -> SetLineStyle(kDashed);
h_S24 -> Draw("1SAME");
h_M14 -> GetXaxis()->SetRangeUser(0,2500);
h_M14 -> Rebin(2);
h_M14 -> SetTitle("M1_{0p70}");
h_M14 -> SetLineColor(kRed);
//h_M14 -> SetLineStyle(kDotted);
h_M14 -> Draw("1SAME");
h_T14 -> GetXaxis()->SetRangeUser(0,2500);
h_T14 -> Rebin(2);
h_T14 -> SetLineColor(kGreen);
h_T14 -> SetTitle("T1_{0p5}");
h_T14 -> Draw("1SAME");
gPad -> BuildLegend();
//pT4 -> SaveAs(".pdf");

//__________________________________________________________invMass-Hists
TCanvas * iM4 = new TCanvas("invMass4","invMass4", 400, 400);

TH1F * h_SMM4;
signal_region->GetObject("MjjHists_invMAk4sel_1p0/M_jj_AK4_S2_0p0", h_SMM4);
TH1F * h_S2M4;
signal_region->GetObject("MjjHists_invMAk4sel_1p0/M_jj_AK4_S2_5p0", h_S2M4);
TH1F * h_M1M4;
signal_region->GetObject("MjjHists_invMAk4sel_1p0/M_jj_AK4_M1_0p70", h_M1M4);
TH1F * h_T1M4;
signal_region->GetObject("MjjHists_invMAk4sel_1p0/M_jj_AK4_T1_0p5", h_T1M4);
// book<TH1F>(AK4_pT_hist_name, "p_{T}^{leading AK4 jets} [GeV/c^{2}]", 40 ,0 ,4000);
//    book<TH1F>(AK4_hist_name, "M_{jj-AK4} [GeV/c^{2}]",10000,0,10000);_____Bin
iM4 -> SetLogy();
h_SMM4 -> Rebin(500);
h_SMM4 -> GetXaxis()->SetRangeUser(500,6000);
h_SMM4 -> GetYaxis()->SetTitle("Events");
h_SMM4 ->GetXaxis()->SetTitle("[GeV/c^{2}]");
h_SMM4 -> SetTitle("M_{jj} leading AK4 jets");
h_SMM4 -> SetLineColor(kBlack);
h_SMM4 -> Draw("H");
h_S2M4 -> Rebin(500);
h_S2M4 -> GetXaxis()->SetRangeUser(500,6000);
h_S2M4 -> SetTitle("S2_{5p0}");
h_S2M4 -> SetLineColor(kBlue);
//h_S2M4 -> SetLineStyle(kDashed);
h_S2M4 -> Draw("1SAME");
h_M1M4 -> GetXaxis()->SetRangeUser(500,6000);
h_M1M4 -> Rebin(500);
h_M1M4 -> SetTitle("M1_{0p70}");
h_M1M4 -> SetLineColor(kRed);
//h_M1M4 -> SetLineStyle(kDotted);
h_M1M4 -> Draw("1SAME");
h_T1M4 -> GetXaxis()->SetRangeUser(500,6000);
h_T1M4 -> Rebin(500);
h_T1M4 -> SetLineColor(kGreen);
h_T1M4 -> SetTitle("T1_{0p5}");
h_T1M4 -> Draw("1SAME");
gPad -> BuildLegend();
//iM4 -> SaveAs(".pdf");

//__________________________________________________________eta-Hists
//book<TH1F>(AK4_eta_hist_name, "#eta^{leading AK4 jets}", 40, -6.5, 6.5);
TCanvas * eta4 = new TCanvas("eta4","eta4", 400, 400);

TH1F * h_SMe4;
signal_region->GetObject("Kin_AK8/eta_AK4_12_S2_0p0", h_SMe4);
TH1F * h_S2e4;
signal_region->GetObject("Kin_AK8/eta_AK4_12_S2_5p0", h_S2e4);
TH1F * h_M1e4;
signal_region->GetObject("Kin_AK8/eta_AK4_12_M1_0p70", h_M1e4);
TH1F * h_T1e4;
signal_region->GetObject("Kin_AK8/eta_AK4_12_T1_0p5", h_T1e4);

eta4 -> SetLogy();
h_SMe4 -> Rebin(2);
h_SMe4 -> GetXaxis()->SetRangeUser(-5,5);
h_SMe4 -> GetYaxis()->SetTitle("Events");
h_SMe4 ->GetXaxis()->SetTitle("#eta");
h_SMe4 -> SetTitle("#eta leading AK4 jets");
h_SMe4 -> SetLineColor(kBlack);
h_SMe4 -> Draw("H");
h_S2e4 -> GetXaxis()->SetRangeUser(-5,5);
h_S2e4 -> Rebin(2);
h_S2e4 -> SetTitle("S2_{5p0}");
h_S2e4 -> SetLineColor(kBlue);
//h_S2e4 -> SetLineStyle(kDashed);
h_S2e4 -> Draw("1SAME");
h_M1e4 -> GetXaxis()->SetRangeUser(-5,5);
h_M1e4 -> Rebin(2);
h_M1e4 -> SetTitle("M1_{0p70}");
h_M1e4 -> SetLineColor(kRed);
//h_M1M4 -> SetLineStyle(kDotted);
h_M1e4 -> Draw("1SAME");
h_T1e4 -> GetXaxis()->SetRangeUser(-5,5);
h_T1e4 -> Rebin(2);
h_T1e4 -> SetLineColor(kGreen);
h_T1e4 -> SetTitle("T1_{0p5}");
h_T1e4 -> Draw("1SAME");
gPad -> BuildLegend();
//eta4 -> SaveAs(".pdf");

//__________________________________________________________deta-Hists

//book<TH1F>(AK4_deta_hist_name, "#Delta #eta^{leading AK4 jets}", 40, 0, 13.0);

TCanvas * deta4 = new TCanvas("deta4","deta4", 400, 400);

TH1F * h_SMd4;
signal_region->GetObject("Kin_AK8/deta_AK4_12_S2_0p0", h_SMd4);
TH1F * h_S2d4;
signal_region->GetObject("Kin_AK8/deta_AK4_12_S2_5p0", h_S2d4);
TH1F * h_M1d4;
signal_region->GetObject("Kin_AK8/deta_AK4_12_M1_0p70", h_M1d4);
TH1F * h_T1d4;
signal_region->GetObject("Kin_AK8/deta_AK4_12_T1_0p5", h_T1d4);

deta4 -> SetLogy();
h_SMd4 -> Rebin(2);
h_SMd4 -> GetXaxis()->SetRangeUser(2,10);
h_SMd4 -> GetYaxis()->SetTitle("Events");
h_SMd4 ->GetXaxis()->SetTitle("#Delta #eta");
h_SMd4 -> SetTitle("#Delta #eta leading AK4 jets");
h_SMd4 -> SetLineColor(kBlack);
h_SMd4 -> Draw("H");
h_S2d4 -> GetXaxis()->SetRangeUser(2,10);
h_S2d4 -> Rebin(2);
h_S2d4 -> SetTitle("S2_{5p0}");
h_S2d4 -> SetLineColor(kBlue);
//h_S2d4 -> SetLineStyle(kDashed);
h_S2d4 -> Draw("1SAME");
h_M1d4 -> GetXaxis()->SetRangeUser(2,10);
h_M1d4 -> Rebin(2);
h_M1d4 -> SetTitle("M1_{0p70}");
h_M1d4 -> SetLineColor(kRed);
//h_M1M4 -> SetLineStyle(kDotted);
h_M1d4 -> Draw("1SAME");
h_T1d4 -> GetXaxis()->SetRangeUser(2,10);
h_T1d4 -> Rebin(2);
h_T1d4 -> SetLineColor(kGreen);
h_T1d4 -> SetTitle("T1_{0p5}");
h_T1d4 -> Draw("1SAME");
gPad -> BuildLegend();
//deta4 -> SaveAs(".pdf");

//__________________________________________________________prodeta-Hists
//book<TH1F>(AK4_prodeta_hist_name, "#eta^{1st AK4 jet} #cdot #eta^{2nd AK4 jet}", 87, -43, 43);//what is this ?

TCanvas * prodeta = new TCanvas("prodeta","prodeta", 400, 400);

TH1F * h_SMp;
signal_region->GetObject("Kin_AK8/deta_AK4_12_S2_0p0", h_SMp);
TH1F * h_S2p;
signal_region->GetObject("Kin_AK8/deta_AK4_12_S2_5p0", h_S2p);
TH1F * h_M1p;
signal_region->GetObject("Kin_AK8/deta_AK4_12_M1_0p70", h_M1p);
TH1F * h_T1p;
signal_region->GetObject("Kin_AK8/deta_AK4_12_T1_0p5", h_T1p);

prodeta -> SetLogy();
h_SMp -> Rebin(5);
//h_SMp -> GetXaxis()->SetRangeUser(-5,5);
h_SMp -> GetYaxis()->SetTitle("Events");
h_SMp ->GetXaxis()->SetTitle("#Delta #eta");
h_SMp -> SetTitle("#Delta #eta leading AK4 jets");
h_SMp -> SetLineColor(kBlack);
h_SMp -> Draw("H");
h_S2p -> Rebin(5);
h_S2p -> SetTitle("S2_{5p0}");
h_S2p -> SetLineColor(kBlue);
//h_S2p -> SetLineStyle(kDashed);
h_S2p -> Draw("1SAME");
h_M1p -> Rebin(5);
h_M1p -> SetTitle("M1_{0p70}");
h_M1p -> SetLineColor(kRed);
//h_M1Mp -> SetLineStyle(kDotted);
h_M1p -> Draw("1SAME");
h_T1p -> Rebin(5);
h_T1p -> SetLineColor(kGreen);
h_T1p -> SetTitle("T1_{0p5}");
h_T1p -> Draw("1SAME");
gPad -> BuildLegend();
//prodeta -> SaveAs(".pdf");



//__________________________________________________________N_AK4?? :D makes no sense

TCanvas * N4 = new TCanvas("N4","N4", 400, 400);
//book<TH1F>(AK4_N_hist_name, "N_{AK4 jets}", 20, 0, 20); 
TH1F * h_NSM4;
signal_region->GetObject("Kin_AK8/N_AK4_S2_0p0", h_NSM4);
TH1F * h_NS24;
signal_region->GetObject("Kin_AK8/N_AK4_S2_5p0", h_NS24);
TH1F * h_NM14;
signal_region->GetObject("Kin_AK8/N_AK4_M1_0p70", h_NM14);
TH1F * h_NT14;
signal_region->GetObject("Kin_AK8/N_AK4_T1_0p5", h_NT14);
//Binning >= 5 leads to same distribution for AK4 and AK8
N4 -> SetLogy();
//h_NSM4 -> Rebin(2);
//h_NSM4 -> GetXaxis()->SetRangeUser(2,10);
h_NSM4 -> GetYaxis()->SetTitle("Events");
h_NSM4 ->GetXaxis()->SetTitle("N_{AK4 jets}");
h_NSM4 -> SetTitle("N_{AK4 jets}");
h_NSM4 -> SetLineColor(kBlack);
h_NSM4 -> Draw("H");
//h_NS24 -> Rebin(2);
//h_NS24 -> GetXaxis()->SetRangeUser(2,10);
h_NS24 -> SetTitle("S2_{5p0}");
h_NS24 -> SetLineColor(kBlue);
//h_NS24 -> SetLineStyle(kDashed);
h_NS24 -> Draw("1SAME");
//h_NM14 -> Rebin(2);
//h_NM14 -> GetXaxis()->SetRangeUser(2,10);
h_NM14 -> SetTitle("M1_{0p70}");
h_NM14 -> SetLineColor(kRed);
//h_NM14 -> SetLineStyle(kDotted);
h_NM14 -> Draw("1SAME");
//h_NT14 -> Rebin(2);
//h_NT14 -> GetXaxis()->SetRangeUser(2,10);
h_NT14 -> SetLineColor(kGreen);
h_NT14 -> SetTitle("T1_{0p5}");
h_NT14 -> Draw("1SAME");
gPad -> BuildLegend();
//N4 -> SaveAs(".pdf");

//_________________________________________________________************SelectionCriteria************AK8
//_________________________________________________________pT-Hists

TCanvas * pT = new TCanvas("pT","pT", 400, 400);

TH1F * h_SM;
signal_region->GetObject("Kin_AK8/pT_AK8_12_S2_0p0", h_SM);
TH1F * h_S2;
signal_region->GetObject("Kin_AK8/pT_AK8_12_S2_5p0", h_S2);
TH1F * h_M1;
signal_region->GetObject("Kin_AK8/pT_AK8_12_M1_0p70", h_M1);
TH1F * h_T1;
signal_region->GetObject("Kin_AK8/pT_AK8_12_T1_0p5", h_T1);
// book<TH1F>(AK8_pT_hist_name,"p_{T}^{leading AK8 jets} [GeV/c]", 80 ,0 ,8000);
pT -> SetLogy();
h_SM -> GetXaxis()->SetRangeUser(0,5000);
h_SM -> GetYaxis()->SetTitle("Events");
h_SM ->GetXaxis()->SetTitle("[GeV/c^{2}]");
h_SM -> SetTitle("p_{T} leading AK8 jets");
h_SM -> SetLineColor(kBlack);
h_SM -> Rebin(2);
h_SM -> Draw("H");
h_S2 -> SetTitle("S2_{5p0}");
h_S2 -> SetLineColor(kBlue);
//h_S2 -> SetLineStyle(kDashed);
h_S2 -> GetXaxis()->SetRangeUser(0,5000);
h_S2 -> Rebin(2);
h_S2 -> Draw("1SAME");
h_M1 -> SetTitle("M1_{0p70}");
h_M1 -> SetLineColor(kRed);
//h_M1 -> SetLineStyle(kDotted);
h_M1 -> Rebin(2);
h_M1 -> GetXaxis()->SetRangeUser(0,5000);
h_M1 -> Draw("1SAME");
h_T1 -> SetLineColor(kGreen);
h_T1 -> SetTitle("T1_{0p5}");
h_T1 -> Draw("1SAME");
h_T1 -> Rebin(2);
h_T1 -> GetXaxis()->SetRangeUser(0,5000);
gPad -> BuildLegend();
//pT -> SaveAs(".pdf");

//__________________________________________________________invMass-Hists
TCanvas * iM = new TCanvas("invMass","invMass", 400, 400);

TH1F * h_SMM;
signal_region->GetObject("MjjHists_invMAk4sel_1p0/M_jj_AK8_S2_0p0", h_SMM);
TH1F * h_S2M;
signal_region->GetObject("MjjHists_invMAk4sel_1p0/M_jj_AK8_S2_5p0", h_S2M);
TH1F * h_M1M;
signal_region->GetObject("MjjHists_invMAk4sel_1p0/M_jj_AK8_M1_0p70", h_M1M);
TH1F * h_T1M;
signal_region->GetObject("MjjHists_invMAk4sel_1p0/M_jj_AK8_T1_0p5", h_T1M);
//    book<TH1F>(AK8_hist_name, "M_{jj-AK8} [GeV/c^{2}]",10000,0,10000);_____Bin
iM -> SetLogy();
h_SMM -> GetXaxis()->SetRangeUser(500,9000);
h_SMM -> Rebin(500);
h_SMM -> GetYaxis()->SetTitle("Events");
h_SMM ->GetXaxis()->SetTitle("[GeV/c^{2}]");
h_SMM -> SetTitle("M_{jj} leading AK8 jets");
h_SMM -> SetLineColor(kBlack);
h_SMM -> Draw("H");
h_S2M -> GetXaxis()->SetRangeUser(500,9000);
h_S2M -> Rebin(500);
h_S2M -> SetTitle("S2_{5p0}");
h_S2M -> SetLineColor(kBlue);
//h_S2M -> SetLineStyle(kDashed);
h_S2M -> Draw("1SAME");
h_M1M -> Rebin(500);
h_M1M -> GetXaxis()->SetRangeUser(500,9000);
h_M1M -> SetTitle("M1_{0p70}");
h_M1M -> SetLineColor(kRed);
//h_M1M -> SetLineStyle(kDotted);
h_M1M -> Draw("1SAME");
h_T1M -> GetXaxis()->SetRangeUser(500,9000);
h_T1M -> Rebin(500);
h_T1M -> SetLineColor(kGreen);
h_T1M -> SetTitle("T1_{0p5}");
h_T1M -> Draw("1SAME");
gPad -> BuildLegend();
iM -> SaveAs(".pdf");

//__________________________________________________________eta-Hists

TCanvas * eta = new TCanvas("eta","eta", 400, 400);

TH1F * h_SMe;
signal_region->GetObject("Kin_AK8/eta_AK8_12_S2_0p0", h_SMe);
TH1F * h_S2e;
signal_region->GetObject("Kin_AK8/eta_AK8_12_S2_5p0", h_S2e);
TH1F * h_M1e;
signal_region->GetObject("Kin_AK8/eta_AK8_12_M1_0p70", h_M1e);
TH1F * h_T1e;
signal_region->GetObject("Kin_AK8/eta_AK8_12_T1_0p5", h_T1e);

// book<TH1F>(AK8_eta_hist_name, "#eta^{leading AK8 jets}", 40, -6.5, 6.5); 
eta -> SetLogy();
h_SMe -> Rebin(2);
h_SMe -> GetXaxis()->SetRangeUser(-5,5);
h_SMe -> GetYaxis()->SetTitle("Events");
h_SMe ->GetXaxis()->SetTitle("#eta");
h_SMe -> SetTitle("#eta leading AK8 jets");
h_SMe -> SetLineColor(kBlack);
h_SMe -> Draw("H");
h_S2e -> GetXaxis()->SetRangeUser(-5,5);
h_S2e -> Rebin(2);
h_S2e -> SetTitle("S2_{5p0}");
h_S2e -> SetLineColor(kBlue);
//h_S2e -> SetLineStyle(kDashed);
h_S2e -> Draw("1SAME");
h_M1e -> GetXaxis()->SetRangeUser(-5,5);
h_M1e -> Rebin(2);
h_M1e -> SetTitle("M1_{0p70}");
h_M1e -> SetLineColor(kRed);
//h_M1M -> SetLineStyle(kDotted);
h_M1e -> Draw("1SAME");
h_T1e -> GetXaxis()->SetRangeUser(-5,5);
h_T1e -> Rebin(2);
h_T1e -> SetLineColor(kGreen);
h_T1e -> SetTitle("T1_{0p5}");
h_T1e -> Draw("1SAME");
gPad -> BuildLegend();
//eta -> SaveAs(".pdf");

//__________________________________________________________deta-Hists

//  book<TH1F>(AK8_deta_hist_name,"#Delta #eta^{leading AK8 jets}", 40, 0, 13.0); 

TCanvas * deta = new TCanvas("deta","deta", 400, 400);

TH1F * h_SMd;
signal_region->GetObject("Kin_AK8/deta_AK8_12_S2_0p0", h_SMd);
TH1F * h_S2d;
signal_region->GetObject("Kin_AK8/deta_AK8_12_S2_5p0", h_S2d);
TH1F * h_M1d;
signal_region->GetObject("Kin_AK8/deta_AK8_12_M1_0p70", h_M1d);
TH1F * h_T1d;
signal_region->GetObject("Kin_AK8/deta_AK8_12_T1_0p5", h_T1d);

deta -> SetLogy();
h_SMd -> Rebin(2);
h_SMd -> GetXaxis()->SetRangeUser(0,1.5);
h_SMd -> GetYaxis()->SetTitle("Events");
h_SMd ->GetXaxis()->SetTitle("#Delta #eta");
h_SMd -> SetTitle("#Delta #eta leading AK8 jets");
h_SMd -> SetLineColor(kBlack);
h_SMd -> Draw("H");
h_S2d -> GetXaxis()->SetRangeUser(0,1.5);
h_S2d -> Rebin(2);
h_S2d -> SetTitle("S2_{5p0}");
h_S2d -> SetLineColor(kBlue);
//h_S2d -> SetLineStyle(kDashed);
h_S2d -> Draw("1SAME");
h_M1d -> GetXaxis()->SetRangeUser(0,1.5);
h_M1d -> Rebin(2);
h_M1d -> SetTitle("M1_{0p70}");
h_M1d -> SetLineColor(kRed);
//h_M1M -> SetLineStyle(kDotted);
h_M1d -> Draw("1SAME");
h_T1d -> GetXaxis()->SetRangeUser(0,1.5);
h_T1d -> Rebin(2);
h_T1d -> SetLineColor(kGreen);
h_T1d -> SetTitle("T1_{0p5}");
h_T1d -> Draw("1SAME");
gPad -> BuildLegend();
//deta -> SaveAs(".pdf");

//__________________________________________________________Softdrop-Hists
TCanvas * SD = new TCanvas("SDMass","SDMass", 400, 400);

TH1F * h_SD;
signal_region->GetObject("Kin_AK8/M_softdrop_12_S2_0p0", h_SD);
TH1F * h_S2D;
signal_region->GetObject("Kin_AK8/M_softdrop_12_S2_5p0", h_S2D);
TH1F * h_M1D;
signal_region->GetObject("Kin_AK8/M_softdrop_12_M1_0p70", h_M1D);
TH1F * h_T1D;
signal_region->GetObject("Kin_AK8/M_softdrop_12_T1_0p5", h_T1D);
//book<TH1F>(AK8_M_softdrop_12_hist_name,"M_{softdrop, leading AK8 jets} [GeV/c^{2}]",100,0,300);
SD -> SetLogy();
//h_SD -> Rebin(4);
h_SD -> GetXaxis()->SetRangeUser(55,110);
h_SD -> GetYaxis()->SetTitle("Events");
h_SD ->GetXaxis()->SetTitle("[GeV/c^{2}]");
h_SD -> SetTitle("M_{softdrop}leading AK8 jets");
h_SD -> SetLineColor(kBlack);
h_SD -> Draw("H");
h_S2D -> GetXaxis()->SetRangeUser(55,110);
//h_S2D -> Rebin(4);
h_S2D -> SetTitle("S2_{5p0}");
h_S2D -> SetLineColor(kBlue);
//h_S2D -> SetLineStyle(kDashed);
h_S2D -> Draw("1SAME");
h_M1D -> GetXaxis()->SetRangeUser(55,110);
//h_M1D -> Rebin(4);
h_M1D -> SetTitle("M1_{0p70}");
h_M1D -> SetLineColor(kRed);
//h_M1M -> SetLineStyle(kDotted);
h_M1D -> Draw("1SAME");
h_T1D -> GetXaxis()->SetRangeUser(55,110);
//h_T1D -> Rebin(4);
h_T1D -> SetLineColor(kGreen);
h_T1D -> SetTitle("T1_{0p5}");
h_T1D -> Draw("1SAME");
gPad -> BuildLegend();
//SD -> SaveAs(".pdf");

//__________________________________________________________Subjettness-Hists
TCanvas * SJ = new TCanvas("tau","tau", 400, 400);
//"tau21_12",, 50, 0, 1.0);

TH1F * h_SJ;
signal_region->GetObject("Kin_AK8/tau21_12_S2_0p0", h_SJ);
TH1F * h_S2J;
signal_region->GetObject("Kin_AK8/tau21_12_S2_5p0", h_S2J);
TH1F * h_M1J;
signal_region->GetObject("Kin_AK8/tau21_12_M1_0p70", h_M1J);
TH1F * h_T1J;
signal_region->GetObject("Kin_AK8/tau21_12_T1_0p5", h_T1J);
//  book<TH1F>(AK8_tau_21_12_hist_name,"#tau_{2}/#tau_{1} (leading AK8 jets)",50,0,1.0);
SJ -> SetLogy();
h_SJ -> Rebin(5);
h_SJ -> GetXaxis()->SetRangeUser(0,1);
h_SJ -> GetYaxis()->SetTitle("Events");
h_SJ ->GetXaxis()->SetTitle("#tau_{2}/#tau_{1}");
h_SJ -> SetTitle("#tau_{2}/#tau_{1} leading AK8 jets");
h_SJ -> SetLineColor(kBlack);
h_SJ -> Draw("H");
h_S2J -> GetXaxis()->SetRangeUser(0,1);
h_S2J -> Rebin(5);
h_S2J -> SetTitle("S2_{5p0}");
h_S2J -> SetLineColor(kBlue);
//h_S2J -> SetLineStyle(kDashed);
h_S2J -> Draw("1SAME");
h_M1J -> GetXaxis()->SetRangeUser(0,1);
h_M1J -> Rebin(5);
h_M1J -> SetTitle("M1_{0p70}");
h_M1J -> SetLineColor(kRed);
//h_M1M -> SetLineStyle(kDotted);
h_M1J -> Draw("1SAME");
h_T1J -> GetXaxis()->SetRangeUser(0,1);
h_T1J -> Rebin(5);
h_T1J -> SetLineColor(kGreen);
h_T1J -> SetTitle("T1_{0p5}");
h_T1J -> Draw("1SAME");
gPad -> BuildLegend();
SJ -> SaveAs("tau_5.pdf");

//__________________________________________________________N_AK8?? :D makes no sense
TCanvas * N = new TCanvas("N","N", 400, 400);
//("N_AK8", "N_{AK8 jets}", 20, 0, 20);
TH1F * h_NSM;
signal_region->GetObject("Kin_AK8/N_AK8_S2_0p0", h_NSM);
TH1F * h_NS2;
signal_region->GetObject("Kin_AK8/N_AK8_S2_5p0", h_NS2);
TH1F * h_NM1;
signal_region->GetObject("Kin_AK8/N_AK8_M1_0p70", h_NM1);
TH1F * h_NT1;
signal_region->GetObject("Kin_AK8/N_AK8_T1_0p5", h_NT1);
//Binning >= 5 leads to same distribution for AK4 and AK8
N -> SetLogy();
//h_NSM -> Rebin(2);
//h_NSM -> GetXaxis()->SetRangeUser(2,7);
h_NSM -> GetYaxis()->SetTitle("Events");
h_NSM ->GetXaxis()->SetTitle("N_{AK8 jets}");
h_NSM -> SetTitle("N_{AK8 jets}");
h_NSM -> SetLineColor(kBlack);
h_NSM -> Draw("H");
//h_NS2 -> Rebin(2);
//h_NS2-> GetXaxis()->SetRangeUser(2,7);
h_NS2 -> SetTitle("S2_{5p0}");
h_NS2 -> SetLineColor(kBlue);
//h_NS2 -> SetLineStyle(kDashed);
h_NS2 -> Draw("1SAME");
//h_NM1 -> Rebin(2);
//h_NM1-> GetXaxis()->SetRangeUser(2,7);
h_NM1 -> SetTitle("M1_{0p70}");
h_NM1 -> SetLineColor(kRed);
//h_M1M -> SetLineStyle(kDotted);
h_NM1 -> Draw("1SAME");
//h_NT1 -> Rebin(2);
//h_NT1 -> GetXaxis()->SetRangeUser(2,7);
h_NT1 -> SetLineColor(kGreen);
h_NT1 -> SetTitle("T1_{0p5}");
h_NT1 -> Draw("1SAME");
gPad -> BuildLegend();
//N -> SaveAs(".pdf");

}

