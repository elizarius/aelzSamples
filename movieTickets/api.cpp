#include "api.h"
#include "Schema.h"
#include "UsersDb.h"
#include "SessionsDb.h"
#include "TheatersDb.h"

#include <iostream>
#include <mutex>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;
using namespace movie;

std::mutex mtx_cr;
std::mutex mtx_del;
std::mutex mtx_admcr;
std::mutex mtx_ses_cr;
std::mutex mtx_ses_del;

RetCode User::create(std::string userid, std::string password) {

  if (isExist(userid))  {
    cout <<"Error:  user already exist: "<<userid<<endl;
    return RC_USER_EXIST;
  }

  Schema & schema = Schema::Instance();
  Db* usersDb = schema.getHandler("users");

  if (usersDb) {
    usersType & usersMap  = dynamic_cast<UsersDb *>(usersDb)->getDb();
    mtx_cr.lock();
    usersMap.insert(usersType::value_type (userid,
                                           new UserData(userid, password, false)));
    mtx_cr.unlock();
  }
  return RC_SUCCESS;
}

RetCode User::remove(std::string userid, std::string password) {
  if (!isExist(userid))  {
    cout <<"Warning: does not exist "<<userid<<endl;
    return RC_USER_NOT_EXIST;
  }

  Schema & schema = Schema::Instance();
  Db* usersDb = schema.getHandler("users");

  if (usersDb) {

    usersType & usersMap  = dynamic_cast<UsersDb *>(usersDb)->getDb();
    auto it  =  usersMap.find(userid);

    if (it->second->_password != password) {
      cout <<"Error: wrong password for user: "<<userid<<endl;
      return RC_WRONG_PASSWORD;
    }

    mtx_del.lock();
    usersMap.erase(it);
    mtx_del.unlock();
  }
  return RC_SUCCESS;
}

bool User::isExist(std::string userid) {

  Schema & schema = Schema::Instance();
  Db* usersDb = schema.getHandler("users");
  if (usersDb) {
    usersType & usersMap  = dynamic_cast<UsersDb *>(usersDb)->getDb();
    auto it  =  usersMap.find(userid);
    if (it == usersMap.end()) {
      return false ;
    }
    return true;
  }
}

int Session::create(std::string userid, std::string password) {

  Schema & schema = Schema::Instance();
  Db* usersDb = schema.getHandler("users");
  if (usersDb) {
    bool isOkUser = dynamic_cast<UsersDb *>(usersDb)->isValidUser(userid, password);
    if (!isOkUser) {
      cout <<"Error: wrong user credentials: "<<userid<<endl;
      return 0;
    }
  }

  /* generate session id   */
  std::srand(std::time(nullptr)); // use current time as seed for random generator
  int session_id  = std::rand();

  Db* sessionsDb = schema.getHandler("sessions");
  if (sessionsDb) {
    sessionsType & sessions  = dynamic_cast<SessionsDb *>(sessionsDb)->getSessions();
    mtx_ses_cr.lock();
    sessions.insert(sessionsType::value_type(session_id, new SessionData(session_id)));
    mtx_ses_cr.unlock();
  }
  cout<<__FUNCTION__<<"() session created with id:  "<<session_id<<endl;
  return session_id;
}

RetCode Session::remove(int session_id) {

  Schema & schema = Schema::Instance();
  Db* sessionsDb = schema.getHandler("sessions");
  if (sessionsDb) {
    sessionsType & sessions  = dynamic_cast<SessionsDb *>(sessionsDb)->getSessions();
    auto it  =  sessions.find(session_id);
    if (it == sessions.end()) {
      cout <<"Warning: session does not exist: "<<endl;
      return RC_SUCCESS;
    }
    mtx_ses_del.lock();
    delete it->second;
    it->second = 0;
    sessions.erase(it);
    mtx_ses_del.unlock();
  }
  return RC_SUCCESS;
}

std::vector<std::string>  Session::getTheaters() {

  std::vector<std::string> theaterNames;
  Schema & schema = Schema::Instance();
  Db* theaDb = schema.getHandler("theaters");

  if (theaDb) {
    theatersType & theaters  = dynamic_cast<TheatersDb *>(theaDb)->getTheaters();
    for (auto it = theaters.begin(); it != theaters.end(); ++it) {
      theaterNames.push_back(it->first);
    }
  }
  return theaterNames;
}

