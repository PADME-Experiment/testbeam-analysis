#!/usr/bin/env gnuplot
print system("echo DATFILE=$DATFILE ./timeres.plt")
datfiles=system("echo $DATFILE")

set term png size 1280,800
set term pdf enh size 12,8
#set  log y
set grid
set yla "σ(t_{12}-t_i)/√2"
set xla " "#i^{th} Channel"
set key Left left top
set yra  [1.2:10]
set yra  [.1:4]
#set xtics noenhanced rotate by 45 offset -3,-2 (
set xtics noenhanced rotate by -45  (\
" 0_X1_D2"           0  ,\
" 1_X2_NC"           1  ,\
" 2_X3_D6"           2  ,\
" 3_X4_VBD"          3  ,\
" 4_X5_VBU"          4  ,\
" 5_X6_D4"           5  ,\
" 6_X7_NC"           6  ,\
" 7_X8_D8"           7  ,\
" 8_Y1_D7Al"         8  ,\
" 9_Y2_NC"           9  ,\
"10_Y3_D3Al"        10  ,\
"11_Y4_VTU"         11  ,\
"12_Y5_VTD"         12  ,\
"13_Y6_D5Al"        13  ,\
"14_Y7_NC"          14  ,\
"15_Y8_D1Al"        15  ,\
"16_H1_VBD"         16  ,\
"17_H2_VTD"         17  ,\
"18_H3_VTU"         18  ,\
"19_H4_D2"          19  ,\
"20_H5_VBU"         20  ,\
"21_H6_D6"          21  ,\
"22_H7_D4"          22  ,\
"23_H8_D8"          23  ,\
"24_Calorimeter"    24  ,\
"25_Terminated"     25  ,\
"26_Antena"  26  )

#set o sprintf("%s.pdf",datfile);
set o "timeres.pdf"
do for [datfile in datfiles]{
set title sprintf("%s",datfile);
p [0:24] \
    for [col=1:8] datfile u 1:(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w yerr lt col title  columnheader(col*2-1),\
    for [col=1:8] datfile u 1:(column(col*2)/sqrt(2)):(column(col*2+1)/sqrt(2))  w l    lt col notitle
}

set o

set o "timeresAbs_run.pdf";
set grid
set title "TimeDiffMeanTimeAbs"
set yla "σ(t_{mid}-t_i)/√2"
set xla "i^{th} Channel"
#set key Left left top
#set yra  [1.2:5.5]
set yra  [.7:1.4]
#set xra [7:16]
p \
for [run in "579 582 584 585 586"]  sprintf("%s-timeres.dat",run) u 1:($16/sqrt(2)):($17/sqrt(2))  w yerr lt run title sprintf("run %s",run),\
for [run in "579 582 584 585 586"]  sprintf("%s-timeres.dat",run) u 1:($16/sqrt(2)):($17/sqrt(2))  w l lt run notit
  set o

