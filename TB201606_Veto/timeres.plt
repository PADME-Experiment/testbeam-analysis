#!/usr/bin/env gnuplot
print "datfile=",datfile
set term png size 1280,800
set term pdf enh size 12,8
set o sprintf("%s.pdf",datfile);
#set  log y
set grid
set title sprintf("%s",datfile);
set yla "σ(t_{12}-t_i)/√2"
set xla "i^{th} Channel"
set key Left left top
set yra  [1.2:5.5]
set yra  [.1:4]
p [7:16]\
for [col=1:8]  datfile u 1:(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w yerr lt col title  columnheader(col*2-1),\
for [col=1:8]  datfile u 1:(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w l lt col notitle

set o
