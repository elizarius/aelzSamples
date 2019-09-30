/**
* @file     api.h
* @short    API specification for  web sites monitor
*/
#ifndef _HS_API_H_
#define _HS_API_H_

#include <string>
#include <vector>

namespace hs {

  class Logger;
  enum RetCode
  {
      RC_SUCCESS = 0,
      RC_FAILED,
      RC_NOT_IMPLEMENTED
  };

  enum LogType
  {
      LOG_FILE = 0,
      LOG_STD,
      LOG_SLOG
  };

  /**
   * The class to read configuration file
   */
  class ConfigReader {
    public:
      ConfigReader ();
      ConfigReader (std::string filename);
      virtual ~ConfigReader () {}

      /**
       * read configuration file
       *
       * @param   none
       * @return  http urls to be scanned 
       */
      std::vector<std::string> readConfig() {
        return _urls; 
      }

      /**
       * read list of wrong urls, detected in config file
       *
       * @param   none
       * @return  http urls with wrong format, detected in file 
       */
      std::vector<std::string> readWrongUrls() {
        return _wrongUrls; 
      }

      /**
       * read content string, found in file 
       *
       * @param   none
       * @return  content 
       */
      std::string getContent() {
        return _content; 
      }

      const int  getTimeout() {
        return _timeout; 
      }


      /**
       * clean resources on shutdown to prevent info leaks
       *
       * @param none
       * @return enum return code
       */
      RetCode finalize() {
        return RC_NOT_IMPLEMENTED; 
      }

    private:
      std::string _fileName;
      std::vector<std::string>  _urls;
      std::vector<std::string>  _wrongUrls;
      std::string _content;
      int _timeout;

       /**
       * validate string received
       *
       * @param none
       * @return enum return code
       */
      RetCode validate(std::string) {
        return RC_NOT_IMPLEMENTED; 
      }
  };

  /**
   * The class to scan web links 
   */
  class Scanner  {
    public:
      Scanner ();
      virtual ~Scanner () {}

      /**
       * init http scanner 
       *
       * @param  log type 
       * @return unique session id on SUCCESS, 0 on FAILURE
       */
      RetCode init (LogType logType);

      /**
       * clean resources on shutdown to prevent info leaks
       *
       * @param none
       * @return enum return code
       */
      RetCode finalize();

      /**
       * start http scanner 
       *
       * @param none 
       * @return enum return code

       * @return unique session id on SUCCESS, 0 on FAILURE
       */
      RetCode run ();
      
    private:
      Logger * _logger;
      std::vector<std::string>  _urls;
      int _timeout;
      std::string _content;
      
      bool validateContent(std::string);

      std::string timeToString();
      /**
       * send http GET request  
       *
       * @param none 
       * @return enum return code
       */
      RetCode getRequest (std::string url) {
        return RC_NOT_IMPLEMENTED; 
      }

   };
}
#endif
