#include "binary_tree.h"

namespace yuq{
template <typename Elem>
class rb : public binary_tree<Elem>{
public:
  using node_ptr = typename binary_tree<Elem>::node_ptr;
  rb(const std::initializer_list<Elem>& il){
    for (const auto& ele :il) insert(ele);
  }
  inline void insert(const Elem&);
  inline void left_rot(node_ptr);
  inline void left_rot(const Elem& key) { left_rot(this->search(key)); }
  inline void right_rot(node_ptr);
  inline void right_rot(const Elem& key) { right_rot(this->search(key)); }
private:
  /* inline void fix(); */
};

template <typename Elem>
void rb<Elem>::left_rot(node_ptr current)
{
  auto r_child = current->right_;
  current->right_ = r_child->left_;
  if(r_child->left_){
    r_child->left_->parent_ = current;
  }
  this->transplant(current, r_child);
  r_child->left_ = current;
  current->parent_ = r_child;
}

template <typename Elem>
void rb<Elem>::right_rot(node_ptr current)
{
  auto l_child = current->left_;
  current->left_ = l_child->right_;
  if(l_child->right_){
    l_child->right_->parent_ = current;
  }
  this->transplant(current, l_child);
  l_child->right_ = current;
  current->parent_ = l_child;
}

template <typename Elem>
void rb<Elem>::insert(const Elem& key)
{
  binary_tree<Elem>::insert(key);
}

}
