/**
 *  Chain implementation with usage double linkled list
 *  - Original position in middle of chain
 *  - If ring added to left side. left distance  increased
 *  - If ring added to right side right distance increased
 *  - If left side == right side, chain is looped all distances set to 0
 */

#include <iostream>
#include <list>
#include <iterator>

using namespace std;

class ChainRing
{
    public:
        ChainRing() {
         // std::cout <<"CR ChainRing called " <<std::endl;
        }
        virtual ~ChainRing() {
         std::cout <<"Destructor ChainRing called " <<std::endl;
        }

    private:
};

class Chain
{

    public:
        Chain(): leftDistance_(0),
                 rightDistance_(0)
        { }
        virtual ~Chain() {
            std::list<ChainRing *>::iterator it;

            int sz = chain_.size();
            for ( int i = 1; i <sz;  ++i ){

                std::cout<<"***** Chain size: "<< chain_.size()<<std::endl;
                if (!chain_.empty()) {
                    ChainRing * cr  =  chain_.back();
                    delete cr;
                    cr  = 0;
                    chain_.pop_back();
                 }
            }
            chain_.clear();

            std::cout<<"***** FINALLY in destructor,  Chain size: "<<
                chain_.size()<<std::endl;
       }

        void addLeft(ChainRing * ring)
        {
            chain_.push_front(ring);
            leftDistance_++;

        }

        void   addRight(ChainRing * ring) {
            chain_.push_back(ring);
            rightDistance_++;

        }

        int  loopChain(ChainRing * ring) {
            chain_.push_back(ring);
            chain_.push_front(ring);
            leftDistance_ = 0;
            rightDistance_ = 0;
        }

        int getLeftDistance() {
            return leftDistance_;
        }

        int getRightDistance() {
            return rightDistance_;
        }
        // return true when left ring eq right ring
        bool isLooped() {
            if (!chain_.empty()){
                if (chain_.front() ==  chain_.back()) {
                  std::cout<<"***** Chain finally looped **"<<std::endl;
                  return true;
                } else {
                  std::cout<<"***** Chain NOT YET LOOPED  looped **"<<std::endl;
                  return false;
                }
            }
        }


    private:
        int leftDistance_;
        int rightDistance_;
        std::list<ChainRing *> chain_;

};


int main ()
{
    Chain  chainDemo;
    for (int i = 1; i<=10; i++) {

        if ((i % 2) == 0) {

            ChainRing *  ringLeft  = new ChainRing;
            chainDemo.addLeft(ringLeft);
            std::cout<<"**********Left distance: ";
            std::cout<<chainDemo.getLeftDistance()<<std::endl;
        } else {
            ChainRing *  ringRight  = new ChainRing;
            chainDemo.addRight(ringRight);
            std::cout<<"**********Right distance: ";
            std::cout<<chainDemo.getRightDistance()<<std::endl;
        }
   }

    /* Now loop a chain **/

    ChainRing *  looper  = new ChainRing;
    chainDemo.loopChain(looper);
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

