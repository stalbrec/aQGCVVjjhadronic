#!/bin/bash
# cd /nfs/dust/cms/user/albrechs
cd /afs/desy.de/user/a/albrechs
source setup_UHH2.sh
cd aQGCVVjjhadronic

dataset=(QCD_HT300to500_parameterscan QCD_HT500to700_parameterscan QCD_HT700to1000_parameterscan QCD_HT1000to1500_parameterscan QCD_HT1500to2000_parameterscan QCD_HT2000toInf_parameterscan)


for i in {5..5}
do
  sframe_batch.py -s config/${dataset[$i]}.xml
  #echo sframe_batch.py config/${dataset[$i]}.xml
done