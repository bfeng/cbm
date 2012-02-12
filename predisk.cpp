#include "stdafx.hpp"

int main()
{
  srand(time(0));
  int size[] = {1, 10, 100, 1024, 10*1024, 100*1024, 1024*1024, 100*1024*1024, 1024*1024*1024};
  int n = sizeof(size)/sizeof(int);
  for(int i=0;i<n;++i)
  {
    std::string filename = "./files/"+std::to_string(size[i])+"B.tst"; 
    puts(filename.data());
    FILE *fd = fopen(filename.data(), "w");
    if(fd == NULL)
    {
      perror("open file error");
    }
    for(int j=0;j<size[i];++j)
    {
      fputc(rand(), fd);
    }
    if(fd != NULL)
      fclose(fd);
  }
  return 0;
}

