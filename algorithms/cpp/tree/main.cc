#include "binary_tree.h"

int main()
{
  using yuq::binary_tree;
  binary_tree<int> b;
  b.insert(2);
  b.insert(4);
  b.search(3);
  b.show();

  return 0;
}