TimeMovieSeatsType Session::getBookingInfo(std::string theater_name) {
  TimeMovieSeatsType tms;
  Schema & schema = Schema::Instance();
  Db* theaDb = schema.getHandler("theaters");

  if (theaDb) {
    theatersType & theaters  = dynamic_cast<TheatersDb *>(theaDb)->getTheaters();
    auto it = theaters.find(theater_name);
    if (it == theaters.end()) {
      cout <<"Error: theater does not exist: "<<endl;
      return tms;
    }

    tms = it->second->getBookings();
    return tms;
  }
}

std::vector<int>  Session::bookTickets(int session_id,
                                      std::string theater_name,
                                      std::string movie_name,
                                      std::string movie_time,
                                      int  number_seats) {
          
  Schema & schema = Schema::Instance();
  Db* sessionsDb = schema.getHandler("sessions");
  std::vector<int> reserved_tickets;

  //  1. check whether session is correct
  if (sessionsDb) {
    sessionsType & sessions  = dynamic_cast<SessionsDb *>(sessionsDb)->getSessions();
    auto it  =  sessions.find(session_id);
    if (it == sessions.end()) {
      cout <<"Error: session does not exist: "<<endl;
      return reserved_tickets;
    }
  }
  
  // 2. find get bookings per theater 
  Db* theaDb = schema.getHandler("theaters");

  if (!theaDb) {
    cout <<"Error: theaters DB does not exist"<<endl;
    return reserved_tickets;
  }

  theatersType & theaters  = dynamic_cast<TheatersDb *>(theaDb)->getTheaters();
  auto it = theaters.find(theater_name);
  if (it == theaters.end()) {
    cout <<"Error: theater does not exist: "<<theater_name<<endl;
    return reserved_tickets;
  }

  TimeMovieSeatsType & tms = it->second->getBookings();

  // 3. Find required time slot 
  auto it1 = tms.find(movie_time);
  if (it1 == tms.end()) {
    cout <<"Error: requested movie time does not exist: "<<movie_time<<endl;
    return reserved_tickets;
  }

 // 4. Find required movie in timeslot
  if ( it1->second.first != movie_name) {
    cout <<"Error: requested movie in time slot does not exist: "<<movie_name<<endl;
    return reserved_tickets;
  }

  // 5. Check whether enough free seats
  if ( it1->second.second.size() < number_seats) {
    cout <<"Error: not enough free seats for booking "<<endl;
    return reserved_tickets;
  }

  // 6. Move places from available to out vector 
  for (int i = 1; i <= number_seats; i++) {                                                                           
    reserved_tickets.push_back(it1->second.second.front());
    it1->second.second.pop_front();
  }
  return reserved_tickets;
}


RetCode Admin::create(std::string userid, std::string password) {

  RetCode rc = User::create(userid, password);
  if  (rc != 0) 
    return rc;
  
  Schema & schema = Schema::Instance();
  Db* usersDb = schema.getHandler("users");

  usersType & usersMap  = dynamic_cast<UsersDb *>(usersDb)->getDb();
  auto it  =  usersMap.find(userid);
  mtx_admcr.lock();
  it->second->_isAdmin = true;
  mtx_admcr.unlock();
  
  return RC_SUCCESS;
}

RetCode Admin::remove(std::string userid) {

  if (!isExist(userid))  {
    cout <<"Warning: does not exist "<<userid<<endl;
    return RC_SUCCESS;
  }

  Schema & schema = Schema::Instance();
  Db* usersDb = schema.getHandler("users");

  if (usersDb) {

    usersType & usersMap  = dynamic_cast<UsersDb *>(usersDb)->getDb();
    auto it  =  usersMap.find(userid);

    mtx_del.lock();
    usersMap.erase(it);
    mtx_del.unlock();
  }
  return RC_SUCCESS;
}

RetCode Admin::resetBookingInfo(std::string theater_name) {

  Schema & schema = Schema::Instance();
  Db* theaDb = schema.getHandler("theaters");

  if (!theaDb) {
    cout <<"Error: theaters DB does not exist"<<endl;
    return RC_DB_NOT_EXIST;
  }

  theatersType & theaters  = dynamic_cast<TheatersDb *>(theaDb)->getTheaters();
  auto it = theaters.find(theater_name);
  if (it == theaters.end()) {
    cout <<"Error: theater does not exist: "<<theater_name<<endl;
    return RC_DB_NOT_EXIST;
  }

  TimeMovieSeatsType & tms = it->second->getBookings();
  tms.clear();
  return RC_SUCCESS;
}

RetCode Admin::modify(std::string userid,
                 std::string old_password,
                 std::string new_password) {

  cout <<__FUNCTION__<<"() API NOT YET IMPLEMENTED"<<endl;
  return RC_NOT_IMPLEMENTED;
}
