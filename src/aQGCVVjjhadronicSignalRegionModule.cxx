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
#include <UHH2/common/include/PDFWeights.h>
#include "UHH2/common/include/PrintingModules.h"

#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/MuonHists.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/GenJetsHists.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicSelections.h"
#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicHists.h"
#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicMjjHists.h"
//___________________________________________________________________________new
#include "UHH2/aQGCVVjjhadronic/include/aQGCVVjjhadronicKinematicsjjHists.h"

#define EXTRAOUT false

using namespace std;
using namespace uhh2;

namespace uhh2examples {

  /** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
   *
   * This is the central class which calls other AnalysisModules, Hists or Selection classes.
   * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
   */
  class aQGCVVjjhadronicSignalRegionModule: public AnalysisModule {
  public:

    explicit aQGCVVjjhadronicSignalRegionModule(Context & ctx);
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

    std::shared_ptr<Selection> softdropAK8_sel;
    std::shared_ptr<Selection> tau21_sel;

    std::shared_ptr<Selection> nAK4_sel;
    std::shared_ptr<Selection> EtaSignAK4_sel;
    std::shared_ptr<Selection> deltaEtaAK4_sel;

    std::shared_ptr<Selection> invMassAK4_1p0_sel;

    // std::unique_ptr<Selection> softdropAK8_sel;
    // std::unique_ptr<Selection> tau21_sel;

    // std::unique_ptr<Selection> nAK4_sel;
    // std::unique_ptr<Selection> EtaSignAK4_sel;
    // std::unique_ptr<Selection> deltaEtaAK4_sel;

    // std::unique_ptr<Selection> invMassAK4_1p0_sel;

    AndSelection AK8_selections;
    AndSelection AK4_selections;
    /////////////////////////////////////////
    /////////////////HISTS///////////////////
    /////////////////////////////////////////
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
    std::unique_ptr<Hists> h_preselection;

    //After softdropMass AK8 Cut
    std::unique_ptr<Hists> h_softdropAK8sel;
    std::unique_ptr<Hists> h_AK8jets_softdropAK8sel;
    std::unique_ptr<Hists> h_AK4jets_softdropAK8sel;

    //After nsubjettiness (tau2/tau1) AK8 Cut
    std::unique_ptr<Hists> h_tau21sel;
    std::unique_ptr<Hists> h_AK8jets_tau21sel;
    std::unique_ptr<Hists> h_AK4jets_tau21sel;

    //After deltaR(AK4,AK8) Cut
    std::unique_ptr<Hists> h_deltaR48;
    std::unique_ptr<Hists> h_AK8jets_deltaR48;
    std::unique_ptr<Hists> h_AK4jets_deltaR48;

    //VV REGION
    std::unique_ptr<Hists> h_VVRegion;
    std::unique_ptr<Hists> h_AK8jets_VVRegion;
    std::unique_ptr<Hists> h_AK4jets_VVRegion;
    std::unique_ptr<Hists> h_MjjHistsVVRegion;

    //After N_AL4>2 Cut
    std::unique_ptr<Hists> h_AK4N2sel;
    std::unique_ptr<Hists> h_AK8jets_AK4N2sel;
    std::unique_ptr<Hists> h_AK4jets_AK4N2sel;
    //OppositeEtaSign_Ak4 Cut
    std::unique_ptr<Hists> h_OpSignsel;
    std::unique_ptr<Hists> h_AK8jets_OpSignsel;
    std::unique_ptr<Hists> h_AK4jets_OpSignsel;

    //After deltaEta Ak4 Cut
    std::unique_ptr<Hists> h_detaAk4sel;

    std::unique_ptr<Hists> h_MjjHistsdetaAk4sel;

    std::unique_ptr<Hists> h_AK8jets_detaAk4sel;
    std::unique_ptr<Hists> h_AK4jets_detaAk4sel;

    std::unique_ptr<Hists> h_ele_detaAk4sel;
    std::unique_ptr<Hists> h_muon_detaAk4sel;


    //After invariant Mass AK4 Cut 1.0TeV
    std::unique_ptr<Hists> h_invMAk4sel_1p0;

    std::unique_ptr<Hists> h_MjjHistsinvMAk4sel_1p0;


    std::unique_ptr<Hists> h_AK8jets_invMAk4sel_1p0;
    std::unique_ptr<Hists> h_AK4jets_invMAk4sel_1p0;

    std::unique_ptr<Hists> h_ele_invMAk4sel_1p0;
    std::unique_ptr<Hists> h_muon_invMAk4sel_1p0;
//_________________________________________________new
    std::unique_ptr<Hists> h_Kin_AK8;

