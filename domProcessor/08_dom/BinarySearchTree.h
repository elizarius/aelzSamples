#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

#include "Task.h"

namespace aelzns {

class Node {
  public:
    Node(int value, Node* left, Node* right)
    {
        this->value = value;
        this->left = left;
        this->right = right;
    }

    int getValue() const
    {
        return value;
    }

    Node* getLeft() const
    {
        return left;
    }

    Node* getRight() const
    {
        return right;
    }

  private:
    int value;
    Node* left;
    Node* right;
};

    
class BinarySearchTree : public Task {
  public:
    BinarySearchTree() {}
    virtual ~BinarySearchTree(){}
    virtual bool execute();
    bool contains(const Node& root, int value);
};
}
#endif
