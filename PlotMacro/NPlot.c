//Plot whatever you want

#include "TH1F.h"
#include <iostream>
#include <math.h>

void NPlot(){
gStyle -> SetOptStat(0);
//gROOT->SetBatch();
  TFile * File = new TFile("/nfs/dust/cms/user/loemkerj/bachelor/CMSSW_10_2_13/src/DijetCombineLimitCode/plots/ZZ_T7_1p20/fit_shapes_ZZ_T7_1p200__invMass_combined.root");
  
  bg = File.Get('ch1_prefit/TotalBkg');
  sig = File.Get('ch1_prefit/TotalSig');
  sigbg = File.Get('ch1_prefit/ZZ_T7_1p20_jj');
  dataHist = File.Get('ch1_prefit/data_obs');
  
  TCanvas * ch1_pre = new TCanvas("ch1_pre","chi1_pre",500,500)
  ch1_pre -> SetLogy();
  
  TH1F * Sig = (TH1F*) sig;
  TH1F * Bg = (TH1F*) bg;
  TH1F * SigBg = (TH1F*) sigbg
  TH1F * Data = (TH1F*) dataHist;

  Sig -> Draw();
  Bg -> Draw("HSame");
  SigBg -> Draw("HSame");
  dataHist -> Dra("HSame");

  //TCanvas * ch1_post = new TCanvas("ch1_post", "ch1_post", 500, 500)
}