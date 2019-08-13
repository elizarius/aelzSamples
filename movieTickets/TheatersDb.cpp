#include "TheatersDb.h"
#include <iostream>

using namespace std;
using namespace movie;

Theater::Theater(string name, int seats):_name(name),_totalSeats(seats) {
    seatsType free_seats;
  	for (int i = 1; i <= _totalSeats; i++) {
		  free_seats.push_back(i);
    }
    _bookings.insert(TimeMovieSeatsType::value_type("10:00", make_pair("KILL Bill", free_seats)));
    _bookings.insert(TimeMovieSeatsType::value_type("12:00", make_pair("Pulp fiction", free_seats)));
    _bookings.insert(TimeMovieSeatsType::value_type("14:00", make_pair("Inglourious Basterds", free_seats)));

    cout<<"Theater: " <<_name<<" constructed with timeslots: "<<_bookings.size()<<endl;
  }

TheatersDb::TheatersDb() {
  _theaters.insert(theatersType::value_type("Kosodoi", new Theater("Kosodoi",100)));
  _theaters.insert(theatersType::value_type("Muhosransk", new Theater("Muhosransk", 90)));
  _theaters.insert(theatersType::value_type("ekibastus", new Theater("ekibastus", 45)));
  _theaters.insert(theatersType::value_type("Pasatizhi", new Theater("Pasatizhi",45)));

  cout<<"TheatersDb created with " <<_theaters.size()<<" objects"<<endl;
}

TheatersDb::~TheatersDb() {
  for (auto theIt = _theaters.begin(); theIt != _theaters.end(); ++theIt) {
    delete theIt->second;
    theIt->second = 0;
  }
  _theaters.clear();
}
