#ifndef _SESSIONS_DB_
#define _SESSIONS_DB_

/**
 *  Db handler to process sessions
 */
#include "Db.h"
#include <map>
#include <iostream>
#include <string>


namespace movie {

  class SessionData {
    public:
      SessionData(int id):_sessionId(id) {}
      SessionData() {}
      virtual ~SessionData(){}

    private:
     int  _sessionId;

  };

  typedef std::map<int, SessionData *> sessionsType;

  class SessionsDb : public Db  {
    public:
      SessionsDb() {};
      ~SessionsDb(){};
      sessionsType & getSessions() {return _sessions;}

    private:
      sessionsType _sessions;
  };
}
#endif
