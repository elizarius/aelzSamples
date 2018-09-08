#include <cstdio>
#include <iostream>
#include "SqlConnection.h"

using namespace std;

int main() {

    PGresult *res;
    int     rec_count;
    int     row;
    int     col;

    SqlConnection  sqlConn;
    sqlConn.init("postgres", "localhost", "postgres", "aelzpassword");
    PGconn  *conn = sqlConn.getConnection();

    res = PQexec(conn, "update people set phonenumber=\'3587776665\' where id=3");

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
    sqlConn.finalize();
    return 0;
}

