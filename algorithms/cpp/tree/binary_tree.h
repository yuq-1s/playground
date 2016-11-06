/**
 * 1. Implement a BST without equal elements.
 * 2. Add iterator facility to the tree.
 * 3. Implement a BST with equal elements.
 * 4. Change parent_ to weak_ptr
 * 5. Add sentinel version
 */

#ifndef YUQ_ALGO_BINARY_TREE_
#define YUQ_ALGO_BINARY_TREE_
#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <iomanip>

namespace yuq{
template <typename Elem> class binary_tree{
private:
  struct node : std::enable_shared_from_this<node>{
    using node_ptr = std::shared_ptr<node>;
    Elem key_;
    node_ptr parent_ = nullptr;
    node_ptr left_ = nullptr;
    node_ptr right_ = nullptr;
    node(Elem key, node_ptr parent = nullptr,
      node_ptr left = nullptr, node_ptr right = nullptr) 
      : key_(key), parent_(parent), left_(left), right_(right) {}
    inline void show() const { std::cout << key_; }

    //Why can't I append 'const' here?????
    inline auto min()//const
    {
      if(!left_) return this->shared_from_this();
      return left_->min();
    }

    inline auto max() const
    {
      if(right_) return right_->max();
      return this->shared_from_this();
    }

    inline auto successor() //const
    {
      if(right_)  return right_->min();
      auto parent = parent_;
      auto r_child = this->shared_from_this();
      while(parent && r_child == right_){
        r_child = parent;
        parent = parent->parent_;
      }
      return parent;
    }
  };
public:
  using node_ptr = typename node::node_ptr;
  using node_weak = std::weak_ptr<node>;
private:
  node_ptr root_ = nullptr;
public:
  //template <typename Iterator> binary_tree(Iterator beg, Iterator ed);
  inline binary_tree() = default;
  inline binary_tree(std::initializer_list<Elem> il);
  inline auto search(const Elem& key) const;
  inline void insert(const Elem& key);
  inline void show() const;
  inline auto max() const { return root_.max(); }
  inline auto min() const { return root_.min(); }
  inline auto successor(const node_ptr& base) const { return base->successor();}
  inline void remove(node_ptr n);
  inline void remove(const Elem& ele) { remove(search(ele)); }
private:
  inline node_ptr do_search(const Elem&, const node_ptr&) const;
  inline void do_insert(const Elem&, const node_ptr&);
  inline void walk(const node_ptr&) const;
  inline void transplant(node_ptr, node_ptr);
  inline void postorder(node_ptr p, int indent) const;
};

template <typename Elem>
void binary_tree<Elem>::postorder(node_ptr p, int indent) const
{
  if(p) {
    if(p->right_) {
      postorder(p->right_, indent+4);
    }
    if (indent) {
      std::cout << std::setw(indent) << ' ';
    }
    if (p->right_) std::cout<<" /\n" << std::setw(indent) << ' ';
    std::cout<< p->key_ << "\n ";
    if(p->left_) {
      std::cout << std::setw(indent) << ' ' <<" \\\n";
      postorder(p->left_, indent+4);
    }
  }
}

template <typename Elem>
auto binary_tree<Elem>::search(const Elem& key) const
{
  //Doesn't matter if !root_
  return do_search(key, root_);
}

template<typename Elem>
typename binary_tree<Elem>::node_ptr
binary_tree<Elem>::do_search(const Elem& key, const node_ptr& current) const
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
  //walk(root_);
  postorder(root_, 16);
  std::cout << std::endl;
}

template <typename Elem>
void binary_tree<Elem>::walk(const node_ptr& current) const
{
  if(!current)  return;
  walk(current->left_);
  current->show();
  std::cout << ' ';
  walk(current->right_);
}

template <typename Elem>
binary_tree<Elem>::binary_tree(std::initializer_list<Elem> il)
{
  for(const auto& ele : il){
    insert(ele);
  }
}

template <typename Elem>
void binary_tree<Elem>::transplant(node_ptr target, node_ptr new_node)
{
  if(!target->parent_){
    root_ = new_node;
  }

  //parent get new child.
  else {
    if(target == target->parent_->right_){
      target->parent_->right_ = new_node;
    }
    else {
      target->parent_->left_ = new_node;
    }
  }

  //New child get parent.
  if(new_node)
    new_node->parent_ = target->parent_;
}

template <typename Elem>
void binary_tree<Elem>::remove(node_ptr target)
{
  if(!target) throw std::runtime_error("Deleting null element.");

  //target has 1 or 0 child
  if(!target->left_){
    transplant(target, target->right_);
  }
  else if(!target->right_){
    transplant(target, target->left_);
  }

  //target has 2 children
  else {
    auto succ = target->successor();
    if(succ != target->right_){
      transplant(succ, succ->right_);
      succ->right_ = target->right_;
      target->right_->parent_ = succ;
    }
    transplant(target, succ);
    succ->left_ = target->left_;
    target->left_->parent_ = succ;
  }
}

}

#endif
