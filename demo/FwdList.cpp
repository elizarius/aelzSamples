// sample forward_list / single linked list operations in C++
// double linked list operations are similar but extended
// to both ends


#include <iostream>
#include <forward_list>
#include <iterator>
#include "FwdList.h"

using namespace std;
using namespace aelzns;


//  run demo directly from cli handler
//  Insert members to start of list
//  Insert members to end of list is impossible because forward list

int FwdList::processCli(int c, char * argv[]) {

    std::forward_list<int> mylist = { 34, 77, 16, 2 };
    std::forward_list<int>::iterator it;
    std::cout << "mylist contains:";
    for ( it = mylist.begin(); it != mylist.end(); ++it )
        std::cout << ' ' << *it;
    std::cout <<std::endl;
    
    // Replace first node
    mylist.front() =11;

    std::cout << "mylist modified:";
    for ( it = mylist.begin(); it != mylist.end(); ++it )
        std::cout << ' ' << *it;
    std::cout <<std::endl;

    // Insert before first node
    mylist.insert_after ( mylist.before_begin(), 99 );
    mylist.insert_after ( mylist.begin(), 1025 );
    it = mylist.begin();


    //   Insert into beginning of list:
    mylist.push_front(200);

    // Insert at end could not be done easily, below is not working
    //mylist.insert_after ( mylist.end(), 1111 );


    std::cout << "mylist updated:";
    for (it = mylist.begin(); it != mylist.end(); ++it )
        std::cout << ' ' << *it;
    std::cout <<std::endl;


    std::cout <<"Now in sorted order: \t ";
    mylist.sort();
    for (it = mylist.begin(); it != mylist.end(); ++it )
        std::cout << ' ' << *it;
    std::cout <<std::endl;

    return 0;
}
