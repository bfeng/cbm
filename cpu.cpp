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

void float_martric(float martric[N][N])
{
  for(int i=0;i<N;++i)
  {
    for(int j=0;j<N;++j)
    {
      martric[i][j] = (float)rand()/(float)RAND_MAX;
    }
  }
}

void integer_operation(int A[N][N], int B[N][N], int C[N][N])
{
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
}

void float_operation(float A[N][N], float B[N][N], float C[N][N])
{
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
}

void cput(int n)
{
  int test = 10;

  // integer operations test
  long operations = long(std::pow(N, 3)*3)*n;

  for(int j=0;j<test;++j)
  {
    double dur = 0.0;
    int A[N][N];
    int B[N][N];
    int C[N][N];

    int_martric(A);
    int_martric(B);

    boost::thread worker[n];
    for(int i=0;i<n;++i)
      worker[i] = boost::thread(integer_operation, A, B, C);

    auto start = NOW();
    for(int i=0;i<n;++i)
      worker[i].join();
    auto end = NOW();
    dur = DURATION(end, start);

    std::cout << n << ", Duration, " << dur*1000 << ", ms" << ", IOPS, "<< operations/(dur) << std::endl;
  }

  // floating-point operations test

  for(int j=0;j<test;++j)
  {
    double dur = 0.0;
    float A[N][N];
    float B[N][N];
    float C[N][N];

    float_martric(A);
    float_martric(B);

    boost::thread worker[n];
    for(int i=0;i<n;++i)
      worker[i] = boost::thread(float_operation, A, B, C);

    auto start = NOW();
    for(int i=0;i<n;++i)
      worker[i].join();
    auto end = NOW();
    dur = DURATION(end, start);

    std::cout << n << ", Duration, " << dur*1000 << ", ms" << ", FLOPS, "<< operations/(dur) << std::endl;
  }
}

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cerr << "Usuage: <n_thread>" << std::endl;
    return 1;
  }
  srand(time(0));
  int n_thread = atoi(argv[1]);
  cput(n_thread);
  return 0;
}

