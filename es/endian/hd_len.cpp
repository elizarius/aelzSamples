#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std ;
typedef struct libcom_header_struct {
    int datalen;
    int padding;
    int hmaclen;
} libcom_header;


int main(int argc, char **argv)
{
    /* header for PDUs transmitted using libcom protocol */
    libcom_header *  hdr = (libcom_header *)malloc ( sizeof (libcom_header ) );
    hdr->datalen =  142 ;
    hdr->padding =  100 ;
    hdr->hmaclen =  100 ;

    cout<<"In header "<<hex<<hdr->datalen<<endl;
    cout<<"In header "<<hex<<hdr->padding<<endl;
    return 0 ;
}

