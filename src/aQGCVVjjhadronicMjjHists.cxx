#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicMjjHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include <iostream>
#include <math.h>
using namespace std;
using namespace uhh2;
using namespace uhh2examples;


aQGCVVjjhadronicMjjHists::aQGCVVjjhadronicMjjHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
    // book all histograms here
    // std::cout << "dirname: "<<dirname<<" dirname.find(WPWP): " << dirname.find("WPWP")<<std::endl;
    // std::cout << "stdf::string::npos: " << std::string::npos << std::endl;
    if(dirname.find("WPWP") != std::string::npos){
	// std::cout << "CHECK"<<std::endl;
	//S0=[83,8.00,-328.00,328.00]
	for(unsigned int i=0; i<83; i++){
	    reweight_names.push_back(getParName("S0",-328.00f,8.00f,i));
	}
	//S1=[71,30.00,-1050.00,1050.00]
	for(unsigned int i=0; i<71; i++){
	    reweight_names.push_back(getParName("S1",-1050.00f,30.00f,i));
	}
	//M0=[71,3.00,-105.00,105.00]
	for(unsigned int i=0; i<71; i++){
	    reweight_names.push_back(getParName("M0",-105.00f,3.00f,i));
	}
	//M1=[71,3.00,-105.00,105.00]
	for(unsigned int i=0; i<71; i++){
	    reweight_names.push_back(getParName("M1",-105.00f,3.00f,i));
	}
	//M6=[71,6.00,-210.00,210.00]
	for(unsigned int i=0; i<71; i++){
	    reweight_names.push_back(getParName("M6",-210.00f,6.00f,i));
	}
	//M7=[85,4.00,-168.00,168.00]
	for(unsigned int i=0; i<85; i++){
	    reweight_names.push_back(getParName("M7",-168.00f,4.00f,i));
	}
	//T0=[91,0.12,-5.40,5.40]
	for(unsigned int i=0; i<91; i++){
	    reweight_names.push_back(getParName("T0",-5.40f,0.12f,i));
	}
	//T1=[97,0.03,-1.44,1.44]
	for(unsigned int i=0; i<97; i++){
	    reweight_names.push_back(getParName("T1",-1.44f,0.03f,i));
	}
	//T2=[71,0.18,-6.30,6.30]
	for(unsigned int i=0; i<71; i++){
	    reweight_names.push_back(getParName("T2",-6.30f,0.18f,i));
	}

    }else if(dirname.find("WPWM") != std::string::npos){
	//S0=[91,20,-900,900]
	for(unsigned int i=0; i<91; i++){
	    reweight_names.push_back(getParName("S0",-900.0f,20.0f,i));
	}
	// S1=[67,10,-330,330]
	for(unsigned int i=0; i<67; i++){
	    reweight_names.push_back(getParName("S1",-330.0f,10.0f,i));
	} 
	// M0=[85,1,-42,42]
	for(unsigned int i=0; i<85; i++){
	    reweight_names.push_back(getParName("M0",-42.0f,1.0f,i));
	} 
	// M1=[67,5,-165,165]
	for(unsigned int i=0; i<67; i++){
	    reweight_names.push_back(getParName("M1",-165.0f,5.0f,i));
	} 
	// M6=[84,2,-84,82]
	for(unsigned int i=0; i<85; i++){
	    reweight_names.push_back(getParName("M6",-84.0f,2.0f,i));
	} 
	// M7=[121,5,-300,300]
	for(unsigned int i=0; i<121; i++){
	    reweight_names.push_back(getParName("M7",-300.0f,5.0f,i));
	}
	// T0=[69,0.2,-6.8,6.8]
	for(unsigned int i=0; i<69; i++){
	    reweight_names.push_back(getParName("T0",-6.8f,0.2f,i));
	} 
	// T1=[51,0.5,-12.5,12.5]
	for(unsigned int i=0; i<51; i++){
	    reweight_names.push_back(getParName("T1",-12.5f,0.5f,i));
	} 
	// T2=[83,0.5,-20.5,20.5]
	for(unsigned int i=0; i<83; i++){
	    reweight_names.push_back(getParName("T2",-20.5f,0.5f,i));
	} 

    }else if(dirname.find("WMWM") != std::string::npos){
	//S0=[91,20,-900,900]
	for(unsigned int i=0; i<91; i++){
	    reweight_names.push_back(getParName("S0",-900.0f,20.0f,i));
	}
	// S1=[67,10,-330,330]
	for(unsigned int i=0; i<67; i++){
	    reweight_names.push_back(getParName("S1",-330.0f,10.0f,i));
	} 
	// M0=[85,1,-42,42]
	for(unsigned int i=0; i<85; i++){
	    reweight_names.push_back(getParName("M0",-42.0f,1.0f,i));
	} 
	// M1=[67,5,-165,165]
	for(unsigned int i=0; i<67; i++){
	    reweight_names.push_back(getParName("M1",-165.0f,5.0f,i));
	} 
	// M6=[84,2,-84,82]
	for(unsigned int i=0; i<85; i++){
	    reweight_names.push_back(getParName("M6",-84.0f,2.0f,i));
	} 
	// M7=[121,5,-300,300]
	for(unsigned int i=0; i<121; i++){
	    reweight_names.push_back(getParName("M7",-300.0f,5.0f,i));
	}
	// T0=[69,0.2,-6.8,6.8]
	for(unsigned int i=0; i<69; i++){
	    reweight_names.push_back(getParName("T0",-6.8f,0.2f,i));
	} 
	// T1=[51,0.5,-12.5,12.5]
	for(unsigned int i=0; i<51; i++){
	    reweight_names.push_back(getParName("T1",-12.5f,0.5f,i));
	} 
	// T2=[83,0.5,-20.5,20.5]
	for(unsigned int i=0; i<83; i++){
	    reweight_names.push_back(getParName("T2",-20.5f,0.5f,i));
	} 

    }else if(dirname.find("WPZ") != std::string::npos){
	//S0=[91,20,-900,900]
	for(unsigned int i=0; i<91; i++){
	    reweight_names.push_back(getParName("S0",-900.0f,20.0f,i));
	}
	// S1=[67,10,-330,330]
	for(unsigned int i=0; i<67; i++){
	    reweight_names.push_back(getParName("S1",-330.0f,10.0f,i));
	} 
	// M0=[85,1,-42,42]
	for(unsigned int i=0; i<85; i++){
	    reweight_names.push_back(getParName("M0",-42.0f,1.0f,i));
	} 
	// M1=[67,5,-165,165]
	for(unsigned int i=0; i<67; i++){
	    reweight_names.push_back(getParName("M1",-165.0f,5.0f,i));
	} 
	// M6=[84,2,-84,82]
	for(unsigned int i=0; i<85; i++){
	    reweight_names.push_back(getParName("M6",-84.0f,2.0f,i));
	} 
	// M7=[121,5,-300,300]
	for(unsigned int i=0; i<121; i++){
	    reweight_names.push_back(getParName("M7",-300.0f,5.0f,i));
	}
	// T0=[69,0.2,-6.8,6.8]
	for(unsigned int i=0; i<69; i++){
	    reweight_names.push_back(getParName("T0",-6.8f,0.2f,i));
	} 
	// T1=[51,0.5,-12.5,12.5]
	for(unsigned int i=0; i<51; i++){
	    reweight_names.push_back(getParName("T1",-12.5f,0.5f,i));
	} 
	// T2=[83,0.5,-20.5,20.5]
	for(unsigned int i=0; i<83; i++){
	    reweight_names.push_back(getParName("T2",-20.5f,0.5f,i));
	} 

    }else if(dirname.find("WMZ") != std::string::npos){
	//S0=[91,20,-900,900]
	for(unsigned int i=0; i<91; i++){
	    reweight_names.push_back(getParName("S0",-900.0f,20.0f,i));
	}
	// S1=[67,10,-330,330]
	for(unsigned int i=0; i<67; i++){
	    reweight_names.push_back(getParName("S1",-330.0f,10.0f,i));
	} 
	// M0=[85,1,-42,42]
	for(unsigned int i=0; i<85; i++){
	    reweight_names.push_back(getParName("M0",-42.0f,1.0f,i));
	} 
	// M1=[67,5,-165,165]
	for(unsigned int i=0; i<67; i++){
	    reweight_names.push_back(getParName("M1",-165.0f,5.0f,i));
	} 
	// M6=[84,2,-84,82]
	for(unsigned int i=0; i<85; i++){
	    reweight_names.push_back(getParName("M6",-84.0f,2.0f,i));
	} 
	// M7=[121,5,-300,300]
	for(unsigned int i=0; i<121; i++){
	    reweight_names.push_back(getParName("M7",-300.0f,5.0f,i));
	}
	// T0=[69,0.2,-6.8,6.8]
	for(unsigned int i=0; i<69; i++){
	    reweight_names.push_back(getParName("T0",-6.8f,0.2f,i));
	} 
	// T1=[51,0.5,-12.5,12.5]
	for(unsigned int i=0; i<51; i++){
	    reweight_names.push_back(getParName("T1",-12.5f,0.5f,i));
	} 
	// T2=[83,0.5,-20.5,20.5]
	for(unsigned int i=0; i<83; i++){
	    reweight_names.push_back(getParName("T2",-20.5f,0.5f,i));
	} 

    }else if(dirname.find("ZZ") != std::string::npos){
	//S0=[91,20,-900,900]
	for(unsigned int i=0; i<91; i++){
	    reweight_names.push_back(getParName("S0",-900.0f,20.0f,i));
	}
	// S1=[67,10,-330,330]
	for(unsigned int i=0; i<67; i++){
	    reweight_names.push_back(getParName("S1",-330.0f,10.0f,i));
	} 
	// M0=[85,1,-42,42]
	for(unsigned int i=0; i<85; i++){
	    reweight_names.push_back(getParName("M0",-42.0f,1.0f,i));
	} 
	// M1=[67,5,-165,165]
	for(unsigned int i=0; i<67; i++){
	    reweight_names.push_back(getParName("M1",-165.0f,5.0f,i));
	} 
	// M6=[84,2,-84,82]
	for(unsigned int i=0; i<85; i++){
	    reweight_names.push_back(getParName("M6",-84.0f,2.0f,i));
	} 
	// M7=[121,5,-300,300]
	for(unsigned int i=0; i<121; i++){
	    reweight_names.push_back(getParName("M7",-300.0f,5.0f,i));
	}
	// T0=[69,0.2,-6.8,6.8]
	for(unsigned int i=0; i<69; i++){
	    reweight_names.push_back(getParName("T0",-6.8f,0.2f,i));
	} 
	// T1=[51,0.5,-12.5,12.5]
	for(unsigned int i=0; i<51; i++){
	    reweight_names.push_back(getParName("T1",-12.5f,0.5f,i));
	} 
	// T2=[83,0.5,-20.5,20.5]
	for(unsigned int i=0; i<83; i++){
	    reweight_names.push_back(getParName("T2",-20.5f,0.5f,i));
	} 
    }


    book<TH1F>("M_jj_AK8", "M_{jj-AK8} [GeV/c^{2}]",100,0,10000);
    
    for(unsigned int i=0; i<reweight_names.size();i++){
	// std::cout << "reweight.size(): " << reweight_names.size() << std::endl;
	// std::cout << "paranames: " << reweight_names.at(i)<<std::endl;
	
	std::string hist_name="M_jj_AK8_"+ reweight_names.at(i);
	book<TH1F>(hist_name, "M_{jj-AK8} [GeV/c^{2}]",100,0,10000);    
    }

}


