#!/usr/bin/env gnuplot
#filename=
set term png size 1280,800
set term pdf size 12,8
set o sprintf("%s.pdf",datfile);
set  log y
set grid xtics ytics mytics
set title sprintf("%s",datfile);
set yla "[%]"
set xla "Threshold [nPhE]"
set key Left left top
p [-10:35][.01:50] \
    datfile index 0  u 2:3  w l lw 2              lc 1 title "ch 8 err type 1(ineff)",\
    datfile index 0  u 2:4  w l lw 2 dashtype '_' lc 1 title "ch 8 err type 2(noise)",\
    datfile index 1  u 2:3  w l lw 2              lc 2 title "ch 9 err type 1(ineff)",\
    datfile index 1  u 2:4  w l lw 2 dashtype '_' lc 2 title "ch 9 err type 2(noise)",\
    datfile index 2  u 2:3  w l lw 2              lc 3 title "ch10 err type 1(ineff)",\
    datfile index 2  u 2:4  w l lw 2 dashtype '_' lc 3 title "ch10 err type 2(noise)",\
    datfile index 3  u 2:3  w l lw 2              lc 4 title "ch11 err type 1(ineff)",\
    datfile index 3  u 2:4  w l lw 2 dashtype '_' lc 4 title "ch11 err type 2(noise)",\
    datfile index 4  u 2:3  w l lw 2              lc 5 title "ch12 err type 1(ineff)",\
    datfile index 4  u 2:4  w l lw 2 dashtype '_' lc 5 title "ch12 err type 2(noise)",\
    datfile index 5  u 2:3  w l lw 2              lc 6 title "ch13 err type 1(ineff)",\
    datfile index 5  u 2:4  w l lw 2 dashtype '_' lc 6 title "ch13 err type 2(noise)",\
    datfile index 6  u 2:3  w l lw 2              lc 7 title "ch14 err type 1(ineff)",\
    datfile index 6  u 2:4  w l lw 2 dashtype '_' lc 7 title "ch14 err type 2(noise)",\
    datfile index 7  u 2:3  w l lw 2              lc 8 title "ch15 err type 1(ineff)",\
    datfile index 7  u 2:4  w l lw 2 dashtype '_' lc 8 title "ch15 err type 2(noise)"

set o
