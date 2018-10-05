#include <iostream>
#include <memory>
#include <string>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Selection.h"

#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/MuonIds.h"
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/JetCorrections.h"
#include <UHH2/common/include/MCWeight.h>
#include "UHH2/common/include/PrintingModules.h"

#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/MuonHists.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/GenJetsHists.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicSelections.h"
#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicHists.h"
#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicMjjHists.h"
#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicUncertaintiesHists.h"
#include "UHH2/aQGCVVjjhadronic/include/VBFresonanceToWW_WTopJetHists.h"
#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicGenHists.h"

#define EXTRAOUT false

using namespace std;
using namespace uhh2;

namespace uhh2examples {

  /** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
   *
   * This is the central class which calls other AnalysisModules, Hists or Selection classes.
   * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
   */
  class aQGCVVjjhadronicUncertaintiesModule: public AnalysisModule {
  public:

    explicit aQGCVVjjhadronicUncertaintiesModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    std::string channel_;
    std::string version_;

    std::vector<std::unique_ptr<AnalysisModule>> weight_modules;
    std::unique_ptr<uhh2::AnalysisModule> MCWeightModule;
    std::unique_ptr<uhh2::AnalysisModule> MCPileupReweightModule;

    PDFWeights* m_pdfweights;
    PDFWeights* m_refpdfweights;
    TString m_pdfname;
    TString m_refpdfname;
    

    std::unique_ptr<AnalysisModule> genparticle_printer;

    //TODO
    // Data/MC scale factors
    std::unique_ptr<uhh2::AnalysisModule> pileup_SF;
    std::unique_ptr<uhh2::AnalysisModule> lumiweight;

    /////////////////////////////////////////
    ////////////////SELECTIONS///////////////
    /////////////////////////////////////////
    // declare the Selections to use. Use unique_ptr to ensure automatic call of delete in the destructor,
    // to avoid memory leaks.
    //std::unique_ptr<Selection> njet_sel, dijet_sel;

    std::unique_ptr<Selection> softdropAK8_sel;
    std::unique_ptr<Selection> tau21_sel;

    std::unique_ptr<Selection> nAK4_sel;
    std::unique_ptr<Selection> EtaSignAK4_sel;
    std::unique_ptr<Selection> deltaEtaAK4_sel;

    std::unique_ptr<Selection> invMassAK4_1p0_sel;
			
    /////////////////////////////////////////
    /////////////////HISTS///////////////////
    /////////////////////////////////////////
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.

    std::unique_ptr<Hists> h_MjjHistsVVRegion;
    std::unique_ptr<Hists> h_UncertaintiesHistsVVRegion;

    std::unique_ptr<Hists> h_MjjHistsinvMAk4sel_1p0;
    std::unique_ptr<Hists> h_UncertaintiesHistsinvMAk4sel_1p0;

    const int runNR_BCD = 276811;
    const int runNR_EF = 278802;
    const int runNR_G = 280385;
    bool isMC;
    int reweight_index_;
		
  };


  aQGCVVjjhadronicUncertaintiesModule::aQGCVVjjhadronicUncertaintiesModule(Context & ctx){
    isMC = (ctx.get("dataset_type") == "MC");
    channel_ = ctx.get("channel");
    version_ = ctx.get("dataset_version");
		
    reweight_index_ = std::stoi(version_.substr(version_.find_last_of("_")+1));
		
    // If running in SFrame, the keys "dataset_version", "dataset_type", "dataset_lumi",
    // and "target_lumi" are set to the according values in the xml file. For CMSSW, these are
    // not set automatically, but can be set in the python config file.
    for(auto & kv : ctx.get_all()){
      cout << " " << kv.first << " = " << kv.second << endl;
    }

    if(isMC){
      MCWeightModule.reset(new MCLumiWeight(ctx));
      MCPileupReweightModule.reset(new MCPileupReweight(ctx));
    }


    m_refpdfname = "NNPDF30_lo_as_0130_nf_4";
    m_refpdfweights = new PDFWeights(m_refpdfname);
    m_pdfname = "NNPDF30_lo_as_0130";
    m_pdfweights = new PDFWeights(m_pdfname);
   
    
		
    genparticle_printer.reset(new GenParticlesPrinter(ctx));

    /////////////////////////////////////////
    ////////////////SELECTIONS///////////////
    /////////////////////////////////////////


    softdropAK8_sel.reset(new VVSoftDropMassSelection(65.f,105.f));
    tau21_sel.reset(new NSubjettinessTau21Selection(0.0f,0.35f));

    nAK4_sel.reset(new NJetSelection(2));
    EtaSignAK4_sel.reset(new OppositeEtaAK4Selection());
    deltaEtaAK4_sel.reset(new deltaEtaAk4Selection(3.0f));

    invMassAK4_1p0_sel.reset(new invMassAK4JetSelection(1000.0f));
	
    if(EXTRAOUT){
      std::cout << "Selections set up" <<std::endl;
    }


    /////////////////////////////////////////
    /////////////////HISTS///////////////////
    /////////////////////////////////////////

    h_MjjHistsVVRegion.reset(new aQGCVVjjhadronicMjjHists(ctx,"MjjHists_VVRegion"));
    h_UncertaintiesHistsVVRegion.reset(new aQGCVVjjhadronicUncertaintiesHists(ctx,"UncertaintiesHists_VVRegion",reweight_index_));

    h_MjjHistsinvMAk4sel_1p0.reset(new aQGCVVjjhadronicMjjHists(ctx,"MjjHists_invMAk4sel_1p0"));
    h_UncertaintiesHistsinvMAk4sel_1p0.reset(new aQGCVVjjhadronicUncertaintiesHists(ctx,"UncertaintiesHists_invMAk4sel_1p0",reweight_index_));

    if(EXTRAOUT){
      std::cout << "Hists set up"<<std::endl;
    }

  }


