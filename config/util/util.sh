#!/bin/bash
rm ntuple_set.xml
for i in {0..99}
do
    echo '<In FileName="PATH_TO_NTUPLES/Ntuple_'${i}'.root" Lumi="0.0"/>' >> 'ntuple_set.xml'
done