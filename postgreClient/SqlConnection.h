#ifndef _SQLC_H_
#define _SQLC_H_

#include <string>

extern "C" {
#include <postgresql/libpq-fe.h>
}

/*
 *
 *  @brief  Declares postgre connection.
 *  Later could be abstracted if more rdbms added
 *
 **/
class SqlConnection {
    public:

        SqlConnection ():conn_(0) {}

        void init(
                const std::string& dbname,
                const std::string& hostname,
                const std::string& user,
                const std::string& password);

        // copy ctor
        SqlConnection(SqlConnection const&);

        // assignment operator
        SqlConnection& operator=(SqlConnection const&);
        virtual  ~SqlConnection(){}

        PGconn* getConnection(){
            return conn_;
        }

        void finalize();
    private:
        PGconn  *conn_;
};

#endif
