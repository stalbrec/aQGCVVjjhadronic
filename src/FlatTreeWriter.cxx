#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/Utils.h"
#include "UHH2/core/include/Jet.h"
#include "UHH2/core/include/TopJet.h"
#include "UHH2/core/include/TopJet.h"
#include "UHH2/core/include/PFParticle.h"
#include "UHH2/aQGCVVjjhadronic/include/FlatTreeWriter.h"


using namespace uhh2;

FlatTreeWriter::FlatTreeWriter(uhh2::Context & ctx){
  // First up undeclare all event output that is usually populating AnalysisTree:
  ctx.undeclare_all_event_output();

  verbose =  string2bool(ctx.get("verbose", "true"));

  h_weight = ctx.declare_event_output<double>("weight");
  h_index = ctx.declare_event_output<double>("index");

    
  h_genAK8_pt = ctx.declare_event_output<std::vector<double>>("v_genAK8_pt");
  h_genAK8_eta = ctx.declare_event_output<std::vector<double>>("v_genAK8_eta");
  h_genAK8_phi = ctx.declare_event_output<std::vector<double>>("v_genAK8_phi");
  h_genAK8_m = ctx.declare_event_output<std::vector<double>>("v_genAK8_m");
  h_genAK4_pt = ctx.declare_event_output<std::vector<double>>("v_genAK4_pt");
  h_genAK4_eta = ctx.declare_event_output<std::vector<double>>("v_genAK4_eta");
  h_genAK4_phi = ctx.declare_event_output<std::vector<double>>("v_genAK4_phi");
  h_genAK4_m = ctx.declare_event_output<std::vector<double>>("v_genAK4_m");

  h_genPart_pt = ctx.declare_event_output<std::vector<double>>("v_genPart_pt");
  h_genPart_eta = ctx.declare_event_output<std::vector<double>>("v_genPart_eta");
  h_genPart_phi = ctx.declare_event_output<std::vector<double>>("v_genPart_phi");
  h_genPart_m = ctx.declare_event_output<std::vector<double>>("v_genPart_m");
  h_genPart_pdgId = ctx.declare_event_output<std::vector<double>>("v_genPart_pdgId");

  h_V_candidate_indices = ctx.declare_event_output<std::vector<int>>("v_V_candidate_indices");
  
  h_AK8_pt = ctx.declare_event_output<std::vector<double>>("v_AK8_pt");
  h_AK8_eta = ctx.declare_event_output<std::vector<double>>("v_AK8_eta");
  h_AK8_phi = ctx.declare_event_output<std::vector<double>>("v_AK8_phi");
  h_AK8_m = ctx.declare_event_output<std::vector<double>>("v_AK8_m");
  h_AK4_pt = ctx.declare_event_output<std::vector<double>>("v_AK4_pt");
  h_AK4_eta = ctx.declare_event_output<std::vector<double>>("v_AK4_eta");
  h_AK4_phi = ctx.declare_event_output<std::vector<double>>("v_AK4_phi");
  h_AK4_m = ctx.declare_event_output<std::vector<double>>("v_AK4_m");

}

bool FlatTreeWriter::process(uhh2::Event & event){

  event.set(h_weight,event.weight);
  event.set(h_index,event.event);
  
  
  std::vector<double> genAK8_pt,genAK8_eta,genAK8_phi,genAK8_m;
  std::vector<double> genAK4_pt,genAK4_eta,genAK4_phi,genAK4_m;

  if(verbose)std::cout << "processing GenAK8 jets" << std::endl;  
  for(auto genAK8: *event.gentopjets){
    genAK8_pt.push_back(genAK8.pt());
    genAK8_eta.push_back(genAK8.eta());
    genAK8_phi.push_back(genAK8.phi());
    genAK8_m.push_back(genAK8.v4().M());
  }

  if(verbose)std::cout << "processing GenAK4 jets" << std::endl;
  for(auto genAK4: *event.genjets){
    genAK4_pt.push_back(genAK4.pt());
    genAK4_eta.push_back(genAK4.eta());
    genAK4_phi.push_back(genAK4.phi());
    genAK4_m.push_back(genAK4.v4().M());
  }
  event.set(h_genAK8_pt, genAK8_pt);
  event.set(h_genAK8_eta, genAK8_eta);
  event.set(h_genAK8_phi, genAK8_phi);
  event.set(h_genAK8_m, genAK8_m);
  event.set(h_genAK4_pt, genAK4_pt);
  event.set(h_genAK4_eta, genAK4_eta);
  event.set(h_genAK4_phi, genAK4_phi);
  event.set(h_genAK4_m, genAK4_m);

  std::vector<double> genPart_pt,genPart_eta,genPart_phi,genPart_m,genPart_pdgId;
  std::vector<int> V_cand_indices;
  if(verbose)std::cout << "processing GenParticles" << std::endl;
  for(auto genPart: *event.genparticles){
    genPart_pt.push_back(genPart.pt());
    genPart_eta.push_back(genPart.eta());
    genPart_phi.push_back(genPart.phi());
    genPart_m.push_back(genPart.v4().M());
    genPart_pdgId.push_back(genPart.pdgId());
    if( (abs(genPart.pdgId())==23 || abs(genPart.pdgId()) == 24)){
      V_cand_indices.push_back(genPart.index());
    }
  }

  event.set(h_genPart_pt, genPart_pt);
  event.set(h_genPart_eta, genPart_eta);
  event.set(h_genPart_phi, genPart_phi);
  event.set(h_genPart_m, genPart_m);
  event.set(h_genPart_pdgId, genPart_pdgId);
  event.set(h_V_candidate_indices,V_cand_indices);
  
  std::vector<double> AK8_pt,AK8_eta,AK8_phi,AK8_m;
  std::vector<double> AK4_pt,AK4_eta,AK4_phi,AK4_m;
  if(verbose)std::cout << "processing AK8 jets" << std::endl;
  for(auto AK8: *event.topjets){
    AK8_pt.push_back(AK8.pt());
    AK8_eta.push_back(AK8.eta());
    AK8_phi.push_back(AK8.phi());
    AK8_m.push_back(AK8.v4().M());
  }
  if(verbose)std::cout << "processing AK4 jets" << std::endl;
  for(auto AK4: *event.jets){
    AK4_pt.push_back(AK4.pt());
    AK4_eta.push_back(AK4.eta());
    AK4_phi.push_back(AK4.phi());
    AK4_m.push_back(AK4.v4().M());
  }
  event.set(h_AK8_pt, AK8_pt);
  event.set(h_AK8_eta, AK8_eta);
  event.set(h_AK8_phi, AK8_phi);
  event.set(h_AK8_m, AK8_m);
  event.set(h_AK4_pt, AK4_pt);
  event.set(h_AK4_eta, AK4_eta);
  event.set(h_AK4_phi, AK4_phi);
  event.set(h_AK4_m, AK4_m);

  return true;
}
