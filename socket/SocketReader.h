#ifndef CPP_SAMPLES_SOCKETREADER_H_
#define CPP_SAMPLES_SOCKETREADER_H_

#include <queue>
#include <pthread.h>


#define	NUMBEROFBYTESFORLENGTH	4

namespace cpp_samples
{
	class Socket;
	class UdpSocket;

	/**
	 * this class encapsulates the functionality for handling message
	 * reading from socket.
	 */
	class SocketReader
	{
		public:

			/**
			 * The position in the pdu where the message length data starts.
			 */
			static const unsigned int CLenStartPos_ = 2;


			 /**
			  * The position in the pdu where the message length data ends.
			  */
			  static const unsigned int CLenEndPos_ = 4;
			/**
			 * Tells whether this SocketReader is a blocking or a non-blocking
			 * reader.
			 */

        		enum ReadMode {NON_BLOCKING, BLOCKING};

            /**
	        * constructor
	        * @param pSocket a pointer to Socket attached with this reader
            */
			SocketReader(Socket* pSocket);

            /**
	        * destructor
            */
			virtual ~SocketReader();


            /**
	        * read data  from socket till either no more data is
	        * available or the batch buffer is full.
	        * @param aeRM the read mode blocking or non-blocking
	        * @return read result
            */
			virtual int readDataBatch(ReadMode aeRM = NON_BLOCKING);


			/**
			 * check if internal message buffer size is enough, if not
			 * reallocate a bigger buffer.
			 */
			void checkMsgBufferSize()
			{
				if (messageLength_ > newMessageBufferSize_)
				{
					/** bad luck! resize message buffer */
					delete[] newMessageBuffer_;
					newMessageBuffer_ = new char[messageLength_];
					newMessageBufferSize_ = messageLength_;
					messagePtr_ = newMessageBuffer_;
				}
			}

			/** just for debug */
			void dump(int index);
		private:
			/**
			 * receive data from socket
			 * @param aData receiving buffer
			 * @param aLength length of receiving buffer
			 * @param flags reading option.
			 * @return bytes read so far.
			 */
			int recv(char *aData, int aLength, int flags = 0) const;

			/**
			 * size of buffer used for reading length
			 */
            static const int CMsgLenBuffSize_ = 4;

		      /**
		       * Stores the ptr to the Sock
			   */
			   Socket*  socketPtr_;

				/**
				 * get length of serialized packet
				 * @implemented 1
				 */
        	    void getPduLen(char* pduHeader, unsigned int &len)

		        {
		            len = 0;
		            for(unsigned int j=0; j<(CLenEndPos_ - CLenStartPos_ + 1); j++)
		            {
		                len += ((unsigned int)((unsigned char)
		                                    pduHeader[CLenEndPos_ - j - 1]) << (8*j));
		            }
		        }

		    /* this buffer is added to be able to read as mush as possible information
		     * from socket before returning to minimize system calls */
		    unsigned int		bytesReadSoFar_;
		    unsigned int		lengthBytesReadSoFar_;
		    char*				newMessageBuffer_;
		    unsigned int		newMessageBufferSize_;
		    char*				messagePtr_;
		    char				dataProcessingBuffer_[2*1024];
		    unsigned int		dataProcessingBufferSize_;
		    int 				dataBufferDataLength_;
		    unsigned int	 	messageLength_;
		    char				messageLengthBuffer_[NUMBEROFBYTESFORLENGTH];
		    char*				currentDataOffset_;
		    bool				newMessage_;
            struct              sockaddr_in Addr_;
	};
}
#endif
