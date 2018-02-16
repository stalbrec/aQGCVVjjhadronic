#!/bin/bash
cd /nfs/dust/cms/user/albrechs
source setup.sh
cd aQGCVVjjhadronic

processes=(WPWP WMWM WPWM WPZ WMZ ZZ)

# for i in {0..5}
# do
#   sframe_batch.py -s config/aQGC${processes[$i]}jjhadronic.xml
# done

sframe_main config/aQGC${processes[$i]}jjhadronic.xml