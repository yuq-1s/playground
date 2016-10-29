/**
 * 1. Implement a BST without equal elements.
 * 2. Add iterator facility to the tree.
 * 3. Implement a BST with equal elements.
 */

#ifndef YUQ_ALGO_BINARY_TREE_
#define YUQ_ALGO_BINARY_TREE_
#include <cassert>
#include <iostream>
namespace yuq{
template <typename Elem> class binary_tree{
private:
  struct node{
    Elem key_;
    node* parent_ = nullptr;
    node* left_ = nullptr;
    node* right_ = nullptr;
    node(Elem key, node* parent = nullptr,
      node* left = nullptr, node* right = nullptr) 
    : key_(key), parent_(parent), left_(left), right_(right) {}
  };
  node root_;
public:
  //template <typename Iterator> binary_tree(Iterator beg, Iterator ed);
  binary_tree() : root_(node(Elem())) {}
  const node* search(Elem key) const;
  void insert(Elem key);
  void show() const;
private:
  const node* do_search(Elem, const node*) const;
  void do_insert(Elem, node*);
  void do_show(const node*) const;
};

template<typename Elem>
inline const typename binary_tree<Elem>::node* binary_tree<Elem>::search(Elem key) const
{
  return do_search(key, &root_);
}

template<typename Elem>
inline const typename binary_tree<Elem>::node*
binary_tree<Elem>::do_search(Elem key, const node* current) const
{
  if (!current || current->key_ == key) return current;
  if (key < current->key_) return do_search(key, current->left_);
  return do_search(key, current->right_);
}

template<typename Elem>
inline void binary_tree<Elem>::insert(Elem key)
{
  do_insert(key, &root_);
}

template<typename Elem>
inline void binary_tree<Elem>::do_insert(Elem key, node* current)
{
  assert(current);
  assert(current->key_ != key);
  if(key < current->key_) {
    if(!current->left_) current->left_ = new node(key, current);
    else do_insert(key, current->left_);
  }
  else {
    if(!current->right_) current->right_ = new node(key, current);
    else do_insert(key, current->right_);
  }
}

template<typename Elem>
inline void binary_tree<Elem>::show() const
{
  do_show(&root_);
  std::cout << std::endl;
}

template <typename Elem>
inline void binary_tree<Elem>::do_show(const node* current) const
{
  if(!current)  return;
  do_show(current->left_);
  std::cout << current->key_ << ' ';
  do_show(current->right_);
}
}

#endif
