#ifndef _Hh_H_
#define _Hh_H_

#include "cli.h"

typedef std::map<std::string, Cli *> argHandlersType ;
/*
*  AELZ: singleton to process different base hansdlers 
*  AELZ: canonical class descriptpor: def conbstructor, descr, ass operator
*   Singleton, includes argument handlers storage.Handlers should be reachable 
*   not only from main but from other classes. 
*   AELZ_02 : add destructor , where handlers will be released.  
*/
class Handlers
{
    public:
        static Handlers& Instance() 
        {
          static Handlers ch;
          return ch;
        }

        virtual  ~Handlers(); 
        void init() ;

        Cli * getHandler(const char * arg);


    private:
      Handlers (){}                          // ctor is hidden
      Handlers(Handlers const&);            // copy ctor is hidden
      
      Handlers& operator=(Handlers const&); // assignmet op is hidden

      argHandlersType mHandlers;
}; 

#endif
