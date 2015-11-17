
# Makefile for cold test simulation

simulate: main.cpp event.cpp event.h traverser.h simulate.h
	g++ -std=c++11 -o simulate main.cpp event.cpp coldtestcell.cpp traverser.cpp source.cpp
