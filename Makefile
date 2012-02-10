.PHONY: all clean
CCC=g++
CCFLAGS=-std=c++0x

all: cpu mem
	./cpu
	./mem

cpu: cpu.cpp
	$(CCC) $(CCFLAGS) -o cpu cpu.cpp -I/usr/include/boost -L/usr/lib -lboost_thread-mt

mem: memory.cpp
	$(CCC) $(CCFLAGS) -o mem memory.cpp

clean:
	rm cpu mem
