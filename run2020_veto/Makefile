CFILES=$(wildcard *.cc)
HFILES=$(wildcard *.hh)
OFILES=$(addprefix build/, $(addsuffix .o,$(basename $(CFILES))))

CC=g++
CFLAGS=$(shell root-config --cflags --libs) -lSpectrum
CFLAGS+=-l gsl -l cblas -l jsoncpp -lPadmeRoot -O0 # -pthread -fopenmp

.PHONY: all clear

all: a.out
clean:
	rm -rf build/
	rm a.out


build:
	mkdir build

build/%.o: %.cc $(HFILES) | build
	$(CC) $(CFLAGS) -c $< -o $@

a.out: $(OFILES)
	echo $^
	$(CC) $(CFLAGS) $^ -o a.out

