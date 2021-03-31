#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"

#include "UHH2/aQGCVVjjhadronic/include/FlatTreeWriter.h"

#define EXTRAOUT false

using namespace std;
using namespace uhh2;

namespace uhh2examples {
  class aQGCVVjjhadronicFlatTreesModule: public AnalysisModule {
  public:
    explicit aQGCVVjjhadronicFlatTreesModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    std::string channel_;
    std::string version_;
    std::unique_ptr<CommonModules> common;
    std::unique_ptr<AnalysisModule> writer;
    bool isMC;
  };


  aQGCVVjjhadronicFlatTreesModule::aQGCVVjjhadronicFlatTreesModule(Context & ctx){
    isMC = (ctx.get("dataset_type") == "MC");
    channel_ = ctx.get("channel");
    version_ = ctx.get("dataset_version");
    

    common.reset(new CommonModules());
    common->switch_jetlepcleaner(false);
    common->disable_jetpfidfilter();
    common->disable_jec();
    common->disable_jersmear();
    common->disable_lumisel();
    common->disable_metfilters();
    common->disable_pvfilter();
    common->disable_jetpfidfilter();
    common->init(ctx);


    writer.reset(new FlatTreeWriter(ctx));
  }


  bool aQGCVVjjhadronicFlatTreesModule::process(Event & event) {
    bool common_success = common->process(event);
    // if(!common_success) return false;

    assert(event.genparticles);
    if(event.genparticles->size() == 0) return false;
    assert(event.gentopjets);
    if(event.gentopjets->size() < 2) return false;
    if((event.gentopjets->at(0).v4()+event.gentopjets->at(1).v4()).M())
    assert(event.genjets);
    if(event.genjets->size() < 2) return false;

    assert(event.topjets);
    // if(event.topjets->size() == 0) return false;
    assert(event.jets);
    // if(event.jets->size() == 0) return false;
    
    writer->process(event);

    return true;
  }
  UHH2_REGISTER_ANALYSIS_MODULE(aQGCVVjjhadronicFlatTreesModule)
}
