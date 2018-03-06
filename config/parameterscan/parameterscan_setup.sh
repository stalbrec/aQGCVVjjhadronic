#!/bin/bash

for filename in *.xml; do
  suffix='.xml'
  echo ${filename//$suffix}_parameterscan.xml
  cp $filename ${filename//$suffix}_parameterscan.xml
  sed -i 's|Value="aQGCVVjjhadronicModule"|Value="aQGCVVjjhadronicParameterscanModule"|g' ${filename//$suffix}_parameterscan.xml
  sed -i 's|Version="MC_aQGC_WPWPjj_hadronic"|Version="MC_aQGC_WPWPjj_hadronic_parameterscan"|g' ${filename//$suffix}_parameterscan.xml
done
