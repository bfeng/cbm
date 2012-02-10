#include "stdafx.hpp"

void one_thread()
{
  int mem;
  std::cout << "size " << sizeof(mem) << std::endl;
}

int main()
{
  one_thread();
  return 0;
}
