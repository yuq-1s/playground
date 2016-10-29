/**
 * Double-linked list with sentinels
 * 1. Implementation with raw pointers as iterators.
 * 2. Implementation with iterators.
 * 3. Add begin(), end()
 * 4. Decouple node and data_node.
 */
#include <iostream>

namespace yuq{
template <typename Elem> class list{
private:
  struct data_node {
    data_node* prev_ = nullptr;
    data_node* next_ = nullptr;
    Elem data_;
    data_node(Elem val, data_node* p, data_node* n) 
      : data_(val), prev_(p), next_(n) {}
  };
private:
  data_node sentinel;
public:
  list() : sentinel(Elem(), &sentinel, &sentinel) {}
  void append(Elem val)
  {
    auto new_node = new data_node(val, sentinel.prev_, &sentinel);
    sentinel.prev_->next_ = new_node;
    sentinel.prev_ = new_node;
  }

  data_node* begin() { return sentinel.next_; }
  data_node* end()   { return &sentinel; }

  void show() 
  {
    for(auto ptr = begin();ptr != end();ptr = ptr->next_){
      std::cout << ptr->data_ << ' ';
    }
  }
};
}
    
int main() 
{
  using yuq::list;
  list<int> l;
  l.append(2);
  l.append(4);
  l.show();
}
