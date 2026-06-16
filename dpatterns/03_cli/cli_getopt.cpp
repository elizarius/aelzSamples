#include <string>
#include <iostream>

extern "C"
{
#include <getopt.h>
}


using namespace std;

void print_message(char sender, string & msg)
{
    cout<<"Received message:" <<msg<<" from: "<<sender<<endl;
}

int main(int argc, char * argv[])
{
    struct option cliOptions[]=
    {
        {"classA", required_argument, 0, 'a'},
        {"classB", required_argument, 0, 'b'},
        {"classC", required_argument, 0, 'c'},
        {"help",   no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    int c;
    string print_usage = "Usage:   ./a.out  --classX| -X anyMessage \nExample: ./a.out --classA BLABLABLA";
    string message;

    while(-1 != (c = getopt_long(argc, argv, "a:b:c:h", cliOptions, NULL)))
    {
        switch(c)
        {
            case 'a':
                message = optarg;
                print_message(c, message);
                break;
            case 'b':
                message = optarg;
                print_message(c, message);
                break;

            case 'c':
                message = optarg;
                print_message(c, message);
                break;

            case 'h':
                cout<<print_usage<<endl;
                break;

            default:
                cout << "cliManager : unrecognized argument "<<c<<endl;
                break;
        }

    } // END WHILE

    return 0 ;
}

