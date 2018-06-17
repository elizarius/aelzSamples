#include <string>
#include <iostream>

using namespace std;

void print_message(char sender, string & msg)
{
    cout<<"Received message:" <<msg<<" from: "<<sender<<endl;
}


int main(int argc, char * argv[])
{
    string print_usage = "Usage:   ./a.out --classX|-X  anyMessage \nExample: ./a.out --classA BLABLABLA";
    if (argc < 2) {
    //Tell the user how to run the program
        std::cerr <<print_usage << std::endl;
        return 1;
    }
    /*
     *  Then create two vectors or map with arg / optarg pair,
     *  map them to hierarchical handler instance and call instances in cycle
     *  or  in need basis.
     *  Like interface handler example or:
     *  http://www.cplusplus.com/articles/DEN36Up4/
     *
     */
    return 0 ;
}

