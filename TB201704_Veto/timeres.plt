#!/usr/bin/env gnuplot
#print system("echo DATFILE=$DATFILE ./timeres.plt")
#datfiles=system("echo $DATFILE")
datfile="<sort  -n  -k1 -k24 timeres.dat"

set term png size 1280,800
set term pdf enh size 9,6
#set  log y
set grid
set yla "σ(t_{12}-t_i)/√2"
set xla " "#i^{th} Channel"
set key Left left top
#jset yra  [1.2:10]
#jset yra  [.1:4]

runN_pos(x)=(\
x==613?170: \
x==614?150: \
x==616?130: \
x==617?110: \
x==618?90 : \
x==619?70 : \
x==621?50 : \
x==622?30 : \
x==623?10 : \
"-999")

set o "timeres.pdf"
set xla "Beam position starting from SiPM [mm]"

do for [ccc in "4 6 5 7"]{
  chan=ccc*1

  if(ccc==4||ccc==6){
    set yra [0:8]
  }
  if(ccc==5||ccc==7){
    set yra [.25:1.6]
  }

set title sprintf("%s",\
chan==4?"Glued fibre, Scintillator only light collection":\
chan==5?"Aluminized, Fibre+Scintillator light collection":\
chan==6?"No fibre, Scintillator only light collection":\
"Fibre+Scintillator, Fibre+Scintillator light collection");
p \
    for [col=1:11] datfile u ($1==chan?runN_pos($24):0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w yerr lt col title  columnheader(col*2-1),\
    for [col=1:11] datfile u ($1==chan?runN_pos($24):0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w l    lt col notitle
}


set term pdf enh size 4,3
set o "timedef-comp_1.pdf"

set xla "Beam position starting from SiPM [mm]"

  chan=5

    set yra [.25:1.6]

unset title
#set title sprintf("%s", "ch7-ch11 Fibre+Scintillator, Fibre+Scintillator light collection");
    set yra [.25:1.6]
    timedefnames(x)=sprintf("%s",\
x==1 ?"Max*100%":\
x==2 ?"Max*50%":\
x==3 ?"2080 Cros":\
x==4 ?"2080 0%":\
x==5 ?"2080 50%":\
x==6 ?"WMTime":\
x==7 ?"WMTime2":\
x==8 ?"WMTimeAbs":\
x==9 ?"Int*11.5%":\
x==10?"Max*10%":\
x==11?"Max*20%":\
"NONE")

set yla "σ(t_{Ch.7}-t_{Ch.11})/√2 [ns]"

set key top right Right outside horizontal  samplen 1.5

set xla "Beam position starting from SiPM [mm]"

p \
    for [col in "10 11 2 1 4 5 3 6 8 7 9"] datfile u ($1==chan?runN_pos($24):0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w yerr lt col title timedefnames(col),\
    for [col in "10 11 2 1 4 5 3 6 8 7 9"] datfile u ($1==chan?runN_pos($24):0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w l   dt 2 lt col notitle


set o
reset
set grid
set xla "Beam position starting from SiPM [mm]"
set term pdf enh size 4,3
set o "timeres-summary_1.pdf"
set key bottom right Left width -6
set yra [.25:0.9]
set yra [.35:0.85]
set yla "σ(t_{Ch.X}-t_{Ch.Y})/√2 [ns]"
set notitle
#set tit "Time resolution comparison for different scintillator types"
p \
    for [col=2:2] datfile u ($1==4?runN_pos($24):0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w yerr   lt 1 lw 2 ti "Ch.4 - Ch.8: no fibre",\
    for [col=2:2] datfile u ($1==5?runN_pos($24):0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w yerr   lt 2 lw 2 ti "Ch.5 - Ch.9: fibre+scint Al",\
    for [col=2:2] datfile u ($1==6?runN_pos($24):0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w yerr   lt 3 lw 2 ti "Ch.6 - Ch.10: no fibre",\
    for [col=2:2] datfile u ($1==7?runN_pos($24):0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w yerr   lt 4 lw 2 ti "Ch.7 - Ch.11: fibre+scint",\
    for [col=2:2] datfile u ($1==4?runN_pos($24):0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w l dt 2 lt 1 lw 2 notit,\
    for [col=2:2] datfile u ($1==5?runN_pos($24):0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w l dt 2 lt 2 lw 2 notit,\
    for [col=2:2] datfile u ($1==6?runN_pos($24):0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w l dt 2 lt 3 lw 2 notit,\
    for [col=2:2] datfile u ($1==7?runN_pos($24):0/0):(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w l dt 2 lt 4 lw 2 notit
