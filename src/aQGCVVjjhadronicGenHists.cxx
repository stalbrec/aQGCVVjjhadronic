#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicGenHists.h"
#include "UHH2/core/include/Event.h"

#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/GenParticle.h"

#include "TH1F.h"
#include <iostream>
#include <math.h>
using namespace std;
using namespace uhh2;
using namespace uhh2examples;


aQGCVVjjhadronicGenHists::aQGCVVjjhadronicGenHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
    // book all histograms here

    
    book<TH1F>("pdgID_V_mother","pdgID_{V-mothers}",51,-25,25);

    book<TH1F>("N_V", "N_{V gens}", 20, 0, 20);
    book<TH1F>("pT_V", "p_{T}^{V gens} [GeV/c]", 80 ,0 ,8000);
    book<TH1F>("eta_V", "#eta^{V gens}", 40, -6.5, 6.5);

    book<TH1F>("pT_V_1", "p_{T}^{1st V gen} [GeV/c]", 80 ,0 ,8000);
    book<TH1F>("eta_V_1", "#eta^{1st V gen}", 40, -6.5, 6.5);
    book<TH1F>("pT_V_2", "p_{T}^{2nd V gen} [GeV/c]", 80 ,0 ,8000);
    book<TH1F>("eta_V_2", "#eta^{2nd V gen}", 40, -6.5, 6.5);
    book<TH1F>("pT_V_12", "p_{T}^{leading V gens} [GeV/c]", 80 ,0 ,8000);
    book<TH1F>("eta_V_12", "#eta^{leading V gens}", 40, -6.5, 6.5);

    book<TH1F>("M_VV_12","M_{VV-gens} [GeV/c]",100,0,10000);
    
}


void aQGCVVjjhadronicGenHists::fill(const Event & event){
    // fill the histograms. Please note the comments in the header file:
    // 'hist' is used here a lot for simplicity, but it will be rather
    // slow when you have many histograms; therefore, better
    // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
    // Don't forget to always use the weight when filling.
    double weight = event.weight;
    
    assert(event.genparticles);

    std::vector<GenParticle>* VBosons(new std::vector<GenParticle>(*event.genparticles));;
    VBosons->clear();
    VBosons->reserve(event.genparticles->size());
    //std::vector<Particle>*VBosons;

    for ( const GenParticle & thisgen : *event.genparticles){	
	if(abs(thisgen.pdgId())==24 || thisgen.pdgId()==23){
	    hist("pdgID_V_mother")->Fill(event.genparticles->at(thisgen.mother1()).pdgId(),weight);
	    hist("pdgID_V_mother")->Fill(event.genparticles->at(thisgen.mother2()).pdgId(),weight);
	    VBosons->push_back(thisgen);
	    hist("pT_V")->Fill(thisgen.pt(),weight);  
	    hist("eta_V")->Fill(thisgen.eta(),weight); 
	}
    }
    
    hist("N_V")->Fill(VBosons->size(),weight);   
    
    sort_by_pt<GenParticle>(*VBosons);
    if(VBosons->size()>0){
	hist("pT_V_1")->Fill(VBosons->at(0).pt(),weight); 
	hist("eta_V_1")->Fill(VBosons->at(0).eta(),weight); 
    }
    if(VBosons->size()>=2){
	hist("pT_V_2")->Fill(VBosons->at(1).pt(),weight); 
	hist("eta_V_2")->Fill(VBosons->at(1).eta(),weight); 

	auto VV = VBosons->at(0).v4()+VBosons->at(1).v4();
	
	hist("pT_V_12")->Fill(VV.pt(),weight); 
	hist("eta_V_12")->Fill(VV.eta(),weight);
	
	hist("M_VV_12")->Fill(VV.M(),weight);    
    }
    
}

aQGCVVjjhadronicGenHists::~aQGCVVjjhadronicGenHists(){}
