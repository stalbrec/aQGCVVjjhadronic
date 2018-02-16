#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

aQGCVVjjhadronicHists::aQGCVVjjhadronicHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
    // book all histograms here

    // primary vertices
    book<TH1F>("N_pv", "N^{PV}", 50, 0, 50);


    book<TH1F>("pdgID", "pdgID", 50, -25,25);


    // jets
    book<TH1F>("N_AK4", "N_{AK4 jets}", 20, 0, 20);  
    book<TH1F>("N_AK8", "N_{AK8 jets}", 20, 0, 20);
    book<TH1F>("pT_AK4", "p_{T}^{AK4 jets} [GeV/c]", 40 ,0 ,4000);
    book<TH1F>("pT_AK8", "p_{T}^{AK8 jets} [GeV/c]", 80 ,0 ,8000);
    book<TH1F>("eta_AK4", "#eta^{AK4 jets}", 40, -6.5, 6.5);
    book<TH1F>("eta_AK8", "#eta^{AK8 jets}", 40, -6.5, 6.5);

    //same kinematics for each (AK4, AK8) leading pair:
    book<TH1F>("pT_AK4_1", "p_{T}^{1st AK4 jet} [GeV/c]", 40 ,0 ,4000);
    book<TH1F>("eta_AK4_1", "#eta^{1st AK4 jet}", 40, -6.5, 6.5);
    book<TH1F>("pT_AK4_2", "p_{T}^{2nd AK4 jet} [GeV/c]", 40 ,0 ,4000);
    book<TH1F>("eta_AK4_2", "#eta^{2nd AK4 jet}", 40, -6.5, 6.5);
    book<TH1F>("pT_AK4_12", "p_{T}^{leading AK4 jets} [GeV/c]", 40 ,0 ,4000);
    book<TH1F>("eta_AK4_12", "#eta^{leading AK4 jets}", 40, -6.5, 6.5);

    book<TH1F>("prodeta_AK4_12", "#eta^{1st AK4 jet} #cdot #eta^{2nd AK4 jet}", 87, -43, 43);

    book<TH1F>("M_jj_AK4", "M_{jj-AK4} [GeV/c^{2}]",100,0,10000);

   
    book<TH1F>("pT_AK8_1", "p_{T}^{1st AK8 jet} [GeV/c]", 80 ,0 ,8000);
    book<TH1F>("eta_AK8_1", "#eta^{1st AK8 jet}", 40, -6.5, 6.5);
    book<TH1F>("pT_AK8_2", "p_{T}^{2nd AK8 jet} [GeV/c]", 80 ,0 ,8000);
    book<TH1F>("eta_AK8_2", "#eta^{2nd AK8 jet}", 40, -6.5, 6.5);
    book<TH1F>("pT_AK8_12", "p_{T}^{leading AK8 jets} [GeV/c]", 80 ,0 ,8000);
    book<TH1F>("eta_AK8_12", "#eta^{leading AK8 jets}", 40, -6.5, 6.5);


    book<TH1F>("M_jj_AK8", "M_{jj-AK8} [GeV/c^{2}]",100,0,10000);
    

    // book<TH1F>("eta_VBFJet", "#eta^{VBF-Jets}", 40, -6.5,6.5);
    // book<TH1F>("eta_WWJet", "#eta^{WW-Jets}", 40, -6.5,6.5);
    // book<TH1F>("eta_3WJet", "#eta^{3W-Jets}", 40, -6.5,6.5);


}


