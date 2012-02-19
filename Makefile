.PHONY: all clean
CCC=g++
CCFLAGS=-std=c++0x -I/usr/include/boost -L/usr/lib -lboost_thread-mt -lboost_system-mt -lpthread
OBJECTS=cpu mem predisk disk network_client network_server

all: $(OBJECTS)

run: all
	##./cpu
	##./mem
	##./predisk
	##./disk

cpu: cpu.cpp stdafx.hpp
	$(CCC) -o cpu cpu.cpp $(CCFLAGS)

mem: memory.cpp stdafx.hpp
	$(CCC) -o mem memory.cpp $(CCFLAGS)

predisk: predisk.cpp stdafx.hpp
	$(CCC) -o predisk predisk.cpp $(CCFLAGS)

disk: disk.cpp stdafx.hpp
	$(CCC) -o disk disk.cpp $(CCFLAGS)

network_client: network_client.cpp stdafx.hpp
	$(CCC) -o network_client network_client.cpp $(CCFLAGS)

network_server: network_server.cpp stdafx.hpp
	$(CCC) -o network_server network_server.cpp $(CCFLAGS)

clean:
	rm $(OBJECTS)
