//pseudorapidity - plots deta, prodeta and eta in one-separate them
#include "TH1F.h"
#include <iostream>
#include <math.h>
#include <string>

void etaPlot(){
gStyle -> SetOptStat(0);
//gROOT->SetBatch();
  TFile * signal_region = new TFile("/nfs/dust/cms/user/loemkerj/bachelor/CMSSW_10_2_16/src/UHH2/aQGCVVjjhadronic/test/uhh2.AnalysisModuleRunner.MC.MC_aQGC_ZZjj_hadronic_2016v3_test.root","READ");
  TString hist_dir("Kin_AK8");
  TDirectory * full_selection = signal_region->GetDirectory(hist_dir);
  TIter next(full_selection->GetListOfKeys());
  TKey* key;
  TObject* obj;
  TString current_operator = "S0";
   TCanvas * canvas = new TCanvas(TString::Format("canvas_%s", current_operator.Data() ) ,"", 400, 400);
 canvas -> SetLogy();
   while (( key = (TKey*)next() )) {
    obj = key->ReadObj() ;
    //______skip all histograms, but pT_12(leading) with applied SMEFT:|| TString(obj->GetName()).Contains("AK8"
    if(!TString(obj->GetName()).Contains("prodeta_AK4_12_")||TString(obj->GetName()).Contains("AK8")) continue;
    //______check if the operator in Name string is equal to the current operator
    if (!TString(obj->GetName()).Contains(current_operator)){
//  gPad -> BuildLegend();
   canvas -> SaveAs(".pdf");
    current_operator=TString(obj->GetName())(15,2);//______________________________________________chnage number
    canvas = new TCanvas(TString::Format("canvas_%s", current_operator.Data()),"",400,400);
canvas -> SetLogy();
    }
    TH1F * hist = (TH1F*) obj;
    hist -> SetTitle(hist -> GetName());
    //hist -> Rebin(2);    //group together the 2 bins -> book<TH1F>(AK8_eta_hist_name, "#eta^{AK8 jets}", 40, -6.5, 6.5); 
    hist -> SetMarkerStyle(kFullTriangleUp);
    hist -> Draw("SAME PLC PMC");
    hist -> GetYaxis()->SetTitle("Events");
    hist ->GetXaxis()->SetTitle("#Delta #eta^{leading AK4 jets}");
    }
    //_______for the last case:
 //gPad -> BuildLegend();
   canvas -> SaveAs(".pdf");

}

