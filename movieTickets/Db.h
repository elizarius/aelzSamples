#ifndef _DB_H_
#define _DB_H_

#include <string>

namespace movie {

  /**
   *  Abstract class representing ticketing system DB object 
   */
  class Db {
    public:
      Db(){}
      virtual ~Db(){}
  };
}
#endif
