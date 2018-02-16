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
    if(invMass<invMass_min) return false;
    else return true;
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
