#!/bin/bash
processes=(WPWP WMWM WPWM WPZ WMZ ZZ)

for i in {0..5}
do
  cp aQGCVVjjhadronic.xml aQGC${processes[$i]}jjhadronic.xml 
  sed -i "s|NT_VV|NT_${processes[$i]}|g" aQGC${processes[$i]}jjhadronic.xml
  sed -i "s|_VV|_${processes[$i]}|g" aQGC${processes[$i]}jjhadronic.xml
done