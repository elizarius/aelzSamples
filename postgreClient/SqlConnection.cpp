#include "SqlConnection.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>


using namespace std;

SqlConnection::SqlConnection(
                const std::string& dbname,
                const std::string& hostname,
                const std::string& user,
                const std::string& password) {

    std::string temp_str ="dbname=" + dbname + " host=" + hostname + " user=" + user +  " password=" + password;
    conn_ =  PQconnectdb(temp_str.c_str());
    if (PQstatus(conn_) == CONNECTION_BAD) {
        std::cout<<"We were unable to connect to the database"<<std::endl;
        exit (1);
    }
}

