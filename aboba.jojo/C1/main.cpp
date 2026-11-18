#include "classes.hpp"
#include <iostream>

int main()
{
  Ints arr(3, 0);
  arr.set(0, 10);
  std::cout << arr.get(0) << "\n";
}
