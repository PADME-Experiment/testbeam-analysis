#!/usr/bin/env gnuplot
print system("echo DATFILES=$DATFILE ./fft.plt")
datfiles=system("echo $DATFILES")
set term png size 1280,800
set term pdf size 12,8

do for [datfile in datfiles]{
 set o sprintf("%s.pdf",datfile)
set title datfile noenh;
p [:1024][:] \
    for [kk=1:512:10] datfile i kk*1 u 0:1:(512-kk*1) lc palette w l title sprintf("%s %s",columnhead(1),columnhead(2)), "" i 0 u 0:1 w lp ps .2 lc 2 lw 2 title columnheader,\
      "" i 400 u 0:1 w lp ps .2 lc 3 lw 2 title sprintf("%s %s",columnhead(1),columnhead(2))
}
set o
