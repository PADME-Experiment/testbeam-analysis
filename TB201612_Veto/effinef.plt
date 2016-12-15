#!/usr/bin/env gnuplot
#filename=
datfile="effinef-abs.dat"
set term png size 1280,800
set term pdf size 12,8
set o sprintf("%s.pdf",datfile);
set  log y
set grid xtics ytics mytics
set title sprintf("%s",datfile);
set yla "[%]"
set xla "Threshold [nPhE]"
set key Left left top noenhanced

channelname(x)=(\
x== 0?"X1_D2"        :\
x== 1?"X2_NC"        :\
x== 2?"X3_D6"        :\
x== 3?"X4_VBD"       :\
x== 4?"X5_VBU"       :\
x== 5?"X6_D4"        :\
x== 6?"X7_NC"        :\
x== 7?"X8_D8"        :\
x== 8?"Y1_D7Al"      :\
x== 9?"Y2_NC"        :\
x==10?"Y3_D3Al"      :\
x==11?"Y4_VTU"       :\
x==12?"Y5_VTD"       :\
x==13?"Y6_D5Al"      :\
x==14?"Y7_NC"        :\
x==15?"Y8_D1Al"      :\
x==16?"H1_VBD"       :\
x==17?"H2_VTD"       :\
x==18?"H3_VTU"       :\
x==19?"H4_D2"        :\
x==20?"H5_VBU"       :\
x==21?"H6_D6"        :\
x==22?"H7_D4"        :\
x==23?"H8_D8"        :\
x==24?"Calorimeter"  :\
x==25?"Terminated"   :\
x==26?"Antena":"NONE")
p [-10:35][.01:50] \
    for [kk=0:7]   datfile index kk  u 2:3  w l lw 2              lc kk+1 title sprintf("%s err type 1(ineff)",channelname(kk)),\
    for [kk=0:7]   datfile index kk  u 2:4  w l lw 2 dashtype '_' lc kk+1 title sprintf("%s err type 2(noise)",channelname(kk))
p [-10:35][.01:50] \
    for [kk=8:15]  datfile index kk  u 2:3  w l lw 2              lc kk+1 title sprintf("%s err type 1(ineff)",channelname(kk)),\
    for [kk=8:15]  datfile index kk  u 2:4  w l lw 2 dashtype '_' lc kk+1 title sprintf("%s err type 2(noise)",channelname(kk))
p [-10:35][.01:50] \
    for [kk=16:23] datfile index kk  u 2:3  w l lw 2              lc kk+1 title sprintf("%s err type 1(ineff)",channelname(kk)),\
    for [kk=16:23] datfile index kk  u 2:4  w l lw 2 dashtype '_' lc kk+1 title sprintf("%s err type 2(noise)",channelname(kk))
#p [-10:35][.01:50] \
#    for [kk=24:26] datfile index kk  u 2:3  w l lw 2              lc kk+1 title sprintf("ch %d err type 1(ineff)",kk),\
#    for [kk=24:26] datfile index kk  u 2:4  w l lw 2 dashtype '_' lc kk+1 title sprintf("ch %d err type 2(noise)",kk)

set o
