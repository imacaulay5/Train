# make all
default: project06

project06: project06.o train.o
	g++ -o project06 project06.o train.o

train.o: train.cpp train.h
	g++ -c train.cpp