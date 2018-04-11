#!/bin/bash
export ROOTSYS=/usr
export PATH=$PATH:$ROOTSYS/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOTSYS/lib
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$ROOTSYS/lib
module load root

cd /afs/desy.de/user/a/albrechs
source setup_UHH2.sh
cd aQGCVVjjhadronic

sframe_main config/aQGC$1jjhadronic_SignalRegion.xml
sframe_main config/aQGC$1jjhadronic_SidebandRegion.xml
