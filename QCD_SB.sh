#!/bin/bash
cd /nfs/dust/cms/user/albrechs
source setup.sh
cd aQGCVVjjhadronic

dataset=(QCD_HT300to500 QCD_HT500to700 QCD_HT700to1000 QCD_HT1000to1500 QCD_HT1500to2000 QCD_HT2000toInf)


for i in {0..5}
do
  sframe_batch.py config/${dataset[$i]}.xml
  #echo sframe_batch.py config/${dataset[$i]}.xml
done
