#include <stdexcept>
#include <iostream>
#include <list>


class TrainComposition
{
public:
    void attachWagonFromLeft(int wagonId)
    {
        trainChain.push_front(wagonId);
    }

    void attachWagonFromRight(int wagonId)
    {
         trainChain.push_back(wagonId);
    }

    int detachWagonFromLeft()
    {
       int wagId = trainChain.front(); 
       trainChain.pop_front();
       return wagId;
    }

    int detachWagonFromRight()
    {
       int wagId = trainChain.back(); 
       trainChain.pop_back();
       return wagId;
    }
    
private:
   std::list<int> trainChain;
    
    
    
};

int main()
{
    TrainComposition tree;
    tree.attachWagonFromLeft(7);
    tree.attachWagonFromLeft(13);
    std::cout << tree.detachWagonFromRight() << "\n"; // 7 
    std::cout << tree.detachWagonFromLeft(); // 13
}
