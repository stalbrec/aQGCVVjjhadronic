#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicUncertaintiesHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;
using namespace uhh2;
using namespace uhh2examples;


aQGCVVjjhadronicUncertaintiesHists::aQGCVVjjhadronicUncertaintiesHists(Context & ctx, const string & dirname,const int parameter_index_): Hists(ctx, dirname), parameter_index(parameter_index_) {

  if(parameter_index<83){
    std::string parameter_string="S0";
    reweight_name=getParNamePDF("S0",-328.00f,8.00f,parameter_index-0);
  }else if(parameter_index<154){
    std::string parameter_string="S1";
    reweight_name=getParNamePDF("S1",-1050.00f,30.00f,parameter_index-83);
  }else if(parameter_index<225){
    std::string parameter_string="M0";
    reweight_name=getParNamePDF("M0",-105.00f,3.00f,parameter_index-154);
  }else if(parameter_index<296){
    std::string parameter_string="M1";
    reweight_name=getParNamePDF("M1",-105.00f,3.00f,parameter_index-225);
  }else if(parameter_index<377){
    std::string parameter_string="M2";
    reweight_name=getParNamePDF("M2",-200.00f,5.00f,parameter_index-296);
  }else if(parameter_index<458){
    std::string parameter_string="M3";
    reweight_name=getParNamePDF("M3",-320.00f,8.00f,parameter_index-377);
  }else if(parameter_index<539){
    std::string parameter_string="M4";
    reweight_name=getParNamePDF("M4",-320.00f,8.00f,parameter_index-458);
  }else if(parameter_index<620){
    std::string parameter_string="M5";
    reweight_name=getParNamePDF("M5",-520.00f,13.00f,parameter_index-539);
  }else if(parameter_index<691){
    std::string parameter_string="M6";
    reweight_name=getParNamePDF("M6",-210.00f,6.00f,parameter_index-620);
  }else if(parameter_index<776){
    std::string parameter_string="M7";
    reweight_name=getParNamePDF("M7",-168.00f,4.00f,parameter_index-691);
  }else if(parameter_index<867){
    std::string parameter_string="T0";
    reweight_name=getParNamePDF("T0",-5.40f,0.12f,parameter_index-776);
  }else if(parameter_index<964){
    std::string parameter_string="T1";
    reweight_name=getParNamePDF("T1",-1.44f,0.03f,parameter_index-867);
  }else if(parameter_index<1035){
    std::string parameter_string="T2";
    reweight_name=getParNamePDF("T2",-6.30f,0.18f,parameter_index-964);
  }else if(parameter_index<1116){
    std::string parameter_string="T5";
    reweight_name=getParNamePDF("T5",-28.00f,0.70f,parameter_index-1035);
  }else if(parameter_index<1197){
    std::string parameter_string="T6";
    reweight_name=getParNamePDF("T6",-20.00f,0.50f,parameter_index-1116);
  }else if(parameter_index<1278){
    std::string parameter_string="T7";
    reweight_name=getParNamePDF("T7",-56.00f,1.40f,parameter_index-1197);
  }else if(parameter_index<1359){
    std::string parameter_string="T8";
    reweight_name=getParNamePDF("T8",-6.00f,0.15f,parameter_index-1278);
  }else if(parameter_index<1440){
    std::string parameter_string="T9";
    reweight_name=getParNamePDF("T9",-12.00f,0.30f,parameter_index-1359);
  }	
    
  std::string AK8_hist_name_pdf="M_jj_AK8_"+ reweight_name;
  AK8_hist_name_pdf=AK8_hist_name_pdf+"_pdf_";
  for(unsigned int j=0 ; j< 103;j++){
    std::string pdf_AK8_hist_name=AK8_hist_name_pdf+std::to_string(j);
    book<TH1F>(pdf_AK8_hist_name, "M_{jj-AK8} [GeV/c^{2}]",14000,0,14000);    
  }
  std::string AK8_hist_name_scale="M_jj_AK8_"+ reweight_name;
  AK8_hist_name_scale=AK8_hist_name_scale+"_scale_";
  for(unsigned int j=0 ; j< 9;j++){
    std::string pdf_AK8_hist_name=AK8_hist_name_scale+std::to_string(j);
    book<TH1F>(pdf_AK8_hist_name, "M_{jj-AK8} [GeV/c^{2}]",14000,0,14000);    
  }
	
}


void aQGCVVjjhadronicUncertaintiesHists::fill(const Event & event){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
  // Don't forget to always use the weight when filling.
  double weight = event.weight;
    
    
  int N_systweights=event.genInfo->systweights().size();
  int N_pdfwgt=0;
  N_pdfwgt=1080;

  assert(event.topjets);
  std::vector<TopJet>* AK8Jets = event.topjets;
  auto N_AK8=AK8Jets->size();

  if(N_AK8>2){ 
    std::string hist_name="M_jj_AK8_"+ reweight_name;
    hist_name=hist_name+"_pdf_";
    auto fillweight=event.weight * event.genInfo->systweights().at(parameter_index+N_pdfwgt) / event.genInfo->originalXWGTUP();
    for(unsigned int j=0 ; j< 103;j++){
      auto pdf_fillweight=fillweight * event.genInfo->systweights().at(j+9) / event.genInfo->originalXWGTUP();
      std::string pdf_hist_name=hist_name+std::to_string(j);
			
      hist(pdf_hist_name.c_str())->Fill((AK8Jets->at(0).v4()+AK8Jets->at(1).v4()).M(),pdf_fillweight);    			
    }

		std::string hist_name_scale="M_jj_AK8_"+ reweight_name;
    hist_name_scale=hist_name_scale+"_scale_";
    for(unsigned int j=0 ; j< 9;j++){
      auto scale_fillweight=fillweight * event.genInfo->systweights().at(j) / event.genInfo->originalXWGTUP();
      std::string scale_hist_name=hist_name_scale+std::to_string(j);			
      hist(scale_hist_name.c_str())->Fill((AK8Jets->at(0).v4()+AK8Jets->at(1).v4()).M(),scale_fillweight);    			
    }

  }
  
}

aQGCVVjjhadronicUncertaintiesHists::~aQGCVVjjhadronicUncertaintiesHists(){}


std::string getParNamePDF(std::string set, float startx, float increment,int i){
  int parameter = 100*startx + i* 100 * increment;
  std::string name;
  if(parameter>=0){
    name = std::to_string(parameter/100) + "p" + std::to_string(parameter%100);
  }else{
    name = "m"+std::to_string(-parameter/100) + "p" + std::to_string((-parameter)%100);
  }	
  return set+"_"+name;
}
