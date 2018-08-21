#pragma once

#include "UHH2/core/include/fwd.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/common/include/ObjectIdUtils.h"

namespace uhh2examples {

	class MqqSelection: public uhh2::Selection {
	public:
		MqqSelection(float mqq_min_=100.0f);  
		virtual bool passes(const uhh2::Event & event) override;
	private:
		float mqq_min;
	};  
  /* Select events with at least two jets in which the leading two jets have deltaphi > 2.7 and the third jet pt is
   * below 20% of the average of the leading two jets, where the minimum deltaphi and
   * maximum third jet pt fraction can be changed in the constructor.
   * The jets are assumed to be sorted in pt.
   */
  class DijetSelection: public uhh2::Selection {
  public:
    DijetSelection(float dphi_min = 2.7f, float third_frac_max = 0.2f);
    virtual bool passes(const uhh2::Event & event) override;
  private:
    float dphi_min, third_frac_max;
  };

  class invMassAK8JetSelection: public uhh2::Selection {
  public:
    invMassAK8JetSelection(float invMass_min=1050.0f);
    virtual bool passes(const uhh2::Event & event) override;
  private:
    float invMass_min;
  };
  class deltaEtaAk8Selection: public uhh2::Selection {
  public:
    deltaEtaAk8Selection(float delta_max=6.5f);
    virtual bool passes(const uhh2::Event & event) override;
  private:
    float deta_max;
  };
  class VVSoftDropMassSelection: public uhh2::Selection {
  public:
    VVSoftDropMassSelection(float MSD_min=65.f,float MSD_max=105.f);
    virtual bool passes(const uhh2::Event & event) override;
  private:
    float MSD_min,MSD_max;
  };
  class SidebandVVSoftDropMassSelection: public uhh2::Selection {
  public:
    SidebandVVSoftDropMassSelection(float Signal_min=65.f,float Signal_max=105.f,float Sideband_min=105.f);
    virtual bool passes(const uhh2::Event & event) override;
  private:
    float Signal_min, Signal_max, Sideband_min;
  };
  class NSubjettinessTau21Selection: public uhh2::Selection {
  public:
    NSubjettinessTau21Selection(float tau21_min,float tau21_max);
    virtual bool passes(const uhh2::Event & event) override;
  private:
    float tau21_min;
    float tau21_max;
  };

  class OppositeEtaAK4Selection: public uhh2::Selection {
  public:
    OppositeEtaAK4Selection();
    virtual bool passes(const uhh2::Event & event) override;
  };

  class deltaEtaAk4Selection: public uhh2::Selection {
  public:
    deltaEtaAk4Selection(float delta_min=0.0f);
    virtual bool passes(const uhh2::Event & event) override;
  private:
    float deta_min;
  };
  class invMassAK4JetSelection: public uhh2::Selection {
  public:
    invMassAK4JetSelection(float invMass_min=2000.0f);
    virtual bool passes(const uhh2::Event & event) override;
  private:
    float invMass_min;
  };
  class JetIdSelection: public uhh2::Selection {
  public:
    JetIdSelection(const JetId & jetid);
    virtual bool passes(const uhh2::Event & event) override;
  private:
    const JetId & jetid;
  };
  class TopJetIdSelection: public uhh2::Selection {
  public:
    TopJetIdSelection(const TopJetId & topjetid);
    virtual bool passes(const uhh2::Event & event) override;
  private:
    const TopJetId & topjetid;
  };
  class ElectronVeto: public uhh2::Selection {
  public:
    ElectronVeto(float deltR_min = 0.8f, const boost::optional<ElectronId> & eleid = boost::none);
    virtual bool passes(const uhh2::Event & event) override;
  private:
    float deltaR_min;
    boost::optional<ElectronId> eleid;
  };
  class MuonVeto: public uhh2::Selection {
  public:
    MuonVeto(float deltR_min = 0.8f, const boost::optional<MuonId> & muid = boost::none);
    virtual bool passes(const uhh2::Event & event) override;
  private:
    float deltaR_min;
    boost::optional<MuonId> muid;
  };
}
