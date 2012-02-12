#include "stdafx.hpp"

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
    long size = buf.st_size;
    std::cout << "Size: " << size << " Bytes" << std::endl;
    std::cout << "Time: " << dur << " s" << std::endl;
    std::cout << "Throughput: " << ((float)size/1024/1024)/(dur) << " MB/s" << std::endl;
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
    long size = buf.st_size;
    std::cout << "Size: " << size << " Bytes" << std::endl;
    std::cout << "Time: " << dur << " s" << std::endl;
    std::cout << "Throughput: " << ((float)size/1024/1024)/(dur) << " MB/s" << std::endl;
  }
}

int main()
{
  one_thread();
  return 0;
}

