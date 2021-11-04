#g++ -O4 -march=native -lgsl -lgslcblas -Wall -pthread -std=c++1y -Wno-deprecated-declarations -m64 -I/usr/include/root -Iinclude -I/home/georgieff/git/padme/PadmeRoot/include -m64 -L/usr/lib64/root -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic -lPadmeRoot -lRecoBase  *.cc -o TB201704_Veto.exe "$@" -fopenmp



alias g++root="g++ `root-config --cflags --libs` -l gsl -l cblas"
g++root -pthread *.cc -lPadmeRoot ~/git/padme-fw1/PadmeReco/RecoBase/lib/libRecoBase-static.a -O2
