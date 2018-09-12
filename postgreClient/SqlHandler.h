#ifndef _SQLHANDLER_H_
#define _SQLHANLDER_H_

#include <string>

extern "C" {
#include <postgresql/libpq-fe.h>
}

class SqlConnection;
/*
 *
 *  @brief  Postgresql handler, executing main db actions with assigned connection
 *
 **/
class SqlHandler {
    public:

        SqlHandler ():sqlconn_(0) {}
        SqlHandler (const SqlConnection* con):sqlconn_(con) {}

        /* return status code */
        int execute(const char * command);

        // copy ctor
        SqlHandler(SqlHandler const&);

        // assignment operator
        SqlHandler& operator=(SqlHandler const&);
        virtual  ~SqlHandler(){}

        void finalize(){}

    private:
        SqlConnection  *sqlconn_;
};

#endif
