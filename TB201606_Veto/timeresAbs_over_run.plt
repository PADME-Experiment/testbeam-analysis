#!/usr/bin/env gnuplot
set term pdf enh size 12,8
set o "timeresAbs_run.pdf";
set grid
set title "TimeDiffMeanTimeAbs"
set yla "σ(t_{12}-t_i)/√2"
set xla "i^{th} Channel"
#set key Left left top
#set yra  [1.2:5.5]
#set yra  [.1:4]
set xra [7:16]
p \
for [run in "441 443 446 444 445"]  sprintf("proc-run-%s-timeres-nonfft-50.dat",run) u 1:($16/sqrt(2)):($17/sqrt(2))  w yerr lt run title sprintf("run %s",run),\
for [run in "441 443 446 444 445"]  sprintf("proc-run-%s-timeres-nonfft-50.dat",run) u 1:($16/sqrt(2)):($17/sqrt(2))  w l lt run notit
  set o
