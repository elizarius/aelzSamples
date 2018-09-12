#include <stdexcept>
#include <string>
#include <iostream>

class Node
{
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

class BinarySearchTree
{
public:
    static bool contains(const Node& root, int value)
    {
        int rootValue = root.getValue();
        if (rootValue == value) {
            std::cout<<"AELZ step 1 equal: ";
            return true;
        }

         int leftValue;
         if (value < rootValue) {
            // go to left node
            if (root.getLeft() !=0) {
                std::cout<<"AELZ step 2 in left: ";
                return BinarySearchTree::contains(*(root.getLeft()), value);
            }  else
             return false;
        }

        /* check right branch */
        int rightValue;
        if (root.getRight() !=0){
            std::cout<<"AELZ step 3 in right:";
            return BinarySearchTree::contains(*(root.getRight()), value);
        } return false;

     return false;
    }
};

#ifndef RunTests
int main()
{
    Node n1(1, NULL, NULL);
    Node n3(3, NULL, NULL);
    Node n2(2, &n1, &n3);

    std::cout << BinarySearchTree::contains(n2, 3)<<std::endl;
    std::cout << BinarySearchTree::contains(n2, 2)<<std::endl;
    std::cout << BinarySearchTree::contains(n2, 1)<<std::endl;
    std::cout << BinarySearchTree::contains(n2, 5)<<std::endl;
}
#endif
