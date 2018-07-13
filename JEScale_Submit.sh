#!/bin/bash

FLAG=$1

# REGIONS=(PreSelection)
REGIONS=(SignalRegion)

for ((j=0;j<${#REGIONS[@]};j+=1))
do
	sframe_batch.py $FLAG config/aQGCVVjjhadronic_JEScaleNOMINAL_${REGIONS[$j]}.xml
	sframe_batch.py $FLAG config/aQGCVVjjhadronic_JEScaleUP_${REGIONS[$j]}.xml
	sframe_batch.py $FLAG config/aQGCVVjjhadronic_JEScaleDOWN_${REGIONS[$j]}.xml  
done

