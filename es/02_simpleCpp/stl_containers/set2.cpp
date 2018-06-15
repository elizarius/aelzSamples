#include <iostream>
#include <set>

using namespace std ;
int main()
{
    //type of the collection
    typedef std::set<unsigned int> IntSet;

    IntSet coll;

    /* insert elements from 1 to 6 order
    *- value 1 inserted twice
    */
    coll.insert(3);
    coll.insert(1);
    coll.insert(5);
    coll.insert(4);
    coll.insert(1);
    coll.insert(6);
    coll.insert(2);




    /* print all elements
     *- iterate over all elements
    */
    IntSet::const_iterator pos;
    IntSet::const_iterator pos_1;

    pos_1 = coll.find(5) ;
	if ( pos_1 != coll.end() ) {
	    std::cout<< "Found pos_1 : "<<(*pos_1)<<std::endl;
        std::cout<< "Container size  : "<<coll.size()<<std::endl;
	}
    else {
	    std::cout<< "pos_1  not found "<<std::endl;
        std::cout<< "Container size  : "<<coll.size()<<std::endl;
	}

    for (pos = coll.begin(); pos != coll.end(); ++pos) {
        std::cout << *pos << ' '<<endl;
    }
    std::cout << std::endl;

   }

