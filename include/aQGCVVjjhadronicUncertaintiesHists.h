#pragma once

#include "UHH2/core/include/Hists.h"
#include <string>
namespace uhh2examples {

  /**  \brief Example class for booking and filling histograms
   * 
   * NOTE: This class uses the 'hist' method to retrieve histograms.
   * This requires a string lookup and is therefore slow if you have
   * many histograms. Therefore, it is recommended to use histogram
   * pointers as member data instead, like in 'common/include/ElectronHists.h'.
   */
  class aQGCVVjjhadronicUncertaintiesHists: public uhh2::Hists {
  public:
    // use the same constructor arguments as Hists for forwarding:
    aQGCVVjjhadronicUncertaintiesHists(uhh2::Context & ctx, const std::string & dirname,const int parameter_index_);

    virtual void fill(const uhh2::Event & ev) override;
    virtual ~aQGCVVjjhadronicUncertaintiesHists();
  private:
    std::string reweight_name;
    std::string BosonChannel;
    int parameter_index;
    
  };

}


std::string getParNamePDF(std::string set, float startx, float increment,int i);
