#ifndef TIME_ROUTINE_H
#define TIME_ROUTINE_H

#include <iostream>
#include <climits>
#include <sstream>


void printTimeStamp(  )
{
   struct tm * current  ;
   time_t  now ;

   time (&now ) ;
   current = localtime(&now) ;

   std::cerr<<current->tm_mday<<"."<<(1+current->tm_mon)<<"." <<(1900+current->tm_year)<<" " ;

   if ((current->tm_hour)<10)
      std::cerr<<"0";
   std::cerr<<current->tm_hour<<":";

   if ((current->tm_min)<10)
      std::cerr<<"0";
   std::cerr<<current->tm_min<<":";

   if ((current->tm_sec)<10)
     std::cerr<<"0";
   std::cerr<<current->tm_sec<<" ";

}


#endif