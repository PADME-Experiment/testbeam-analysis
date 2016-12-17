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
x== 0?" 0_X1_D2"        :\
x== 1?" 1_X2_NC"        :\
x== 2?" 2_X3_D6"        :\
x== 3?" 3_X4_VBD"       :\
x== 4?" 4_X5_VBU"       :\
x== 5?" 5_X6_D4"        :\
x== 6?" 6_X7_NC"        :\
x== 7?" 7_X8_D8"        :\
x== 8?" 8_Y1_D7Al"      :\
x== 9?" 9_Y2_NC"        :\
x==10?"10_Y3_D3Al"      :\
x==11?"11_Y4_VTU"       :\
x==12?"12_Y5_VTD"       :\
x==13?"13_Y6_D5Al"      :\
x==14?"14_Y7_NC"        :\
x==15?"15_Y8_D1Al"      :\
x==16?"16_H1_VBD"       :\
x==17?"17_H2_VTD"       :\
x==18?"18_H3_VTU"       :\
x==19?"19_H4_D2"        :\
x==20?"20_H5_VBU"       :\
x==21?"21_H6_D6"        :\
x==22?"22_H7_D4"        :\
x==23?"23_H8_D8"        :\
x==24?"24_Calorimeter"  :\
x==25?"25_Terminated"   :\
x==26?"26_Antena":"NONE")
exclude(ch)=(\
ch==1?0:\
ch==3?0:\
ch==4?0:\
ch==6?0:\
ch==9?0:\
ch==11?0:\
ch==12?0:\
ch==14?0:\
ch==16?0:\
ch==17?0:\
ch==18?0:\
ch==20?0:\
1)


### Uncomment for all channels
#exclude(ch)=1


p [-10:35][.01:100] \
    for [kk=16:23] datfile index kk  u ($2/exclude(kk)):3  w l lw 2              lc kk+1 title sprintf("%s err type 1(ineff)",channelname(kk)),\
    for [kk=16:23] datfile index kk  u ($2/exclude(kk)):4  w l lw 2 dashtype '_' lc kk+1 title sprintf("%s err type 2(noise)",channelname(kk))
p [-10:35][.01:100] \
    for [kk=0:7]   datfile index kk  u ($2/exclude(kk)):3  w l lw 2              lc kk+1 title sprintf("%s err type 1(ineff)",channelname(kk)),\
    for [kk=0:7]   datfile index kk  u ($2/exclude(kk)):4  w l lw 2 dashtype '_' lc kk+1 title sprintf("%s err type 2(noise)",channelname(kk))
p [-10:35][.01:100] \
    for [kk=8:15]  datfile index kk  u ($2/exclude(kk)):3  w l lw 2              lc kk+1 title sprintf("%s err type 1(ineff)",channelname(kk)),\
    for [kk=8:15]  datfile index kk  u ($2/exclude(kk)):4  w l lw 2 dashtype '_' lc kk+1 title sprintf("%s err type 2(noise)",channelname(kk))
#p [-10:35][.01:50] \
#    for [kk=24:26] datfile index kk  u 2:3  w l lw 2              lc kk+1 title sprintf("ch %d err type 1(ineff)",kk),\
#    for [kk=24:26] datfile index kk  u 2:4  w l lw 2 dashtype '_' lc kk+1 title sprintf("ch %d err type 2(noise)",kk)

set o
