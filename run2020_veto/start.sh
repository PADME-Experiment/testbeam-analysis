#!/bin/bash
#LD_LIBRARY_PATH=/home/georgieff/git/padme/PadmeRoot/lib/ ./ReadTest.exe -i ~/work/padme-raw/tb201606/run_438.root "$@"
#time OMP_NUM_THREADS=1 LD_LIBRARY_PATH=/home/georgieff/git/padme-fw/PadmeRoot/lib/ ./TB201612_Veto.exe  "$@"
time OMP_NUM_THREADS=1 ./a.out  "$@"
