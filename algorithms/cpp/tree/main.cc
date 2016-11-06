#include "binary_tree.h"
#include <iostream>

int main(int argc, char* argv[])
{
  using yuq::binary_tree;
  /* binary_tree<int> b; */
  /* b.insert(2); */
  /* b.insert(4); */
  /* b.search(3); */
  /* b.show(); */
  /* b.successor(b.search(2))->show(); */
  /* std::cout << std::endl; */
  
  binary_tree<int> b2{5,26,9,6,1,62,3};
  b2.show();
  /* b2.min()->show(); */
  std::cout << std::endl;
  std::cout << "What to remove?" << std::endl;
  int to_remov;
  std::cin >> to_remov;
  b2.remove(to_remov);
  b2.show();
  std::cout << std::endl;

  return 0;
}
