#include <cstdio>
#include <iostream>
#include "SqlConnection.h"

using namespace std;

int main() {

//    PGconn  *conn;
    PGresult *res;
    int     rec_count;
    int     row;
    int     col;

    SqlConnection  sqlConn("postgres", "localhost", "postgres", "aelzpassword");
    PGconn  *conn=sqlConn.getConnection();

//    conn = PQconnectdb("dbname=postgres host=localhost user=postgres password=aelzpassword");
//    if (PQstatus(conn) == CONNECTION_BAD) {
//            std::cout<<"We were unable to connect to the database"<<std::endl;
//        return 1;
//    }

    res = PQexec(conn, "update people set phonenumber=\'3587776665\' where id=3");

    std::cout<<"AELZ ,first res "<<PQresultStatus(res)<<std::endl;

    res = PQexec(conn, "select lastname,firstname,phonenumber from people order by id");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cout<<"We did not get any data!"<<std::endl;
        return 1;
    }

    rec_count = PQntuples(res);
    std::cout<<"We received "<<rec_count <<" records"<<std::endl;
    std::cout<<"=========================="<<std::endl;

    for (row=0; row<rec_count; row++) {
        for (col=0; col<3; col++) {
            std::cout<<PQgetvalue(res, row, 1)<<std::endl;
       }
    }
    std::cout<<"=========================="<<std::endl;

    PQclear(res);
    PQfinish(conn);
    return 0;
}

