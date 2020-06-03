#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicMjjHists.h"
#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicSelections.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include <iostream>
#include <math.h>
using namespace std;
using namespace uhh2;
using namespace uhh2examples;


aQGCVVjjhadronicMjjHists::aQGCVVjjhadronicMjjHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // book all histograms here

  if(dirname.find("Unc") != std::string::npos){//This value, when used as the value for a len (or sublen) parameter in string's member functions, means "until the end of the string". 
    //T0=[91,0.12,-5.40,5.40]
    for(unsigned int i=0; i<61; i++){
      reweight_names.push_back(getParName("T0",-15.00f,0.5f,i));
    }
  }else{
    for(unsigned int i = 0; i < 6; i++){//S0=[6,5.00,0.00,30.00]
      reweight_names.push_back(getParName("S0",0.00,5.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//S1=[6,8.00,0.00,48.00]
      reweight_names.push_back(getParName("S1",0.00,8.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//S2=[6,5.00,0.00,30.00]
      reweight_names.push_back(getParName("S2",0.00,5.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M0=[6,0.90,0.00,5.40]
      reweight_names.push_back(getParName("M0",0.00,0.90,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M1=[6,0.70,0.00,4.20]
      reweight_names.push_back(getParName("M1",0.00,0.70,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M2=[6,1.50,0.00,9.00]
      reweight_names.push_back(getParName("M2",0.00,1.50,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M3=[6,2.00,0.00,12.00]
      reweight_names.push_back(getParName("M3",0.00,2.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M4=[6,2.00,0.00,12.00]
      reweight_names.push_back(getParName("M4",0.00,2.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M5=[6,4.00,0.00,24.00]
      reweight_names.push_back(getParName("M5",0.00,4.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M7=[6,2.00,0.00,12.00]
      reweight_names.push_back(getParName("M7",0.00,2.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T0=[6,0.05,0.00,0.30]
      reweight_names.push_back(getParName("T0",0.00,0.05,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T1=[6,0.05,0.00,0.30]
      reweight_names.push_back(getParName("T1",0.00,0.05,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T2=[6,0.10,0.00,0.60]
      reweight_names.push_back(getParName("T2",0.00,0.10,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T5=[6,0.20,0.00,1.20]
      reweight_names.push_back(getParName("T5",0.00,0.20,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T6=[6,0.20,0.00,1.20]
      reweight_names.push_back(getParName("T6",0.00,0.20,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T7=[6,0.40,0.00,2.40]
      reweight_names.push_back(getParName("T7",0.00,0.40,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T8=[6,0.50,0.00,3.00]
      reweight_names.push_back(getParName("T8",0.00,0.50,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T9=[6,0.50,0.00,3.00]
      reweight_names.push_back(getParName("T9",0.00,0.50,i));
    }
  }
  
  
  //TODO correct binning!
  
  book<TH1F>("M_jj_AK8", "M_{jj-AK8} [GeV/c^{2}]",10000,0,10000);//(const char *name, const char *title, Int_t nbinsx, Double_t xlow, Double_t xup)
  book<TH1F>("M_jj_AK4", "M_{jj-AK4} [GeV/c^{2}]",10000,0,10000);

  
  for(unsigned int i=0; i<reweight_names.size();i++){
    // std::cout << "reweight.size(): " << reweight_names.size() << std::endl;
    // std::cout << "paranames: " << reweight_names.at(i)<<std::endl;

    std::string AK8_hist_name="M_jj_AK8_"+ reweight_names.at(i);
    std::string AK4_hist_name="M_jj_AK4_"+ reweight_names.at(i);

    book<TH1F>(AK8_hist_name, "M_{jj-AK8} [GeV/c^{2}]",10000,0,10000);
    book<TH1F>(AK4_hist_name, "M_{jj-AK4} [GeV/c^{2}]",10000,0,10000);
  }

}



void aQGCVVjjhadronicMjjHists::fill(const Event & event){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'

  // Don't forget to always use the weight when filling.
  double weight = event.weight;
  //event.genInfo->systweights().at(i)

  // std::cout << "length systweights: " << event.genInfo->systweights().size() << std::endl;
  // std::cout << "lenght reweight_names: " << reweight_names.size() << std::endl;

  int N_systweights=event.genInfo->systweights().size();
  int N_reweight=reweight_names.size();
  int N_pdfwgt = 148;
  int N_pdfwgt_postSMEFT = 1322;

  if(N_systweights==N_reweight+N_pdfwgt+N_pdfwgt_postSMEFT){
    assert(event.topjets);
    std::vector<TopJet>* AK8Jets = event.topjets;
    auto N_AK8=AK8Jets->size();

    if(N_AK8>2){
      hist("M_jj_AK8")->Fill((AK8Jets->at(0).v4()+AK8Jets->at(1).v4()).M(),weight);

      for(unsigned int i=0; i<reweight_names.size();i++){
	std::string hist_name="M_jj_AK8_"+ reweight_names.at(i);
	// std::cout << "histname: " << hist_name<<std::endl;
	auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo->originalXWGTUP();

	hist(hist_name.c_str())->Fill((AK8Jets->at(0).v4()+AK8Jets->at(1).v4()).M(),fillweight);
      }
    }
    std::vector<Jet>* AK4Jets = event.jets;
    auto N_AK4=AK4Jets->size();

    if(N_AK4>2){
      hist("M_jj_AK4")->Fill((AK4Jets->at(0).v4()+AK4Jets->at(1).v4()).M(),weight);

      for(unsigned int i=0; i<reweight_names.size();i++){
	std::string hist_name="M_jj_AK4_"+ reweight_names.at(i);
	// std::cout << "histname: " << hist_name<<std::endl;
	auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo->originalXWGTUP();

	hist(hist_name.c_str())->Fill((AK4Jets->at(0).v4()+AK4Jets->at(1).v4()).M(),fillweight);
      }
    }

  }else{
    std::cout << "Not expected Number of Reweighting Points! Skipping Event for MjjHists" << std::endl;
    std::cout << "(expected: " << N_reweight<< " - actual: "<< N_systweights-N_pdfwgt <<std::endl;

  }


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
}