    const int runNR_BCD = 276811;
    const int runNR_EF = 278802;
    const int runNR_G = 280385;

    bool isMC;

  };


  aQGCVVjjhadronicSignalRegionModule::aQGCVVjjhadronicSignalRegionModule(Context & ctx): AK8_selections(ctx, "AK8_selections"),AK4_selections(ctx, "AK4_selections"){
    isMC = (ctx.get("dataset_type") == "MC");
    channel_ = ctx.get("channel");
    version_ = ctx.get("dataset_version");
    // If running in SFrame, the keys "dataset_version", "dataset_type", "dataset_lumi",
    // and "target_lumi" are set to the according values in the xml file. For CMSSW, these are
    // not set automatically, but can be set in the python config file.
    for(auto & kv : ctx.get_all()){
      cout << " " << kv.first << " = " << kv.second << endl;
    }

    if(isMC){
      MCWeightModule.reset(new MCLumiWeight(ctx));
      // MCPileupReweightModule.reset(new MCPileupReweight(ctx));
      //   		m_refpdfname = "NNPDF30_lo_as_0130_nf_4";
      //   		m_refpdfweights = new PDFWeights(m_refpdfname);
      //   		m_pdfname = "NNPDF30_lo_as_0130";
      //   		m_pdfweights = new PDFWeights(m_pdfname);
		}

    genparticle_printer.reset(new GenParticlesPrinter(ctx));

    /////////////////////////////////////////
    ////////////////SELECTIONS///////////////
    /////////////////////////////////////////


    softdropAK8_sel.reset(new VVSoftDropMassSelection(65.f,105.f));
    tau21_sel.reset(new NSubjettinessTau21Selection(0.0f,0.45f));

    nAK4_sel.reset(new NJetSelection(2));
    EtaSignAK4_sel.reset(new OppositeEtaAK4Selection());
    deltaEtaAK4_sel.reset(new deltaEtaAk4Selection(3.0f));

    invMassAK4_1p0_sel.reset(new invMassAK4JetSelection(1000.0f));

    // all_selections.add<VVSoftDropMassSelection>("65GeV<MSD<105GeV",softdropAK8_sel);
    // all_selections.add<NSubjettinessTau21Selection>("0<tau21<0.45",tau21_sel);
    // all_selections.add<NJetSelection>("nAK4>=2",nAK4_sel);
    // all_selections.add<OppositeEtaAK4Selection>("eta1*eta2<0",EtaSignAK4_sel);
    // all_selections.add<deltaEtaAk4Selection>("dEta<3.0",deltaEtaAK4_sel);
    // all_selections.add<invMassAK4JetSelection>("MjjAK4>1TeV",invMassAK4_1p0_sel);

    AK8_selections.add("65 GeV<M_{SD}<105 GeV",softdropAK8_sel);
    AK8_selections.add("0<#tau_{2}/#tau_{1}<0.45",tau21_sel);
    AK4_selections.add("N_{AK4}>=2",nAK4_sel);
    AK4_selections.add("#eta_{1}*#eta_{2}<0",EtaSignAK4_sel);
    AK4_selections.add("#Delta #eta<3.0",deltaEtaAK4_sel);
    AK4_selections.add("M_{jj-AK4}>1 TeV",invMassAK4_1p0_sel);

    if(EXTRAOUT){
      std::cout << "Selections set up" <<std::endl;
    }


    /////////////////////////////////////////
    /////////////////HISTS///////////////////
    /////////////////////////////////////////

    h_preselection.reset(new aQGCVVjjhadronicHists(ctx,"preselection"));

    //SoftdropMass Cut
    h_softdropAK8sel.reset(new aQGCVVjjhadronicHists(ctx,"softdropAK8sel"));
    h_AK8jets_softdropAK8sel.reset(new TopJetHists(ctx,"AK8_softdropAK8sel"));
    h_AK4jets_softdropAK8sel.reset(new JetHists(ctx,"AK4_softdropAK8sel"));

    //After nsubjettiness (tau2/tau1) AK8 Cut
    h_tau21sel.reset(new aQGCVVjjhadronicHists(ctx,"tau21sel"));
    h_AK8jets_tau21sel.reset(new TopJetHists(ctx,"AK8_tau21sel"));
    h_AK4jets_tau21sel.reset(new JetHists(ctx,"AK4_tau21sel"));

    //After deltaR(AK4,AK8) Cut
    h_deltaR48.reset(new aQGCVVjjhadronicHists(ctx,"deltaR48"));
    h_AK8jets_deltaR48.reset(new TopJetHists(ctx,"AK8_deltaR48"));
    h_AK4jets_deltaR48.reset(new JetHists(ctx,"AK4_deltaR48"));

    //VV REGION
    h_VVRegion.reset(new aQGCVVjjhadronicHists(ctx,"VVRegion"));
    h_AK8jets_VVRegion.reset(new TopJetHists(ctx,"AK8_VVRegion"));
    h_AK4jets_VVRegion.reset(new JetHists(ctx,"AK4_VVRegion"));
    h_MjjHistsVVRegion.reset(new aQGCVVjjhadronicMjjHists(ctx,"MjjHists_VVRegion"));

    //After N_AL4>2 Cut
    h_AK4N2sel.reset(new aQGCVVjjhadronicHists(ctx,"AK4N2sel"));
    h_AK8jets_AK4N2sel.reset(new TopJetHists(ctx,"AK8_AK4N2sel"));
    h_AK4jets_AK4N2sel.reset(new JetHists(ctx,"AK4_AK4N2sel"));

    //OppositeEtaSign_Ak4 Cut
    h_OpSignsel.reset(new aQGCVVjjhadronicHists(ctx,"OpSignsel"));
    h_AK8jets_OpSignsel.reset(new TopJetHists(ctx,"AK8_OpSignsel"));
    h_AK4jets_OpSignsel.reset(new JetHists(ctx,"AK4_OpSignsel"));

    //After deltaEta Ak4 Cut
    h_detaAk4sel.reset(new aQGCVVjjhadronicHists(ctx,"detaAk4sel"));

    h_MjjHistsdetaAk4sel.reset(new aQGCVVjjhadronicMjjHists(ctx,"MjjHists_detaAk4sel"));


    h_AK8jets_detaAk4sel.reset(new TopJetHists(ctx,"AK8_detaAk4sel"));
    h_AK4jets_detaAk4sel.reset(new JetHists(ctx,"AK4_detaAk4sel"));

    h_ele_detaAk4sel.reset(new ElectronHists(ctx,"electron_detaAk4sel"));
    h_muon_detaAk4sel.reset(new MuonHists(ctx,"muon_detaAk4sel"));

    //After invariant Mass AK4 Cut 1.0TeV
    h_invMAk4sel_1p0.reset(new aQGCVVjjhadronicHists(ctx,"invMAk4sel_1p0"));

    h_MjjHistsinvMAk4sel_1p0.reset(new aQGCVVjjhadronicMjjHists(ctx,"MjjHists_invMAk4sel_1p0"));
//whats the difference between MjjHists and AK_invMass ?
    h_AK8jets_invMAk4sel_1p0.reset(new TopJetHists(ctx,"AK8_invMAk4sel_1p0"));
    h_AK4jets_invMAk4sel_1p0.reset(new JetHists(ctx,"AK4_invMAk4sel_1p0"));

    h_ele_invMAk4sel_1p0.reset(new ElectronHists(ctx,"electron_invMAk4sel_1p0"));
    h_muon_invMAk4sel_1p0.reset(new MuonHists(ctx,"muon_invMAk4sel_1p0"));
//_____________________________________________________________________1stTry
    h_Kin_AK8.reset(new aQGCVVjjhadronicKinematicsjjHists(ctx, "Kin_AK8"));


    if(EXTRAOUT){
      std::cout << "Hists set up"<<std::endl;
    }

  }


