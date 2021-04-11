#ifndef _THEATERS_DB_
#define _THEATERS_DB_

/**
 *  Db contains theaters info
 *
 */
#include "Db.h"
#include "api.h"

namespace movie {

  class Theater {
    public:
      Theater(std::string name, int seats);
      Theater() {}
      virtual ~Theater(){}
      TimeMovieSeatsType & getBookings(){return _bookings;}

    private:
      std::string _name;
      int _totalSeats;
      TimeMovieSeatsType _bookings;
  };

  typedef std::map<std::string, Theater*> theatersType;

  class TheatersDb : public Db  {
    public:
      TheatersDb();
      virtual ~TheatersDb();
      theatersType &  getTheaters () {return _theaters;}

    private:
      theatersType  _theaters;
  };
}
#endif
