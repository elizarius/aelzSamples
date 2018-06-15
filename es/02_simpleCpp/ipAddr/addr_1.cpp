#include <iostream>
#include <string>

#include <sys/utsname.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


using namespace std ;

int main()
{
    string ip = "10.159.9.73" ;
    // get the IP from the hostname */
    struct addrinfo *res = NULL;
    int rc;

     if((rc = getaddrinfo(ip.c_str(),NULL, NULL, &res)) != 0) {
        cout << "Error to getaddrinfo is " << gai_strerror(rc) << std::endl;
        return 0 ;
    }

    //convert addinfo structure to sockaddr
    struct sockaddr_in *addr;
    memset(&addr, 0, sizeof(addr));
    addr=(struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    addr= (struct sockaddr_in *) res->ai_addr;
    std::cout <<"IP address " << inet_ntoa(addr->sin_addr)<<std::endl ;

    freeaddrinfo(res);
    return 0 ;
}




