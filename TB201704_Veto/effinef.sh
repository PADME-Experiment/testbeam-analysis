#!/bin/bash

for f in "$@";do
  i=${f%%-*};
  cat ${i}-effinef.dat|
  awk 'BEGIN{
  a[0]=0;
  e[0]=0;
  n[0]=0;
  e10[0]=0;
  n10[0]=0;
  }
  {
    ch=$1;
    ampl=$2;
    eff=$3;
    ineff=$4;
    nevt=$5;
    if(ampl<10){
      e10[ch]=eff;
      n10[ch]=ineff;
    }
    if(eff<ineff){
      a[ch]=ampl;
      e[ch]=eff;
      n[ch]=ineff;
    }
  }
END{
for(i=8;i<12;++i){
  print '$i',i,a[i],100-e[i],n[i],100-e10[i],n10[i]
};
}';
done |sort -n -k2|awk '{if($2!=a){a=$2;printf(\"\\n\\n%d\\n\",a);};print}' >effinef
