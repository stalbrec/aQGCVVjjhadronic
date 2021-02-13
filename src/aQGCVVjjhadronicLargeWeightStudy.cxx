#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/EventHists.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/MCLargeWeightKiller.h"
#include "UHH2/common/include/MCLargeWeightKiller.h"
#include "UHH2/aQGCVVjjhadronic/include/LargeWeightHists.h"

#define EXTRAOUT false

using namespace std;
using namespace uhh2;

namespace uhh2examples {

  /** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
   *
   * This is the central class which calls other AnalysisModules, Hists or Selection classes.
   * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
   */
  class aQGCVVjjhadronicLargeWeightStudy: public AnalysisModule {
  public:

    explicit aQGCVVjjhadronicLargeWeightStudy(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    std::string channel_;
    std::string version_;

    std::unique_ptr<CommonModules> common;
    std::unique_ptr<MCLargeWeightKiller> mcSpikeKiller;

    std::unique_ptr<Hists> h_nocuts,h_nocuts_event;
    std::unique_ptr<Hists> h_spikekiller,h_spikekiller_event;
    std::unique_ptr<Hists> h_common,h_common_event;

    bool isMC;
  };


  aQGCVVjjhadronicLargeWeightStudy::aQGCVVjjhadronicLargeWeightStudy(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.

    cout << "Hello World from aQGCVVjjhadronicLargeWeightStudy!" << endl;

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
                         2 // maximum allowed ratio of leading gen jet pT / pTHat
                         ));


    common.reset(new CommonModules());

    common->switch_jetlepcleaner(false);
    common->disable_jetpfidfilter();
    common->disable_jec();
    common->disable_jersmear();
    common->init(ctx);
    
    //INPUT
    h_nocuts_event.reset(new EventHists(ctx,"nocuts_event"));
    h_nocuts.reset(new LargeWeightHists(ctx,"nocuts"));

    h_spikekiller_event.reset(new EventHists(ctx,"spikekiller_event"));
    h_spikekiller.reset(new LargeWeightHists(ctx,"spikekiller"));

    h_common_event.reset(new EventHists(ctx,"common_event"));
    h_common.reset(new LargeWeightHists(ctx,"common"));

  }


  bool aQGCVVjjhadronicLargeWeightStudy::process(Event & event) {
    //INPUT Hists
    h_nocuts_event->fill(event);
    h_nocuts->fill(event);

    if (!event.isRealData) {
    if (!mcSpikeKiller->passes(event)) return false;
    }

    h_spikekiller_event->fill(event);
    h_spikekiller->fill(event);

    bool common_pass=common->process(event);
    if(!common_pass) return false;
    h_common_event->fill(event);
    h_common->fill(event);

    return true;
  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the aQGCVVjjhadronicLargeWeightStudy is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(aQGCVVjjhadronicLargeWeightStudy)

}
