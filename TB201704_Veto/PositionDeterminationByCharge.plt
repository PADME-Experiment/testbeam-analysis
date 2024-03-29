#!/usr/bin/env gnuplot

DATFILE="PositionDeterminationByCharge.dat"

set term pdf size 4*1.4,3*1.4
set o "PositionDeterminationByCharge.pdf"

f(x)=a+b*exp(c*(d-x))
Fr(f)=d-log((f-a)/b)/c
a=100;b=1e-5;c=.1;d=180;
fit f(x) DATFILE  u 2:3:($4) via a,b,c,d

set log y
set grid
set xti 10 rotate by  35 right
set title "Position determination based on collected charge LC: scint+fibre"
set yla "Mean of collected charge distribution [au]"
set yti (60,80,100,140,200,300,400)
set xla "Beam position [mm]"

p  [0:200] [50:600] \
DATFILE u 2:3:4 w yerr lw 2 tit "Charge distribution RMS (1σ)",\
DATFILE u 2:3 w l notit,\
DATFILE u 2:3:($3-$4<83?1000:Fr($3-$4)):(Fr($3+$4)) w xerr lc 6 lw 3 tit "Determined position uncertainty (1σ)",\
f(x) tit sprintf("%f+%f*exp(%f*(%f-x))",a,b,c,d)

set o


set o "PositionDeterminationByCharge.pdf"
p  [0:200] [50:600] \
DATFILE u 2:3:4 w yerr lw 2 tit "Charge distribution RMS (1σ)",\
DATFILE u 2:3 w l notit,\
DATFILE u 2:3:($3-$4<83?1000:Fr($3-$4)):(Fr($3+$4)) w xerr lc 6 lw 3 tit "Determined position uncertainty (1σ)",\
f(x) tit sprintf("%f+%f*exp(%f*(%f-x))",a,b,c,d)

set o
