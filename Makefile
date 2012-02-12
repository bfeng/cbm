.PHONY: all clean
CCC=g++
CCFLAGS=-std=c++0x -I/usr/include/boost -L/usr/lib -lboost_thread-mt
OBJECTS=cpu mem predisk disk

all: $(OBJECTS)
	##./cpu
	##./mem
	./predisk
	./disk

cpu: cpu.cpp
	$(CCC) -o cpu cpu.cpp $(CCFLAGS)

mem: memory.cpp
	$(CCC) -o mem memory.cpp $(CCFLAGS)

predisk: predisk.cpp
	$(CCC) -o predisk predisk.cpp $(CCFLAGS)

disk: disk.cpp
	$(CCC) -o disk disk.cpp $(CCFLAGS)

clean:
	rm $(OBJECTS)
