#!/usr/bin/env gnuplot

DATFILE="PositionDeterminationByCharge.dat"

set term pdf enh size 9,6
set o "PositionDeterminationByCharge.pdf"

f(x)=a+b*exp(c*(d-x))
Fr(f)=d-log((f-a)/b)/c
a=100;b=1e-5;c=.1;d=180;
fit f(x) DATFILE  u 2:3:($4) via a,b,c,d

set log y
set grid
set xti 10
set title "Position determination based on collected charge (channel 11 best light output, light collection fibre+scintillator)"
set yla "Mean of collected charge distribution [au]"
set xla "Beam position [mm]"

p  [0:200] [50:600] \
DATFILE u 2:3:4 w yerr lw 2 tit "Charge distribution RMS (1σ)",\
DATFILE u 2:3 w l notit,\
DATFILE u 2:3:($3-$4<83?1000:Fr($3-$4)):(Fr($3+$4)) w xerr lc 6 lw 3 tit "Determined position uncertainty (1σ)",\
f(x) tit sprintf("%f+%f*exp(%f*(%f-x))",a,b,c,d)