void aQGCVVjjhadronicMjjHists::fill(const Event & event){
    // fill the histograms. Please note the comments in the header file:
    // 'hist' is used here a lot for simplicity, but it will be rather
    // slow when you have many histograms; therefore, better
    // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
    // Don't forget to always use the weight when filling.
    double weight = event.weight;

    // S0: 882  - 972
    // S1: 973	 - 1039
    // M0: 1040 - 1124
    // M1: 1125 - 1191
    // M6: 1192 - 1276
    // M7: 1277 - 1397
    // T0: 1398 - 1466
    // T1: 1467 - 1517
    // T2: 1518 - 1600
    //event.genInfo->systweights().at(i)
  
    //std::vector<GenParticle>* genjets = event.genjets;
    //for(const GenParticle & thisgenjet : * genjets){
    //  cout << "genjet pdgId: " << thisgenjet.pdgId() <<endl;
    //}
    
    // std::cout << "lenght systweights: " << event.genInfo->systweights().size() << std::endl;
    // std::cout << "lenght reweight_names: " << reweight_names.size() << std::endl;
    
    int N_systweights=event.genInfo->systweights().size();
    int N_reweight=reweight_names.size();
    if(N_systweights==N_reweight+882){
	assert(event.topjets);
	std::vector<TopJet>* AK8Jets = event.topjets;
	auto N_AK8=AK8Jets->size();
	if(N_AK8>2){
	    hist("M_jj_AK8")->Fill((AK8Jets->at(0).v4()+AK8Jets->at(1).v4()).M(),weight);
	    
	    for(unsigned int i=0; i<reweight_names.size();i++){
		std::string hist_name="M_jj_AK8_"+ reweight_names.at(i);
		// std::cout << "histname: " << hist_name<<std::endl;
	    
		auto fillweight=event.weight * event.genInfo->systweights().at(i+882) / event.genInfo->originalXWGTUP();
		// std::cout << "i= " << i+882 << "  fillweight: " <<  fillweight << std::endl; 
		hist(hist_name.c_str())->Fill((AK8Jets->at(0).v4()+AK8Jets->at(1).v4()).M(),fillweight);
	    }
	}
    }else{
	std::cout << "Not expected Number of Reweighting Points! Skipping Event for MjjHists" << std::endl;
	std::cout << "(expected: " << N_reweight<< " - actual: "<< N_systweights-882 <<std::endl;
	
    }
    // std::vector<TopJet>* AK8Jets = event.topjets;

    // auto N_AK8=AK8Jets->size();
    // hist("N_AK8")->Fill(N_AK8,weight);

    // for(const TopJet & thisjet : *AK8Jets){
    // 	hist("pT_AK8")->Fill(thisjet.pt(),weight);
    // 	hist("eta_AK8")->Fill(thisjet.eta(),weight);
    // }

    // if(N_AK8>=1){
    // 	hist("pT_AK8_1")->Fill(AK8Jets->at(0).pt(),weight); 
    // 	hist("eta_AK8_1")->Fill(AK8Jets->at(0).eta(),weight);
    //     }
    // if(N_AK8>=2){
    // 	hist("pT_AK8_2")->Fill(AK8Jets->at(1).pt(),weight); 
    // 	hist("eta_AK8_2")->Fill(AK8Jets->at(1).eta(),weight);
    // 	hist("pT_AK8_12")->Fill(AK8Jets->at(0).pt()+AK8Jets->at(1).pt(),weight);
    // 	hist("eta_AK8_12")->Fill(AK8Jets->at(0).eta()+AK8Jets->at(1).eta(),weight);
    // hist("M_jj_AK8")->Fill((AK8Jets->at(0).v4()+AK8Jets->at(1).v4()).M(),weight);
    // }
  
}

aQGCVVjjhadronicMjjHists::~aQGCVVjjhadronicMjjHists(){}


std::string getParName(std::string set, float startx, float increment,int i){
    int parameter = 100*startx + i* 100 * increment;
    std::string name;
    if(parameter>=0){
	name = std::to_string(parameter/100) + "p" + std::to_string(parameter%100);
    }else{
	name = "m"+std::to_string(-parameter/100) + "p" + std::to_string((-parameter)%100);
    }	
    return set+"_"+name;
    // float f_parameter = startx+i*increment;
    // float f_remainder = fmod(f_parameter,1.0f);
    // int i_parameter   = f_parameter-f_remainder;
    // int i_remainder   = f_remainder*10;
    // std::string str_parameter=std::to_string(i_parameter)+"p"+std::to_string(i_remainder);
    // if(i_parameter<0)str_parameter="m"+std::to_string(-i_parameter)+"p"+std::to_string(-i_remainder);  
    // std::string current=set+"_"+str_parameter;
    // return current;
}
