# aQGCVVjjhadronic
when adding to fresh UHH2 Installation, add following line to Makefile.local:
```
dirs += aQGCVVjjhadronic
```

works in UHH2/RunII_80X_v3 (old version, currently testing if new version works out of the box) with a few additions:

```
git status:

#       modified:   common/include/JetCorrections.h
#       modified:   common/src/JetCorrections.cxx


#       common/data/Spring16_25nsV10_MC_PtResolution_AK4PFPuppi.txt
#       common/data/Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt
#       common/data/Spring16_25nsV10_MC_PtResolution_AK8PFPuppi.txt
#       common/data/Spring16_25nsV10_MC_PtResolution_AK8PFchs.txt
```
stuff for sampleproduction (i.e. ntuplewriting)
```
#       core/python/NTUPLE_WORK/
#       core/python/aQGCMYPROC_ntuplewriter.py
#       core/python/aQGCWPWP_ntuplewriter.py
#       core/python/crab_aQGCWPWP_ntuplewriter.py
#       core/python/ntuplewriter_irene.py
#       core/python/pydump.py
#       scripts/crab/crab.log
#       scripts/crab/miniaod_set.xml
#       scripts/crab/ntupleAQGCWPWP_crab.py
#       scripts/crab/ntupleAQGCWPWP_crab.pyc
#       scripts/crab/ntupleAQGCWPWP_crab/
#       scripts/crab/ntupleAQGCWPWP_crab_v1/
#       scripts/crab/pydump.py
#       scripts/crab/setup_crab.sh
#       scripts/crab/util.sh
```
