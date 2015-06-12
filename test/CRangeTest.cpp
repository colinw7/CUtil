#include <CRange/CRange.h>

#include <iostream>

int
main(int argc, char **argv)
{
  for (auto i : IRange::of({1, 2, 4, 8}))
    std::cout << i << std::endl;

  std::cout << "----" << std::endl;

  for (auto i : IRange::range(1, 3))
    std::cout << i << std::endl;

  std::cout << "----" << std::endl;

  for (auto i : IRange(0, 21, 2))
    std::cout << i << std::endl;

  return 0;
}
