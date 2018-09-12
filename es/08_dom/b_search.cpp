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
        if (rootValue == value;
            return true;

        std::cout<<"AELZ_01 step 1 pass"<<std::endl;

         int leftValue;
         if (value < rootValue) {
            // go to left node
            if (root.getLeft() !=0) {
                leftValue = root.getLeft()->getValue();
                if (leftValue == value)
                return true;
            }  else
             return false;
        }
        std::cout<<"AELZ_02 step 2 pass"<<std::endl;


         int rightValue;
         if (root.getRight() !=0){
             rightValue = root.getRight()->getValue();
              if (rightValue == value)
                return true;
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

    std::cout << BinarySearchTree::contains(n2, 3);
//    std::cout << BinarySearchTree::contains(n2, 5);
//    std::cout << BinarySearchTree::contains(n2, 2);

}
#endif
