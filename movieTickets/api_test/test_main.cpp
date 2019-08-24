#include <iostream>
#include <string>
#include <cassert>
#include "Schema.h"
#include "api.h"
#include "Exception.h"


using namespace std;
using namespace movie;
using namespace aelzns;

  class UserApiTest {
    public:
      static UserApiTest& Instance() {
        static UserApiTest ch;
        return ch;
      }

      void testCreateUserOK() {
        assert (_user.create("aela", "huy") == 0);
      }

      void testCreateSecondUserOK() {
        assert (_user.create("zapb", "huy") == 0);
      }

      void testCreateSameUserFails() {
        try {
          _user.create("aela", "huy");
        }
        catch (Exception& e) {
          std::cout << "Exception caught USER CREATION test " << std::endl;
          std::cout << e.what() << std::endl;
          std::cout << e.getFunctionName() << std::endl;

          return;
        }
      }

      void testUserExistsOK() {
        assert (_user.isExist("aela") == true);
      }

      void testUserDoesNotExist() {
        assert (_user.isExist("aela") == false);
      }

      void testDeleteUserOK() {
        assert (_user.remove("aela", "huy" ) == 0);
      }

  private:
    UserApiTest(){}
    User _user;
  };

  class SessionApiTest {
    public:
      static SessionApiTest& Instance() {
        static SessionApiTest ch;
        return ch;
      }

      int testCreateSessionOK() {
        int id = _session.create("zapb", "huy");
        assert (id != 0);
        return id;
      }

      void testDeleteSessionOK(int id ) {
        assert (_session.remove(id) == 0);
      }

      void testGetTheatersOK() {
        vector<string> theaters = _session.getTheaters();
        assert (theaters.size() == 4);
      }

      void testGetBookingInfoOK(int free_seats) {
        TimeMovieSeatsType bi = _session.getBookingInfo("ekibastus");
        assert (bi.size() == 3);

        // extra visual control
        auto it =bi.begin();
        cout<<endl<<"BI test,  timeslot:\t" <<it->first<<endl;
        cout<<"BI test,  movie:\t" <<it->second.first<<endl;
        cout<<"BI test,  free seats:\t" <<it->second.second.size()<<endl;

        assert (it->second.second.size() == free_seats);
      }

      void testBookTicketsOK(int id) {

         std::vector<int> booked_tickets = \
             _session.bookTickets(id,
                                  "ekibastus",
                                  "KILL Bill",
                                  "10:00", 3);
        assert (booked_tickets.size() == 3);
      }

      private:
        SessionApiTest(){}
        Session _session;
  };


  class AdminApiTest {
    public:
      static AdminApiTest& Instance() {
        static AdminApiTest ch;
        return ch;
      }

      void testCreateUserOK() {
        assert (_user.create("admin", "zapa") == 0);
      }

      void testCreateSameUserFails() {
        try {
          _user.create("admin", "zapa");
        }
        catch (Exception& e) {
          std::cout << "Exception caught ADMIN test " << std::endl;
          return;
        }
      }

      void testDeleteAnyUserOK() {
        assert (_user.remove("zapb") == 0);
      }

      void testModifyUserFails() {
        assert (_user.modify("aela", "huy", "net") == 5);
      }

  private:
    AdminApiTest(){}
    Admin _user;
  };


int main(int argc, char* argv[])
{

  /*  Init DB Schema. */
  Schema & schema = Schema::Instance();

  try {
    schema.init();

    /****  USER API MODULE  ****/
    UserApiTest & ust = UserApiTest::Instance();
    ust.testCreateUserOK();
    ust.testCreateSecondUserOK();
    ust.testCreateSameUserFails();
    ust.testUserExistsOK();
    ust.testDeleteUserOK();
    ust.testUserDoesNotExist();

    /****  SESSION MANAGEMENT API MODULE  ****/
    SessionApiTest & st = SessionApiTest::Instance();
    int id = st.testCreateSessionOK();
    st.testGetTheatersOK();
    st.testGetBookingInfoOK(45);
    st.testBookTicketsOK(id);typedef std::map<std::string, Db *> argHandlersType;

    st.testGetBookingInfoOK(42);
    st.testDeleteSessionOK(id);

    /****  ADMIN MANAGEMENT API MODULE  ****/
    AdminApiTest & adm = AdminApiTest::Instance();

    adm.testCreateUserOK();
    adm.testCreateSameUserFails();
    adm.testModifyUserFails();
    adm.testDeleteAnyUserOK();

    cout <<endl<<"** API TESTS FINISHED SUCCESSFULLY **"<<endl;
  }
  catch (Exception& e) {
    std::cout << "Exception caught" << std::endl;
    std::cout << e.what() << std::endl;
  }
  catch (std::exception& e) {
    std::cout << "std::exception caught" << std::endl;
    std::cout << e.what() << std::endl;
  }

  return 0;
}
