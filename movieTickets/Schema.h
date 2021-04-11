#ifndef _SCHEMA_H_
#define _SCHEMA_H_

#include <map>
#include <string>
#include "Db.h"

namespace movie {
  typedef std::map<std::string, Db *> argHandlersType;

  /*
  * Movie DBs storage.
  * Like postgre, schema contains list of DBs (tables in terms of postgresql)
  * Signleton pattern used to reach from several classes.
  */
  class Schema {
    public:
      static Schema& Instance() {
        static Schema ch;
        return ch;
      }

      virtual  ~Schema();
      void init();

      /* run all handlers in loop */
      Db * getHandler(std::string arg);

    private:
      Schema (){}                         // default ctor is hidden
      Schema(Schema const&);              // copy ctor is hidden
      Schema& operator=(Schema const&);   // assignment op is hidden

    argHandlersType _handlers;
  };
}
#endif
