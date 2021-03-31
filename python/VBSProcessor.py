import json
import awkward as ak
from coffea.nanoevents import NanoEventsFactory, NanoAODSchema, BaseSchema
from coffea import processor, hist
from coffea.nanoevents.methods import vector
#reload(vector)
ak.behavior.update(vector.behavior)

import numpy as np
class VBSHadronicPlots(processor.ProcessorABC):
    def __init__(self):
        dataset_ax = hist.Cat("dataset", "Dataset")
        pT_ax  = hist.Bin("pt" , "$p_{T}$ [GeV]", 100, 0., 1500.)
        eta_ax = hist.Bin("eta", "$\eta$", 100,-6.0, 6.0)
        mJJ_ax  = hist.Bin("mJJ" , "invariant dijetmass [GeV]", 100, 0., 3000.)
        mJ_ax  = hist.Bin("mJ" , "$m_{genjet}$ [GeV]", 100, 0., 200.)
        hists = {}
        
        for cut in ['2cleanJets','VBF','VBF_mjjAK4','VBF_topVeto']:
            for jet_rank in [0,1]:
                hists.update({"genAK8_%i_"%jet_rank+cut : hist.Hist("Events",
                                                                    dataset_ax,
                                                                    pT_ax,eta_ax,mJ_ax)})
                
                hists.update({"genAK8Matched_%i_"%jet_rank+cut : hist.Hist("Events",
                                                                           dataset_ax,
                                                                           pT_ax,eta_ax,mJ_ax)})
                
                hists.update({"genAK4_%i_"%jet_rank+cut : hist.Hist("Events",
                                                                    dataset_ax,
                                                                    pT_ax,eta_ax,mJ_ax)})
                
            hists.update({"genAK8Matched_mjj_"+cut: hist.Hist("Events", dataset_ax, mJJ_ax)})
            hists.update({"genAK8_mjj_"+cut: hist.Hist("Events", dataset_ax, mJJ_ax)})
            hists.update({"genAK4_mjj_"+cut: hist.Hist("Events", dataset_ax, mJJ_ax)})


        self._hists = processor.dict_accumulator(hists)
    
    @property
    def accumulator(self):
        return self._hists
    
    def lorentz_vectors(self, tree, branch_prefix):
        return ak.zip({k:tree[branch_prefix + k.replace("mass","m")]  for k in ['pt', 'eta', 'phi', 'mass']},with_name='PtEtaPhiMLorentzVector')

    def mask_lorentz_vector_branches(self,tree,branch_prefix, mask):
        for k in ['pt', 'eta', 'phi', 'm']:
            tree[branch_prefix+k] = tree[branch_prefix+k][mask]
        return tree
    
    def rank_lorentz_vectors(self, a, b, key='pt'):
        keys = ['pt', 'eta', 'phi', 'mass']
        a_np = {k:np.array(a[k]) for k in keys}
        b_np = {k:np.array(b[k]) for k in keys}        
        not_leading= a_np[key]<b_np[key]
        c = ak.copy(a)
        c_np = {k:np.array(c[k]) for k in keys}        
        for k in keys:
            a_np[k][not_leading] = b_np[k][not_leading]
            b_np[k][not_leading] = c_np[k][not_leading]
            
        a = ak.zip(a_np,with_name="PtEtaPhiMLorentzVector")
        b = ak.zip(b_np,with_name="PtEtaPhiMLorentzVector")
        return (a,b)

    def matchedVJets(self,tree,threshold=None):
        V_indices = tree["v_V_candidate_indices"]
        
        V1_indices = ak.from_regular(ak.unflatten(V_indices[:,0],1))
        V2_indices = ak.from_regular(ak.unflatten(V_indices[:,1],1))
        V1_branches = {k:tree["v_genPart_"+k.replace("mass","m")][V1_indices]  for k in ['pt', 'eta', 'phi', 'mass']}
        V2_branches = {k:tree["v_genPart_"+k.replace("mass","m")][V2_indices]  for k in ['pt', 'eta', 'phi', 'mass']}

        V1_v4 = ak.zip(V1_branches,with_name="PtEtaPhiMLorentzVector")
        V2_v4 = ak.zip(V2_branches,with_name="PtEtaPhiMLorentzVector")        
        V1_v4,V2_v4 = self.rank_lorentz_vectors(V1_v4,V2_v4,key='pt')
        
        genJets_branches = {k:tree["v_genAK8_"+k.replace("mass","m")] for k in ['pt', 'eta', 'phi', 'mass']}
        genJet_v4 = ak.zip(genJets_branches, with_name="PtEtaPhiMLorentzVector")
        J1,dR1 = V1_v4.nearest(genJet_v4,return_metric=True,threshold=threshold)
        J2,dR2 = V2_v4.nearest(genJet_v4,return_metric=True,threshold=threshold)
        
        #dR metric that is returned by .nearest is not masked like the returned v4 objects, so they will include values > threshold
        return (J1,J2),(dR1,dR2)
        
    def process(self, events):
        out = self.accumulator.identity()
        dataset = events.metadata['dataset']
        
        def mjj(prefix,t):
            # mjj_arr = np.sqrt(sum([t[prefix+b][:, 0] *t[prefix+b][:, 1] for b in ['pt', 'eta', 'phi', 'm']]))
            jets = self.lorentz_vectors(t,prefix)
            return (jets[:,0]+jets[:,1]).mass


        two_jets_selection = lambda t:(ak.num(t.v_genAK8_pt) >= 2) & (ak.num(t.v_genAK4_pt)>=2)
        jet_cleaning = lambda t: ( (t.v_genAK4_pt[:,0]>30) & (t.v_genAK4_pt[:,1]>30) & (abs(t.v_genAK4_eta[:,0])<4.7) & (abs(t.v_genAK4_eta[:,1])<4.7) )
        # VBF_selection = lambda t:(t.v_genAK8_pt[:,0]>200)&(t.v_genAK8_pt[:,1]>200) & (mjj("v_genAK8_",t)>500) & (mjj("v_genAK4_",t)>500)
        VBF_selection = lambda t:(t.v_genAK8_pt[:,0]>200)&(t.v_genAK8_pt[:,1]>200)# & (mjj("v_genAK8_",t)>500)
        VBF_mjjAK4_selection = lambda t:(mjj("v_genAK4_",t)>500)

        def topVeto(tree):
            pdg_ids = tree['v_genPart_pdgId']
            tops = abs(pdg_ids) == 6
            n_top = ak.num(pdg_ids[tops])
            return n_top==0
        
        two_jets_events_unclean = events[two_jets_selection(events)]
        two_jets_events = two_jets_events_unclean[jet_cleaning(two_jets_events_unclean)]
        VBF_events = two_jets_events[VBF_selection(two_jets_events)]
        VBF_mjjAK4_events = VBF_events[VBF_mjjAK4_selection(VBF_events)]
        VBF_topVeto_events = VBF_mjjAK4_events[topVeto(VBF_mjjAK4_events)]
        
        cuts = {"2cleanJets":two_jets_events, "VBF":VBF_events,'VBF_mjjAK4':VBF_mjjAK4_events,'VBF_topVeto':VBF_topVeto_events}

        
        for cut,cut_events in cuts.items():
            # print(cut_events["v_genAK4_pt"].type)
            gen_ak8_v4 = self.lorentz_vectors(cut_events,"v_genAK8_")
            gen_ak4_v4 = self.lorentz_vectors(cut_events,"v_genAK4_")

            matching_threshold = 0.4
            J_matched,dR_matched = self.matchedVJets(cut_events,matching_threshold)

            wgt = cut_events["weight"]
            wgt_matched = ak.copy(wgt)

            found_matches = (~ak.is_none(J_matched[0],axis=-1)) & (~ak.is_none(J_matched[1],axis=-1))
            J_matched = [J[found_matches] for J in J_matched]
            found_matches = ((ak.num(J_matched[0])>0) & (ak.num(J_matched[1])>0))
            J_matched = [J[found_matches] for J in J_matched]
            # gen_ak4_v4 = self.lorentz_vectors(cut_events,'v_genAK4_')[found_matches]
            gen_ak4_v4 = gen_ak4_v4[found_matches]
            wgt_matched = wgt_matched[found_matches]

            if('VBF' in cut):
                dR_min = 1.2

                
                not_overlap = (gen_ak4_v4.delta_r(J_matched[0][:,0])>dR_min) & (gen_ak4_v4.delta_r(J_matched[1][:,0])>dR_min)
                gen_ak4_v4 = gen_ak4_v4[not_overlap]

                n2_ak4 = ak.num(gen_ak4_v4.pt)>=2                
                J_matched = [J[n2_ak4] for J in J_matched]
                gen_ak4_v4 = gen_ak4_v4[n2_ak4] 
                wgt_matched = wgt_matched[n2_ak4]

                if(cut == 'VBF_mjjAK4' or cut == 'VBF_topVeto'):
                    mjjAK4 = (gen_ak4_v4[:,0]+gen_ak4_v4[:,1]).mass>500
                    J_matched = [J[mjjAK4] for J in J_matched]
                    gen_ak4_v4 = gen_ak4_v4[mjjAK4] 
                    wgt_matched = wgt_matched[mjjAK4]

                mVV_sel = (J_matched[0][:,0]+J_matched[1][:,0]).mass > 500
                J_matched = [J[mVV_sel] for J in J_matched]
                gen_ak4_v4 = gen_ak4_v4[mVV_sel] 
                wgt_matched = wgt_matched[mVV_sel]
                
                
                

            for jet_rank in [0,1]:
                out["genAK8_%i_"%jet_rank+cut].fill(dataset=dataset,
                                                 pt = gen_ak8_v4[:,jet_rank].pt,
                                                 eta = gen_ak8_v4[:,jet_rank].eta,
                                                 mJ = gen_ak8_v4[:,jet_rank].mass,
                                                 weight = wgt
                                                 )
                out["genAK4_%i_"%jet_rank+cut].fill(dataset=dataset,
                                                 pt = gen_ak4_v4[:,jet_rank].pt,
                                                 eta = gen_ak4_v4[:,jet_rank].eta,
                                                 mJ = gen_ak4_v4[:,jet_rank].mass,
                                                 weight = wgt_matched
                                                 )
                out["genAK8Matched_%i_"%jet_rank+cut].fill(dataset=dataset,
                                                        pt = ak.flatten(J_matched[jet_rank].pt),
                                                        eta = ak.flatten(J_matched[jet_rank].eta),
                                                        mJ = ak.flatten(J_matched[jet_rank].mass),
                                                        weight = wgt_matched
                                                        )
                # out["genAK8Matched_%i_"%jet_rank+cut].fill(dataset=dataset,
                #                                         pt = ak.flatten(ak.fill_none(J_matched[jet_rank].pt,-1.0)),
                #                                         eta = ak.flatten(ak.fill_none(J_matched[jet_rank].eta,-1.0)),
                #                                         mJ = ak.flatten(ak.fill_none(J_matched[jet_rank].mass,-1.0)),
                #                                         weight = wgt_weird_due_to_overlap_and_matching
                #                                         )
                
            out["genAK8_mjj_"+cut].fill(dataset=dataset,
                                 mJJ=(gen_ak8_v4[:,0]+gen_ak8_v4[:,1]).mass,
                                 weight = wgt)
            out["genAK8Matched_mjj_"+cut].fill(dataset=dataset,
                                               mJJ=ak.flatten((J_matched[0]+J_matched[1]).mass),
                                               weight = wgt_matched
                                               )
            # out["genAK8Matched_mjj_"+cut].fill(dataset=dataset,
            #                      mJJ=ak.flatten(ak.fill_none((J_matched[0]+J_matched[1]).mass,-1.0)),
            #                      weight = wgt)
            out["genAK4_mjj_"+cut].fill(dataset=dataset,
                                        mJJ=(gen_ak4_v4[:,0]+gen_ak4_v4[:,1]).mass,
                                        weight = wgt_matched
                                        )
            
        return out

    def postprocess(self, accumulator):
        return accumulator
    
