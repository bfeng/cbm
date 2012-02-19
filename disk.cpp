#include "stdafx.hpp"

void disk_read_seq_worker()
{
  
}

void print_result(long file_size, double dur)
{
    std::cout << "Size: " << file_size << " Bytes" << std::endl;
    std::cout << "Time: " << dur << " ms" << std::endl;
    std::cout << "Throughput: " << ((float)file_size/1024/1024)/(dur/1000) << " MB/s" << std::endl;
}

void one_thread()
{
  std::cout << "Disk Test" << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  int size[] = {1, 10, 100, 1024, 10*1024, 100*1024, 1024*1024, 100*1024*1024, 1024*1024*1024};
  int n = sizeof(size)/sizeof(int);

  std::cout << "Read Operation" << std::endl;
  for(int i=0;i<n;++i)
  {
    std::string filename_str = "./files/"+std::to_string(size[i])+"B.tst"; 
    const char * filename = filename_str.data();

    auto start = NOW();
    FILE *fd = fopen(filename, "r");
    while(fgetc(fd)!=EOF);
    fclose(fd);
    auto end = NOW();

    double dur = DURATION(end, start);
    
    struct stat buf;
    stat(filename, &buf);
    long file_size = buf.st_size;

    print_result(file_size, dur);
  }

  std::cout << "Write Operation" << std::endl;
  for(int i=0;i<n;++i)
  {
    std::string filename_str = "./files/"+std::to_string(size[i])+"B_write.tst"; 
    const char * filename = filename_str.data();

    if(remove(filename)==0);

    auto start = NOW();
    FILE *fd = fopen(filename, "w");
    for(int j=0;j<size[i];++j)
    {
      fputc('\0', fd);
    }
    fclose(fd);
    auto end = NOW();

    double dur = DURATION(end, start);
    
    struct stat buf;
    stat(filename, &buf);
    long file_size = buf.st_size;

    print_result(file_size, dur);
  }

  std::cout << "Random Read Operations" << std::endl;
  for(int i=0;i<n;++i)
  {
    std::string filename_str = "./files/"+std::to_string(size[i])+"B.tst";

    char c;
    auto start = NOW();
    std::ifstream file(filename_str);
    for(int k=0;k<size[n];++k)
    {
      //auto start1 = NOW();
      int ram = rand() % size[n];
      //auto end1 = NOW();
      //start += end1-start1;
      file.seekg(ram, std::ios::beg);
      file.get(c);
    }
    file.close();
    auto end = NOW();

    double dur = DURATION(end, start);

    struct stat buf;
    stat(filename_str.data(), &buf);
    long file_size = buf.st_size;

    print_result(file_size, dur);
  }

  /*
  std::cout << "Random Write Operations" << std::endl;
  for(int i=0;i<n;++i)
  {
    std::string filename_str = "./files/"+std::to_string(size[i])+"B.tst";

    char c = '\0';
    auto start = NOW();
    std::ofstream file(filename_str);
    for(int k=0;k<size[n];++k)
    {
      //auto start1 = NOW();
      int ram = rand() % size[n];
      //auto end1 = NOW();
      //start += end1-start1;
      //file.seekp(ram, std::ios::beg);
      //file.put(c);
    }
    file.close();
    auto end = NOW();

    double dur = DURATION(end, start);

    struct stat buf;
    stat(filename_str.data(), &buf);
    long file_size = buf.st_size;
    std::cout << "Size: " << file_size << " Bytes" << std::endl;
    std::cout << "Time: " << dur << " s" << std::endl;
    std::cout << "Throughput: " << ((float)file_size/1024/1024)/(dur) << " MB/s" << std::endl;
  }
  */
}

int main()
{
  one_thread();
  return 0;
}
