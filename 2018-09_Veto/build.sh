g++ -O2 -march=native -lgsl -lgslcblas -Wall -pthread -std=c++1z -Wno-deprecated-declarations -m64 -I/usr/include/root -Iinclude -I/home/georgieff/git/padme/PadmeRoot/include -m64 -L/usr/lib64/root -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic -lPadmeRoot -lRecoBase  *.cc -o TB201704_Veto.exe "$@" #-fopenmp
