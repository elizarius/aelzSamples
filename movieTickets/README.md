How to run:
----------
cd movieTickets/api_test/
make clean
make
./test_tickets


Use cases
---------

0.  api.h  including required API with Doxygen comments OK

1.  User management
    - create user                   OK
    - delete user                   OK
    - API unit test                 OK

2.  Theaters class                  OK


3.  Session  management (search)
    - create session                OK
    - remove session                OK
    - get list of theaters          OK
    - get theater info (name):
      time / movie / free places    OK
    - API unit test                 OK

4.  Session  management (book)      OK


5.  Admin user management
    - create admin user             OK
    - remove any user               OK
    - reset booking in theater      OK
    - modify booking info           TBD
    - modify any user password      TBD
    - API unit test                 OK


6. ENUM Error codes instead of 0,1  OK


TBD
---

7. Multiple requests concurency is provided by mutexes.
   It can be improved to "task fabric concept" when all api tasks serialized
   to message queue and another threads fetches from queue and executes tasks

8.  Exception handling instead of traditional status codes

9.  Modify users, modify booking data by admin

10. Client service that uses movie API
    - socket API or similar impl
    - google protobuf as messaging transport

11. Abstract API and add several api implementations, f.i.:
    - local host based api
    - socket based , when  client located on another host

12. Convert movie time from string to time_t structure

13. google test, grey box test in addition to  API test


Limitations
-----------
- Theaters list is hardcoded: creation, deletion of theater out scope exercise
- Security issues such as userid leakage by isExist() should be processed separately
- Authentication management is simplified
- Authorization management is out of scope

