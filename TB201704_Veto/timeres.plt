#!/usr/bin/env gnuplot
#print system("echo DATFILE=$DATFILE ./timeres.plt")
#datfiles=system("echo $DATFILE")
datfile="timeres.dat"

set term png size 1280,800
set term pdf enh size 9,6
#set  log y
set grid
set yla "σ(t_{12}-t_i)/√2"
set xla " "#i^{th} Channel"
set key Left left top
#jset yra  [1.2:10]
#jset yra  [.1:4]

set o "timeres.pdf"
set xla "Beam position starting from SiPM [mm]"

do for [ccc in "4 6 5 7"]{
  chan=ccc*1

set title sprintf("%s",\
chan==4?"Glued fibre, Scintillator only light collection":\
chan==5?"Aluminized, Fibre+Scintillator light collection":\
chan==6?"No fibre, Scintillator only light collection":\
"Fibre+Scintillator, Fibre+Scintillaotr light collection");
p [0:200] [0.2:2] \
    for [col=1:9] datfile u ($1==chan?$20:0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w yerr lt col title  columnheader(col*2-1),\
    for [col=1:9] datfile u ($1==chan?$20:0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w l    lt col notitle
}




set o
