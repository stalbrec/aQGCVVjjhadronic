#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicHists.h"
#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicSelections.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicKinematicsjjHists.h"

#include "TH2D.h"
#include "TH1F.h"
#include <iostream>
#include <math.h>
using namespace std;
using namespace uhh2;
using namespace uhh2examples;

aQGCVVjjhadronicKinematicsjjHists::aQGCVVjjhadronicKinematicsjjHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
//EFT Parametrisstion for the kinematic variables of AK8_Jet 1, 2 and the leading AK8_Jets
//parametrisation for all selection criteria -> write all methods and plots
//selectioncriteria [VV] left: delte eta, N>=2, 65 < MSD < 105 GeV, 0< tau1/tau2 < 0.45
 if(dirname.find("Unc") != std::string::npos){//This value, when used as the value for a len (or sublen) parameter in string's member functions, means "until the end of the string". 
    //T0=[91,0.12,-5.40,5.40]
    for(unsigned int i=0; i<61; i++){
      reweight_names.push_back(GetParName("T0",-15.00f,0.5f,i));
    }
  }else{
    for(unsigned int i = 0; i < 6; i++){//S0=[6,5.00,0.00,30.00]
      reweight_names.push_back(GetParName("S0",0.00,5.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//S1=[6,8.00,0.00,48.00]
      reweight_names.push_back(GetParName("S1",0.00,8.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//S2=[6,5.00,0.00,30.00]
      reweight_names.push_back(GetParName("S2",0.00,5.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M0=[6,0.90,0.00,5.40]
      reweight_names.push_back(GetParName("M0",0.00,0.90,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M1=[6,0.70,0.00,4.20]
      reweight_names.push_back(GetParName("M1",0.00,0.70,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M2=[6,1.50,0.00,9.00]
      reweight_names.push_back(GetParName("M2",0.00,1.50,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M3=[6,2.00,0.00,12.00]
      reweight_names.push_back(GetParName("M3",0.00,2.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M4=[6,2.00,0.00,12.00]
      reweight_names.push_back(GetParName("M4",0.00,2.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M5=[6,4.00,0.00,24.00]
      reweight_names.push_back(GetParName("M5",0.00,4.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//M7=[6,2.00,0.00,12.00]
      reweight_names.push_back(GetParName("M7",0.00,2.00,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T0=[6,0.05,0.00,0.30]
      reweight_names.push_back(GetParName("T0",0.00,0.05,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T1=[6,0.05,0.00,0.30]
      reweight_names.push_back(GetParName("T1",0.00,0.05,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T2=[6,0.10,0.00,0.60]
      reweight_names.push_back(GetParName("T2",0.00,0.10,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T5=[6,0.20,0.00,1.20]
      reweight_names.push_back(GetParName("T5",0.00,0.20,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T6=[6,0.20,0.00,1.20]
      reweight_names.push_back(GetParName("T6",0.00,0.20,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T7=[6,0.40,0.00,2.40]
      reweight_names.push_back(GetParName("T7",0.00,0.40,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T8=[6,0.50,0.00,3.00]
      reweight_names.push_back(GetParName("T8",0.00,0.50,i));
    }
    for(unsigned int i = 0; i < 6; i++){//T9=[6,0.50,0.00,3.00]
      reweight_names.push_back(GetParName("T9",0.00,0.50,i));
    }
  }
  //Selection Criteria AK4 _______________________________________________________****************************
  book<TH1F>("N_AK4", "N_{AK4 jets}", 20, 0, 20);  
  
  book<TH1F>("pT_AK4_1", "p_{T}^{1st AK4 jet} [GeV/c]", 40 ,0 ,4000);
  book<TH1F>("eta_AK4_1", "#eta^{1st AK4 jet}", 40, -6.5, 6.5);
  book<TH1F>("pT_AK4_2", "p_{T}^{2nd AK4 jet} [GeV/c]", 40 ,0 ,4000);
  book<TH1F>("eta_AK4_2", "#eta^{2nd AK4 jet}", 40, -6.5, 6.5);
  //_____________________________________________________________________________2D_compare pT and eta
  book<TH2D>("pT_AK4_1_vs_pT_AK4_2", "pT_AK4_1_vs_pT_AK4_2",40,0,4000,40,0,4000);
  book<TH2D>("eta_AK4_1_vs_eta_AK4_2", "eta_AK4_1_vs_eta_AK4_2",40,-6.5,6.5,40,-6.5,6.5);

  book<TH1F>("pT_AK4_12", "p_{T}^{leading AK4 jets} [GeV/c]", 40 ,0 ,4000);
  book<TH1F>("eta_AK4_12", "#eta^{leading AK4 jets}", 40, -6.5, 6.5);
  book<TH1F>("deta_AK4_12", "#Delta #eta^{leading AK4 jets}", 40, 0, 13.0);

  book<TH1F>("prodeta_AK4_12", "#eta^{1st AK4 jet} #cdot #eta^{2nd AK4 jet}", 87, -43, 43);
  //_______________________________________________________________________________***************************
  //__________Selection Criteria AK8
  //__________Kinematics [pT and eta]
  book<TH1F>("pT_AK8_1", "p_{T}^{1st AK8 jet} [GeV/c]", 80 ,0 ,8000);
  book<TH1F>("eta_AK8_1", "#eta^{1st AK8 jet}", 40, -6.5, 6.5);
  book<TH1F>("pT_AK8_2", "p_{T}^{2nd AK8 jet} [GeV/c]", 80 ,0 ,8000);
  book<TH1F>("eta_AK8_2", "#eta^{2nd AK8 jet}", 40, -6.5, 6.5);
  //__________Leading AK8 Jets
  book<TH1F>("pT_AK8_12", "p_{T}^{leading AK8 jets} [GeV/c^{2}]", 80 ,0 ,8000);
  book<TH1F>("eta_AK8_12", "#eta^{leading AK8 jets}", 40, -6.5, 6.5);

  //__________Further [VV] Selection Criteria
  book<TH1F>("deta_AK8_12", "#Delta #eta^{leading AK8 jets}", 40, 0, 13.0);

  book<TH1F>("N_AK8", "N_{AK8 jets}", 20, 0, 20);

  book<TH1F>("M_softdrop_1","M_{softdrop,1st AK8 jet} [GeV/c^{2}]",100,0,300);
  book<TH1F>("M_softdrop_2","M_{softdrop,2nd AK8 jet} [GeV/c^{2}]",100,0,300);
  book<TH1F>("M_softdrop_12","M_{softdrop, leading AK8 jets} [GeV/c^{2}]",100,0,300);

  book<TH1F>("tau21_1", "#tau_{2}/#tau_{1} (1st AK8 jet)", 50, 0, 1.0);
  book<TH1F>("tau21_2", "#tau_{2}/#tau_{1} (2nd AK8 jet)", 50, 0, 1.0);
  book<TH1F>("tau21_12", "#tau_{2}/#tau_{1} (leading AK8 jets)", 50, 0, 1.0);
  // sure ?
  /*
  //(hists l. 89 ++ ) also Check for Noise from Calorimeter? what is met ?
  book<TH1F>("met_pt_over_mjjAK8_2","MET/M_{jj-AK8}",40,0,2);
  book<TH1F>("met_pt_over_mjjAK8_4","MET/M_{jj-AK8}",40,0,4);

  book<TH1F>("met_pt_over_sumptAK8_2","MET/#Sigma_{AK8-Jets} p_{T}",40,0,2);
  book<TH1F>("met_pt_over_sumptAK8_4","MET/#Sigma_{AK8-Jets} p_{T}",40,0,4);

  book<TH1F>("met_pt_over_sumptAK4_2","MET/#Sigma_{AK4-Jets} p_{T}",40,0,2);
  book<TH1F>("met_pt_over_sumptAK4_4","MET/#Sigma_{AK4-Jets} p_{T}",40,0,4);

  book<TH1F>("met_pt_over_sumptJets_2","MET/#Sigma_{Jets} p_{T}",40,0,2);
  book<TH1F>("met_pt_over_sumptJets_4","MET/#Sigma_{Jets} p_{T}",40,0,4);
  */
  for(unsigned int i=0; i<reweight_names.size();i++){
    std::string AK4_N_hist_name="N_AK4_"+reweight_names.at(i);

    std::string AK4_pT_1_hist_name="pT_AK4_1_"+reweight_names.at(i);
    std::string AK4_eta_1_hist_name="eta_AK4_1_"+reweight_names.at(i);
    std::string AK4_pT_2_hist_name="pT_AK4_2_"+reweight_names.at(i);
    std::string AK4_eta_2_hist_name="eta_AK4_2_"+reweight_names.at(i);
    //__________________________________________________________________________________sure??
    std::string AK4_pT_1_vs_pT_2_hist_name="pT_AK4_1_vs_pT_AK4_2_"+reweight_names.at(i);
    std::string AK4_eta_1_vs_eta_2_hist_name="eta_AK4_1_vs_eta_AK4_2_"+reweight_names.at(i);

    std::string AK4_pT_hist_name="pT_AK4_12_"+reweight_names.at(i);
    std::string AK4_eta_hist_name="eta_AK4_12_"+reweight_names.at(i);
    std::string AK4_deta_hist_name="deta_AK4_12_"+reweight_names.at(i);
    std::string AK4_prodeta_hist_name="prodeta_AK4_12_"+reweight_names.at(i);

    std::string AK8_pT_1_hist_name="pT_AK8_1_"+reweight_names.at(i);
    std::string AK8_eta_1_hist_name="eta_AK8_1_"+reweight_names.at(i);
    std::string AK8_pT_2_hist_name="pT_AK8_2_"+reweight_names.at(i);
    std::string AK8_eta_2_hist_name="eta_AK8_2_"+reweight_names.at(i);

    std::string AK8_pT_hist_name="pT_AK8_12_"+ reweight_names.at(i);
    std::string AK8_eta_hist_name="eta_AK8_12_"+reweight_names.at(i);
  
    std::string AK8_deta_hist_name="deta_AK8_12_"+reweight_names.at(i);

    std::string AK8_N_hist_name="N_AK8_"+reweight_names.at(i);

    std::string AK8_M_softdrop_1_hist_name="M_softdrop_1_"+reweight_names.at(i);
    std::string AK8_M_softdrop_2_hist_name="M_softdrop_2_"+reweight_names.at(i);
    std::string AK8_M_softdrop_12_hist_name="M_softdrop_12_"+reweight_names.at(i);

    std::string AK8_tau_21_1_hist_name="tau21_1_"+reweight_names.at(i);
    std::string AK8_tau_21_2_hist_name="tau21_2_"+reweight_names.at(i);
    std::string AK8_tau_21_12_hist_name="tau21_12_"+reweight_names.at(i);

  book<TH1F>(AK4_N_hist_name, "N_{AK4 jets}", 20, 0, 20);  
  
  book<TH1F>(AK4_pT_1_hist_name, "p_{T}^{1st AK4 jet} [GeV/c^{2}]", 40 ,0 ,4000);
  book<TH1F>(AK4_eta_1_hist_name, "#eta^{1st AK4 jet}", 40, -6.5, 6.5);
  book<TH1F>(AK4_pT_2_hist_name, "p_{T}^{2nd AK4 jet} [GeV/c^{2}]", 40 ,0 ,4000);
  book<TH1F>(AK4_eta_2_hist_name, "#eta^{2nd AK4 jet}", 40, -6.5, 6.5);

  book<TH2D>(AK4_pT_1_vs_pT_2_hist_name,"pT_AK4_1_vs_pT_AK4_2 [GeV/c^{2}]",40,0,4000,40,0,4000);
  book<TH2D>(AK4_eta_1_vs_eta_2_hist_name, "#eta _AK4_1_vs_ #eta _AK4_2",40,-6.5,6.5,40,-6.5,6.5);

  book<TH1F>(AK4_pT_hist_name, "p_{T}^{leading AK4 jets} [GeV/c^{2}]", 40 ,0 ,4000);
  book<TH1F>(AK4_eta_hist_name, "#eta^{leading AK4 jets}", 40, -6.5, 6.5);
  book<TH1F>(AK4_deta_hist_name, "#Delta #eta^{leading AK4 jets}", 40, 0, 13.0);

  book<TH1F>(AK4_prodeta_hist_name, "#eta^{1st AK4 jet} #cdot #eta^{2nd AK4 jet}", 87, -43, 43);//what is this ?

  book<TH1F>(AK8_pT_1_hist_name,"p_{T}^{1st AK8 jet} [GeV/c]", 80 ,0 ,8000);
  book<TH1F>(AK8_eta_1_hist_name,"#eta^{1st AK8 jet}", 40, -6.5, 6.5);
  book<TH1F>(AK8_pT_2_hist_name,"p_{T}^{2nd AK8 jet} [GeV/c]", 80 ,0 ,8000);
  book<TH1F>(AK8_eta_2_hist_name,"#eta^{2nd AK8 jet}", 40, -6.5, 6.5);

  book<TH1F>(AK8_pT_hist_name,"p_{T}^{leading AK8 jets} [GeV/c]", 80 ,0 ,8000);
  book<TH1F>(AK8_eta_hist_name, "#eta^{leading AK8 jets}", 40, -6.5, 6.5); 

  book<TH1F>(AK8_deta_hist_name,"#Delta #eta^{leading AK8 jets}", 40, 0, 13.0); 

  book<TH1F>(AK8_N_hist_name,"N_{AK8 jets}", 20, 0, 20);

  book<TH1F>(AK8_M_softdrop_1_hist_name,"M_{softdrop,1st AK8 jet} [GeV/c^{2}]",100,0,300);
  book<TH1F>(AK8_M_softdrop_2_hist_name,"M_{softdrop,2nd AK8 jet} [GeV/c^{2}]",100,0,300);
  book<TH1F>(AK8_M_softdrop_12_hist_name,"M_{softdrop, leading AK8 jets} [GeV/c^{2}]",100,0,300);

  book<TH1F>(AK8_tau_21_1_hist_name,"#tau_{2}/#tau_{1} (1st AK8 jet)",50,0,1.0);
  book<TH1F>(AK8_tau_21_2_hist_name,"#tau_{2}/#tau_{1} (2nd AK8 jet)",50,0,1.0);
  book<TH1F>(AK8_tau_21_12_hist_name,"#tau_{2}/#tau_{1} (leading AK8 jets)",50,0,1.0);

  /*
  at last(CalorimeterNoise) if needed
  */

  }
}
//_______________________________________________________________
void aQGCVVjjhadronicKinematicsjjHists::fill(const Event & event){
  //Don't forget to always use the weight when filling.
  double weight = event.weight;
  //some more initialisations before assert to use the reweighting! 
  int N_systweights=event.genInfo->systweights().size();
  int N_reweight=reweight_names.size();
  int N_pdfwgt = 148;
  int N_pdfwgt_postSMEFT = 1322;

  if(N_systweights==N_reweight+N_pdfwgt+N_pdfwgt_postSMEFT){
  //____________________________________________________________**********************AK4
  assert(event.jets);
  std::vector<Jet>* AK4Jets = event.jets;
  auto N_AK4 = AK4Jets -> size();
  //___________________________________________________________AK4>=1
  if(N_AK4 >=1){
  hist("pT_AK4_1")->Fill(AK4Jets->at(0).pt(),weight); 
  hist("eta_AK4_1")->Fill(AK4Jets->at(0).eta(),weight);
  //____________________________________________________________AK4_1_pT
    for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="pT_AK4_1_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();
    hist(hist_name.c_str())->Fill((AK4Jets->at(0).pt()),fillweight);
    }
  //____________________________________________________________AK4_1_eta
    for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="eta_AK4_1_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();
    hist(hist_name.c_str())->Fill((AK4Jets->at(0).eta()), fillweight);
    }
  }

  //_____________________________________________________________AK4>=2
  if(N_AK4 >=2 ){
  //_____________________________________________________________AK4_N
  hist("N_AK4")->Fill(N_AK4,weight);
  for(unsigned int i = 0; i<reweight_names.size(); i++){
    std::string hist_name="N_AK4_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();
    hist(hist_name.c_str())->Fill(N_AK4, fillweight);
  }
  hist("pT_AK4_2")->Fill(AK4Jets->at(1).pt(),weight); 
  hist("eta_AK4_2")->Fill(AK4Jets->at(1).eta(),weight);

  const auto & AK4_1=event.jets->at(0); 
  const auto & AK4_2=event.jets->at(1); 
  //________________________________________________________________________special case
  ((TH2D*)hist("pT_AK4_1_vs_pT_AK4_2"))->Fill(AK4_1.pt(),AK4_2.pt(),weight);
  ((TH2D*)hist("eta_AK4_1_vs_eta_AK4_2"))->Fill(AK4_1.eta(),AK4_2.eta(),weight);

  hist("pT_AK4_12")->Fill(AK4Jets->at(1).pt(),weight);
  hist("pT_AK4_12")->Fill(AK4Jets->at(0).pt(),weight);

  hist("eta_AK4_12")->Fill(AK4Jets->at(0).eta(),weight);
  hist("eta_AK4_12")->Fill(AK4Jets->at(1).eta(),weight);

  auto detaAK4 = fabs(event.jets->at(0).eta()-event.jets->at(1).eta());

  hist("deta_AK4_12")->Fill(detaAK4,weight);
  hist("prodeta_AK4_12")->Fill(AK4Jets->at(0).eta()*AK4Jets->at(1).eta(),weight);
  //_____________________________________________________________pT_AK4_2
  for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="pT_AK4_2_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();
    hist(hist_name.c_str())->Fill((AK4Jets->at(1).pt()),fillweight);
    }
  //_____________________________________________________________eta_AK4_2
  for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="eta_AK4_2_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();
    hist(hist_name.c_str())->Fill((AK4Jets->at(1).eta()), fillweight);
    }
  //_____________________________________________________________pT_AK4_1_vs_2
    for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="pT_AK4_1_vs_pT_AK4_2_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();
    ((TH2D*)hist(hist_name.c_str()))->Fill(AK4_1.pt(), AK4_2.pt(),fillweight);
    }
  //_____________________________________________________________eta_Ak4_1vs_2
    for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="eta_AK4_1_vs_eta_AK4_2_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();
    ((TH2D*)hist(hist_name.c_str()))->Fill(AK4_1.eta(), AK4_2.eta(),fillweight);
    }
  //_____________________________________________________________pT_AK4
  for(unsigned int i=0; i<reweight_names.size(); i++){
  std::string hist_name="pT_AK4_12_"+reweight_names.at(i);
  auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();
  hist(hist_name.c_str())->Fill(AK4Jets->at(0).pt(),fillweight);
  hist(hist_name.c_str())->Fill(AK4Jets->at(1).pt(),weight);
  }
  //_____________________________________________________________eta_AK4
  for(unsigned int i=0; i<reweight_names.size(); i++){
  std::string hist_name="eta_AK4_12_"+reweight_names.at(i);
  auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();
  hist(hist_name.c_str())->Fill(AK4Jets->at(0).eta(),fillweight);
  hist(hist_name.c_str())->Fill(AK4Jets->at(1).eta(),fillweight); 
  }
  //_____________________________________________________________deta_AK4
  for(unsigned int i=0; i<reweight_names.size(); i++){
    std::string hist_name="deta_AK4_12_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();
    hist(hist_name.c_str())->Fill(detaAK4,fillweight); 
  }
  //_____________________________________________________________prodeta_AK4
  for(unsigned int i=0; i<reweight_names.size(); i++){
  std::string hist_name="prodeta_AK4_12_"+reweight_names.at(i);
  auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();
  hist(hist_name.c_str())->Fill(AK4Jets->at(0).eta()*AK4Jets->at(1).eta(),fillweight); 
  }
  
  }
  //_____________________________________________________________***************************AK8
  assert(event.topjets);
  std::vector<TopJet>* AK8Jets = event.topjets;
  auto N_AK8=AK8Jets->size();
 
  if(N_AK8 >=1){
  hist("pT_AK8_1")->Fill(AK8Jets->at(0).pt(),weight); 
  hist("eta_AK8_1")->Fill(AK8Jets->at(0).eta(),weight);
  //____________________________________________________________AK8_1_pT
    for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="pT_AK8_1_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();
    hist(hist_name.c_str())->Fill((AK8Jets->at(0).pt()),fillweight);
    }
  //____________________________________________________________AK8_1_eta
    for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="eta_AK8_1_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();

    hist(hist_name.c_str())->Fill((AK8Jets->at(0).eta()), fillweight);
    }
  }
  if(N_AK8 >= 2){
  hist("pT_AK8_2")->Fill(AK8Jets->at(1).pt(),weight); 
  hist("eta_AK8_2")->Fill(AK8Jets->at(1).eta(),weight);
  hist("pT_AK8_12")->Fill(AK8Jets->at(0).pt(),weight);
  hist("pT_AK8_12")->Fill(AK8Jets->at(1).pt(),weight);
  hist("eta_AK8_12")->Fill(AK8Jets->at(0).eta(),weight);
  hist("eta_AK8_12")->Fill(AK8Jets->at(1).eta(),weight);

  auto detaAK8 = fabs(event.topjets->at(0).eta()-event.topjets->at(1).eta());//fabs?!
  hist("deta_AK8_12")->Fill(detaAK8,weight);
  //_________________________________________
  const auto & AK8_1=event.topjets->at(0); 
  const auto & AK8_2=event.topjets->at(1);

  auto MSD1=AK8_1.softdropmass();
  auto MSD2=AK8_2.softdropmass();
  //_________________________________________
  hist("M_softdrop_1")->Fill(MSD1,weight); 
  hist("M_softdrop_2")->Fill(MSD2,weight);
  hist("M_softdrop_12")->Fill(MSD1,weight);
  hist("M_softdrop_12")->Fill(MSD2,weight);

  hist("tau21_1")->Fill(AK8_1.tau2()/AK8_1.tau1(),weight);
  hist("tau21_2")->Fill(AK8_2.tau2()/AK8_2.tau1(),weight); 
  hist("tau21_12")->Fill(AK8_1.tau2()/AK8_1.tau1(),weight);
  hist("tau21_12")->Fill(AK8_2.tau2()/AK8_2.tau1(),weight);
  //__________________________________________________________N_AK8_12
  hist("N_AK8")->Fill(N_AK8,weight);
  for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="N_AK8_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo -> originalXWGTUP();
    hist(hist_name.c_str())->Fill(N_AK8,fillweight);
  }
  //___________________________________________________________AK8_2_pT
    for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="pT_AK8_2_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo->originalXWGTUP();
    hist(hist_name.c_str())->Fill((AK8Jets->at(0).pt()),fillweight);
    }
  //___________________________________________________________AK8_2_eta
    for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="eta_AK8_2_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo->originalXWGTUP();
    hist(hist_name.c_str())->Fill((AK8Jets->at(0).eta()),fillweight);
    }
  //_________________________________________________________AK8_12_pT
    for(unsigned int i=0; i<reweight_names.size();i++){
	  std::string hist_name="pT_AK8_12_"+ reweight_names.at(i);
	  auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo->originalXWGTUP();
	  hist(hist_name.c_str())->Fill(AK8Jets->at(0).pt(), fillweight);
    hist(hist_name.c_str())->Fill(AK8Jets->at(1).pt(),fillweight);
    }
  //_________________________________________________________AK8_12_eta
    for(unsigned int i=0; i<reweight_names.size();i++){
	  std::string hist_name="eta_AK8_12_"+ reweight_names.at(i);
	  auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo->originalXWGTUP();
    //this was wrong for the previous plots! I added them like in Mjj...upsi wupsi
	  hist(hist_name.c_str())->Fill(AK8Jets->at(0).eta(),fillweight);
    hist(hist_name.c_str())->Fill(AK8Jets->at(1).eta(),fillweight);
    }
    //_______________________________________________________AK8_deta
    for(unsigned int i=0; i<reweight_names.size();i++){
      std::string hist_name="deta_AK8_12_"+ reweight_names.at(i);
      auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo->originalXWGTUP();
      hist(hist_name.c_str())->Fill(detaAK8,fillweight); //->at()))______________________Hmmm...??
    }
    //_______________________________________________________AK8_softdrop_1
    for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="M_softdrop_1_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo->originalXWGTUP();
    //No Fill(AK8Jets -> MSD1 needed: declared, linked, whatever line 218 ++ above!)
    hist(hist_name.c_str())->Fill(MSD1,fillweight);
    }
    //_______________________________________________________AK8_softdrop_2
    for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="M_softdrop_2_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo->originalXWGTUP();
    hist(hist_name.c_str())->Fill(MSD2,fillweight);
    }
    //_______________________________________________________AK8_softdrop_12
    for(unsigned int i=0; i<reweight_names.size();i++){
    std::string hist_name="M_softdrop_12_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo->originalXWGTUP();
    hist(hist_name.c_str())->Fill(MSD1,fillweight);
    hist(hist_name.c_str())->Fill(MSD2,fillweight);
    }
    //_______________________________________________________AK8_tau_1
    for(unsigned int i=0; i<reweight_names.size(); i++){
    std::string hist_name="tau21_1_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo->originalXWGTUP();
    //No Fill(AK8Jets ->  needed: AK8_2 declared, linked, whatever line 215 ++ above!)
    hist(hist_name.c_str())->Fill(AK8_1.tau2()/AK8_1.tau1(),fillweight);
    }
    //_______________________________________________________AK8_tau_2
    for(unsigned int i=0; i<reweight_names.size(); i++){
    std::string hist_name="tau21_2_"+reweight_names.at(i); 
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo->originalXWGTUP();
    hist(hist_name.c_str())->Fill(AK8_2.tau2()/AK8_2.tau1(),fillweight);
    }
    //_______________________________________________________AK8_tau_12
    for(unsigned int i=0; i<reweight_names.size(); i++){
    std::string hist_name="tau21_12_"+reweight_names.at(i);
    auto fillweight=event.weight * event.genInfo->systweights().at(i+N_pdfwgt) / event.genInfo->originalXWGTUP();
    hist(hist_name.c_str())->Fill(AK8_1.tau2()/AK8_1.tau1(),fillweight);
    hist(hist_name.c_str())->Fill(AK8_2.tau2()/AK8_2.tau1(),fillweight);
    }
  
  }

  }
   else{
    std::cout << "Not expected Number of Reweighting Points! Skipping Event for KinematicHists" << std::endl;
    std::cout << "(expected: " << N_reweight<< " - actual: "<< N_systweights-N_pdfwgt <<std::endl;
    }
  

}

aQGCVVjjhadronicKinematicsjjHists::~aQGCVVjjhadronicKinematicsjjHists(){}

std::string GetParName(std::string set, float startx, float increment,int i){
int parameter = 100*startx + i* 100 * increment;
std::string name;
if(parameter>=0){
name = std::to_string(parameter/100) + "p" + std::to_string(parameter%100);
}else{
name = "m"+std::to_string(-parameter/100) + "p" + std::to_string((-parameter)%100);
}
return set+"_"+name;
}