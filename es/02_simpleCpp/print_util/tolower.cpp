#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std ;

int main(void)
{
    std::string classId ="EthernetPort";
    classId[0] = tolower(classId[0]);
    classId = classId+"Id";
    std::cout<< classId<<std::endl;
    return 1;

}


