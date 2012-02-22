#include "stdafx.hpp"

void disk_read_seq_worker(std::string filename_str)
{
  FILE *fd = fopen(filename_str.data(), "r");
  while(fgetc(fd)!=EOF);
  fclose(fd);
}

void disk_write_seq_worker(std::string filename_str, int size)
{
  FILE *fd = fopen(filename_str.data(), "w");
  for(int j=0;j<size;++j)
  {
    fputc('0', fd);
  }
  fclose(fd);
}

void disk_read_ran_worker(std::string filename_str, int size)
{
  FILE *fd = fopen(filename_str.data(), "r");
  for(int i=0;i<size;++i)
  {
    int ram = rand() % size;
    fseek(fd, ram, SEEK_SET);
    fgetc(fd);
  }
  fclose(fd);
}

void disk_write_ran_worker(std::string filename_str, int size)
{
  FILE *fd = fopen(filename_str.data(), "r");
  for(int i=0;i<size;++i)
  {
    int ram = rand() % size;
    fseek(fd, ram, SEEK_SET);
    fputc('A', fd);
  }
  fclose(fd);
}

void diskt(char *cmd, bool is_random, int block_size, int n_thread)
{
  boost::thread worker[n_thread];
  long size = 0;
  double dur = 0.0;

  if(is_random)
  {
    if(strcmp(cmd, "read")==0)
    {
      for(int i=0;i<n_thread;++i)
      {
        std::stringstream file_out;
        file_out << "./files/" << block_size << "B." << i << ".tst";

        if(cbm::make_ran_file(block_size, file_out.str()) < 0)
          return;
        
        worker[i] = boost::thread(disk_read_ran_worker, file_out.str(), block_size);
      }
    }
    else if(strcmp(cmd, "write")==0)
    {
      for(int i=0;i<n_thread;++i)
      {
        std::stringstream file_out;
        file_out << "./files/" << block_size << "B.write." << i << ".tst";

        worker[i] = boost::thread(disk_write_ran_worker, file_out.str(), block_size);
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
        file_out << "./files/" << block_size << "B." << i << ".tst";

        if(cbm::make_ran_file(block_size, file_out.str()) < 0)
          return;
        
        worker[i] = boost::thread(disk_read_seq_worker, file_out.str());
      }
    }
    else if(strcmp(cmd, "write")==0)
    {
      for(int i=0;i<n_thread;++i)
      {
        std::stringstream file_out;
        file_out << "./files/" << block_size << "B.write." << i << ".tst";

        worker[i] = boost::thread(disk_write_seq_worker, file_out.str(), block_size);
      }
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

