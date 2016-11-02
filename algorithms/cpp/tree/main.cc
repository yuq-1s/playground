#include "binary_tree.h"
#include <iostream>

int main()
{
  using yuq::binary_tree;
  binary_tree<int> b;
  b.insert(2);
  b.insert(4);
  b.search(3);
  b.show();
  b.successor(b.search(2))->show();
  std::cout << std::endl;

  binary_tree<int> b2{5,26,9,6,1,62,3};
  b2.show();

  return 0;
}
