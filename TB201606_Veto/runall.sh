#for i in ~/work/padme-raw/tb201606/run_{438..447}.root;  ./startsh -i $i -o proc-${${i##*/}%.root}-nonfft-50.root
#GROOT="g++ `root-config --cflags --libs` -lCCfits -lcfitsio"
#$GROOT PostAnalysis.C||exit
#  ./a.out




#for i in {438..447};{
#  gnuplot -e "datfile='proc-run-$i-timeres-nonfft-50.dat'"     timeres.plt
#  gnuplot -e "datfile='proc-run-$i-effinef-nonfft-50.dat'"     effinef.plt
#  gnuplot -e "datfile='proc-run-$i-effinef-nonfft-50-abs.dat'" effinef.plt
#}
#for i in {441,443,446,444,445};{
#  echo $i
#  awk 'BEGIN{a[0]=0;e[0]=0;n[0]=0;e10[0]=0;n10[0]=0;}{if($2<10){e10[$1]=$3;n10[$1]=$4;}if($3<$4){e[$1]=$3;n[$1]=$4;a[$1]=$2;}}END{for(i=8;i<16;++i){print "'"$i"'",i,a[i],100-e[i],n[i],100-e10[i],n10[i]};}'<proc-run-$i-effinef-nonfft-50-abs.dat
#  echo
#  echo
#}>effinef
gnuplot << EOF
set grid;
set term pdf size 12,8;
set title "Best noise/signal threshold";
set xla "Channel";
set yla "Amplitude [# Phe]";
set o "thres.pdf";
p [7:16] for [k=0:8] "effinef" i k u 2:3 w lp title columnheader(1);
set o;
reset

#set label "signal" at graph .5,.9;
#set label "noise" at graph .5,.3;
set grid;
set grid y2tics;
set term pdf size 12,8;
set title "Efficincy / Noise Best";
set xla "Channel";
set yla "Efficincy [%]";
set yti 99.5,.1,100;
set y2la "Noise [%]";
set y2ti mirror 0,.1,.7;
set y2ra [0:1.5];
set o "effbest.pdf";
p [7:16][99:100.1] for [k=0:8] "effinef" i k u 2:4 w lp pt k+1 lc k+1 title columnheader(1),\
                   for [k=0:8] "effinef" i k u 2:5 w lp pt k+1 lc k+1 notit ax x1y2;
set o;
reset
print 10
#set label "signal" at graph .5,.9;
#set label "noise" at graph .5,.3;
set grid;
set grid y2tics;
set term pdf size 12,8;
set title "Efficincy / Noise at 10Phe threshold";
set xla "Channel";
set yla "Efficincy [%]";
set yti 99.5,.1,100;
set y2la "Noise [%]";
set o "eff10.pdf";
set y2ti mirror 0,.1,.7;
set y2ra [0:1.5];
p [7:16][99.0:100.1] for [k=0:8] "effinef" i k u 2:6 w lp pt k+1 lc k+1 title columnheader(1),\
                     for [k=0:8] "effinef" i k u 2:7 w lp pt k+1 lc k+1 notit ax x1y2;
set o
EOF

#pdfjoin proc-run-{441,443,446,444,445}-timeres-nonfft-50.dat.pdf
#pdfjoin proc-run-{441,443,446,444,445}-effinef-nonfft-50.dat.pdf
#pdfjoin proc-run-{441,443,446,444,445}-effinef-nonfft-50-abs.dat.pdf
#
