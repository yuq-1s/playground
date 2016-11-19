#include "binary_tree.h"
#include <stack>

using namespace std;
using pnode = yuq::binary_tree<int>::node_ptr;
void fuck(pnode n)
{
  if(!n)  return;
  fuck(n->left_);
  fuck(n->right_);
  cout << n->key_ << ' ';
}

void iterfuck(pnode n)
{
  struct SnapShorStruct {
    pnode n;
    int stage;
    SnapShorStruct(pnode node, int s):n(node), stage(s) {}
  };
    stack<SnapShorStruct> snapshotstack;

    snapshotstack.emplace(n, 0);

    while(!snapshotstack.empty()){
      auto currentSnapshot = snapshotstack.top();
      snapshotstack.pop();

      switch (currentSnapshot.stage){
        case 0:
          currentSnapshot.stage = 1;
          snapshotstack.push(currentSnapshot);
          if(currentSnapshot.n->left_){
            snapshotstack.emplace(currentSnapshot.n->left_, 0);
          }
          break;
        case 1:
          currentSnapshot.stage = 2;
          snapshotstack.push(currentSnapshot);
          if(currentSnapshot.n->right_){
            snapshotstack.emplace(currentSnapshot.n->right_, 0);
          }
          break;
        case 2:
          cout << currentSnapshot.n->key_ << ' ';
          break;
      }
    }
}

int main()
{
  yuq::binary_tree<int> a{4,8,6,9,2,1,3};
  fuck(a.root());
  cout << endl;
  iterfuck(a.root());
  cout << endl;
}

