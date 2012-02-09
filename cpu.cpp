#include <iostream>
#include <boost/timer.hpp>
#include <cmath>

using boost::timer;

int main()
{
  double times[20];
  for(int j=0;j<20;++j)
  {
    timer t;
    for(long i=0;i<1000000000;++i);
    times[j]=t.elapsed();
  }

  std::cout<<"Integer Operations"<<std::endl;
  for(int j=0;j<20;++j)
  {
    std::cout<<times[j]<<"s"<<std::endl;
  }

  return 0;
}
