#ifndef CPP_SAMPLES_SOCKETWRITER_H_
#define CPP_SAMPLES_SOCKETWRITER_H_

//#include <sys/types.h>
//#include <sys/socket.h>
//#include <pthread.h>
//#include <queue>


namespace cpp_samples
{
	class Socket;
	class UdpSocket;
	class Msg;
	/**
	 * This class should handle writing data to skocket
	 */
	class SocketWriter{

		public:
			/**
			 * Socket writing mode
			 * NON_BLOCKING	-> if socket buffer is full return immdeiately
			 * BLOCKING		-> block till the whole message is sent
			 */
			enum WriteMode {NON_BLOCKING, BLOCKING };

			/**
			 * writing result
			 * COMPLETED	-> all message was written successfully
			 * NOTCOMPLETED	-> the message was written partially
			 * FAILD		-> failed to write the message
			 * EMPTY_QUEUE	-> not used
			 */
			enum WriteResult {COMPLETED, NOTCOMPLETED, FAILED, EMPTYQUEUE };

    /**
	 * constructor
	 * @param socket a pointer to Socket associated with this writer
     */
			SocketWriter(Socket* socket);

    /**
	 * destructor
     */
			~SocketWriter();

			/**
			 * send some message
			 * @param pTransportData the message to be sent
			 * @return sending result
			 * @exception SyncException is thrown in case any of pthread calls fail
	    	 */
			int writeData(TransportData* pTransportData) throw (SyncException);
			int writeData(TransportData* pTransportData,sockaddr* addr) throw (SyncException);


        /**
	    * @return how many bytes are not yet written
        */
			int getTotalLeft()
			{
				return nleft_;
			}

            void close();

		private:
			/**
			 * send a message
			 * @param msg the message to be written
			 * @param aFlags the mode of writing
			 * @return how man
			 */
			int send(struct msghdr* msg, int aFlags = 0) const;
			int sendTo(char* msg, int size, sockaddr* addr, int aFlags = 0) const;

			/**
			 * initialize SocketWriter for next write
			 */
			void initialize()
			{
				nleft_ = 0;
				index_ = 0;
				adjustedPointer_ = 0;
				adjustedSize_ = 0;
				totalMsgLen_ = 0;
				msgVecLen_ = 0;
				transportDataPtr_ = 0;
                if (udpMsgBuffer_)
                {
                    memset(udpMsgBuffer_, 0, udpMsgSize_);
                }
                udpMsgSize_ = 0;
			}

			/**
			 * do writing to socket
			 * @param msghdr the message to be written
			 * @param aeWM the writing mode
			 * @return how many bytes were written
			 */
			inline int doWrite(struct msghdr& mhdr, WriteMode aeWM);
			inline int doSend(char* msg, int size, sockaddr* addr, WriteMode aeWM);
			Socket*				socketPtr_;
			struct iovec* 		msgVecPtr_;
			unsigned int 		msgVecLen_;
			unsigned int 		totalMsgLen_;

//			TransportData* 		transportDataPtr_;

//			FastLock			lock_;




			/** for handling partial writes */
			int 				nleft_;
			int 				index_;
			__ptr_t 			adjustedPointer_;
			size_t  			adjustedSize_;
			struct iovec 		iovector_[10];

            bool                closed_;
//            char*               udpMsgBuffer_;
//            size_t              udpMsgSize_;

	};
} // end of namespace
#endif


