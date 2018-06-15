#include <iostream>
#include <string>

#include <sys/utsname.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>



using namespace std ;

   int main()
   {
       string ip = "172.21.216.126" ;
       struct hostent* he;
       struct sockaddr_in saddr  ;
       inet_aton(ip.c_str() , &saddr.sin_addr ) ;
       he = gethostbyname(ip.c_str());

        if (!he)
        {
          std::cout<<"Impossible to get host by name "<<std::endl ;
	    return 0 ;
        }
	string hostname = he->h_name ;
	std::cout<<hostname<< std::endl ;
       return 0 ;
   }




