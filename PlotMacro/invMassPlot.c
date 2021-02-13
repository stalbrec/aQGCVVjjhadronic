#include "TH1F.h"
#include <iostream>
#include <math.h>
#include <string>

void invMassPlot(){
gStyle -> SetOptStat(0);
//gROOT->SetBatch();
  TFile * signal_region = new TFile("/nfs/dust/cms/user/loemkerj/bachelor/CMSSW_10_2_16/src/UHH2/aQGCVVjjhadronic/SignalRegion/uhh2.AnalysisModuleRunner.MC.MC_aQGC_ZZjj_hadronic_2016v3.root","READ");
  TString hist_dir("MjjHists_invMAk4sel_1p0");
  TDirectory * full_selection = signal_region->GetDirectory(hist_dir);
  TIter next(full_selection->GetListOfKeys());
  TKey* key;
  TObject* obj;
  TString current_operator = "S0";
  TCanvas * canvas = new TCanvas(TString::Format("canvas_%s", current_operator.Data() ) ,"", 400, 400);
  //canvas -> SetLogy();
  while (( key = (TKey*)next() )) {
    obj = key->ReadObj() ;
    //______skip these nominal histograms wihtout any SMEFT weight applied and also AK4 hists:
    if(TString(obj->GetName()) == "M_jj_AK4" || TString(obj->GetName()).Contains("AK8")) continue;
    //______check if the operator in Name string is equal to the current operator
    if (!TString(obj->GetName()).Contains(current_operator)){
    gPad -> BuildLegend();
    //canvas -> SaveAs(".pdf");
    //______make new canvas and replace current_operator if they are not the same
    current_operator=TString(obj->GetName())(9,2);
    canvas = new TCanvas(TString::Format("canvas_%s", current_operator.Data()),"",400,400);
    //canvas -> SetLogy();
    }
    TH1F * hist = (TH1F*) obj;//(TH1F*) converts obj to a TH1F!, hist points to histogram
    hist -> SetTitle(hist -> GetName());
   // hist ->GetXaxis()->SetRange(500,4000);// book<TH1F>(AK8_hist_name, "M_{jj-AK8} [GeV/c^{2}]",10000,0,10000);
    hist->GetXaxis()->SetRangeUser(0,8000);
    hist -> Rebin(500);     //group together the 50 bins -> manuel regrouping!
    hist -> SetMarkerStyle(kFullTriangleUp);
    hist -> Draw("SAME PLC PMC");//to draw  in different colors 
    hist -> GetYaxis()->SetTitle("Events");
    hist ->GetXaxis()->SetTitle("Mjj_[GeV/c^{2}]");
    }
    //_______for the last case:
    gPad -> BuildLegend();

    canvas -> SaveAs(".pdf");
}