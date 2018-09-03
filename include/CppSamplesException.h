#ifndef CPP_SAMPLES_EXCEPTION_H_
#define CPP_SAMPLES_EXCEPTION_H_

#include <string>
#include <exception>
#include <iostream>

namespace cpp_samples
{
    /**
    *
    * This class represents the CppSamples exception class.
    *
    *
    */
    class CppSamplesException : public std::exception
    {
        public:
            /**
            *
            * Constructor
            *
            * @param errorMsg the error message associated with this exception
            * @param fileName the name of file in source code where the exception was thrown
            * @param lineNumberthe number of the line where the exception was thrown
            * @param apcFunctionName the name of the function in which the exception was thrown
            * @param aErrorCode the error code associated with this exception
            *
            */
            CppSamplesException(const char* errorMsg,
                                const char* fileName,
                                unsigned short lineNumber,
						        const char* functionName,
                                int errorCode):errorMsgPtr_(errorMsg), fileNamePtr_(fileName),
                                functionNamePtr_(functionName), lineNo_(lineNumber),
                                errorCode_(errorCode) {}

            /**
            *
            * Virtual destructor
            *
            */
            virtual ~CppSamplesException() throw();

            /**
            * @brief    What operation
            * @return   const char* a pointer to the c-string representing the error message
            *
            */
            virtual const char* what() const throw()
            {
                return errorMsgPtr_.c_str();
            }

            /**
            * @brief    Gets the Line number from where this exception has been generated.
            * @return   The line number where the exception occured.
            *
            */
            unsigned short getLineNumber() const
            {
                return lineNo_;
            }

            /**
            *
            * @brief    Gets the File Name from where this exception has been generated.
            * @return   The file name where the exception occured.
            *
            */
            const char* getFileName() const
            {
             return fileNamePtr_.c_str();
            }

            /**
            * getFunctionName operation
            * Gets the Function Name from where this exception has been generated.
            *
            * @return The function name where the exception occured.
            *
            */
            const char* getFunctionName() const
            {
                return functionNamePtr_.c_str();
            }

	        /**
	        * getErrorCode operation
	        * Gets the error code associated with this exception
	        *
	        * @return The error code associated with the exception, 0 means no error code
	        *			is available
	        *
	        */
            int getErrorCode() const
            {
                return errorCode_;
            }

        private:
            /**
            * Stores the Error Message
            */
	    	std::string errorMsgPtr_;

            /**
            * Stores the File Name from where exception has been raised.
            */
            std::string fileNamePtr_;

            /**
            * Stores the File Name from where exception has been raised.
            */
            std::string functionNamePtr_;

            /**
            * Stores the Line number from where exception has been raised.
            */
            unsigned short lineNo_;

			/**
			* Optional field for storing error code
			*/
			int errorCode_;
    };
}

#endif
