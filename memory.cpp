#include "stdafx.hpp"

void random_read_worker(char mem[], const int block_size)
{
  char tmp;
  int idx;

  for(int i=0;i<block_size;++i)
  {
    idx = rand()%block_size;
    tmp = mem[idx];
  }
}

void random_write_worker(char mem[], const int block_size)
{
  char tmp = 'A';
  int idx;

  for(int i=0;i<block_size;++i)
  {
    idx = rand()%block_size;
    mem[idx] = tmp;
  }
}

void read_worker(char mem[], const int block_size)
{
  char tmp;
  for(int i = 0;i<block_size;++i)
  {
    tmp = mem[i];
  }
}

void write_worker(char mem[], const int block_size)
{
  char tmp;
  for(int i = 0;i<block_size;++i)
  {
    mem[i] = tmp;
  }
}

void memt(char *cmd, bool is_random, int block_size, int n_thread)
{
  boost::thread worker[n_thread];
  long size = 0;
  double dur = 0.0;
  char mem_space[1024*1024];
  if(is_random)
  {
    if(strcmp(cmd, "read")==0)
    {
      for(int j=0;j<n_thread;++j)
        worker[j] = boost::thread(random_read_worker, mem_space, block_size);
    }
    else if(strcmp(cmd, "write")==0)
    {
      for(int j=0;j<n_thread;++j)
        worker[j] = boost::thread(random_write_worker, mem_space, block_size);
    }
  }
  else
  {
    if(strcmp(cmd, "read")==0)
    {
      for(int j=0;j<n_thread;++j)
        worker[j] = boost::thread(read_worker, mem_space, block_size);
    }
    else if(strcmp(cmd, "write")==0)
    {
      for(int j=0;j<n_thread;++j)
        worker[j] = boost::thread(write_worker, mem_space, block_size);
    }
  }
  auto start = NOW();
  for(int j=0;j<n_thread;++j)
    worker[j].join();
  auto end = NOW();
  dur = DURATION(end, start);
  size = block_size * n_thread;
  cbm::print_results(cmd, is_random, block_size, n_thread, size, dur);
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
  return 0;
}

