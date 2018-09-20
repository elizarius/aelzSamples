#include <iostream>
#include <string>

using namespace std;
class Singleton
{
    private:
        static Singleton s;
        int i;
        Singleton (int x):i(x){}
        void operator=(Singleton&);
        Singleton(const Singleton&);


    public :
        static Singleton& getHandle() { return s;}
        int getValue() {return i;}
        void setValue(int x) {i=x;}
};

/* Only static members can be adressed via scope resolution
   operator  and not inside of main , why ?  */

Singleton Singleton::s(47);

int main ()
{
    int x=10;
    Singleton& p = Singleton::getHandle();

    cout <<"Singleton S value =" <<p.getValue()<<endl;
    Singleton& p2 = Singleton::getHandle();
    p2.setValue(9) ;
    cout <<"Singleton S value now = "<<p2.getValue()<<endl;


    cout <<"Singleton S via static member now = "<<(Singleton::getHandle()).getValue()<<endl;
}
