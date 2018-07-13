#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicSelections.h"
#include "UHH2/core/include/Event.h"

#include <stdexcept>

using namespace uhh2examples;
using namespace uhh2;


DijetSelection::DijetSelection(float dphi_min_, float third_frac_max_): dphi_min(dphi_min_), third_frac_max(third_frac_max_){}
    
bool DijetSelection::passes(const Event & event){
  assert(event.jets); // if this fails, it probably means jets are not read in
  if(event.jets->size() < 2) return false;
  const auto & jet0 = event.jets->at(0);
  const auto & jet1 = event.jets->at(1);
  auto dphi = deltaPhi(jet0, jet1);
  if(dphi < dphi_min) return false;
  if(event.jets->size() == 2) return true;
  const auto & jet2 = event.jets->at(2);
  auto third_jet_frac = jet2.pt() / (0.5 * (jet0.pt() + jet1.pt()));
  return third_jet_frac < third_frac_max;
}

deltaEtaAk8Selection::deltaEtaAk8Selection(float deta_max_): deta_max(deta_max_){}

bool deltaEtaAk8Selection::passes(const Event & event){
  assert(event.topjets);
  if(event.topjets->size()<2) return false;
  auto deta = fabs(event.topjets->at(0).eta()-event.topjets->at(1).eta());
  if(deta > deta_max) return false;
  else return true;    
}

invMassAK8JetSelection::invMassAK8JetSelection(float invMass_min_): invMass_min(invMass_min_){}

bool invMassAK8JetSelection::passes(const Event & event){
  assert(event.topjets);
  if(event.topjets->size()<2) return false;
  auto invMass = (event.topjets->at(0).v4()+event.topjets->at(1).v4()).M();
  if(invMass<invMass_min){
    return false;
  }else{
    return true;
  }
}

VVSoftDropMassSelection::VVSoftDropMassSelection(float MSD_min_,float MSD_max_): MSD_min(MSD_min_),MSD_max(MSD_max_){}

bool VVSoftDropMassSelection::passes(const Event & event){
  assert(event.topjets);
  if(event.topjets->size()<2) return false;

  const auto & AK8_1=event.topjets->at(0); 
  const auto & AK8_2=event.topjets->at(1); 
  //   LorentzVector subjetsum_1,subjetsum_2;
  //   for (const auto subjet1:AK8_1.subjets()){
  // subjetsum_1+=subjet1.v4();
  //   }
  //   for (const auto subjet2:AK8_2.subjets()){
  // subjetsum_2+=subjet2.v4();
  //   }
  //   auto MSD1=subjetsum_1.M();
  //   auto MSD2=subjetsum_2.M();
  auto MSD1=AK8_1.softdropmass();
  auto MSD2=AK8_2.softdropmass();

  //dont know if correct
  // auto MSD1=event.topjets->at(1).softdropmass();
  // auto MSD2=event.topjets->at(2).softdropmass();

  //demand 65GeV<M_SD<105GeV
  if( (MSD1<MSD_min) || (MSD1>MSD_max) || (MSD2<MSD_min) || (MSD2>MSD_max) ){
    return false;
  }else{
    return true;
  }
}

SidebandVVSoftDropMassSelection::SidebandVVSoftDropMassSelection(float Signal_min_,float Signal_max_,float Sideband_min_): Signal_min(Signal_min_),Signal_max(Signal_max_),Sideband_min(Sideband_min_){}

bool SidebandVVSoftDropMassSelection::passes(const Event & event){
  assert(event.topjets);
  if(event.topjets->size()<2) return false;

  const auto & AK8_1=event.topjets->at(0); 
  const auto & AK8_2=event.topjets->at(1); 
  //   LorentzVector subjetsum_1,subjetsum_2;
  //   for (const auto subjet1:AK8_1.subjets()){
  // subjetsum_1+=subjet1.v4();
  //   }
  //   for (const auto subjet2:AK8_2.subjets()){
  // subjetsum_2+=subjet2.v4();
  //   }
  //   auto MSD1=subjetsum_1.M();
  //   auto MSD2=subjetsum_2.M();
  auto MSD1=AK8_1.softdropmass();
  auto MSD2=AK8_2.softdropmass();
    

  //dont know if correct
  // auto MSD1=event.topjets->at(1).softdropmass();
  // auto MSD2=event.topjets->at(2).softdropmass();

  //demand 65GeV<M_SD<105GeV
  if( (MSD1<Sideband_min) || (MSD2<Signal_min) || (MSD2>Signal_max) ){
    return false;
  }else{
    return true;
  }
}

