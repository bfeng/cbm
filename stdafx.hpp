#ifndef CBM_STDAFX_HEADER
#define CBM_STDAFX_HEADER

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
#include <boost/thread/thread.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#define NOW() std::chrono::high_resolution_clock::now()
#define DURATION(end, start) std::chrono::duration<double>(end - start).count() 

namespace cbm
{
  std::string make_daytime_string()
  {
    time_t now = std::time(0);
    return std::ctime(&now);
  }

  void rand_char_array(char arr[], int n)
  {
    for(int i=0;i<n;++i)
    {
      char c = (char) rand();
      arr[i] = c;
    }
  }
}

#endif
