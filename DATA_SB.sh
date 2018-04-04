#!/bin/bash
# cd /nfs/dust/cms/user/albrechs
cd /afs/desy.de/user/a/albrechs
source setup_UHH2.sh
cd aQGCVVjjhadronic

dataset=(Data)

for i in {0..0}
do
  sframe_batch.py -s config/${dataset[$i]}.xml
  #echo sframe_batch.py config/${dataset[$i]}.xml
done
