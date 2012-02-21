#include "stdafx.hpp"

void print_results(long size, double dur)
{
  std::cout << "Size: " << size << " Bytes" << std::endl;
  std::cout << "Time: " << dur*1000 << " ms" << std::endl;
  std::cout << "Throughput: " << ((float)size/1024/1024)/(dur) << " MB/s" << std::endl;
}

void random_read_worker(char mem[], int ran[], const int block_size)
{
  for(int i = 0;i<block_size;++i)
  {
    mem[ran[i]];
  }
}

void random_write_worker(char mem[], int ran[], const int block_size)
{
  char c = '0';
  for(int i = 0;i<block_size;++i)
  {
    std::cout << ran[i] << " " << std::endl;
    //mem[ran[i]] = c;
  }
}

void read_worker(char mem[], char c, const int block_size)
{
  for(int i = 0;i<block_size;++i)
  {
    c = mem[i];
  }
}

void write_worker(char mem[], char c, const int block_size)
{
  for(int i = 0;i<block_size;++i)
  {
    mem[i] = c;
  }
}

void memt(char *cmd, bool is_random, int block_size, int n_thread)
{
  boost::thread worker[n_thread];
  char mem[block_size];
  char tmp = '0';
  long size = 0;
  double dur = 0.0;
  if(is_random)
  {
    std::cout << "randomly ";
    int ran[block_size];
    
    for(int i=0;i<block_size;++i)
    {
      ran[i] = rand()%block_size;
      std::cout << ran[i] << " " << std::endl;
      mem[i] = (char)(ran[i]+'A');
    }
    if(strcmp(cmd, "read")==0)
    {
      std::cout << "read" << std::endl;
      for(int j=0;j<n_thread;++j)
        worker[j] = boost::thread(random_read_worker, mem, ran, block_size);
    }
    else if(strcmp(cmd, "write")==0)
    {
      std::cout << "write" << std::endl;
      for(int j=0;j<n_thread;++j)
        worker[j] = boost::thread(random_write_worker, mem, ran, block_size);
    }
  }
  else
  {
    if(strcmp(cmd, "read")==0)
    {
      std::cout << "read" << std::endl;
      for(int j=0;j<n_thread;++j)
        worker[j] = boost::thread(read_worker, mem, tmp, block_size);
    }
    else if(strcmp(cmd, "write")==0)
    {
      std::cout << "write" << std::endl;
      for(int j=0;j<n_thread;++j)
        worker[j] = boost::thread(write_worker, mem, tmp, block_size);
    }
  }
  std::cout << "Memrory testing...." << std::endl;
  auto start = NOW();
  for(int j=0;j<n_thread;++j)
    worker[j].join();
  auto end = NOW();
  dur = DURATION(end, start);
  size = block_size * n_thread;
  print_results(size, dur);
}

int main(int argc, char * argv[])
{
  if(argc != 5)
  {
    std::cerr << "Usuage: <read/write> <is_random> <block_size> <n_thread>" << std::endl;
    return 1;
  }

  srand(time(0));
  bool is_random = strcmp(argv[2], "true")==0?true:false;
  memt(argv[1], is_random, atoi(argv[3]), atoi(argv[4]));
  /*
  const int N[] = {1, 10, 100, 1024, 100*1024, 1024*1024};
  int n = sizeof(N)/sizeof(int);
  for(int i=0;i<n;++i)
  {
    n_thread(1, N[i]);
    n_thread(2, N[i]);
    n_thread(4, N[i]);
    n_thread(8, N[i]);
  }
  */
  return 0;
}

