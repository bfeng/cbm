#include "stdafx.hpp"

void mem_worker(char mem[], int ran[], char c, const int N)
{
    for(int i = 0;i<N;++i)
    {
      c = mem[i];
    }
    for(int i = 0;i<N;++i)
    {
      mem[i] = c;
    }
    for(int i = 0;i<N;++i)
    {
      mem[ran[i]] = c;
    }
}

void n_thread(int n, const int N)
{
  int test = 10;

  std::cout << "Memory testing: " << n << " threads" << std::endl;

  for(int i=0;i<test;++i)
  {
    std::cout << "Test " << i << "\t~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    char mem[N];
    int ran[N];
    char tmp;

    for(int i=0;i<N;++i)
    {
      ran[i] = rand() % N;
    }

    boost::thread worker[n];
    for(int j=0;j<n;++j)
      worker[j] = boost::thread(mem_worker, mem, ran, tmp, N);

    auto start = NOW();
    for(int j=0;j<n;++j)
      worker[j].join();
    auto end = NOW();
    double dur = DURATION(end, start);
    long size = sizeof(mem) * n;

    std::cout << "Size: " << size << " Bytes" << std::endl;
    std::cout << "Time: " << dur << " s" << std::endl;
    std::cout << "Throughput: " << ((float)size/1024/1024)/(dur) << " MB/s" << std::endl;
  }
}

int main()
{
  srand(time(0));
  const int N[] = {1, 10, 100, 1024, 100*1024, 1024*1024};
  int n = sizeof(N)/sizeof(int);
  for(int i=0;i<n;++i)
  {
    n_thread(1, N[i]);
    n_thread(2, N[i]);
    n_thread(4, N[i]);
    n_thread(8, N[i]);
  }
  return 0;
}

