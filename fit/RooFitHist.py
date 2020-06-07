from array import array
from ROOT import gROOT, gStyle, gPad,TCanvas, TColor, TH1F,TF1, TFile, TLegend, THStack, TGraph, TMath, kTRUE, kFALSE
from ROOT import RooRealVar, RooDataHist, RooPlot, RooGaussian, RooAbsData, RooFit, RooArgList,RooCBShape,RooVoigtian,RooBreitWigner,RooFFTConvPdf,RooLandau,RooBifurGauss,RooPolynomial,RooChebychev,RooMsgService
import os,subprocess

class color:
   PURPLE = '\033[95m'
   CYAN = '\033[96m'
   DARKCYAN = '\033[36m'
   BLUE = '\033[94m'
   GREEN = '\033[92m'
   YELLOW = '\033[93m'
   RED = '\033[91m'
   BOLD = '\033[1m'
   UNDERLINE = '\033[4m'
   END = '\033[0m'

process = subprocess.Popen(["module list"],shell=True,stderr=subprocess.PIPE)
module_list=process.communicate()[1]
if('root6/6.02' in module_list):
   print('Loaded Modules:')
   print(module_list)
   print(color.RED+color.BOLD+'For the custom ROOFit Shapes root5.34 is necessary'+color.END)
   # change_root_version=subprocess.Popen(["module load","root"],shell=True,stderr=subprocess.PIPE)
   # print(change_root_version.communicate())
   # exit()
