#!/bin/bash

FLAG=$1

# REGIONS=(PreSelection)
REGIONS=(SignalRegion SidebandRegion)
# REGIONS=(SignalRegion)
# REGIONS=(SidebandRegion)

for ((j=0;j<${#REGIONS[@]};j+=1))
do
	sframe_batch.py $FLAG config/aQGCVVjjhadronic_${REGIONS[$j]}.xml
   
	sframe_batch.py $FLAG config/QCD_${REGIONS[$j]}.xml
	sframe_batch.py $FLAG config/WJetsToQQ_${REGIONS[$j]}.xml
	sframe_batch.py $FLAG config/ZJetsToQQ_${REGIONS[$j]}.xml
	sframe_batch.py $FLAG config/TTBar_${REGIONS[$j]}.xml

	sframe_batch.py $FLAG config/Data_${REGIONS[$j]}.xml
done
