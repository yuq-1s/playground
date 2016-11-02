/**
 * 1. Implement a BST without equal elements.
 * 2. Add iterator facility to the tree.
 * 3. Implement a BST with equal elements.
 */

#ifndef YUQ_ALGO_BINARY_TREE_
#define YUQ_ALGO_BINARY_TREE_
#include <cassert>
#include <iostream>
#include <limits>
#include <memory>

namespace yuq{
template <typename Elem> class binary_tree{
private:
  struct node{
    using node_ptr = std::shared_ptr<node>;
    Elem key_;
    node_ptr parent_ = nullptr;
    node_ptr left_ = nullptr;
    node_ptr right_ = nullptr;
    node(Elem key, node_ptr parent = nullptr,
      node_ptr left = nullptr, node_ptr right = nullptr) 
    : key_(key), parent_(parent), left_(left), right_(right) {}
  };
  using node_ptr = typename node::node_ptr;
  std::shared_ptr<node> root_ = nullptr;
public:
  //template <typename Iterator> binary_tree(Iterator beg, Iterator ed);
  inline binary_tree() = default;
  inline auto search(const Elem& key) const;
  inline void insert(const Elem& key);
  inline auto max() const;
  inline auto min() const;
  inline void show() const;
private:
  inline auto do_search(const Elem&, const node_ptr&) const;
  inline void do_insert(const Elem&, const node_ptr&);
  inline void do_show(const node_ptr&) const;
};

template<typename Elem>
auto binary_tree<Elem>::search(const Elem& key) const
{
  //Doesn't matter if !root_
  return do_search(key, root_);
}

template<typename Elem>
auto binary_tree<Elem>::do_search(const Elem& key, const node_ptr& current) const
{
  if (!current || current->key_ == key) return current;
  if (key < current->key_) return do_search(key, current->left_);
  return do_search(key, current->right_);
}

template<typename Elem>
void binary_tree<Elem>::insert(const Elem& key)
{
  if(root_){
    do_insert(key, root_);
  }
  else{
    root_ = std::make_shared<node>(key);
  }
}

template<typename Elem>
void binary_tree<Elem>::do_insert(const Elem& key, const node_ptr& current)
{
  assert(current);
  assert(current->key_ != key);
  if(key < current->key_) {
    if(!current->left_) current->left_ = std::make_shared<node>(key, current);
    else do_insert(key, current->left_);
  }
  else {
    if(!current->right_) current->right_ = std::make_shared<node>(key, current);
    else do_insert(key, current->right_);
  }
}

template <typename Elem>
void binary_tree<Elem>::show() const
{
  //Doesn't matter if !root_
  do_show(root_);
  std::cout << std::endl;
}

template <typename Elem>
void binary_tree<Elem>::do_show(const node_ptr& current) const
{
  if(!current)  return;
  do_show(current->left_);
  std::cout << current->key_ << ' ';
  do_show(current->right_);
}

template <typename Elem>
auto binary_tree<Elem>::max() const
{
  const auto current_node = root_;
  while(current_node && current_node->right_){
    current_node = current_node->right_;
  }
  return current_node;
}

template <typename Elem>
auto binary_tree<Elem>::min() const
{
  const auto current_node = root_;
  while(current_node && current_node->left_){
    current_node = current_node->left_;
  }
  return current_node;
}

}
#endif
