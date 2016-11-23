#include "binary_tree.h"
#include <iostream>
#include "rb.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
  using yuq::binary_tree;
  using yuq::rb;
  rb<int> tree{5,8,2,4,3,7,1};
  tree.show();
  tree.left_rot(2);
  cout << "After left rotation 2:" << endl;
  tree.show();
  cout << "After right rotation 5:" << endl;
  tree.right_rot(5);
  tree.show();

  return 0;
}
  /* /1* binary_tree<int> b; *1/ */
  /* /1* b.insert(2); *1/ */
  /* /1* b.insert(4); *1/ */
  /* /1* b.search(3); *1/ */
  /* /1* b.show(); *1/ */
  /* /1* b.successor(b.search(2))->show(); *1/ */
  /* /1* std::cout << std::endl; *1/ */
  
  /* binary_tree<int> b2{5,26,9,6,1,62,3}; */
  /* b2.show(); */
  /* /1* b2.min()->show(); *1/ */
  /* std::cout << std::endl; */
  /* std::cout << "What to remove?" << std::endl; */
  /* int to_remov; */
  /* std::cin >> to_remov; */
  /* b2.remove(to_remov); */
  /* b2.show(); */
  /* std::cout << std::endl; */
