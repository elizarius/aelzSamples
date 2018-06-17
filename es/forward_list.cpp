// sample forward_list / single linked list operations in C++
// double linked list generally oprations are similar but extended
// to both ends

#include <iostream>
#include <forward_list>
#include <iterator>

using namespace std;

int main ()
{
    std::forward_list<int> mylist = { 34, 77, 16, 2 };
      std::forward_list<int>::iterator it;
    std::cout << "mylist contains:";
    for ( it = mylist.begin(); it != mylist.end(); ++it )
        std::cout << ' ' << *it;
    std::cout <<std::endl;


    std::cout <<"Insert members to start and end of list:  ";

    // Replace first node
    mylist.front() =11;

    // Insert before first node
    mylist.insert_after ( mylist.before_begin(), 99 );
    mylist.insert_after ( mylist.begin(), 1025 );
    it = mylist.begin();

   //   Insert into beginning of list:
   mylist.push_front(200);

    // Insert at end could not be done easily, below is not working
    //mylist.insert_after ( mylist.end(), 1111 );


    for (it = mylist.begin(); it != mylist.end(); ++it )
        std::cout << ' ' << *it;
    std::cout <<std::endl;


    std::cout <<"Now in sorted order: \t ";
    mylist.sort();
    for (it = mylist.begin(); it != mylist.end(); ++it )
        std::cout << ' ' << *it;
    std::cout <<std::endl;

    return 0 ;

}

