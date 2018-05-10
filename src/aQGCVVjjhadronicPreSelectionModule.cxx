
#include <iostream>
#include <memory>
#include <string>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"

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
    class aQGCVVjjhadronicPreSelectionModule: public AnalysisModule {
    public:
    
	explicit aQGCVVjjhadronicPreSelectionModule(Context & ctx);
	virtual bool process(Event & event) override;

    private:
	std::string channel_;
	std::string version_;
    
	std::unique_ptr<CommonModules> common;
  
	std::unique_ptr<AnalysisModule> genparticle_printer; 
    
	//AK4JetCorrection MC:
	std::unique_ptr<JetCorrector> jet_corrector;
	//AK4JetCorrection Data:
	std::unique_ptr<JetCorrector> jet_corrector_BCD;
	std::unique_ptr<JetCorrector> jet_corrector_EF;
	std::unique_ptr<JetCorrector> jet_corrector_G;
	std::unique_ptr<JetCorrector> jet_corrector_H;

	//AK8JetCorrection MC:
	std::unique_ptr<TopJetCorrector> topjet_corrector;
	//AK8JetCorrection Data:
	std::unique_ptr<TopJetCorrector> topjet_corrector_BCD;
	std::unique_ptr<TopJetCorrector> topjet_corrector_EF;
	std::unique_ptr<TopJetCorrector> topjet_corrector_G;
	std::unique_ptr<TopJetCorrector> topjet_corrector_H;
    
	//AK8JetCorrection MC:  
	std::unique_ptr<SubJetCorrector> subjet_corrector;
	//AK8JetCorrection Data:     
	std::unique_ptr<SubJetCorrector> subjet_corrector_BCD;
	std::unique_ptr<SubJetCorrector> subjet_corrector_EF;
	std::unique_ptr<SubJetCorrector> subjet_corrector_G;
	std::unique_ptr<SubJetCorrector> subjet_corrector_H;

	//AK4JERSmearer 
	std::unique_ptr<JetResolutionSmearer> jetER_smearer;
	//AK8JERSmearer
	std::unique_ptr<GenericJetResolutionSmearer> topjetER_smearer;

	std::unique_ptr<JetCleaner> ak4cleaner;
	std::unique_ptr<TopJetCleaner> ak8cleaner;
    
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

	std::unique_ptr<Selection> nAK8_sel;
	std::unique_ptr<Selection> invMassAK8_sel;
	std::unique_ptr<Selection> deltaEtaAK8_sel;
    
	/////////////////////////////////////////
	/////////////////HISTS///////////////////
	/////////////////////////////////////////  
	// store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.

	//INPUT
	std::unique_ptr<Hists> h_nocuts;
	std::unique_ptr<Hists> h_AK8jets_nocuts;
	std::unique_ptr<Hists> h_AK4jets_nocuts;
   
	std::unique_ptr<Hists> h_ele_nocuts;
	std::unique_ptr<Hists> h_muon_nocuts;

	//After Cleaner
	std::unique_ptr<Hists> h_cleaner;
	std::unique_ptr<Hists> h_AK8jets_cleaner;
	std::unique_ptr<Hists> h_AK4jets_cleaner;

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


	const int runNR_BCD = 276811;
	const int runNR_EF = 278802;
	const int runNR_G = 280385;

	bool isMC;

	MuonId     MuId;
	ElectronId EleId;
    };


    aQGCVVjjhadronicPreSelectionModule::aQGCVVjjhadronicPreSelectionModule(Context & ctx){
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
    
	MuId = AndId<Muon>(MuonIDTight(), PtEtaCut(30.,2.4));
	EleId = AndId<Electron>(ElectronID_HEEP_RunII_25ns, PtEtaCut(30.,2.5));
    
	genparticle_printer.reset(new GenParticlesPrinter(ctx));

	// 1. setup other modules. CommonModules and the JetCleaner:
	common.reset(new CommonModules());
	// TODO: configure common here, e.g. by 
	//  calling common->set_*_id or common->disable_*

	//disableing pileup reweighting for now
	//common->disable_mcpileupreweight();

	common->switch_jetlepcleaner(false);
	common->change_pf_id(JetPFID::WP_LOOSE_PUPPI);
	common->disable_jersmear();
	common->disable_jec();

	if(EXTRAOUT){
		std::cout << "CommonModules set up"<<std::endl;
	}
	
	std::vector<std::string> JEC_AK4, JEC_AK8,JEC_AK4_BCD,JEC_AK4_EF,JEC_AK4_G,JEC_AK4_H,JEC_AK8_BCD,JEC_AK8_EF,JEC_AK8_G,JEC_AK8_H;
	if(isMC)
	    {
		JEC_AK4 = JERFiles::Summer16_23Sep2016_V4_L123_AK4PFPuppi_MC;
		JEC_AK8 = JERFiles::Summer16_23Sep2016_V4_L123_AK8PFPuppi_MC;
	    }
	else
	    {
		JEC_AK4_BCD =  JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK4PFPuppi_DATA;
		JEC_AK4_EF = JERFiles::Summer16_23Sep2016_V4_EF_L123_AK4PFPuppi_DATA;
		JEC_AK4_G =  JERFiles::Summer16_23Sep2016_V4_G_L123_AK4PFPuppi_DATA;
		JEC_AK4_H =  JERFiles::Summer16_23Sep2016_V4_H_L123_AK4PFPuppi_DATA;
	
		JEC_AK8_BCD =  JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK8PFPuppi_DATA;
		JEC_AK8_EF =  JERFiles::Summer16_23Sep2016_V4_EF_L123_AK8PFPuppi_DATA;
		JEC_AK8_G =  JERFiles::Summer16_23Sep2016_V4_G_L123_AK8PFPuppi_DATA;
		JEC_AK8_H =  JERFiles::Summer16_23Sep2016_V4_H_L123_AK8PFPuppi_DATA;
	    }

	if(isMC)
	    { 
		jet_corrector.reset(new JetCorrector(ctx, JEC_AK4));
		topjet_corrector.reset(new TopJetCorrector(ctx, JEC_AK8));
		subjet_corrector.reset(new SubJetCorrector(ctx,JEC_AK4));
		if(channel_=="signal")
		    {
			jetER_smearer.reset(new JetResolutionSmearer(ctx));
			if(EXTRAOUT)std::cout << "AK4jetER_smearer set up!" << std::endl;
			topjetER_smearer.reset(new GenericJetResolutionSmearer(ctx,"topjets","gentopjets",true,JERSmearing::SF_13TeV_2016,"Spring16_25nsV10_MC_PtResolution_AK8PFPuppi.txt"));
			if(EXTRAOUT)std::cout << "AK8jetER_smearer set up!" << std::endl;
		    }
	    }
	else 
	    {
		jet_corrector_BCD.reset(new JetCorrector(ctx, JEC_AK4_BCD));
		jet_corrector_EF.reset(new JetCorrector(ctx, JEC_AK4_EF));
		jet_corrector_G.reset(new JetCorrector(ctx,JEC_AK4_G ));
		jet_corrector_H.reset(new JetCorrector(ctx,JEC_AK4_H ));

		topjet_corrector_BCD.reset(new TopJetCorrector(ctx, JEC_AK8_BCD));
		topjet_corrector_EF.reset(new TopJetCorrector(ctx, JEC_AK8_EF));
		topjet_corrector_G.reset(new TopJetCorrector(ctx,JEC_AK8_G ));
		topjet_corrector_H.reset(new TopJetCorrector(ctx,JEC_AK8_H ));
	
		subjet_corrector_BCD.reset(new SubJetCorrector(ctx, JEC_AK4_BCD));
		subjet_corrector_EF.reset(new SubJetCorrector(ctx, JEC_AK4_EF));
		subjet_corrector_G.reset(new SubJetCorrector(ctx,JEC_AK4_G ));
		subjet_corrector_H.reset(new SubJetCorrector(ctx,JEC_AK4_H ));
	    }

	if(EXTRAOUT){
		std::cout << "Custom Jet-Corrections added to CommonModules"<<std::endl;
	}
	common->init(ctx);
    
    

	ak8cleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(200.0,2.5))));
	ak4cleaner.reset(new JetCleaner(ctx, 30.0, 5.0)); 

	
	

	/////////////////////////////////////////
	////////////////SELECTIONS///////////////
	/////////////////////////////////////////
    
	// 2. set up selections

	nAK8_sel.reset(new NTopJetSelection(2));
	invMassAK8_sel.reset(new invMassAK8JetSelection(1050.0f));
	deltaEtaAK8_sel.reset(new deltaEtaAk8Selection(1.3f));

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
   
	h_ele_nocuts.reset(new ElectronHists(ctx,"electron_nocuts"));
	h_muon_nocuts.reset(new MuonHists(ctx,"muon_nocuts"));

	//After Cleaner
	h_cleaner.reset(new aQGCVVjjhadronicHists(ctx,"cleaner"));
	h_AK8jets_cleaner.reset(new TopJetHists(ctx,"AK8_cleaner"));
	h_AK4jets_cleaner.reset(new JetHists(ctx,"AK4_cleaner"));

	//After N_AK8>=2 Cut
	h_AK8N2sel.reset(new aQGCVVjjhadronicHists(ctx,"AK8N2sel"));
	h_AK8jets_AK8N2sel.reset(new TopJetHists(ctx,"AK8_AK8N2sel"));
	h_AK4jets_AK8N2sel.reset(new JetHists(ctx,"AK4_AK8N2sel"));

	//After invariant Mass AK8 Cut
	h_invMAk8sel.reset(new aQGCVVjjhadronicHists(ctx,"invMAk8sel"));
	h_AK8jets_invMAk8sel.reset(new TopJetHists(ctx,"AK8_invMAk8sel"));
	h_AK4jets_invMAk8sel.reset(new JetHists(ctx,"AK4_invMAk8sel"));
	    
	//After deltaEta AK8 Cut
	h_detaAk8sel.reset(new aQGCVVjjhadronicHists(ctx,"detaAk8sel"));
	h_AK8jets_detaAk8sel.reset(new TopJetHists(ctx,"AK8_detaAk8sel"));
	h_AK4jets_detaAk8sel.reset(new JetHists(ctx,"AK4_detaAk8sel"));

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
	// if(!event.isRealData){
	//     pileup_SF->process(event);
	//     lumiweight->process(event);
	// }

	//INPUT Hists
	h_nocuts->fill(event);
	h_AK8jets_nocuts->fill(event);
	h_AK4jets_nocuts->fill(event);
	
	h_ele_nocuts->fill(event);
	h_muon_nocuts->fill(event);

	// if(version_=="MC_aQGC_WPWPjj_hadronic_newrange_genplots"){
	//     h_genparticle_nocuts->fill(event);
	// }

	if(EXTRAOUT)std::cout << "Input Hists done!"<<std::endl;	

	bool common_pass=common->process(event);
	if(!common_pass) return false;
	if(EXTRAOUT)std::cout << "common done!"<<std::endl;
	
	if(EXTRAOUT)genparticle_printer->process(event);

	// 2. test selections and fill histograms

	//cout << "#weights: " << GenInfo().weights().size() << endl;
	//cout << "#systweights: " << GenInfo().systweights().size() << endl;


	if(EXTRAOUT&&false){
	    for (const GenParticle & thisgen : *event.genparticles){
		cout << "(" << thisgen.index() << ") " << " id: " << thisgen.pdgId()<< " status: " << thisgen.status() << " m1: " << thisgen.mother1() << " m2: " << thisgen.mother2() << " d1: " << thisgen.daughter1() << " d2: " <<thisgen.daughter2() << "  pT:  " << thisgen.pt() << endl;
	    }
	}
	// h_genAK8jets_nocuts;
	// h_genAK4jets_nocuts;
	// h_gendijets_nocuts;
	// h_genparticle_nocuts;
	if(isMC){
	    if(EXTRAOUT)std::cout << "MC JEC and Smearing!"<<std::endl;	
	    topjet_corrector->process(event);
	    if(EXTRAOUT)std::cout << "MC topjet done!"<<std::endl;	
	    subjet_corrector->process(event);
	    if(EXTRAOUT)std::cout << "MC subjet done!"<<std::endl;	
	    jet_corrector->process(event);
	    if(EXTRAOUT)std::cout << "MC jet done!"<<std::endl;	
			jet_corrector->correct_met(event);
			if(EXTRAOUT)std::cout << "MC METCorrector done!"<<std::endl;	
	    if(channel_=="signal"){
				jetER_smearer->process(event);
				if(EXTRAOUT)std::cout << "MC sigjet done!"<<std::endl;	
				topjetER_smearer->process(event);
				if(EXTRAOUT)std::cout << "MC sigtopjet done!"<<std::endl;	
	    }
	}else{
	    if(event.run <= runNR_BCD){
		jet_corrector_BCD->process(event);
		topjet_corrector_BCD->process(event);
		subjet_corrector_BCD->process(event);
		jet_corrector_BCD->correct_met(event);
	    }
	    if(event.run < runNR_EF){
		jet_corrector_EF->process(event);
		topjet_corrector_EF->process(event);
		subjet_corrector_EF->process(event);
		jet_corrector_EF->correct_met(event);
	    }
	    if(event.run <= runNR_G){
		jet_corrector_G->process(event);
		topjet_corrector_G->process(event);
		subjet_corrector_G->process(event);
		jet_corrector_G->correct_met(event);
	    }
	    if(event.run > runNR_G){
		jet_corrector_H->process(event);
		topjet_corrector_H->process(event);
		subjet_corrector_H->process(event);
		jet_corrector_H->correct_met(event);
	    }
	}
	if(EXTRAOUT)std::cout << "JER/Smearer done!"<<std::endl;	
	sort_by_pt<Jet>(*event.jets);
	sort_by_pt<TopJet>(*event.topjets);
	
	ak4cleaner->process(event);
	ak8cleaner->process(event);
	if(EXTRAOUT)std::cout << "Jet Cleaner done!"<<std::endl;
	//After Cleaner Hists 
	h_cleaner->fill(event);
	h_AK8jets_cleaner->fill(event);
	h_AK4jets_cleaner->fill(event);


	//N_AK8>2 Cut
	bool nAK8_selection = nAK8_sel->passes(event);
	if(!nAK8_selection) return false;
	h_AK8N2sel->fill(event);
	h_AK8jets_AK8N2sel->fill(event);
	h_AK4jets_AK8N2sel->fill(event);
	if(EXTRAOUT)std::cout << "N_AK8 Sel done!"<<std::endl;  

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

	// // 3. decide whether or not to keep the current event in the output:
	// return njet_selection && dijet_selection;
	return true;
    }

    // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
    // make sure the aQGCVVjjhadronicPreSelectionModule is found by class name. This is ensured by this macro:
    UHH2_REGISTER_ANALYSIS_MODULE(aQGCVVjjhadronicPreSelectionModule)

}
