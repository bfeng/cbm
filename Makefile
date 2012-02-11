.PHONY: all clean
CCC=g++
CCFLAGS=-std=c++0x -I/usr/include/boost -L/usr/lib -lboost_thread-mt

all: cpu mem
	##./cpu
	./mem

cpu: cpu.cpp
	$(CCC) -o cpu cpu.cpp $(CCFLAGS)

mem: memory.cpp
	$(CCC) -o mem memory.cpp $(CCFLAGS)

clean:
	rm cpu mem
