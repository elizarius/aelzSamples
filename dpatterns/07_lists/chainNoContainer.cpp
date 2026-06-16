/**
 *  Chain implementation without list container
 *  - Original position in middle of chain
 *  - If ring added to left side. left distance  increased
 *  - If ring added to right side right distance increased
 *  - If left side == right side, chain is looped all distances set to 0
 */

#include <iostream>
#include <list>
#include <iterator>

using namespace std;

class Ring
{
    public:
        Ring() {
        }
        virtual ~Ring() {
         std::cout <<"Destructor Ring called " <<std::endl;
        }
};

class  Node
{
    public:
        Node() {
            next = 0;
            prev = 0;
        }

        Node(Ring & dt,  Node *ne = 0, Node *pre = 0) {
            data = dt;
            next = ne;
            prev = pre;
        }
    //private:
        Ring data;
        Node* next;
        Node* prev;

};




class Chain
{

    public:
        Chain(): leftDistance_(0),
                 rightDistance_(0)
        { }
        virtual ~Chain() {}
        bool    isEmpty() {
            return head_ == 0;

        }
        int getLeftDistance() {
            return leftDistance_;
        }

        int getRightDistance() {
            return rightDistance_;
        }



        void addLeft(Ring & ring)
        {
            if (head_ == 0){
                head_ = new Node(ring);
                std::cout<<"***** addLeft, first head **"<<std::endl;
            } else {
                std::cout<<"***** addLeft, update exisitng  heads **"<<std::endl;
                Node * temp = new Node(ring, head_);
                head_->prev = temp;
                head_ = temp;

            }
            leftDistance_++;
       }

        void   addRight(Ring & ring) {
            if (tail_ == 0){
                tail_ = new Node(ring);
                std::cout<<"***** addRight, first tail **"<<std::endl;
            } else {
                std::cout<<"***** addRight, update exisitng  tails **"<<std::endl;
                Node * temp = new Node(ring, 0, tail_);
                tail_->next = temp;
            }
            rightDistance_++;
        }

        void loopChain(Ring & ring) {
            Node * temp = new Node(ring);
            tail_ = temp;
            head_ = temp;
            leftDistance_ = 0;
            rightDistance_ = 0;
        }


        // return true when left ring eq right ring
        bool isLooped() {

            if ((tail_) && (head_)) {
                if (tail_  == head_)
                    std::cout<<"***** Chain finally looped **"<<std::endl;
                    return true;
            } else {
                  std::cout<<"***** Chain NOT YET LOOPED  looped **"<<std::endl;
                  return false;
            }

            return true;
        }



    private:
        int leftDistance_;
        int rightDistance_;
        Node*   head_;
        Node*   tail_;

};


int main ()
{
    Chain  chainDemo;
    Ring  ringLeft;
    Ring  ringRight;

    for (int i = 1; i<=10; i++) {

        if ((i % 2) == 0) {
            chainDemo.addLeft(ringLeft);
            std::cout<<"**********Left distance: ";
            std::cout<<chainDemo.getLeftDistance()<<std::endl;
        } else {
            chainDemo.addRight(ringRight);
            std::cout<<"**********Right distance: ";
            std::cout<<chainDemo.getRightDistance()<<std::endl;
        }
   }

    /* Now loop a chain **/
    chainDemo.loopChain(ringLeft);
    std::cout<<"**********Looping chain**** "<<std::endl;
    std::cout<<"**********Left distance: ";
    std::cout<<chainDemo.getLeftDistance()<<std::endl;
    std::cout<<"**********Right distance: ";
    std::cout<<chainDemo.getRightDistance()<<std::endl;

    if (chainDemo.isLooped()){
        std::cout<<"Chaining competed, EXIT "<<std::endl;
        return 0;
    } else  {
        std::cout<<"ERROR: WRONG LOOPING";
        return 1;
    }

    return 0 ;

}

