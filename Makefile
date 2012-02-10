.PHONY: all clean

all: cpu
	./cpu

cpu:
	g++ -o cpu cpu.cpp

clean:
	rm cbm
