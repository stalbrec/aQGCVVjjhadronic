
from array import array
import csv,collections,numpy
import ROOT as rt
from ROOT import gROOT, gStyle, gPad,TCanvas, TColor, TF1, TH1F, TFile, TLegend, THStack, TGraph, TMath, kTRUE, kFALSE,TLatex,TMath
from ROOT import RooRealVar, RooDataHist, RooPlot, RooGaussian, RooAbsData, RooFit, RooArgList,RooFormulaVar,RooGenericPdf

def fitMacro(File):
    #gROOT.SetBatch(True)
#-----------------------------*************!!!file now in in SignalRegion/backup!!!!!!!!!!!!!***************
# don't forget to add at bottomline as well 
    filename='/nfs/dust/cms/user/loemkerj/bachelor/CMSSW_10_2_16/src/UHH2/aQGCVVjjhadronic/SignalRegion/uhh2.AnalysisModuleRunner.MC.MC_QCD.root'
    File=TFile(filename)

    VVHist_1GeV= File.Get('invMAk4sel_1p0/M_jj_AK8_highbin')#SM QCD BG
    #VVEFT_1GeV= File.Get('Kin_AK8/MjjHists_invMAk4sel_1p0/M_jj_AK8_S2_5p0')
    #VVHist_1GeV.Draw('PE1')
    #raw_input('press enter to continue')

    VVHist_1GeV.Scale(1./VVHist_1GeV.Integral(),'width')

    #.Scale(1./VVEFT_1GeV.Integral(),'width')
    #VVHist_1GeV.Draw('PE1')
    #raw_input('press enter to continue')

    equidistant=False
    fitbinning=array('d')

    if(equidistant):
        binwidth=500
        yTitle='Normalized # Events / (%.1f GeV)'%binwidth
        NBins=(14000/binwidth) - ( (1040/binwidth)+1 )#from 14000 -> 10000 1040 -> 1050?
        NBins=int(NBins)
        for i in range(NBins+1):
            fitbinning.append(1050+i*binwidth)
        #print(fitbinning)#change back
    else:
        yTitle='Normalized # Events'
        #not plotting bin before Mjj>1050GeV Cut
        #optimized for detektor resolution
        #nonequidistant_binning=[1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607, 1687, 1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072, 10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000]
        #selfmade
        nonequidistant_binning=[1058, 1118, 1181, 1246, 1330, 1373, 1455, 1530, 1607, 1677, 1750, 1820, 1910, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072, 10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000]
        # nonequidistant_binning=[1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325, 354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607, 1687, 1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072, 10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000]
        NBins=len(nonequidistant_binning)-1
        for b in nonequidistant_binning:
            fitbinning.append(b)

    VVHist_100GeV=VVHist_1GeV.Rebin(NBins,"fit parameter",fitbinning)

    #VVHist_100GeV.Scale(1./VVHist_100GeV.Integral(),'width')
    #VVHist_100GeV.Draw('PE1')
    #raw_input('press enter to continue')

    gStyle.SetOptStat(0)
    #gStyle.SetOptFit(0000)    
    gStyle.SetOptFit(1111)    
    gStyle.SetOptTitle(0)
                            #Create structure to store sum of squares of weights by TH1F::SumW2(kTRUE) for each following histo
                            #if histogram is already filled, the sum of squares of weights is filled with the existing bin contents
    RooFit.SumW2Error(kTRUE)#The error per bin will be computed as sqrt(sum of squares of weight) for each bin

    VV_MAXIMUM=0
    for i in range(VVHist_100GeV.GetNbinsX()):

        if(VVHist_100GeV.GetBinContent(i)>0):
            VV_MAXIMUM=VVHist_100GeV.GetBinCenter(i)
 
    VVcanv=TCanvas('VV','VV',700,700)
    VVcanv.SetLogy()
    VVcanv.SetLeftMargin(0.20) 
    VVcanv.cd() #cd() change directory
                #R Use the range specified in the function range
    #fitOptions='L'#L Use log likelihood method (default is chi-square method). To be used when the histogram represents counts
    fitOptions='REM'# WL Weighted log likelihood method. To be used when the histogram has been filled with weights different than 1
    #fitOptions='RSWLM'#M Improve fit results, by using the IMPROVE algorithm of TMinuit.
    twopar='[0]/TMath::Power(x/13000,[1])'
    threeparlog='[0]/TMath::Power(x/13000,[1])+([2]*TMath::Log10(x/13000))'
    threepar='[0]*TMath::Power((1-(x/13000)),[2])/TMath::Power(x/13000,[1])'

    # threepar='[0]*TMath::Power((1-x)/13000,[1])+(x/13000)*[2]'
    fourpar='[0]*TMath::Power((1-(x/13000)),[1])/TMath::Power(x/13000,[2]+[3]*TMath::Log10(x/13000))'
    #fourpar does not work yet
    fitfunc=twopar

    VVTF1=TF1('VVTF1',fitfunc,1058,VV_MAXIMUM)#Range should be VV_MAXIMUM

    VVTF1.SetParameter(0,1.508*10**(-9))#3.17862e-10
    VVTF1.SetParameter(0, 7.75534)

    VVHist_100GeV.SetMarkerStyle(8)
    VVHist_100GeV.SetLineColor(1)
    VVHist_100GeV.GetYaxis().SetRangeUser(10**(-6),10)
    VVHist_100GeV.GetXaxis().SetTitle('M_{jj-AK8} [GeV/c^{2}]')
    VVHist_100GeV.GetYaxis().SetTitle(yTitle)
    VVHist_100GeV.GetYaxis().SetTitleOffset(2)

    VVHist_100GeV.Draw('PE1')   
    VVHist_100GeV.GetXaxis().SetRangeUser(1058,VV_MAXIMUM+1000)#SetRangeUser(1058,VV_MAXIMUM+1000)
    VVHist_100GeV.Draw('PE1SAME')   


    VVHist_100GeV.Fit('VVTF1',fitOptions)
    #print('Sumw2:',VVHist_100GeV.GetSumw2())
    print('chi2/ndf:',VVTF1.GetChisquare(),'/',VVTF1.GetNDF())

    VVTF1.Draw('SAME')
    raw_input('press enter to continue')

