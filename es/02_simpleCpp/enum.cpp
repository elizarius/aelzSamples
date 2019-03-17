#include <iostream>
#include <string>

namespace aelz_space
{
        enum RouteType
        {
            rLOCAL = 0,
            rOTHER = 1,
            rREJECT = 2,
            rREMOTE = 3
        };

        enum ProtoType
        {
            pLOCAL = 0,
            pOSPF = 1,
            pBGP = 2,
            pNETMGMT = 3,
            pREMOTE = 4
        };

}


using namespace std ;
int main()
{
    std::cout <<aelz_space::rREMOTE<<std::endl;
    std::cout <<aelz_space::pREMOTE<<std::endl;
    aelz_space::RouteType rt = aelz_space::rREJECT;
    std::cout <<"Print variable rt: "<< rt<<std::endl;
    return 0;
}

