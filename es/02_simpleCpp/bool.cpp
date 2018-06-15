#include <iostream>
#include <string>

#define IPSEC_CONF_OK                      0
#define IPSEC_CONF_ERROR                  -1

using namespace std ;
int main()
{
    bool success = true;

    std::cout<< "success=true:" <<success<<std::endl ;

    success = IPSEC_CONF_ERROR;
    std::cout<< "IPSEC_CONF_ERROR: "<<IPSEC_CONF_ERROR<<" casted to success: " <<success<<std::endl;

    success = !IPSEC_CONF_ERROR;
    std::cout<< "!IPSEC_CONF_ERROR: "<<!IPSEC_CONF_ERROR<<" casted to success: " <<success<<std::endl;
 
    success = IPSEC_CONF_OK;
    std::cout<< "IPSEC_CONF_OK: "<<IPSEC_CONF_OK<<" casted to success: " <<success<<std::endl;

    success = !IPSEC_CONF_OK;
    std::cout<< "!IPSEC_CONF_OK: "<<!IPSEC_CONF_OK<<" casted to success: " <<success<<std::endl;

    return 1;

}




