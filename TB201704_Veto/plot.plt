#!/usr/bin/env gnuplot

set term pdf enh size 8,6
set key  bottom
set grid
set xra [100:300]
set yra [:400]
set log y;set yra [1:400]
set ytics (      \
"1  "   1     , \
"1.5"   1.5   , \
"2  "   2     , \
"3  "   3     , \
"4  "   4     , \
"5  "   5     , \
"6.5"   6.5   , \
"8  "   8     , \
"10 "   10    , \
"15 "   15    , \
"20 "   20    , \
"30 "   30    , \
"40 "   40    , \
"50 "   50    , \
"65 "   65    , \
"80 "   80    , \
"100"   100   , \
"150"   150   , \
"200"   200   , \
"300"   300   , \
"400"   400 )

set title "light collection fibre only"
set xla "Non SiPM side\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tSiPM side\nY coordinate on the table[mm]"
set yla "Single electron gaus fit mean"
set o "fibreo.pdf"
p '< grep "single" signlesidero|sort -nk 3'\
 u ($3==1  ?$2:0/0):5:6 pt 1+1  lt 1+1   w yerrorlines tit "sc+fibre, LC-fibre", \
 25 w l lc 0 lw 2 notit

set title "light collection scintillator and fibre"
set o "scint_fibre.pdf"
p '< grep "single" signlesidero|sort -nk 3'\
 u ($3==1  ?$2:0/0):5:6 pt 1+1  lt 1+1   w yerrorlines tit "sc+fibre, LC-fibre",'' \
 u ($3==3  ?$2:0/0):5:6 pt 1+3  lt 1+3   w yerrorlines tit "sc+fibre, LC-FibSc",'' \
 u ($3==7  ?$2:0/0):5:6 pt 1+7  lt 1+7   w yerrorlines tit "sc+fibre, LC-FibSc",'' \
 u ($3==11 ?$2:0/0):5:6 pt 1+11 lt 1+11  w yerrorlines tit "sc+fibre, LC-FibSc",'' \
 u ($3==15 ?$2:0/0):5:6 pt 1+15 lt 1+15  w yerrorlines tit "sc+fibre, LC-FibSc",\
 25 w l lc 0 lw 2 notit

set title "light collection scintillator and fibre Al included"
set o "scint_fibre_al.pdf"
p '< grep "single" signlesidero|sort -nk 3'\
 u ($3==1  ?$2:0/0):5:6 pt 1+1  lt 1+1   w yerrorlines tit "sc+fibre, LC-fibre",'' \
 u ($3==3  ?$2:0/0):5:6 pt 1+3  lt 1+3   w yerrorlines tit "sc+fibre, LC-FibSc",'' \
 u ($3==5  ?$2:0/0):5:6 pt 1+5  lt 1+5   w yerrorlines tit "sc+FibAl, LC-FibSc",'' \
 u ($3==7  ?$2:0/0):5:6 pt 1+7  lt 1+7   w yerrorlines tit "sc+fibre, LC-FibSc",'' \
 u ($3==9  ?$2:0/0):5:6 pt 1+9  lt 1+9   w yerrorlines tit "sc+FibAl, LC-FibSc",'' \
 u ($3==11 ?$2:0/0):5:6 pt 1+11 lt 1+11  w yerrorlines tit "sc+fibre, LC-FibSc",'' \
 u ($3==13 ?$2:0/0):5:6 pt 1+13 lt 1+13  w yerrorlines tit "sc+FibAl, LC-FibSc",'' \
 u ($3==15 ?$2:0/0):5:6 pt 1+15 lt 1+15  w yerrorlines tit "sc+fibre, LC-FibSc",\
 25 w l lc 0 lw 2 notit



set title "light collection scintillator only"
set o "all.pdf"
p '< grep "single" signlesidero|sort -nk 3'\
 u ($3==0  ?$2:0/0):5:6 pt 1+0  lt 1+0   w yerrorlines tit "sc+fibre, LC-scint",'' \
 u ($3==1  ?$2:0/0):5:6 pt 1+1  lt 1+1   w yerrorlines tit "sc+fibre, LC-fibre",'' \
 u ($3==2  ?$2:0/0):5:6 pt 1+2  lt 1+2   w yerrorlines tit "scint   , LC-scint",'' \
 u ($3==3  ?$2:0/0):5:6 pt 1+3  lt 1+3   w yerrorlines tit "sc+fibre, LC-FibSc",'' \
 u ($3==4  ?$2:0/0):5:6 pt 1+4  lt 1+4   w yerrorlines tit "sc+fibre, LC-scint",'' \
 u ($3==5  ?$2:0/0):5:6 pt 1+5  lt 1+5   w yerrorlines tit "sc+FibAl, LC-FibSc",'' \
 u ($3==6  ?$2:0/0):5:6 pt 1+6  lt 1+6   w yerrorlines tit "scint   , LC-scint",'' \
 u ($3==7  ?$2:0/0):5:6 pt 1+7  lt 1+7   w yerrorlines tit "sc+fibre, LC-FibSc",'' \
 u ($3==8  ?$2:0/0):5:6 pt 1+8  lt 1+8   w yerrorlines tit "sc+fibre, LC-scint",'' \
 u ($3==9  ?$2:0/0):5:6 pt 1+9  lt 1+9   w yerrorlines tit "sc+FibAl, LC-FibSc",'' \
 u ($3==10 ?$2:0/0):5:6 pt 1+10 lt 1+10  w yerrorlines tit "scint   , LC-scint",'' \
 u ($3==11 ?$2:0/0):5:6 pt 1+11 lt 1+11  w yerrorlines tit "sc+fibre, LC-FibSc",'' \
 u ($3==12 ?$2:0/0):5:6 pt 1+12 lt 1+12  w yerrorlines tit "sc+fibre, LC-scint",'' \
 u ($3==13 ?$2:0/0):5:6 pt 1+13 lt 1+13  w yerrorlines tit "sc+FibAl, LC-FibSc",'' \
 u ($3==14 ?$2:0/0):5:6 pt 1+14 lt 1+14  w yerrorlines tit "scint   , LC-scint",'' \
 u ($3==15 ?$2:0/0):5:6 pt 1+15 lt 1+15  w yerrorlines tit "sc+fibre, LC-FibSc",\
 25 w l lc 0 lw 2 notit


reset

set term pdf noenh size 8,6 
set key  bottom
set grid
#set xra [100:300]
#set yra [:400]
#set log y;set yra [1:400]
set title "Double side ReadOut"
set xla "Scintillator only RO\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tScintillator and fibre RO\nY coordinate on the table[mm]"
set yla "log(scint&fibre)-log(scint only)"

set o "doubleROcomp.pdf"
p for [a in "0_11 1_10 2_9 3_8"] '<sort -k 3 double.dat' u ($3==a?$2:0/0):4 w lp tit a
set o
