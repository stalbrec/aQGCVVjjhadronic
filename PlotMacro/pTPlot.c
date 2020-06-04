//transverse momentum
#include "TH1F.h"
#include <iostream>
#include <math.h>

void pTPlot(){
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
  //canvas -> SetLogy();
  while (( key = (TKey*)next() )) {
    obj = key->ReadObj();
    //______skip all histograms, but pT_12(leading) with applied SMEFT:
    if(!TString(obj->GetName()).Contains("pT_AK4_12_")) continue;
    //______check if the operator in Name string is equal to the current operator
    if (!TString(obj->GetName()).Contains(current_operator)){
    gPad -> BuildLegend();

    canvas -> SaveAs(".pdf");
    //______make new canvas and replace current_operator if they are not the same
    current_operator=TString(obj->GetName())(10,2);//_______________________________________________count the number again!
    canvas = new TCanvas(TString::Format("canvas_%s", current_operator.Data()),"",400,400);
   // canvas -> SetLogy();
    }
    TH1F * hist = (TH1F*) obj;//(TH1F*) converts obj to a TH1F!, hist points to histogram
    hist -> SetTitle(hist -> GetName());
    //hist ->GetXaxis()->SetRange(0,4000);// book<TH1F>(AK8_hist_name, "M_{jj-AK8} [GeV/c^{2}]",10000,0,10000);
    hist -> SetAxisRange(0., 2500.,"X");
    //hist -> Rebin(4);     //group together the 8 bins -> book<TH1F>(AK8_pT_hist_name, "p_{T}^{AK8 jets} [GeV/c]", 80 ,0 ,8000);
    hist -> SetMarkerStyle(kFullTriangleUp);
    hist -> Draw("SAME PLC PMC");//to draw  in different colors 
    hist -> GetYaxis()->SetTitle("Events");
    hist ->GetXaxis()->SetTitle("p_{T}^{leading AK4 jets} [GeV/c]");
    }
    //_______for the last case:
    gPad -> BuildLegend();
   canvas -> SaveAs(".pdf");//this works :D
}

