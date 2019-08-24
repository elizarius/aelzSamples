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
      // Exception(const char* errorMsg,
      //           int errorCode = 0,
      //           const char* fileName = 0,
      //           unsigned short lineNo = 0,
      //           const char* functionName = 0): errorMsgPtr_(errorMsg),
	    //                                         fileNamePtr_(fileName),
	    //                                         functionNamePtr_(functionName),
	    //                                         lineNo_(lineNo),
	    //                                         errorCode_(errorCode) {}
      Exception(const char* errorMsg): errorMsgPtr_(errorMsg) {
        functionNamePtr_ = __FUNCTION__;
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
        return errorMsgPtr_.c_str();
      }

      /**
      * @return  a pointer to the c-string representing the error message
      */        
      virtual const char* what() const throw() {
        return errorMsgPtr_.c_str(); 
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
        return fileNamePtr_.c_str();
      }

      /**
      *
      * @return The function name where the exception occured.
      *
      */
      const char* getFunctionName() const {
        	return functionNamePtr_.c_str();
      }

	    friend std::ostream&
	    operator<<(std::ostream& arOStream,
		       const Exception& _exception);

      /**
      *
      * @return The error code associated with the exception, 0 means no error code
      *			is available
      */
		  int getErrorCode() const {
         return errorCode_;
      }
	    
    private:

	    std::string errorMsgPtr_;
      std::string fileNamePtr_;
      std::string functionNamePtr_;
      unsigned short lineNo_;
			int errorCode_;
    };
}

#endif 