void aQGCVVjjhadronicHists::fill(const Event & event){
    // fill the histograms. Please note the comments in the header file:
    // 'hist' is used here a lot for simplicity, but it will be rather
    // slow when you have many histograms; therefore, better
    // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
    // Don't forget to always use the weight when filling.
    double weight = event.weight;
  
    //std::vector<GenParticle>* genjets = event.genjets;
    //for(const GenParticle & thisgenjet : * genjets){
    //  cout << "genjet pdgId: " << thisgenjet.pdgId() <<endl;
    //}
    assert(event.jets);
    assert(event.topjets);

    std::vector<Jet>* AK4Jets = event.jets;
    std::vector<TopJet>* AK8Jets = event.topjets;

    auto N_AK4=AK4Jets->size();
    auto N_AK8=AK8Jets->size();
    hist("N_AK4")->Fill(N_AK4,weight);
    hist("N_AK8")->Fill(N_AK8,weight);

    for(const Jet & thisjet : *AK4Jets){
	hist("pT_AK4")->Fill(thisjet.pt(),weight);
	hist("eta_AK4")->Fill(thisjet.eta(),weight);
    }

    if(N_AK4>=1){
	hist("pT_AK4_1")->Fill(AK4Jets->at(0).pt(),weight); 
	hist("eta_AK4_1")->Fill(AK4Jets->at(0).eta(),weight);
        }
    if(N_AK4>=2){
	hist("pT_AK4_2")->Fill(AK4Jets->at(1).pt(),weight); 
	hist("eta_AK4_2")->Fill(AK4Jets->at(1).eta(),weight);
    	hist("pT_AK4_12")->Fill((AK4Jets->at(0).v4()+AK4Jets->at(1).v4()).pt(),weight);
    	hist("eta_AK4_12")->Fill((AK4Jets->at(0).v4()+AK4Jets->at(1).v4()).eta(),weight);

	hist("prodeta_AK4_12")->Fill(AK4Jets->at(0).eta()*AK4Jets->at(1).eta(),weight);

	hist("M_jj_AK4")->Fill((AK4Jets->at(0).v4()+AK4Jets->at(1).v4()).M(),weight);
    }

    for(const TopJet & thisjet : *AK8Jets){
	hist("pT_AK8")->Fill(thisjet.pt(),weight);
	hist("eta_AK8")->Fill(thisjet.eta(),weight);
    }

    if(N_AK8>=1){
	hist("pT_AK8_1")->Fill(AK8Jets->at(0).pt(),weight); 
	hist("eta_AK8_1")->Fill(AK8Jets->at(0).eta(),weight);
        }
    if(N_AK8>=2){
	hist("pT_AK8_2")->Fill(AK8Jets->at(1).pt(),weight); 
	hist("eta_AK8_2")->Fill(AK8Jets->at(1).eta(),weight);
    	hist("pT_AK8_12")->Fill((AK8Jets->at(0).v4()+AK8Jets->at(1).v4()).pt(),weight);
    	hist("eta_AK8_12")->Fill((AK8Jets->at(0).v4()+AK8Jets->at(1).v4()).eta(),weight);
	hist("M_jj_AK8")->Fill((AK8Jets->at(0).v4()+AK8Jets->at(1).v4()).M(),weight);
    }
    
    // int Nmuons = event.muons->size();
    // hist("N_mu")->Fill(Nmuons, weight);
    // for (const Muon & thismu : *event.muons){
    //     hist("pt_mu")->Fill(thismu.pt(), weight);
    //     hist("eta_mu")->Fill(thismu.eta(), weight);
    //     hist("reliso_mu")->Fill(thismu.relIso(), weight);
    // }
  
    int Npvs = event.pvs->size();
    hist("N_pv")->Fill(Npvs, weight);
  
    int NW=0;

    for (const GenParticle & thisgen : *event.genparticles){
	if(abs(thisgen.pdgId())==24) NW++;
	hist("pdgID")->Fill(thisgen.pdgId(),weight);
    }
    // int Nww=0;
    // int Nvbf=0;
    // //cout << "GenParticles: " << endl;


    // for (const GenParticle & thisgen : *event.genparticles){
    // 	if(thisgen.status()==23){
    // 	    hist("pdgIdofmother")->Fill(event.genparticles->at(thisgen.mother1()).pdgId());
    // 	    //if (thisgen.mother2()<1000) hist("pdgIdofmother")->Fill(event.genparticles->at(thisgen.mother2()).pdgId());
    // 	    bool isDaughterOfW=abs(event.genparticles->at(thisgen.mother1()).pdgId())==24;
    // 	    if(isDaughterOfW){
    // 		if(NW==3){
    // 		    hist("eta_3WJet")->Fill(thisgen.eta(),weight);
    // 		    hist("pT_3WJet")->Fill(thisgen.pt(),weight);
    // 		}else{
    // 		    hist("eta_WWJet")->Fill(thisgen.eta(),weight);
    // 		    hist("pT_WWJet")->Fill(thisgen.pt(),weight);
    // 		}
    // 		Nww++;
    // 		//cout << "pdg of mother:" << event.genparticles->at(thisgen.mother1()).pdgId() << " # of daughters: " << Nww<<endl;
    // 	    }else{  
    // 		hist("eta_VBFJet")->Fill(thisgen.eta(),weight);
    // 		hist("pT_VBFJet")->Fill(thisgen.pt(),weight);
    // 		Nvbf++;
    // 		//cout << "pdg of mother:" << event.genparticles->at(thisgen.mother1()).pdgId() << " # of daughters: " << Nvbf<<endl;
    // 	    }
    // 	}
    // }
    // //cout << "Nww: " << Nww << "  Nvbf: " << Nvbf << "  weight: " << weight<< endl;
    // hist("N_WJet")->Fill(Nww,weight);
    // hist("N_VBFJet")->Fill(Nvbf,weight);
  
}

aQGCVVjjhadronicHists::~aQGCVVjjhadronicHists(){}
