#pragma once
#include "UHH2/core/include/fwd.h"
#include "UHH2/core/include/AnalysisModule.h"
#include <vector>
#include <TString.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <algorithm>


using namespace std;
using namespace uhh2;


class FlatTreeWriter: public uhh2::AnalysisModule {
public:
    FlatTreeWriter(uhh2::Context & ctx);
    virtual bool process(uhh2::Event & ) override;

private:

    
    uhh2::Event::Handle<double>h_weight;
    uhh2::Event::Handle<double>h_index;
    
    
    uhh2::Event::Handle<std::vector<double>> h_genAK8_pt, h_genAK8_eta, h_genAK8_phi, h_genAK8_m;
    uhh2::Event::Handle<std::vector<double>> h_genAK4_pt, h_genAK4_eta, h_genAK4_phi, h_genAK4_m;  
    uhh2::Event::Handle<std::vector<double>> h_AK8_pt, h_AK8_eta, h_AK8_phi, h_AK8_m;
    uhh2::Event::Handle<std::vector<double>> h_AK4_pt, h_AK4_eta, h_AK4_phi, h_AK4_m;
    uhh2::Event::Handle<std::vector<double>> h_genPart_pt, h_genPart_eta, h_genPart_phi, h_genPart_m, h_genPart_pdgId;
    uhh2::Event::Handle<std::vector<int>> h_V_candidate_indices;
    
    
    
    bool isMC, verbose;
};
