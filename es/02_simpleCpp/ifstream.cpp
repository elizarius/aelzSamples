// read file data using associated buffer's members.

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

int main () {
    filebuf *pbuf;
    ifstream filestr;
    long size;
    char * buffer;

    string file_name = "bool.cpp";
    std::cout<<":::::"<<file_name<<std::endl;
    filestr.open (file_name.c_str());

    // get pointer to associated buffer object
    pbuf=filestr.rdbuf();

    // get file size using buffer's members
    size=pbuf->pubseekoff (0,ios::end,ios::in);
    pbuf->pubseekpos (0,ios::in);

    // allocate memory to contain file data
    buffer=new char[size];

    // get file data
    pbuf->sgetn (buffer,size);

    filestr.close();

    // Next step to replace in buffer  TCP 3215 to TCP  49313

    string listen =("Listen=") ;
    string port ="TCP 49313" ;
    string connect_port = "TCP esfleg03 49313";

    char * pch = strstr (buffer,"Listen=");

    cout << "---------------------------------"<<std::endl ;

    std::string zz = buffer ;

    size_t index  = zz.find(listen) ;
    zz.replace (index + listen.size(), port.size() , port);

    buffer = (char *)zz.c_str();

    cout<<buffer<<endl;
    return 0;
}


