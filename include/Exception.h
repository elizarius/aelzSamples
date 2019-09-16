#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <string>
#include <exception>
#include <iostream>

namespace aelzns {
  /**
  *     
  * This class represents the Exception exception
  *                     
  */
  class Exception : public std::exception {
    public:

      /**
       *  
       * Exception constructor
       * 
       * @param the error message associated with this exception
       * @param the name of file in source code where the exception was thrown
       * @param the number of the line where the exception was thrown
       * @param functionName the name of the function in which the exception was thrown
       * @param errorCode the error code associated with this exception
       *
       */        
      Exception(const char* errorMsg,
                const char* fileName ,
                unsigned short lineNo ,
                const char* functionName,
                int errorCode): errorMsg_(errorMsg),
	                                            fileName_(fileName),
	                                            functionName_(functionName),
	                                            lineNo_(lineNo),
	                                            errorCode_(errorCode) {}
      Exception(const char* errorMsg): errorMsg_(errorMsg) {
        functionName_ = __FUNCTION__;
        fileName_ = __FILE__;
        lineNo_ = __LINE__;
			  errorCode_ = 0;
      }

      /**
       *  
       * Exception virtual destructor
       *
       */        
      virtual ~Exception() throw(){}


      /**
      * @return the error message
      */        
      const char* getErrorMsg() const {
        return errorMsg_.c_str();
      }

      /**
      * @return  a pointer to the c-string representing the error message
      */        
      virtual const char* what() const throw() {
        return errorMsg_.c_str(); 
      }

      /**
      * 
      * @return The line number where the exception occured.
      *
      */
      unsigned short getLineNo() const {
        return lineNo_;
      }

      /**
      *
      * @return The file name where the exception occured.
      *
      */
      const char* getFileName() const {
        return fileName_.c_str();

      }

      /**
      *
      * @return The function name where the exception occured.
      *
      */
      const char* getFunctionName() const {
        	return functionName_.c_str();
      }

	    //friend std::ostream&
	    //operator<<(std::ostream& arOStream,
		  //     const Exception& _exception);

      /**
      *
      * @return The error code associated with the exception
      */
		  int getErrorCode() const {
         return errorCode_;
      }
	    
    private:

	    std::string errorMsg_;
      std::string fileName_;
      std::string functionName_;
      unsigned short lineNo_;
			int errorCode_;
    };

#define AELZ_EXCEPTION(msg,err) Exception(msg, __FILE__, __LINE__, __func__, err)
}

#endif 
