#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <istream>
#include <iterator>
#include <cstdlib>
#include <queue>
#include <thread>
#include <chrono>
#include <mutex>

//  g++ threads.cpp  -std=c++11 -lpthread
// ./float.sh | a.out */

using namespace std;

typedef std::queue<double> dqType;
std::mutex mtx;

/*
*   Singleton to process input queue
*/
class queueHandler {
    public:
        static queueHandler& Instance() {
            static queueHandler qh;
            return qh;
        }

        virtual  ~queueHandler(){}

        dqType & getQueue() {
            return _inputQueue;
        }

    private:
        queueHandler (){}                             // ctor is hidden
        queueHandler(queueHandler const&);            // copy ctor is hidden
        queueHandler& operator=(queueHandler const&); // assignmet op is hidden

        dqType _inputQueue;
};


// Read double floating numbers for stdin, first  thread entry function
void readN()
{
    std::string s;
    double in_num;

    queueHandler & qh =queueHandler::Instance();
    dqType & inputQueue =  qh.getQueue();
    while (!cin.eof()) {
        std::getline(std::cin, s);
        if(!s.empty()) {
            in_num = std::stof(s);
            mtx.lock();
            inputQueue.push(in_num);
            mtx.unlock();
        }
    }
    std::cout<<"***** Finished reading from file"<<std::endl;
}


// Write numbers for stdin, second thread entry function
void writeN()
{
    queueHandler & qh =queueHandler::Instance();
    dqType & inputQueue =  qh.getQueue();
    std::ofstream myfile;
    myfile.open ("threads_out.txt");

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    while (inputQueue.size() > 0) {

        mtx.lock();
        myfile <<inputQueue.front()<<std::endl;
        inputQueue.pop();
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    myfile.close();
    std::cout<<"***** Finished writing  to file"<<std::endl;
}


int main()
{
    thread first(readN);
    thread second(writeN);

    first.join();
    second.join();

    return 0;
}