def plot_everything(result,datasets=None):
    from coffea import hist
    import mplhep as hep 
    import matplotlib.pyplot as plt
    plt.style.use(hep.style.CMS)
    import matplotlib as mpl
    font_size = 25
    mpl.rcParams['axes.labelsize'] = font_size
    import os
    


    def plot_hist(chist,hist_prefix = "genAK4_0", cut = "raw", var = "pt",density = True,out_dir='VBSPlots/',vars_list = ['pt','eta','mJ']):
        vars_list = list(vars_list)
        if(not os.path.isdir(out_dir)):
            os.makedirs(out_dir)
        f,ax = plt.subplots(figsize=(10,10))
        print(f"plotting {hist_prefix}_{cut} var:{var}")
        if(var in vars_list):
            vars_list.remove(var)
            hist.plot1d(chist[hist_prefix+"_"+cut][datasets].sum(*vars_list),density=density,ax = ax)
        else:
            hist.plot1d(chist[hist_prefix+"_"+var+"_"+cut][datasets],density=density,ax = ax)        
        
        hep.cms.label(llabel=', work in progress',ax=ax,lumi=None,year=int('2017'))
        plt.xticks(fontsize = font_size-2)
        plt.yticks(fontsize = font_size-2)
        xlabel = ax.get_xlabel()
        if("AK4" in hist_prefix):
            xlabel = xlabel.replace("AK8","AK4")
        ax.set_xlabel(xlabel)
        if(var == "mJ"):
            ax.set_xlim(0,200)
        if(density):
            ax.set_ylabel("$\Delta N/N$")
        f.savefig(out_dir + '/' + cut.replace("_","") + '_' + hist_prefix + '_' + var +'.pdf',bbox_inches='tight')
    
    hist_prefixe = ['genAK4','genAK8','genAK8Matched']
    kin_vars = ['pt','eta','mJ']
    cuts = ['2cleanJets','VBF']#,'VBF_mjjAK4','VBF_topVeto']
    density=True
    for cut in cuts:
        for hist_prefix in hist_prefixe:
            for jet_rank in [0,1]:
                for var in kin_vars:
                    plot_hist(result,hist_prefix+f"_{jet_rank}",var=var,cut=cut,density=density,vars_list=kin_vars)
            plot_hist(result,hist_prefix,var='mjj',cut=cut,density=density)

    