if __name__=='__main__':
    fitMacro('/nfs/dust/cms/user/loemkerj/bachelor/CMSSW_10_2_16/src/UHH2/aQGCVVjjhadronic/SignalRegion/uhh2.AnalysisModuleRunner.MC.MC_QCD.root')

    # VVTF1UP=TF1('VVTF1UP',fitfunc,1050,VV_MAXIMUM)
    # VVTF1UP.SetParameter(0,VVTF1.GetParameter(0)+VVTF1.GetParError(0))
    # VVTF1UP.SetParameter(1,VVTF1.GetParameter(1)+VVTF1.GetParError(1))
    # VVTF1UP.SetLineStyle(rt.kDashed)   
    # VVTF1DOWN=TF1('VVTF1DOWN',fitfunc,1050,VV_MAXIMUM)
    # VVTF1DOWN.SetParameter(0,VVTF1.GetParameter(0)-VVTF1.GetParError(0))
    # VVTF1DOWN.SetParameter(1,VVTF1.GetParameter(1)-VVTF1.GetParError(1))
    # VVTF1DOWN.SetLineStyle(rt.kDashed)
    # VVTF1UP.Draw('SAME')
    # VVTF1DOWN.Draw('SAME')

   # print('chi2/ndf:',VVTF1.GetChisquare(),'/',VVTF1.GetNDF())

   # latex=TLatex()
   # latex.SetNDC(kTRUE)
   # latex.SetTextSize(0.03)

    # latex.DrawLatex(0.52,0.953,"%.2f fb^{-1} (13 TeV)"%36.1)

   # latex.DrawLatex(0.45,0.65,"#chi^{2}/ndof=%.2f/%.2f=%.2f"%(VVTF1.GetChisquare(),VVTF1.GetNDF(),VVTF1.GetChisquare()/VVTF1.GetNDF()))
   # latex.Draw("SAME")
   
   # VVleg = TLegend(0.45,0.7,0.9,0.9)
   # VVleg.SetBorderSize(0)
   # VVleg.SetFillStyle(0)

   # if('Data' in filename): 
   #     VVleg.AddEntry(VVHist_100GeV,'Data-!VBF','p')
   #     VVleg.AddEntry(VVTF1,'Data-!VBF Fit %s'%functionTeX,'l')
   # else:
   #     VVleg.AddEntry(VVHist_100GeV,'QCD-!VBF','p')
   #     VVleg.AddEntry(VVTF1,'QCD-!VBF Fit %s'%functionTeX,'l')

 #   VVleg.SetTextSize(0.03)
  #  VVleg.Draw('SAME')  
   # VVcanv.Print(REGION+'_VVRegion.eps')

    # VVTF1.SetLineStyle(2)
 #   VVTF1.Draw('SAME')
    # VVTF1UP.Draw('SAME')
    # VVTF1DOWN.Draw('SAME')

