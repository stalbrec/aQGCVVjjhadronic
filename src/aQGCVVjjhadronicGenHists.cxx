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

  const int NBINS=104;
  Double_t BOUNDARIES[NBINS] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325, 354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607, 1687, 1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072, 10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

  book<TH1F>("M_VV_12","M_{VV-gens} [GeV/c]",100,0,10000);
  book<TH1F>("M_VV_12_highbin","M_{VV-gens} [GeV/c]",14000,0,14000);
  book<TH1F>("M_VV_12_nonequi","M_{VV-gens} [GeV/c]",NBINS-1,BOUNDARIES);

  book<TH1F>("45_mother0_index","pdgID_{V-mothers}",15,0,15);
  book<TH1F>("45_mother1_index","pdgID_{V-mothers}",15,0,15);
  
    
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
		hist("M_VV_12_highbin")->Fill(VV.M(),weight);    
		hist("M_VV_12_nonequi")->Fill(VV.M(),weight);    
    
	}

	hist("45_mother0_index")->Fill(event.genparticles->at(4).mother1());
	hist("45_mother0_index")->Fill(event.genparticles->at(5).mother1());
	hist("45_mother1_index")->Fill(event.genparticles->at(4).mother2());
	hist("45_mother1_index")->Fill(event.genparticles->at(5).mother2());
}

aQGCVVjjhadronicGenHists::~aQGCVVjjhadronicGenHists(){}
