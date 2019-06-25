#include "BinarySearchTree.h"
#include <iostream>

// https://en.wikipedia.org/wiki/Binary_tree
// https://www.cs.cmu.edu/~adamchik/15-121/lectures/Trees/trees.html

using namespace std;
using namespace aelzns;

bool BinarySearchTree::contains(const Node& root, int value) {

  std::cout<<"\t"<<__PRETTY_FUNCTION__<<" checking for value:  "<<value<<endl;

  int rootValue = root.getValue();
  if (rootValue == value) {
    //std::cout<<"\t"<<__PRETTY_FUNCTION__<<" contains value:  ";
    return true;
  }

  int leftValue;
  if (value < rootValue) {
    // go to left node
    if (root.getLeft() !=0) {
      std::cout<<"\t"<<__PRETTY_FUNCTION__<<" check left node:  "<<endl;
      return BinarySearchTree::contains(*(root.getLeft()), value);
    }  else
        return false;
    }

    /* check right branch */
    int rightValue;
    if (root.getRight() !=0) {
      std::cout<<"\t"<<__PRETTY_FUNCTION__<<" check right node:  "<<endl;
      return BinarySearchTree::contains(*(root.getRight()), value);
    } 

  return false;
}


bool BinarySearchTree::execute() {
    Node n1(1, NULL, NULL);
    Node n3(3, NULL, NULL);
    Node n2(2, &n1, &n3);

    std::cout<<std::boolalpha<<BinarySearchTree::contains(n2, 3)<<std::endl;
    std::cout<<std::boolalpha<<BinarySearchTree::contains(n2, 2)<<std::endl;
    std::cout<<std::boolalpha<<BinarySearchTree::contains(n2, 1)<<std::endl;
    std::cout<<std::boolalpha<<BinarySearchTree::contains(n2, 5)<<std::endl;
    return true;
}
