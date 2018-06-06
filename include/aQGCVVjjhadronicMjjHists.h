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
	class aQGCVVjjhadronicMjjHists: public uhh2::Hists {
	public:
    // use the same constructor arguments as Hists for forwarding:
    aQGCVVjjhadronicMjjHists(uhh2::Context & ctx, const std::string & dirname);

    virtual void fill(const uhh2::Event & ev) override;
    virtual ~aQGCVVjjhadronicMjjHists();
	private:
    std::vector<std::string> reweight_names;
    std::string BosonChannel;
    std::string dirname_var;
    
	};

}


std::string getParName(std::string set, float startx, float increment,int i);
