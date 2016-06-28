#include "Handlers.h"
#include "HelpHandler.h"

using namespace std;

int helpMessage(const char  * msg)
{
   std::cout<<std::endl<<msg<<std::endl;
   return 0 ;  
}


HelpHandler::HelpHandler()
{}

int HelpHandler::processCli(int argc , char * argv[])
{
   // Only help without parameters 
   if( argc == 2 ) 
   {
    usage();
    return 0 ;
   }

   // Check arguments 
   for(int i = 2; i < argc; i++)
   {

     string temp_arg(argv[i]) ;
     
     if(temp_arg =="examples")    examples();
     if(temp_arg =="design")      design();
   }

  return 0 ;

}


void HelpHandler::usage()
{
   std::cout <<endl<< "Usage: " << endl;

   std::cout <<"./rtclient <iface|server>  arguments"<< endl;

   std::cout <<" more info :./rtclient add|set|delete|get|server> -h"<< endl<<endl;

   std::cout <<" Examples : ./rtclient help examples "<< endl<<endl;
   
   std::cout <<" Design   : ./rtclient help design "<< endl<<endl;

}


void HelpHandler::design()
{
 /*
  cout <<endl<< "Design: " << endl;
  cout << "-------" << endl<<endl;
  cout << "To implemenent new protoclient commands next steps have to be done : " <<endl;
  cout << "\t"<<" 1. Design your protoclient command " <<endl;
  cout << "\t"<<" 2. Write cli handler, processing protoclient commands." <<endl;
  cout << "\t"<<"    This handler have to be inherited from abstract Cli class. " <<endl;
  cout << "\t"<<"    Handler must implement at least fillRequest() function " <<endl;
  cout << "\t"<<" 3. Add your handler to mapHandlers in Handlers::init()/Handlers.cpp " <<endl;
  cout << "\t"<<" 4. Call your handler from corresponding 1 level handler:   " <<endl;
  cout << "\t"<<"    fillRequest() in ComponentHandler/ConfigHander/GetHandler " <<endl;
  cout << "\t"<<" 5. Add help strings to HelpHanlder.h   " <<endl;
  cout << "\t"<<" 6. GetHandler class can be used as referenced example" <<endl;
  cout << "\t"<<" 7. DO NOT implement any request/response logic directly in main() but write own handlers" <<endl<<endl;

  cout << "At start, protoclient calls corresponding handlers and sends request to server" <<endl;
  cout << "File tbd.txt under svn includes list of improvements still to be done " <<endl<<endl;
 */
}

void HelpHandler::examples()
{
   std::cout <<endl<<"Examples : "<< endl;
   std::cout <<endl<<"./rtclient server"<<endl<<endl;
}




