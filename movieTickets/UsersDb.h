#ifndef _USERS_DB_
#define _USERS_DB_

/**
 *  Db with users
 *  Db handler to process transactions
 */
#include "Db.h"
#include <map>
#include <iostream>
#include <string>


namespace movie {

    class UserData {
    public: 
      UserData(std::string userid,
               std::string password,
               bool isAdmin): _userid(userid),
                              _password(password),
                              _isAdmin(isAdmin) {}
      public:
        std::string  _userid;
        std::string  _password;
        bool _isAdmin;
  };

  typedef std::map<std::string, UserData *> usersType;

  class UsersDb : public Db  {
    public:
      UsersDb() {};

      virtual~UsersDb(){
        for (auto theIt = _users.begin(); theIt != _users.end(); ++theIt) {
          delete theIt->second;
          theIt->second = 0;
        }
        _users.clear();
      };

      usersType & getDb() {return _users;}

      bool isValidUser(std::string userid, std::string pwd) {      
        auto it  = _users.find(userid);
        if (it == _users.end()) {
          return false;
        }
        if (it->second->_password != pwd) {
          std::cout <<"Error: wrong password for user: "<<userid<<std::endl;
          return false;
        } 
        return true;
      } 
    private:
      usersType _users;
  };
}
#endif
