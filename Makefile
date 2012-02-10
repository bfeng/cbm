.PHONY: all clean
CCC=g++
CCFLAGS=-std=c++0x

all: cpu
	./cpu

cpu: cpu.cpp
	$(CCC) $(CCFLAGS) -o cpu cpu.cpp -I/usr/include/boost -L/usr/lib -lboost_thread-mt

clean:
	rm cpu
