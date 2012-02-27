#include "stdafx.hpp"

void disk_read_seq_worker(std::string filename_str, int block_size)
{
  FILE *fd = fopen(filename_str.data(), "r");
  for(int i=0;i<block_size && fgetc(fd)!=EOF;++i);
  fclose(fd);
}

void disk_write_seq_worker(std::string filename_str, int block_size)
{
  FILE *fd = fopen(filename_str.data(), "rw");
  for(int j=0;j<block_size;++j)
  {
    fputc('A', fd);
  }
  fclose(fd);
}

void disk_read_ran_worker(std::string filename_str, int file_size, int block_size)
{
  FILE *fd = fopen(filename_str.data(), "r");
  int ram = 0;
  if(file_size - block_size > 0)
    ram = rand() % (file_size - block_size);
  fseek(fd, ram, SEEK_SET);
  for(int i=0;i<block_size && fgetc(fd)!=EOF;++i);
  fclose(fd);
}

void disk_write_ran_worker(std::string filename_str, int file_size, int block_size)
{
  FILE *fd = fopen(filename_str.data(), "rw");
  int ram = 0;
  if(file_size - block_size > 0)
    ram = rand() % (file_size - block_size);
  fseek(fd, ram, SEEK_SET);
  for(int i=0;i<block_size;++i)
  {
    fputc('A', fd);
  }
  fclose(fd);
}

void diskt(char *cmd, bool is_random, int block_size, int n_thread)
{
  boost::thread worker[n_thread];
  unsigned long size = 0;
  double dur = 0.0;
  long test_size = 1024*1024*1024;

  if(is_random)
  {
    if(strcmp(cmd, "read")==0)
    {
      for(int i=0;i<n_thread;++i)
      {
        std::stringstream file_out;
        file_out << "/tmp/" << test_size << "B." << i << ".tst";

        if(cbm::make_ran_file(test_size, file_out.str()) < 0)
          return;
        
        worker[i] = boost::thread(disk_read_ran_worker, file_out.str(), test_size, block_size);
      }
    }
    else if(strcmp(cmd, "write")==0)
    {
      for(int i=0;i<n_thread;++i)
      {
        std::stringstream file_out;
        file_out << "/tmp/" << test_size << "B." << i << ".tst";

        if(cbm::make_ran_file(test_size, file_out.str()) < 0)
          return;

        worker[i] = boost::thread(disk_write_ran_worker, file_out.str(), test_size, block_size);
      }
    }
  }
  else
  {
    if(strcmp(cmd, "read")==0)
    {
      for(int i=0;i<n_thread;++i)
      {
        std::stringstream file_out;
        file_out << "/tmp/" << test_size << "B." << i << ".tst";

        if(cbm::make_ran_file(test_size, file_out.str()) < 0)
          return;
        
        worker[i] = boost::thread(disk_read_seq_worker, file_out.str(), block_size);
      }
    }
    else if(strcmp(cmd, "write")==0)
    {
      for(int i=0;i<n_thread;++i)
      {
        std::stringstream file_out;
        file_out << "/tmp/" << test_size << "B." << i << ".tst";

        if(cbm::make_ran_file(test_size, file_out.str()) < 0)
          return;

        worker[i] = boost::thread(disk_write_seq_worker, file_out.str(), block_size);
      }
    }
  }

  auto start = NOW();
  for(int j=0;j<n_thread;++j)
    worker[j].join();
  auto end = NOW();
  dur = DURATION(end, start);

  size = (unsigned long)(block_size) * n_thread;
  cbm::print_results(cmd, is_random, block_size, n_thread, size, dur);
}

int main(int argc, char *argv[])
{
  if(argc != 5)
  {
    std::cerr << "Usuage: <read/write> <is_random> <block_size> <n_thread>" << std::endl;
    return 1;
  }

  srand(time(0));
  bool is_random = strcmp(argv[2], "true")==0?true:false;
  diskt(argv[1], is_random, atoi(argv[3]), atoi(argv[4]));
  return 0;
}

