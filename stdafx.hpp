#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define NOW() std::chrono::high_resolution_clock::now()
#define DURATION(end, start) std::chrono::duration<double>(end - start).count() 

