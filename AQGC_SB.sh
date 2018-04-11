#!/bin/bash
# cd /nfs/dust/cms/user/albrechs
# /afs/desy.de/user/a/albrechs
# source setup_UHH2.sh
# cd aQGCVVjjhadronic

processes=(WPWP WMWM WPWM WPZ WMZ ZZ)

for i in {0..5}
do
	qsub -cwd -N UHH2_${processes[$i]} submitSample.sh ${processes[$i]}
	#   sframe_batch.py -s config/aQGC${processes[$i]}jjhadronic.xml
done