if(__name__ == '__main__'):
    from coffea.util import load, save

    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--process',action='store_true', help='process all datasets.')
    parser.add_argument('--test',action='store_true', help='test processing with a few events.')
    parser.add_argument('--plots',action='store_true', help='make plots.')
    args = parser.parse_args()

    
    samples =  ['WPMJJWPMJJjj', 'WPJJWMJJjj','ZJJZJJjj'] if (args.test or args.plots) else ['WPMJJWPMJJjj', 'WPJJWMJJjj','ZJJZJJjj', 'ZNuNuWPMJJjj', 'ZBBWPMJJjj'] 
    # samples = ['WPMJJWPMJJjj']
    path = '/nfs/dust/cms/user/albrechs/UHH2/VBSOutput/VBSSMSignal/'
    file_path = path+'uhh2.AnalysisModuleRunner.MC.MC_%s_EWK_UL17.root'

    samples_dict = {s:[file_path%s] for s in samples}
    if(args.process or args.test):
        result = processor.run_uproot_job(
            samples_dict,
            "AnalysisTree",
            VBSHadronicPlots(),
            processor.iterative_executor,
            {"schema": BaseSchema},
            chunksize=100 if args.test else 100000 ,
            # chunksize=1000 if args.test else 100000 ,
            maxchunks=1 if args.test else None
        )
        save(result, "vbs_hist_test.coffea" if args.test else 'vbs_hists.coffea')

    if(args.plots):
        if(not (args.process or args.test)):
            result = load('vbs_hists.coffea')
        plot_everything(result,datasets=samples)

    


    