NSubjettinessTau21Selection::NSubjettinessTau21Selection(float tau21_min_,float tau21_max_): tau21_min(tau21_min_),tau21_max(tau21_max_){}

bool NSubjettinessTau21Selection::passes(const Event & event){
  assert(event.topjets);
  if(event.topjets->size()<2)return false;
    
  auto tau1_1 = event.topjets->at(0).tau1();
  if(tau1_1 == 0.0) return false;
  auto tau2_1= event.topjets->at(0).tau2();
  if(!std::isfinite(tau2_1)) return false;

  auto tau1_2 = event.topjets->at(1).tau1();
  if(!std::isfinite(tau1_2) || tau1_2 == 0.0) return false;
  auto tau2_2= event.topjets->at(1).tau2();
  if(!std::isfinite(tau2_2)) return false;
    
  auto tau21_1=tau2_1/tau1_1;
  auto tau21_2=tau2_2/tau1_2;
    
  if( (tau21_1 <= tau21_min) || (tau21_1 > tau21_max) || (tau21_2 <= tau21_min) || (tau21_2 > tau21_max) ){    
    return false;
  }else{
    return true;
  }
}   


OppositeEtaAK4Selection::OppositeEtaAK4Selection( ){}

bool OppositeEtaAK4Selection::passes(const Event & event){
  assert(event.jets);
  if(event.jets->size()<2) return false;
  auto etaproduct = event.jets->at(0).eta() * event.jets->at(1).eta();
  if(etaproduct >0) return false;
  else return true;
}

deltaEtaAk4Selection::deltaEtaAk4Selection(float deta_min_):deta_min(deta_min_){}

bool deltaEtaAk4Selection::passes(const Event & event){
  assert(event.jets);
  if(event.jets->size()<2) return false;
  auto deta = fabs(event.jets->at(0).eta()-event.jets->at(1).eta());
  if(deta < deta_min) return false;
  else return true;
}

invMassAK4JetSelection::invMassAK4JetSelection(float invMass_min_): invMass_min(invMass_min_){}

bool invMassAK4JetSelection::passes(const Event & event){
  assert(event.jets);
  if(event.jets->size()<2) return false;
  auto invMass = (event.jets->at(0).v4()+event.jets->at(1).v4()).M();
  if(invMass<invMass_min) return false;
  else return true;
}

JetIdSelection::JetIdSelection(const JetId & jetid_): jetid(jetid_){}

bool JetIdSelection::passes(const Event & event){
  assert(event.jets);
  if(event.jets->size()<2) return false;
  return jetid(event.jets->at(0),event) && jetid(event.jets->at(1),event);
}

TopJetIdSelection::TopJetIdSelection(const TopJetId & topjetid_): topjetid(topjetid_){}

bool TopJetIdSelection::passes(const Event & event){
  assert(event.topjets);
  if(event.topjets->size()<2) return false;
  return topjetid(event.topjets->at(0),event) && topjetid(event.topjets->at(1),event);
}


MuonVeto::MuonVeto(float deltaR_min_, const boost::optional<MuonId> & muid_): deltaR_min(deltaR_min_), muid(muid_){}
    
bool MuonVeto::passes(const Event & event){
  assert(event.topjets); // if this fails, it probably means jets are not read in
  assert(event.muons); // if this fails, it probably means jets are not read in
  if(muid)
    {
      for(const auto & topjets : *event.topjets)
	{
	  for(const auto & muons : *event.muons)    
	    {
	      if(deltaR(topjets,muons)  < deltaR_min) return false;
	      else return true;
	    }
	}
    }
  return true;
    
}

ElectronVeto::ElectronVeto(float deltaR_min_, const boost::optional<ElectronId> & eleid_): deltaR_min(deltaR_min_), eleid(eleid_){}
    
bool ElectronVeto::passes(const Event & event){
  assert(event.topjets); // if this fails, it probably means jets are not read in
  assert(event.electrons); // if this fails, it probably means jets are not read in
  if(eleid)
    {
      for(const auto & topjets : *event.topjets)
	{
	  for(const auto & electrons : *event.electrons)    
	    {
	      if(deltaR(topjets,electrons)  < deltaR_min) return false;
	      else return true;
	    }
	}
    }
  return true;
    
}