# gROOT.ProcessLine('.L RooFit/RooLogistics.cxx+')
# gROOT.ProcessLine('.L RooFit/RooExpAndGauss.C+')
# from ROOT import RooLogistics,RooExpAndGauss
RooFit.SumW2Error(kTRUE)
def RooFitHist(inputhist,title='title',path='.'):
   # RooFit.gErrorIgnoreLevel = RooFit.kInfo # <6.02
   # RooFit.SetSilentMode()# >6.02
   # RooMsgService().instance().SetSilentMode(kTRUE)

   fitbinning=array('d')
   binwidth=200
   #NBins=(14000/binwidth) - ( (1040/binwidth) + 1 )
   NBins=(14000/binwidth) - ( (1040/binwidth)+1 )#14000
   for i in range(NBins+1):
      fitbinning.append(1050+i*binwidth)
      # print(fitbinning)

   hist=inputhist.Rebin(NBins,"fit parameter",fitbinning) 
   #meanstart=hist.GetBinCenter(2000)
   meanstart=hist.GetBinCenter(hist.GetMaximumBin())#maximum
   sigmastart=hist.GetRMS()
   #sigmastart=3000
   print('meanstart:',meanstart,'sigmastart:',sigmastart)
   # inputhist.Draw()  
   # hist.Draw()

   # hold=raw_input('press enter to exit.')
   gStyle.SetOptFit(1111)
   gStyle.SetOptTitle(0)

   RooFit.SumW2Error(kTRUE)
   # RooDataHist::adjustBinning(dh): fit range of variable mjj expanded to nearest bin boundaries: [1050,13850] --> [1050,13850]
   mjj=RooRealVar('mjj','M_{jj-AK8}',fitbinning[0],fitbinning[len(fitbinning)-1],'GeV')
   mjjral=RooArgList(mjj)
   dh=RooDataHist('dh','dh',mjjral,RooFit.Import(hist))
   
   shapes={}
   #Gaussian not really
   # 3rd, 4th and 5th arguments are: (starting value, minimum possible value, maximum possible value) -- not goot
   gaussmean = RooRealVar('#mu_{gauss}','mass mean value',meanstart,0,2*meanstart)
   gausssigma= RooRealVar('#sigma_{gauss}','mass resolution',sigmastart,0,2*meanstart)            
   gauss=RooGaussian('gauss','gauss',mjj,gaussmean,gausssigma)
   shapes.update({'Gauss':gauss})

   #Landau -- not good
   landaumean=RooRealVar('#mu_{landau}','mean landau',meanstart,0,2*meanstart)
   landausigma= RooRealVar('#sigma_{landau}','mass resolution',sigmastart,0,2*sigmastart)#bzw8
   landau=RooLandau('landau','landau',mjj,landaumean,landausigma)
   shapes.update({'Landau':landau})

   #CrystalBall -> this is close to be good but matrix error :( 
   mean = RooRealVar('#mu','mean',meanstart,0,2*meanstart)
   sigma= RooRealVar('#sigma','sigma',sigmastart,0,2*sigmastart)
   alpha=RooRealVar('#alpha','Gaussian tail',-1000,0)
   n=RooRealVar('n','Normalization',-1000,1000)            
   cbshape=RooCBShape('cbshape','crystalball PDF',mjj,mean,sigma,alpha,n)
   shapes.update({'CrystalBall':cbshape})

   #Voigt ---pff
   voigtmean = RooRealVar('#mu','mass mean value',meanstart,0,2*meanstart)
   voigtwidth = RooRealVar('#gamma','width of voigt',0,5000)
   voigtsigma= RooRealVar('#sigma','mass resolution',sigmastart,0,2*sigmastart)
   voigt=RooVoigtian('voigt','voigt',mjj,voigtmean,voigtwidth,voigtsigma)
   shapes.update({'Voigt':voigt})

   #BreitWigner--worst
   bwmean = RooRealVar('#mu','mass mean value',meanstart,0,2*meanstart)
   bwwidth = RooRealVar('#sigma','width of bw',sigmastart,0,2*sigmastart)            
   bw=RooBreitWigner('bw','bw',mjj,bwmean,bwwidth)
   shapes.update({'BreitWigner':bw})

   #Logistics
   # logisticsmean=RooRealVar('#mu_{logistics}','mean logistics',meanstart,0,2*meanstart)
   # logisticssigma= RooRealVar('#sigma_{logistics}','mass resolution',sigmastart,0,2*sigmastart)
   # logistics=RooLogistics('logistics','logistics',mjj,logisticsmean,logisticssigma)
   # shapes.update({'Logistics':logistics})

   #ExpAndGauss
   # expgaussmean=RooRealVar('#mu_{expgauss}','mean expgauss',meanstart,0,2*meanstart)
   # expgausssigma= RooRealVar('#sigma_{expgauss}','mass resolution',sigmastart,0,2*sigmastart)
   # expgausstrans= RooRealVar('trans','trans',0,100)
   # expgauss=RooExpAndGauss('expgauss','expgauss',mjj,expgaussmean,expgausssigma,expgausstrans)
   # shapes.update({'ExpAndGauss':expgauss})
   
   #BifurGauss -bad
   BifurGaussmean=RooRealVar('#mu_{BifurGauss}','mean BifurGauss',meanstart,0,meanstart*2)
   BifurGausslsigma= RooRealVar('#sigma_{left}','mass resolution',sigmastart,0,2*sigmastart)#2*sigmastart
   BifurGaussrsigma= RooRealVar('#sigma_{right}','mass resolution',sigmastart,300,sigmastart*3)
   BifurGauss=RooBifurGauss('BifurGauss','BifurGauss',mjj,BifurGaussmean,BifurGausslsigma,BifurGaussrsigma)
   shapes.update({'BifurGauss':BifurGauss})

   #Chebychev -nope
   Chebychev1=RooRealVar('c0','Chebychev0',-1000,1000)
   Chebychev2= RooRealVar('c1','Chebychev1',-1000,1000)        
   Chebychev3= RooRealVar('c2','Chebychev2',2,-1000,1000)        
   Chebychev=RooChebychev('Chebychev','Chebychev',mjj,RooArgList(Chebychev1,Chebychev2,Chebychev3))
   shapes.update({'Chebychev':Chebychev})

   #Polynomial -nope
   Polynomial1=RooRealVar('Polynomial1','Polynomial1',100,0,1000)
   Polynomial2= RooRealVar('Polynomial2','Polynomial2',100,0,1000)
   Polynomial=RooPolynomial('Polynomial','Polynomial',mjj,RooArgList(Polynomial1,Polynomial2))
   shapes.update({'Polynomial':Polynomial})

   #___________________________________________________________We will see
   #Convolutions 
   #-> use bin > 1000 for better accuracy  -----cyclic trouble 
   #-> Convolution depends on order!!!

   #LandauGauss Convolution  - really bad                   
   landaugauss=RooFFTConvPdf('landaugauss','landau x gauss',mjj,landau, gauss)            
   shapes.update({'LandauGauss':landaugauss})

   #GaussLandau Convolution -> Better but not positiv definite...
   gausslandau=RooFFTConvPdf('gausslandau','gauss x landau ',mjj,gauss,landau)            
   shapes.update({'GaussLandau':gausslandau})
   
   #CrystalBallLandau Convolution  cbshape x landau looks better -> status failed 
   crystlandau=RooFFTConvPdf('crystallandau','cbshape x landau', mjj, cbshape, landau)
   shapes.update({'CrystLandau': crystlandau})
   #LandauCrsystal Convolution -> The other way around is ugly

   #BifurGaussLandau Convolution -> Better in look, NO matrix error !!!!!!!! Yeei ********************
   BifurGaussLandau=RooFFTConvPdf('bigurgausslandau','landau x bifurgauss',mjj,landau, BifurGauss)            
   shapes.update({'BifurGaussLandau':BifurGaussLandau})

   #mjj.setRange("FitRange",1050.,10000.)
   #for fname in ['landau']:       

   for fname in ['BifurGaussLandau']:    
      plottitle='%s Fit of %s'%(fname,title)
      shape=shapes[fname]
     # shape.fitTo(dh,RooFit.Range("FitRange"),RooFit.SumW2Error(True))
      shape.fitTo(dh,RooFit.SumW2Error(False))
     # mjj.setRange("FitRange",1050.,10000.)#tried
      frame=mjj.frame(RooFit.Title(plottitle))
      #frame.GetYaxis().SetTitleOffset(2)

      dh.plotOn(frame,RooFit.MarkerStyle(4))
      shape.plotOn(frame,RooFit.LineColor(2))

      ndof=dh.numEntries()-3      

      #chiSquare legend
      chi2 = frame.chiSquare()
      probChi2 = TMath.Prob(chi2*ndof, ndof)
      chi2 = round(chi2,2)
      probChi2 = round(probChi2,2)
      leg = TLegend(0.5,0.5,0.9,0.65)
      leg.SetBorderSize(0)
      leg.SetFillStyle(0)
      shape.paramOn(frame, RooFit.Layout(0.5,0.9,0.9))
      leg.AddEntry(0,'#chi^{2} ='+str(chi2),'')
      leg.AddEntry(0,'Prob #chi^{2} = '+str(probChi2),'')
      leg.SetTextSize(0.04)
      frame.addObject(leg)
      
      canv=TCanvas(plottitle,plottitle,700,700)
      #canv.SetLogy()
      canv.SetLeftMargin(0.20) 
      canv.cd()
 
      frame.SetMinimum(10**(-7))#from -3 -> -6
      frame.Draw()
      #canv.Print(path+'/%s__%sS2MoreLessY.pdf'%(title,fname))
      raw_input('press enter to continue')
      return chi2


if(__name__=="__main__"):
   #replace signal.root, histDir and histName with you respective paths and names!
   f = TFile("/nfs/dust/cms/user/loemkerj/bachelor/CMSSW_10_2_16/src/UHH2/aQGCVVjjhadronic/SignalRegion/uhh2.AnalysisModuleRunner.MC.MC_aQGC_ZZjj_hadronic_2016v3.root")
   #SM----nope1 para
   hist = f.Get("MjjHists_invMAk4sel_1p0/M_jj_AK8_T1_0p5")
   #Variations
   #hist = f.Get("MjjHists_invMAk4sel_1p0/M_jj_AK8_S2_5p0")
   #hist = f.Get("MjjHists_invMAk4sel_1p0/M_jj_AK8_M1_0p70")
   #hist = f.Get("MjjHists_invMAk4sel_1p0/M_jj_AK8_T1_0p5")
   RooFitHist(hist,title='title')