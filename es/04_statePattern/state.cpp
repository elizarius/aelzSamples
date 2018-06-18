#include <iostream>
#include <string>
#include <map>
#include <sys/types.h>


using namespace std ;

class RsBase ;

// require improvements, logic to switch one state to another should be there
// but not in state instances, that  perhaps should  execute specific for each 
// state actions
class IPSecProcessHandler
{

    public:
        enum RUNNING_STATUS
        {
            RS_NOTRUNNING = 0,
            RS_STARTING   = 1,
            RS_STARTED    = 2,
            RS_START_FAIL = 3,
            RS_STOPPING   = 4,
            RS_STOPPED    = 5
        };
        typedef std::map<IPSecProcessHandler::RUNNING_STATUS, RsBase *> rs_base_type ;

        IPSecProcessHandler () ;
        virtual ~IPSecProcessHandler(){ }

        /**
        * enforces the running state machine
        * @param newstate is the new state to change to
        * @return true if change is complete, false otherwise
        */
        bool setRunningState(const RUNNING_STATUS newstate);

    private:
       /** current daemon running state*/
        RUNNING_STATUS _running_state;
	    rs_base_type _stateHandlers ;

};


class RsBase
{
 public:
   virtual IPSecProcessHandler::RUNNING_STATUS
    setRunningState (const IPSecProcessHandler::RUNNING_STATUS newstate) = 0;
};



class RsNotRunning : public RsBase
{
 public:
// RsNotRunning() {}
 IPSecProcessHandler::RUNNING_STATUS
   setRunningState (const IPSecProcessHandler::RUNNING_STATUS newstate)
   {
	if  ( newstate == IPSecProcessHandler::RS_STARTING)
      	 return newstate ;
     	else
         return IPSecProcessHandler::RS_NOTRUNNING ;
   }
};

class RsStarting : public RsBase
{
 public:
 IPSecProcessHandler::RUNNING_STATUS
   setRunningState (const IPSecProcessHandler::RUNNING_STATUS newstate)
   {
	if  ( (newstate == IPSecProcessHandler::RS_STARTED) ||
              (newstate == IPSecProcessHandler::RS_START_FAIL))
      	 return newstate ;
     	else
         return IPSecProcessHandler::RS_STARTING ;
   }
};


class RsStarted : public RsBase
{
 public:
 IPSecProcessHandler::RUNNING_STATUS
   setRunningState (const IPSecProcessHandler::RUNNING_STATUS newstate)
   {
	if  ( (newstate == IPSecProcessHandler::RS_START_FAIL) ||
              (newstate == IPSecProcessHandler::RS_STOPPING)  ||
              (newstate == IPSecProcessHandler::RS_STOPPED) )
      	 return newstate ;
     	else
         return IPSecProcessHandler::RS_STARTED ;
   }
};

class RsStartFail : public RsBase
{
 public:
 IPSecProcessHandler::RUNNING_STATUS
   setRunningState (const IPSecProcessHandler::RUNNING_STATUS newstate)
   {
	if  ( newstate == IPSecProcessHandler::RS_NOTRUNNING)
      	 return newstate ;
     	else
         return IPSecProcessHandler::RS_START_FAIL ;
   }
};

class RsStopping : public RsBase
{
 public:
 IPSecProcessHandler::RUNNING_STATUS
   setRunningState (const IPSecProcessHandler::RUNNING_STATUS newstate)
   {
	if  ( newstate == IPSecProcessHandler::RS_STOPPED)
      	 return newstate ;
     	else
         return IPSecProcessHandler::RS_STOPPING ;
   }
};


class RsStopped : public RsBase
{
 public:
 IPSecProcessHandler::RUNNING_STATUS
   setRunningState (const IPSecProcessHandler::RUNNING_STATUS newstate)
   {
	if  ( newstate == IPSecProcessHandler::RS_NOTRUNNING)
      	 return newstate ;
     	else
         return IPSecProcessHandler::RS_STOPPED ;
   }
};


IPSecProcessHandler::IPSecProcessHandler()
{

_running_state=RS_NOTRUNNING ;

 _stateHandlers.insert(std::pair<IPSecProcessHandler::RUNNING_STATUS,
                       RsBase *>(IPSecProcessHandler::RS_NOTRUNNING,new RsNotRunning));

 _stateHandlers.insert(std::pair<IPSecProcessHandler::RUNNING_STATUS,
                       RsBase *>(IPSecProcessHandler::RS_STARTING,new RsStarting) );

 _stateHandlers.insert(std::pair<IPSecProcessHandler::RUNNING_STATUS,
                       RsBase *>(IPSecProcessHandler::RS_STARTED,new RsStarted) );

 _stateHandlers.insert(std::pair<IPSecProcessHandler::RUNNING_STATUS,
                       RsBase *>(IPSecProcessHandler::RS_START_FAIL,new RsStartFail) );


 _stateHandlers.insert(std::pair<IPSecProcessHandler::RUNNING_STATUS,
                       RsBase *>(IPSecProcessHandler::RS_STOPPING,new RsStopping) );

 _stateHandlers.insert(std::pair<IPSecProcessHandler::RUNNING_STATUS,
                       RsBase *>(IPSecProcessHandler::RS_STOPPED,new RsStopped) );

}


bool IPSecProcessHandler::setRunningState(const RUNNING_STATUS newstate)
{
    RUNNING_STATUS old_state = _running_state; // mainly for print , to be removed in final vesrion.
   _running_state = _stateHandlers[_running_state]->setRunningState( newstate ) ;

  std:cout<< "IPSecProcessHandler [old : new state] "<<old_state<<" : "<<_running_state<<std::endl ;

// AELZ : anyway newer analysed in code ;
return true ;
}



int main ()
{

  IPSecProcessHandler  ph;

// expectations :
//	0:1
//	1:2
//	2:3
//	3:0
//	0:1
//	1:2
//	2:4
//	4:5

  ph.setRunningState(IPSecProcessHandler::RS_STARTING);
  ph.setRunningState(IPSecProcessHandler::RS_STARTED);
  ph.setRunningState(IPSecProcessHandler::RS_START_FAIL);
  // Now we are in "start_fail" , exit possible via not running
  ph.setRunningState(IPSecProcessHandler::RS_NOTRUNNING);
  ph.setRunningState(IPSecProcessHandler::RS_STARTING);
  ph.setRunningState(IPSecProcessHandler::RS_STARTED);
  ph.setRunningState(IPSecProcessHandler::RS_STOPPING);
  ph.setRunningState(IPSecProcessHandler::RS_STOPPED );

 return 0 ;
}
