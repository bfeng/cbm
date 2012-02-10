#include "stdafx.hpp"

const int N = 100;

void int_martric(int martric[N][N])
{
  for(int i=0;i<N;++i)
  {
    for(int j=0;j<N;++j)
    {
      martric[i][j] = rand();
    }
  }
}

void one_thread()
{
  // integer operations test
  long operations = long(std::pow(N, 3)*3);
  std::cout<<"Integer Operations:"<<operations<<std::endl;
  int test = 10;
  int A[N][N];
  int B[N][N];

  int_martric(A);
  int_martric(B);

  int C[N][N];
  for(int j=0;j<test;++j)
  {
    auto start = NOW();
    
    for(int i=0;i<N;++i)
    {
      for(int j=0;j<N;++j)
      {
        C[i][j] = 0;
        for(int k=0;k<N;++k)
        {
          C[i][j]+=A[i][k]*B[k][j];
        }
      }
    }

    auto end = NOW();

    double dur = DURATION(end, start);
    std::cout<<"Duration:"<< dur <<"s"<<std::endl;
    std::cout<<"IOPS:"<< operations/dur <<std::endl;
  }
}

int main()
{
  srand(time(0));
  one_thread();
  return 0;
}

