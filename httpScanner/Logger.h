/**
* @file     Looger.h 
* @short    API specification for logging utilities 
*/
#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include <iostream>
#include "api.h"
#include <syslog.h>


namespace hs {

  class Logger {
    public :
      virtual void log (const std::string & url,
                         const std::string & status,
                         const std::string & respTime) = 0;

      Logger () {}
      virtual ~Logger () {} 
  };

  /**
  * log http info to std::out 
  * @param none
  */
  class ConsoleLogger: public Logger {
    public :
      virtual void log (const std::string & url,
                      const std::string & status, 
                      const std::string & respTime) {
        std::cout<< "URL: "<<url<<"\tSTATUS: "<<status<< "\tRESPONSE TIME:  "<< respTime;
      }
};

  class SyslogLogger: public Logger {
    public:
      virtual void log (const std::string & url,
                      const std::string & status, 
                      const std::string & respTime) { }

    private:
      /**
      * syslog level , default = LOG_INFO
      */
      int _level;
  } ;
}
#endif
