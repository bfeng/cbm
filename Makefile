.PHONY: all clean
CCC=g++
CCFLAGS=-std=c++0x -I/usr/include/boost -L/usr/lib -lboost_thread-mt -lboost_system-mt -lpthread
OBJECTS=cpu mem predisk disk network_client network_server

all: $(OBJECTS)
	##./cpu
	##./mem
	##./predisk
	##./disk

cpu: cpu.cpp
	$(CCC) -o cpu cpu.cpp $(CCFLAGS)

mem: memory.cpp
	$(CCC) -o mem memory.cpp $(CCFLAGS)

predisk: predisk.cpp
	$(CCC) -o predisk predisk.cpp $(CCFLAGS)

disk: disk.cpp
	$(CCC) -o disk disk.cpp $(CCFLAGS)

network_client: network_client.cpp
	$(CCC) -o network_client network_client.cpp $(CCFLAGS)

network_server: network_server.cpp
	$(CCC) -o network_server network_server.cpp $(CCFLAGS)

clean:
	rm $(OBJECTS)