  bool aQGCVVjjhadronicUncertaintiesModule::process(Event & event) {

    //cout << "aQGCVVjjhadronicUncertaintiesModule: Starting to process event (runid, eventid) = (" << event.run << ", " << event.event << "); weight = " << event.weight << endl;

    // 1. run all modules other modules.
    // if(!event.isRealData){
    //     pileup_SF->process(event);
    //     lumiweight->process(event);
    // }

    if(isMC){
      MCWeightModule->process(event);
      MCPileupReweightModule->process(event);
    }
    std::vector<double> pdf_weights = m_pdfweights->GetWeightList(event);
    std::vector<double> refpdf_weights = m_refpdfweights->GetWeightList(event);
    double new_weight = event.weight;
    // new_weight*=pdf_weights.at(0)/refpdf_weights.at(0);
    new_weight*= pdf_weights.at(0)/refpdf_weights.at(0);
    // new_weight*= event.genInfo->systweights().at(1070+9) / event.genInfo->originalXWGTUP();
    event.genInfo->set_originalXWGTUP(event.genInfo->originalXWGTUP()*(pdf_weights.at(0)/refpdf_weights.at(0)));
    // event.genInfo->set_originalXWGTUP(event.genInfo->systweights().at(1070+9));
    
    // std::cout << event.weight << "  " << new_weight << std::endl;
    event.weight=new_weight;
		
	
    if(EXTRAOUT)genparticle_printer->process(event);

    //SoftdropMass Cut
    bool softdropAK8_selection=softdropAK8_sel->passes(event);
    if(!softdropAK8_selection) return false;
    if(EXTRAOUT)std::cout << "deltaEta AK8 Cut done!"<<std::endl;

    //After nsubjettiness (tau2/tau1) AK8 Cut

    bool tau21_selection = tau21_sel->passes(event);
    if(!tau21_selection) return false;
    if(EXTRAOUT)std::cout << "nsubjettines AK8 Cut done!"<<std::endl;

    //Removing AK4 Jets with deltaR(AK4,AK8_1,2)<1.3
    std::vector<Jet>* AK4Jets(new std::vector<Jet> (*event.jets));
    std::vector<TopJet> AK8Jets = *event.topjets;

    const TopJet & AK8_0 = AK8Jets[0];
    const TopJet & AK8_1 = AK8Jets[1];

    AK4Jets->clear();
    AK4Jets->reserve(event.jets->size());

    for(const Jet AK4:*event.jets){
      double deltaR_0 = deltaR(AK4,AK8_0);
      double deltaR_1 = deltaR(AK4,AK8_1);
      if(deltaR_0 > 1.2 && deltaR_1 > 1.2) AK4Jets->push_back(AK4);
    }

    sort_by_pt<Jet>(*AK4Jets);
    event.jets->clear();
    event.jets->reserve(AK4Jets->size());
    for(const auto &  jet : *AK4Jets) event.jets->push_back(jet);
    sort_by_pt<Jet>(*event.jets);
    sort_by_pt<TopJet>(*event.topjets);

    //After deltaR(AK4,AK8) Cut
    if(EXTRAOUT)std::cout << "deltaR Selection done!"<<std::endl;


    //VBF Selection && VBFVeto
    bool nAK4_selection = nAK4_sel->passes(event);
    bool EtaSignAK4_selection = EtaSignAK4_sel->passes(event);
    bool deltaEtaAK4_selection = deltaEtaAK4_sel->passes(event);
    bool invMassAK4_1p0_selection = invMassAK4_1p0_sel->passes(event);
    bool VBFVeto=!(nAK4_selection && EtaSignAK4_selection && deltaEtaAK4_selection && invMassAK4_1p0_selection);
    // bool VBFVeto=!passes_AK4sels;
    if(VBFVeto){
      if(channel_=="signal"){
	// if(version_.find("ZZ") != std::string::npos)
	h_MjjHistsVVRegion->fill(event);
	h_UncertaintiesHistsVVRegion->fill(event);
      }
    }
    if(EXTRAOUT)std::cout << "VV done!"<<std::endl;
    //After N_AL4>2 Cut
    if(!nAK4_selection) return false;
    if(EXTRAOUT)std::cout << "N_AK4 Cut done!"<<std::endl;
    //OppositeEtaSign_Ak4 Cut
    if(!EtaSignAK4_selection) return false;
    if(EXTRAOUT)std::cout << "AK4 EtaSign Selection done!"<<std::endl;
    //After deltaEta Ak4 Cut
    if(!deltaEtaAK4_selection) return false;
    //After invariant Mass Ak4 Cut
    if(!invMassAK4_1p0_selection) return false;
    if(channel_=="signal"){
      h_MjjHistsinvMAk4sel_1p0->fill(event);
      h_UncertaintiesHistsinvMAk4sel_1p0->fill(event);
    }
    if(EXTRAOUT)std::cout << "invariant Mass AK4 Cut (1.0TeV) done!"<<std::endl;
    return true;
  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the aQGCVVjjhadronicUncertaintiesModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(aQGCVVjjhadronicUncertaintiesModule)

}
