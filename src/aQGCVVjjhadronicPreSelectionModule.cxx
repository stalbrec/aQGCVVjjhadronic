#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

#include "UHH2/common/include/MCLargeWeightKiller.h"
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"

#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
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

#define EXTRAOUT false

using namespace std;
using namespace uhh2;

namespace uhh2examples {

  /** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
   *
   * This is the central class which calls other AnalysisModules, Hists or Selection classes.
   * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
   */
  class aQGCVVjjhadronicPreSelectionModule: public AnalysisModule {
  public:

    explicit aQGCVVjjhadronicPreSelectionModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    std::string channel_;
    std::string version_;

    Event::Handle<vector<Jet>> h_IdCriteriaJets;

    std::unique_ptr<CommonModules> common;
    PDFWeights* m_pdfweights;
    PDFWeights* m_refpdfweights;
    TString m_pdfname;
    TString m_refpdfname;
    std::unique_ptr<AnalysisModule> genparticle_printer;


    std::unique_ptr<YearSwitcher> AK4_JEC_MC,AK8_JEC_MC;
    std::unique_ptr<YearSwitcher> AK4_JEC_data,AK8_JEC_data;
    std::shared_ptr<RunSwitcher> AK4_JEC_Switcher_16,AK4_JEC_Switcher_17,AK4_JEC_Switcher_18;
    std::shared_ptr<RunSwitcher> AK8_JEC_Switcher_16,AK8_JEC_Switcher_17,AK8_JEC_Switcher_18;

    std::unique_ptr<YearSwitcher> jet_corrector_MC, jet_corrector_data;
    std::shared_ptr<RunSwitcher> jec_switcher_16, jec_switcher_17, jec_switcher_18;
    std::unique_ptr<GenericJetResolutionSmearer> AK8_jet_smearer;
    std::unique_ptr<JetResolutionSmearer> AK4_jet_smearer;


    std::unique_ptr<JetCleaner> ak4cleaner;
    std::unique_ptr<TopJetCleaner> ak8cleaner;
    std::unique_ptr<JetCleaner> ak4pfidfilter;
    std::unique_ptr<TopJetCleaner> ak8pfidfilter;

    std::unique_ptr<AnalysisModule> massCalcCorr;
    //TODO
    std::unique_ptr<MCLargeWeightKiller> mcSpikeKiller;
    // Data/MC scale factors

    /////////////////////////////////////////
    ////////////////SELECTIONS///////////////
    /////////////////////////////////////////
    // declare the Selections to use. Use unique_ptr to ensure automatic call of delete in the destructor,
    // to avoid memory leaks.
    //std::unique_ptr<Selection> njet_sel, dijet_sel;
    std::unique_ptr<Selection> muon_sel, electron_sel;//lepton veto

    std::shared_ptr<Selection> nAK8_sel;
    std::shared_ptr<Selection> invMassAK8_sel;
    std::shared_ptr<Selection> deltaEtaAK8_sel;


    AndSelection cutflow_selections;
    /////////////////////////////////////////
    /////////////////HISTS///////////////////
    /////////////////////////////////////////
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.

    //INPUT
    std::unique_ptr<Hists> h_nocuts;
    std::unique_ptr<Hists> h_AK8jets_nocuts;
    std::unique_ptr<Hists> h_AK4jets_nocuts;

    std::unique_ptr<Hists> h_common;

    std::unique_ptr<Hists> h_corrections;

    //After Cleaner
    std::unique_ptr<Hists> h_cleaner;
    std::unique_ptr<Hists> h_AK8jets_cleaner;
    std::unique_ptr<Hists> h_AK4jets_cleaner;

    std::unique_ptr<Hists> h_softdropmassCorr;

    std::unique_ptr<Hists> h_AK4pfidfilter;
    std::unique_ptr<Hists> h_AK8pfidfilter;

    //After N_AK8>2 Cut
    std::unique_ptr<Hists> h_AK8N2sel;
    std::unique_ptr<Hists> h_AK8jets_AK8N2sel;
    std::unique_ptr<Hists> h_AK4jets_AK8N2sel;

    //After invariant Mass AK8 Cut
    std::unique_ptr<Hists> h_invMAk8sel;
    std::unique_ptr<Hists> h_AK8jets_invMAk8sel;
    std::unique_ptr<Hists> h_AK4jets_invMAk8sel;

    //After deltaEta AK8 Cut
    std::unique_ptr<Hists> h_detaAk8sel;
    std::unique_ptr<Hists> h_AK8jets_detaAk8sel;
    std::unique_ptr<Hists> h_AK4jets_detaAk8sel;

