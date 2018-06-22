#include <iostream>
#include <string>
#include <exception>
#include <chrono>
#include <ctime>
#include <ratio>


/* Custom exception example
 * see also exception in aelzSamples/include
 *
 */
using namespace std;
using namespace std::chrono;

class EXC : public std::exception {
    private:
        int level;

    public:
        EXC(int a) {
            level = a;
        } ;

        int get_val() {
            cout << "exception generated with number: "<< level<< endl ;
            return 0;
        }


};


int gen_1(int& i, int flag){

    if  (i==flag)
        throw  EXC(i);
    else {
        gen_1(++i,flag);
    }
    return 0 ;
}


int main()
{
    int fnumber=0 , duration ;
    system_clock::time_point t1 = system_clock::now();
    try {
        gen_1(++fnumber,1000);
    }
    catch (EXC & EXEPT) {
        system_clock::time_point t2 = system_clock::now();
        auto dur = duration_cast<microseconds>( t2 - t1 ).count();
        cout <<"duration in microseconds = "<<dur<<endl;
        cout <<"Exception WHAT:  "<<EXEPT.what() <<endl;
        EXEPT.get_val();
    }
    return 0;
}
