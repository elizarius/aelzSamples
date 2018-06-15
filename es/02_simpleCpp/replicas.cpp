#include <iostream>
#include <string>
#include <map>

// Use map container to eliminate / read off repeated records
//
enum ReplStatusType
{
    RS_NOT_AVAIL,
    RS_AVAILABLE,
};

//type of the collection
typedef std::map<std::string,ReplStatusType> ReplicaMapType ;

using namespace std ;
int main()
{
    ReplicaMapType coll;        //map container.

    /* insert elements from 1 to 6 in arbitray order
     *- value 1 gets inserted twice
    */
    coll.insert(pair<std::string,ReplStatusType>("node_1 ",RS_NOT_AVAIL));
    coll.insert(pair<std::string,ReplStatusType>("node_2 ",RS_NOT_AVAIL));
    coll.insert(pair<std::string,ReplStatusType>("node_2 ",RS_NOT_AVAIL));

       /* print all elements
        *- iterate over all elements
        */
       ReplicaMapType::const_iterator pos;
       for (pos = coll.begin(); pos != coll.end(); ++pos)
       {
           std::cout <<(*pos).first <<static_cast<int>((*pos).second)<<std::endl;
       }

   }