    bool isMC;

    JetId AK4PFID;
    TopJetId AK8PFID;
  };


  aQGCVVjjhadronicPreSelectionModule::aQGCVVjjhadronicPreSelectionModule(Context & ctx): cutflow_selections(ctx,"cutflow_selections"){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.

    cout << "Hello World from aQGCVVjjhadronicPreSelectionModule!" << endl;

    // If needed, access the configuration of the module here, e.g.:
    string testvalue = ctx.get("TestKey", "<not set>");
    cout << "TestKey in the configuration was: " << testvalue << endl;

    //MetaData from XML:
    isMC = (ctx.get("dataset_type") == "MC");
    channel_ = ctx.get("channel");
    version_ = ctx.get("dataset_version");
    // If running in SFrame, the keys "dataset_version", "dataset_type", "dataset_lumi",
    // and "target_lumi" are set to the according values in the xml file. For CMSSW, these are
    // not set automatically, but can be set in the python config file.
    for(auto & kv : ctx.get_all()){
      cout << " " << kv.first << " = " << kv.second << endl;
    }

   mcSpikeKiller.reset(new MCLargeWeightKiller(
                         ctx,
                         1.1, // maximum allowed ratio of leading reco jet pT / generator HT
                         2, // maximum allowed ratio of leading gen jet pT / generator HT
                         infinity, // maximum allowed ratio of leading reco jet pT / Q scale
                         2, // maximum allowed ratio of PU maximum pTHat / gen HT (ensures scale of PU < scale of hard interaction)
                         2, // maximum allowed ratio of leading reco jet pT / pTHat
                         2, // maximum allowed ratio of leading gen jet pT / pTHat
                         "jetsAk8Puppi",
                         "slimmedGenJetsAK8"
                         ));
   
    h_IdCriteriaJets = ctx.get_handle<vector<Jet>>("jetsAk8Puppi");

    genparticle_printer.reset(new GenParticlesPrinter(ctx));

    // 1. setup other modules. CommonModules and the JetCleaner:
    common.reset(new CommonModules());
    // TODO: configure common here, e.g. by
    //  calling common->set_*_id or common->disable_*

    common->switch_jetlepcleaner(false);
    common->disable_jetpfidfilter();

    //disable jec/jer for ak4 in common modules since we do it manually for both ak4 and ak8 below
    common->disable_jec();
    common->disable_jersmear();

    if(EXTRAOUT){
      std::cout << "CommonModules set up"<<std::endl;
    }

    const std::string JEC_tag_2016="Summer16_07Aug2017";
    const std::string JEC_version_2016="11";
    const std::string JEC_tag_2017="Fall17_17Nov2017";
    const std::string JEC_version_2017="32";
    const std::string JEC_tag_2018="Autumn18";
    const std::string JEC_version_2018="8";
    const std::string AK4_jetcoll="AK4PFPuppi";
    const std::string AK8_jetcoll="AK8PFPuppi";

    if(isMC){
      AK4_JEC_MC.reset(new YearSwitcher(ctx));
      AK4_JEC_MC->setup2016(std::make_shared<JetCorrector>(ctx, JERFiles::JECFilesMC(JEC_tag_2016, JEC_version_2016, AK4_jetcoll)));
      AK4_JEC_MC->setup2017(std::make_shared<JetCorrector>(ctx, JERFiles::JECFilesMC(JEC_tag_2017, JEC_version_2017, AK4_jetcoll)));
      AK4_JEC_MC->setup2018(std::make_shared<JetCorrector>(ctx, JERFiles::JECFilesMC(JEC_tag_2018, JEC_version_2018, AK4_jetcoll)));

      AK8_JEC_MC.reset(new YearSwitcher(ctx));
      AK8_JEC_MC->setup2016(std::make_shared<TopJetCorrector>(ctx, JERFiles::JECFilesMC(JEC_tag_2016, JEC_version_2016, AK8_jetcoll)));
      AK8_JEC_MC->setup2017(std::make_shared<TopJetCorrector>(ctx, JERFiles::JECFilesMC(JEC_tag_2017, JEC_version_2017, AK8_jetcoll)));
      AK8_JEC_MC->setup2018(std::make_shared<TopJetCorrector>(ctx, JERFiles::JECFilesMC(JEC_tag_2018, JEC_version_2018, AK8_jetcoll)));


      const JERSmearing::SFtype1 AK8_JER_sf=JERSmearing::SF_13TeV_Summer16_25nsV1;
      const TString resFilename="2016/Summer16_25nsV1_MC_PtResolution_AK8PFPuppi.txt";
      AK4_jet_smearer.reset(new JetResolutionSmearer(ctx));
      if(EXTRAOUT)std::cout << "AK4jetER_smearer set up!" << std::endl;
      AK8_jet_smearer.reset(new GenericJetResolutionSmearer(ctx, "topjets","gentopjets", AK8_JER_sf, resFilename));
      if(EXTRAOUT)std::cout << "AK8jetER_smearer set up!" << std::endl;
    }else{
      AK4_JEC_Switcher_16.reset(new RunSwitcher(ctx, "2016"));
      for (const auto & runItr : runPeriods2016) {
        AK4_JEC_Switcher_16->setupRun(runItr, std::make_shared<JetCorrector>(ctx, JERFiles::JECFilesDATA(JEC_tag_2016, JEC_version_2016, AK4_jetcoll, runItr)));
      }

      AK4_JEC_Switcher_17.reset(new RunSwitcher(ctx, "2017"));
      for (const auto & runItr : runPeriods2017) {
        AK4_JEC_Switcher_17->setupRun(runItr, std::make_shared<JetCorrector>(ctx, JERFiles::JECFilesDATA(JEC_tag_2017, JEC_version_2017, AK4_jetcoll, runItr)));
      }

      AK4_JEC_Switcher_18.reset(new RunSwitcher(ctx, "2018"));
      for (const auto & runItr : runPeriods2018) {
        AK4_JEC_Switcher_18->setupRun(runItr, std::make_shared<JetCorrector>(ctx, JERFiles::JECFilesDATA(JEC_tag_2018, JEC_version_2018, AK4_jetcoll, runItr)));
      }

      AK4_JEC_data.reset(new YearSwitcher(ctx));
      AK4_JEC_data->setup2016(AK4_JEC_Switcher_16);
      AK4_JEC_data->setup2017(AK4_JEC_Switcher_17);
      AK4_JEC_data->setup2018(AK4_JEC_Switcher_18);

      AK8_JEC_Switcher_16.reset(new RunSwitcher(ctx, "2016"));
      for (const auto & runItr : runPeriods2016) {
        AK8_JEC_Switcher_16->setupRun(runItr, std::make_shared<TopJetCorrector>(ctx, JERFiles::JECFilesDATA(JEC_tag_2016, JEC_version_2016, AK8_jetcoll, runItr)));
      }

      AK8_JEC_Switcher_17.reset(new RunSwitcher(ctx, "2017"));
      for (const auto & runItr : runPeriods2017) {
        AK8_JEC_Switcher_17->setupRun(runItr, std::make_shared<TopJetCorrector>(ctx, JERFiles::JECFilesDATA(JEC_tag_2017, JEC_version_2017, AK8_jetcoll, runItr)));
      }

      AK8_JEC_Switcher_18.reset(new RunSwitcher(ctx, "2018"));
      for (const auto & runItr : runPeriods2018) {
        AK8_JEC_Switcher_18->setupRun(runItr, std::make_shared<TopJetCorrector>(ctx, JERFiles::JECFilesDATA(JEC_tag_2018, JEC_version_2018, AK8_jetcoll, runItr)));
      }

      AK8_JEC_data.reset(new YearSwitcher(ctx));
      AK8_JEC_data->setup2016(AK8_JEC_Switcher_16);
      AK8_JEC_data->setup2017(AK8_JEC_Switcher_17);
      AK8_JEC_data->setup2018(AK8_JEC_Switcher_18);
    }

    if(EXTRAOUT){
      std::cout << "Custom Jet-Corrections setup"<<std::endl;
    }
    common->init(ctx);

    ak8cleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(200.0,2.5))));
    ak4cleaner.reset(new JetCleaner(ctx, 30.0, 5.0));


    AK4PFID=JetPFID(JetPFID::WP_LOOSE_PUPPI);
    AK8PFID=JetPFID(JetPFID::WP_LOOSE_PUPPI);


    ak8pfidfilter.reset(new TopJetCleaner(ctx,AK8PFID));
    ak4pfidfilter.reset(new JetCleaner(ctx,AK4PFID));

    massCalcCorr.reset(new SoftDropMassCalculator(ctx, true, "common/data/2016/puppiCorr.root"));


    /////////////////////////////////////////
    ////////////////SELECTIONS///////////////
    /////////////////////////////////////////

    // 2. set up selections

    invMassAK8_sel.reset(new invMassAK8JetSelection(1050.0f));
    deltaEtaAK8_sel.reset(new deltaEtaAk8Selection(1.3f));
    nAK8_sel.reset(new NTopJetSelection(2));

    cutflow_selections.add("M_{jj-AK8}>1050 GeV",invMassAK8_sel);
    cutflow_selections.add("#Delta#eta<1.3",deltaEtaAK8_sel);
    cutflow_selections.add("N_{AK8}>2",nAK8_sel);

    if(EXTRAOUT){
      std::cout << "Selections set up" <<std::endl;
    }


    /////////////////////////////////////////
    /////////////////HISTS///////////////////
    /////////////////////////////////////////
    // 3. Set up Hists classes:

    //INPUT
    h_nocuts.reset(new aQGCVVjjhadronicHists(ctx,"nocuts"));
    h_AK8jets_nocuts.reset(new TopJetHists(ctx,"AK8_nocuts"));
    h_AK4jets_nocuts.reset(new JetHists(ctx,"AK4_nocuts"));

    h_common.reset(new aQGCVVjjhadronicHists(ctx,"common"));

    h_corrections.reset(new aQGCVVjjhadronicHists(ctx,"corrections"));

    //After Cleaner
    h_cleaner.reset(new aQGCVVjjhadronicHists(ctx,"cleaner"));
    h_AK8jets_cleaner.reset(new TopJetHists(ctx,"AK8_cleaner"));
    h_AK4jets_cleaner.reset(new JetHists(ctx,"AK4_cleaner"));

    h_softdropmassCorr.reset(new aQGCVVjjhadronicHists(ctx,"softdropmassCorr"));

    h_AK4pfidfilter.reset(new aQGCVVjjhadronicHists(ctx,"AK4pfidfilter"));
    h_AK8pfidfilter.reset(new aQGCVVjjhadronicHists(ctx,"AK8pfidfilter"));


    //After invariant Mass AK8 Cut
    h_invMAk8sel.reset(new aQGCVVjjhadronicHists(ctx,"invMAk8sel"));
    h_AK8jets_invMAk8sel.reset(new TopJetHists(ctx,"AK8_invMAk8sel"));
    h_AK4jets_invMAk8sel.reset(new JetHists(ctx,"AK4_invMAk8sel"));

    //After deltaEta AK8 Cut
    h_detaAk8sel.reset(new aQGCVVjjhadronicHists(ctx,"detaAk8sel"));
    h_AK8jets_detaAk8sel.reset(new TopJetHists(ctx,"AK8_detaAk8sel"));
    h_AK4jets_detaAk8sel.reset(new JetHists(ctx,"AK4_detaAk8sel"));

    //After N_AK8>=2 Cut
    h_AK8N2sel.reset(new aQGCVVjjhadronicHists(ctx,"AK8N2sel"));
    h_AK8jets_AK8N2sel.reset(new TopJetHists(ctx,"AK8_AK8N2sel"));
    h_AK4jets_AK8N2sel.reset(new JetHists(ctx,"AK4_AK8N2sel"));

    if(EXTRAOUT){
      std::cout << "Hists set up"<<std::endl;
    }

  }


  bool aQGCVVjjhadronicPreSelectionModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.

    //cout << "aQGCVVjjhadronicPreSelectionModule: Starting to process event (runid, eventid) = (" << event.run << ", " << event.event << "); weight = " << event.weight << endl;

    // 1. run all modules other modules.
    vector<Jet> IdCriteriaJets = event.get(h_IdCriteriaJets);
    if (!event.isRealData) {
    if (!mcSpikeKiller->passes(event)) return false;
    }
    std::vector<int> skipindex;
    for(unsigned int i=0;i<event.topjets->size();i++){
      int N_Daughters = event.topjets->at(i).numberOfDaughters();
      float nEMFrac = event.topjets->at(i).neutralEmEnergyFraction();
      float nHFrac = event.topjets->at(i).neutralHadronEnergyFraction();
      float chEMFrac = event.topjets->at(i).chargedEmEnergyFraction();
      float chHFrac = event.topjets->at(i).chargedHadronEnergyFraction();
      float chMulti = event.topjets->at(i).chargedMultiplicity();

      double deltaR_min=99999.;
      int nearest_index=0;
      for(unsigned int j=0;j<IdCriteriaJets.size();j++){
	if(std::find(skipindex.begin(),skipindex.end(),j) != skipindex.end()) continue;
	double deltaR_candiate=deltaR(IdCriteriaJets.at(j),event.topjets->at(i));
	if(deltaR_candiate<deltaR_min){
	  deltaR_min = deltaR_candiate;
	  nearest_index=j;
	}
	skipindex.push_back(nearest_index);
	N_Daughters = IdCriteriaJets.at(nearest_index).numberOfDaughters();
	nEMFrac = IdCriteriaJets.at(nearest_index).neutralEmEnergyFraction();
	nHFrac = IdCriteriaJets.at(nearest_index).neutralHadronEnergyFraction();
	chEMFrac = IdCriteriaJets.at(nearest_index).chargedEmEnergyFraction();
	chHFrac =IdCriteriaJets.at(nearest_index).chargedHadronEnergyFraction();
	chMulti = IdCriteriaJets.at(nearest_index).chargedMultiplicity();
      }
      event.topjets->at(i).set_numberOfDaughters(N_Daughters);
      event.topjets->at(i).set_neutralEmEnergyFraction(nEMFrac);
      event.topjets->at(i).set_neutralHadronEnergyFraction(nHFrac);
      event.topjets->at(i).set_chargedEmEnergyFraction(chEMFrac);
      event.topjets->at(i).set_chargedHadronEnergyFraction(chHFrac);
      event.topjets->at(i).set_chargedMultiplicity(chMulti);
    }

 
    //INPUT Hists
    h_nocuts->fill(event);
    h_AK8jets_nocuts->fill(event);
    h_AK4jets_nocuts->fill(event);

    if(EXTRAOUT)std::cout << "Input Hists done!"<<std::endl;

    bool common_pass=common->process(event);
    if(!common_pass) return false;
    h_common->fill(event);
    if(EXTRAOUT)std::cout << "common done!"<<std::endl;

    if(EXTRAOUT)genparticle_printer->process(event);



    if(EXTRAOUT&&false){
      for (const GenParticle & thisgen : *event.genparticles){
	cout << "(" << thisgen.index() << ") " << " id: " << thisgen.pdgId()<< " status: " << thisgen.status() << " m1: " << thisgen.mother1() << " m2: " << thisgen.mother2() << " d1: " << thisgen.daughter1() << " d2: " <<thisgen.daughter2() << "  pT:  " << thisgen.pt() << endl;
      }
    }


    if(isMC){
      AK4_JEC_MC->process(event);
      AK8_JEC_MC->process(event);
      AK4_jet_smearer->process(event);
      AK8_jet_smearer->process(event);
    }else{
      AK4_JEC_data->process(event);
      AK8_JEC_data->process(event);
    }
    if(EXTRAOUT)std::cout << "JEC/JER done!"<<std::endl;
    sort_by_pt<Jet>(*event.jets);
    sort_by_pt<TopJet>(*event.topjets);

    h_corrections->fill(event);


    ak4cleaner->process(event);
    ak8cleaner->process(event);
    if(EXTRAOUT)std::cout << "Jet Cleaner done!"<<std::endl;
    //After Cleaner Hists
    h_cleaner->fill(event);
    h_AK8jets_cleaner->fill(event);
    h_AK4jets_cleaner->fill(event);

    massCalcCorr->process(event);
    h_softdropmassCorr->fill(event);

    ak4pfidfilter->process(event);
    h_AK4pfidfilter->fill(event);

    ak8pfidfilter->process(event);
    h_AK8pfidfilter->fill(event);



    //After invariant Mass AK8 Cut
    bool invMassAK8_selection = invMassAK8_sel->passes(event);
    if(!invMassAK8_selection) return false;
    h_invMAk8sel->fill(event);
    h_AK8jets_invMAk8sel->fill(event);
    h_AK4jets_invMAk8sel->fill(event);
    if(EXTRAOUT)std::cout << "invMass Cut done!"<<std::endl;

    //After deltaEta AK8 Cut
    bool deltaEtaAK8_selection = deltaEtaAK8_sel->passes(event);
    if(!deltaEtaAK8_selection) return false;
    h_detaAk8sel->fill(event);
    h_AK8jets_detaAk8sel->fill(event);
    h_AK4jets_detaAk8sel->fill(event);
    if(EXTRAOUT)std::cout << "deltaEta AK8 Cut done!"<<std::endl;

		//N_AK8>2 Cut
    bool nAK8_selection = nAK8_sel->passes(event);
    if(!nAK8_selection) return false;
    h_AK8N2sel->fill(event);
    h_AK8jets_AK8N2sel->fill(event);
    h_AK4jets_AK8N2sel->fill(event);
    if(EXTRAOUT)std::cout << "N_AK8 Sel done!"<<std::endl;

    // // 3. decide whether or not to keep the current event in the output:
    // return njet_selection && dijet_selection;
    return true;
  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the aQGCVVjjhadronicPreSelectionModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(aQGCVVjjhadronicPreSelectionModule)

}
