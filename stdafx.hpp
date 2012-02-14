#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <chrono>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/thread.hpp>

#define NOW() std::chrono::high_resolution_clock::now()
#define DURATION(end, start) std::chrono::duration<double>(end - start).count() 