  bool aQGCVVjjhadronicSignalRegionModule::process(Event & event) {

    //cout << "aQGCVVjjhadronicSignalRegionModule: Starting to process event (runid, eventid) = (" << event.run << ", " << event.event << "); weight = " << event.weight << endl;

    // 1. run all modules other modules.
    // if(!event.isRealData){
    //     pileup_SF->process(event);
    //     lumiweight->process(event);
    // }

    if(isMC){
      MCWeightModule->process(event);
      // MCPileupReweightModule->process(event);
      //   		if(version_.find("hadronic") != std::string::npos){
      //   			std::vector<double> pdf_weights = m_pdfweights->GetWeightList(event);
      //   			std::vector<double> refpdf_weights = m_refpdfweights->GetWeightList(event);
      //   			double new_weight = event.weight;
      //   			new_weight*= pdf_weights.at(0)/refpdf_weights.at(0);
      //   			event.genInfo->set_originalXWGTUP(event.genInfo->originalXWGTUP()*(pdf_weights.at(0)/refpdf_weights.at(0)));
      //   			event.weight=new_weight;
      //   		}
		}

    h_preselection->fill(event);

    bool passes_AK8sels=AK8_selections.passes(event);

    if(EXTRAOUT)genparticle_printer->process(event);

    //SoftdropMass Cut
    bool softdropAK8_selection=softdropAK8_sel->passes(event);
    if(!softdropAK8_selection) return false;
    h_softdropAK8sel->fill(event);
    h_AK8jets_softdropAK8sel->fill(event);
    h_AK4jets_softdropAK8sel->fill(event);
    if(EXTRAOUT)std::cout << "deltaEta AK8 Cut done!"<<std::endl;

    //After nsubjettiness (tau2/tau1) AK8 Cut

    bool tau21_selection = tau21_sel->passes(event);
    if(!tau21_selection) return false;
    h_tau21sel->fill(event);
    h_AK8jets_tau21sel->fill(event);
    h_AK4jets_tau21sel->fill(event);
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

    h_deltaR48->fill(event);
    h_AK8jets_deltaR48->fill(event);
    h_AK4jets_deltaR48->fill(event);
    if(EXTRAOUT)std::cout << "deltaR Selection done!"<<std::endl;

    bool passes_AK4sels=AK4_selections.passes(event);

    //VBF Selection && VBFVeto
    bool nAK4_selection = nAK4_sel->passes(event);
    bool EtaSignAK4_selection = EtaSignAK4_sel->passes(event);
    bool deltaEtaAK4_selection = deltaEtaAK4_sel->passes(event);
    bool invMassAK4_1p0_selection = invMassAK4_1p0_sel->passes(event);

    // bool VBFVeto=!(nAK4_selection && EtaSignAK4_selection && deltaEtaAK4_selection && invMassAK4_1p0_selection);
    bool VBFVeto=!passes_AK4sels;

    if(VBFVeto){
      h_VVRegion->fill(event);
      h_AK8jets_VVRegion->fill(event);
      h_AK4jets_VVRegion->fill(event);
      if(channel_=="signal"){
	// if(version_.find("ZZ") != std::string::npos)
	h_MjjHistsVVRegion->fill(event);
      }
    }
    if(EXTRAOUT)std::cout << "VV done!"<<std::endl;


    //After N_AL4>2 Cut
    if(!nAK4_selection) return false;
    h_AK4N2sel->fill(event);
    h_AK8jets_AK4N2sel->fill(event);
    h_AK4jets_AK4N2sel->fill(event);
    if(EXTRAOUT)std::cout << "N_AK4 Cut done!"<<std::endl;

    //OppositeEtaSign_Ak4 Cut
    // if(!EtaSignAK4_selection) return false;
    h_OpSignsel->fill(event);
    h_AK8jets_OpSignsel->fill(event);
    h_AK4jets_OpSignsel->fill(event);
    if(EXTRAOUT)std::cout << "AK4 EtaSign Selection done!"<<std::endl;

    //After deltaEta Ak4 Cut
    if(!deltaEtaAK4_selection) return false;
    h_detaAk4sel->fill(event);
    if(channel_=="signal"){
      h_MjjHistsdetaAk4sel->fill(event);
    }
    h_AK8jets_detaAk4sel->fill(event);
    h_AK4jets_detaAk4sel->fill(event);

    h_ele_detaAk4sel->fill(event);
    h_muon_detaAk4sel->fill(event);
    if(EXTRAOUT)std::cout << "deltaEta AK4 Cut done!"<<std::endl;


    //After invariant Mass Ak4 Cut
    if(!invMassAK4_1p0_selection) return false;
    h_invMAk4sel_1p0->fill(event);
    if(channel_=="signal"){
      h_MjjHistsinvMAk4sel_1p0->fill(event);
    //________________________________________new
      h_Kin_AK8->fill(event);
    }
    //somethings missing here ?.
  //  h_Kin_AK8->fill(event);
    //______________________________________I am so proud if it works now...sad story..maybe now
    h_AK8jets_invMAk4sel_1p0->fill(event);
    h_AK4jets_invMAk4sel_1p0->fill(event);

    h_ele_invMAk4sel_1p0->fill(event);
    h_muon_invMAk4sel_1p0->fill(event);
    if(EXTRAOUT)std::cout << "invariant Mass AK4 Cut (1.0TeV) done!"<<std::endl;


    return true;
  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the aQGCVVjjhadronicSignalRegionModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(aQGCVVjjhadronicSignalRegionModule)

}
