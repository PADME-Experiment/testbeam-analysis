#!/usr/bin/env gnuplot
#filename=
print system("echo DATFILE=$DATFILE ./effinef.plt")
datfiles=system("ls {613..623}*effinef.dat|paste -sd' '")
set term png size 1280,800
set term pdf size 9,6
set  log y
set grid xtics ytics mytics
set yla "[%]"
set xla "Threshold [nPhE]"
set key Left left top noenhanced

#system("for f in *-effinef.dat;{ i=${f%%-*}; echo $i; awk 'BEGIN{a[0]=0;e[0]=0;n[0]=0;e10[0]=0;n10[0]=0;}{if($2<10){e10[$1]=$3;n10[$1]=$4;}if($3<$4){e[$1]=$3;n[$1]=$4;a[$1]=$2;}}END{for(i=8;i<12;++i){print \"'\"$i\"'\",i,a[i],100-e[i],n[i],100-e10[i],n10[i]};}'< ${i}-effinef.dat; echo; echo;}>effinef")

CMD="for f in ".datfiles.";do  i=${f%%-*}; cat ${i}-effinef.dat|awk 'BEGIN{a[0]=0;e[0]=0;n[0]=0;e10[0]=0;n10[0]=0;}{if($2<10){e10[$1]=$3;n10[$1]=$4;}if($3<$4){e[$1]=$3;n[$1]=$4;a[$1]=$2;}}END{for(i=8;i<12;++i){print \"'\"$i\"'\",i,a[i],100-e[i],n[i],100-e10[i],n10[i]};}'; done |sort -n -k2|awk '{if($2!=a){a=$2;printf(\"\\n\\n%d\\n\",a);};print}' >effinef"

print CMD
system (CMD)
#system("for f in ".datfiles.";{ i=${f%%-*}; cat ${i}-effinef.dat|awk 'BEGIN{a[0]=0;e[0]=0;n[0]=0;e10[0]=0;n10[0]=0;}{if($2<15){e10[$1]=$3;n10[$1]=$4;}if($3<$4){e[$1]=$3;n[$1]=$4;a[$1]=$2;}}END{for(i=8;i<12;++i){print \"'\"$i\"'\",i,a[i],100-e[i],n[i],100-e10[i],n10[i]};}'}|sort -n -k2|awk '{if($2!=a){a=$2;printf(\"\\n\\n%d\\n\",a);};print}' >| effinef")

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


channelname(x)=(\
x== 0||x==8?"ch  8 Scintillator LC"      :\
x== 1||x==9?"ch  9 Aluminized"        :\
x== 2||x==10?"ch 10 Scintillator LC"      :\
x== 3||(x*1)==11?"ch 11 Scint + Fibre"       :\
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

#set o sprintf("%s.pdf",datfile);
set o "effinef.pdf"
set xra [-50:100]
set yra [.01:110]
set xti 5



do for [datfile in datfiles]{
runn=system(sprintf("sed 's/-.*//'<<<'%s'",datfile))
runn=runn*1
set title sprintf("%s, Beam at %dmm from SiPM",datfile, runN_pos(runn));
p \
    for [kk=0:4]   datfile index kk  u 2:3  w l lw 2              lc kk+1 title sprintf("%s err type 1(ineff)",channelname(kk)),\
    for [kk=0:4]   datfile index kk  u 2:4  w l lw 2 dashtype '_' lc kk+1 title sprintf("%s err type 2(noise)",channelname(kk))
}


reset
set grid;
#set term pdf size 12,8;
set title "Indifidual thresholds. Best noise/signal threshold for each channel";
set xla "Beam postition starting from SiPM[mm]";
set yla "Amplitude [# Phe]";
p [0:200] for [k=0:4] "effinef" i k u (runN_pos($1)):3 w lp lw 2 title channelname(k);
reset

#set label "signal" at graph .5,.9;
#set label "noise" at graph .5,.3;
set grid;
set grid y2tics;
#set term pdf size 12,8;
set title "Efficincy / Noise Best";
set xla "Beam postition starting from SiPM[mm]";
set yla "Efficincy [%]";
set yti 99.8,.1,100;
set y2la "Noise [%]";
set y2ti mirror 0,.1,.7;
set y2ra [0:1.5];
set y2la "Noise [%]";
set y2ti mirror 0,.02,.3;
set y2ra [0:.5];
set yra [99.7:100.02]
set yti 99.9,.02,100;
p [0:200] for [k=0:4] "effinef" i k u (runN_pos($1)):($4>99.9?$4:0/0) w lp pt k+1 lc k+1 lw 2 title channelname(k),\
                   for [k=0:4] "effinef" i k u (runN_pos($1)):($5<.3?$5:0/0) w lp pt k+1 lc k+1 lw 2 notit ax x1y2;
reset
#set label "signal" at graph .5,.9;
#set label "noise" at graph .5,.3;
set grid;
set grid y2tics;
#set term pdf size 12,8;
set title "Efficincy / Noise at 10Phe threshold";
set xla "Beam postition starting from SiPM[mm]";
set yla "Efficincy [%]";
set y2la "Noise [%]";
set y2ti mirror 0,.02,.3;
set y2ra [0:.5];
set yra [99.7:100.02]
set yti 99.9,.02,100;
p [0:200] for [k=0:4] "effinef" i k u (runN_pos($1)):($6>99.8?$6:0/0) w lp pt k+1 lw 2 lc k+1 title channelname(k),\
                     for [k=0:4] "effinef" i k u (runN_pos($1)):($7<.3?$7:0/0) w lp lw 2 pt k+1 lc k+1 notit ax x1y2;












