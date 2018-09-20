// Simple class implementation

#include "Simple.h"
#include <string>
#include <iostream>


using namespace std;

Simple::Simple()
{
  cout<<"----- Simple: def CONSTRUCTOR called"<<endl; 
}

Simple::~Simple()
{
  cout<<"----- Simple: virtual DESTRUCTOR called"<<endl; 
}


void  Simple::printInstance()
{
  cout<<"----- Simple::printInstance() called"<<endl; 
}




