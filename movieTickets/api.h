/**
* @file     api.h
* @short    API specification for movie ticket booking system
*/
#ifndef _MOVIE_API_H_
#define _MOVIE_API_H_

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <list>


namespace movie {

  typedef std::list<int> seatsType;
  typedef std::pair<std::string, seatsType> seatsMovieType;
  typedef std::map<std::string, seatsMovieType> TimeMovieSeatsType;

enum RetCode
{
    RC_SUCCESS = 0,
    RC_USER_EXIST,
    RC_USER_NOT_EXIST,
    RC_WRONG_PASSWORD,
    RC_DB_NOT_EXIST,
    RC_NOT_IMPLEMENTED
};

  /**
   * The class to manage users using booking system
   */
  class User {
    public:
      /**
       * create user with userid and password
       *
       * @param userid
       * @param password
       * @return enum return code
       */
      virtual RetCode create(std::string userid, std::string password);

      /**
       * delete user with userid and password
       *
       * @param userid
       * @param password
       * @return enum return code
       */
      virtual RetCode remove(std::string userid, std::string password);

      /**
       * check user availability
       *
       * @param userid
       * @return true if user exist
       *
       *  Note: security issues such as userid leakage out of scope
       *
       */
      bool isExist(std::string userid);
  };

  /**
   * The class to manage ticketing sessions
   */
  class Session {
    public:
      /**
       * create session for given user
       *
       * @param userid
       * @param password
       * @return unique session id on SUCCESS, 0 on FAILURE
       */
      int create(std::string userid, std::string password);

      /**
       * remove session
       *
       * @param session_id
       * @return an error code, 0 on SUCCESS
       */
      RetCode remove(int session_id);

      /**
       * book tickets
       *
       * @param session_id
       * @param theater name
       * @param show name
       * @param show time
       * @param number of booked seats
       *
       * @return  booked seats, 0 if booking is not OK
       */
      std::vector<int> bookTickets(int session_id,
                                  std::string theater_name,
                                  std::string movie_name,
                                  std::string movie_time,
                                  int  number_seats);

      /**
       * get list of theaters
       *
       * @param none
       * @return list of theater names
       */
      std::vector<std::string>  getTheaters();

      /**
       * get booking data per theater
       *
       * @param   theater name
       * @return  booking data per theater
       */
      TimeMovieSeatsType  getBookingInfo(std::string theater_name);
    };


 class Admin: public User {
    public:
      /**
       * create admin with userid and password
       *
       * @param userid
       * @param password
       * @return enum status
       */
      RetCode create(std::string userid, std::string password);

      /**
       * delete any user from service
       *
       * @param userid
       * @return  enum status code
       */
      virtual RetCode remove(std::string userid);

      /**
       * modify any users password
       *
       * @param userid
       * @param password
       * @return status code
       */
      RetCode modify(std::string userid,
                 std::string old_password,
                 std::string new_password);

      /**
       * clear booking data per theater
       *
       * @param   theater name
       * @return  an error code, 0 on SUCCESS
       */
      RetCode resetBookingInfo(std::string theater_name);
    };
}
#endif
