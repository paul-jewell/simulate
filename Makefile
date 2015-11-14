
# Makefile for cold test simulation

simulate: main.cpp event.cpp
	g++ -o simulate main.cpp event.cpp coldtestcell.cpp traverser.cpp
