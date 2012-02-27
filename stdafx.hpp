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

  void print_results(char *cmd, bool is_random, int block_size, int n_thread, unsigned long size, double dur)
  {
    std::cout << cmd << ", ";
    std::cout << is_random << ", ";
    std::cout << block_size << ", ";
    std::cout << n_thread << ", ";
    std::cout << "Size, " << size << ", Bytes, ";
    std::cout << "Time, " << dur*1000 << ", ms, ";
    std::cout << "Throughput, " << ((double)size/1024/1024)/(dur) << ", MB/s" << std::endl;
  }

  int make_ran_file(long size, std::string filename)
  {
    struct stat buffer;
    if(stat(filename.data(), &buffer) == 0)
    {
      if(buffer.st_size == size)
        return 0;
    }
    FILE *fd = fopen(filename.data(), "w");
    if(fd == NULL)
    {
      std::cout << filename << ": ";
      perror("open file error");
      return -1;
    }
    for(int j=0;j<size;++j)
    {
      fputc(rand(), fd);
    }
    if(fd != NULL)
      fclose(fd);

    return 0;
  }
}

#endif
