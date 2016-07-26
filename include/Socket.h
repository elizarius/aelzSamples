#ifndef CPP_SAMPLES_SOCKET_H_
#define CPP_SAMPLES_SOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>


#include <netdb.h>

#include "CppSamplesException.h"

namespace  cpp_samples
{
	/**
	 * socket type:
	 * ST_TCP			->	TCP socket
	 * ST_UNIX_DOMAIN	->	unix domain socket
     * ST_UDP           ->  User datagram protocol
	 */
    enum SocketType
	{
        ST_TCP = 0,
		ST_UNIX_DOMAIN,
        ST_UDP
	};

	class Socket;
    class SocketReader;
    class SocketWriter;
    class Msg;

	/**
	 * The socket class contains the main interfaces that are used for sending
	 * and receiving request-reply messages.
	 */
	class Socket
	{

        public:
			/**
			 * constructor
			 * @param type the type of socket ST_TCP or ST_UNIX_DOMIAN
			 */
            Socket(SocketType type);

			/**
			 * virtual destructor
			 */
			virtual ~Socket();

			/**
			 * This is the callback that is used to report received messages
			 * to the application. The default implementation of this method
			 * is to delete the received message.
			 * @param msg a pointer to received message
			 */
			virtual void messageReceived(Msg* msg) throw()
			{
				delete msg;
			}

			/**
			 * This is the callback that is used to report received request
			 * messages to application. The default implementation of this
			 * method is to delete the received request message.
			 *
			 * @param msg a pointer to request message
			 */
			virtual void requestReceived(Msg* msg) throw()
			{
				delete msg;
			}

			/**
			 * This is the callback that is used to report the connection closing
			 * to application. The default implementation of this method is NOP.
			 */
			virtual void connectionClosed() throw()
			{
			}

			/**
			 * send a normal message
			 * @param pMsg a pointer to transfered message, note that the life time of message is kept in the application i.e. the application needs to delete the message after this call returns.
			 * @exception MessagingException is thrown if sending of message failed
			 * @exception SyncException is thrown if any of pthread calls fail
			 */
			 void send(Msg* pMsg) throw (CppSamplesException);

			/**
			 * send a reply to some request, note that the life time of reply message is kept in the application i.e. the application needs to delete the message after this call returns.
			 * @param reqID the id of the request to which the reply is send.
			 * @param pMsg a pointer to reply message.
			 * @exception MessagingException is thrown if sending of message failed
			 * @exception SyncException is thrown if any of pthread calls fail
			 */
			void sendReply(unsigned int reqID, Msg* pMsg) throw (CppSamplesException);

			/**
			 * send a request, note that the life time of request message is kept in the application i.e. the application needs to delete the message after this call returns.
			 * @param pMsg a pointer to request message
			 * @return a handle to request monitor object, this handle can be used to block the caller till the reply is received.
			 * @exception MessagingException is thrown if sending of request message failed.
			 * @exception SyncException is thrown if any of pthread calls fail
			 */
			 void sendRequest(Msg* pMsg) throw (CppSamplesException);

			/**
			 * get type of Socket
			 * @return socket type ST_TCP or ST_UNIX_DOMAIN
			 */
			SocketType getType() const
			{
				return type_;
			}


			/**
			 * get the file descriptor for this socket
			 * @return socket file descriptor
			 */
			int getFD() const
			{
				return fd_;
			}

			/**
			 * shutdown this socket
			 * @return result of socket shutdown
			 */
			bool shutdown()
			{
				if (! ::shutdown(fd_, SHUT_RDWR))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
        protected:

			//RequestMonitorHandle _storeRequest(Msg* pMsg) throw (CppSamplesException);

            void _handleReqSendFailure(unsigned int id);

            void _receiveReply(Msg* pMsg) throw (CppSamplesException);

			/**
			 * writer associated with this socket
			 */
			SocketWriter*		socketWriterPtr_;

			/**
			 * reader associated with this socket
			 */
			SocketReader*		socketReaderPtr_;
		private:
			/**
			 * internal message received callback
			 * @param pMsg a pointer to received message
			 * @exception SyncException is thrown if any of pthread calls fail
			 */
			void _messageReceived(Msg* pMsg) throw (CppSamplesException);

			/**
			 * internal interface for sending message
			 * @param pMsg a pointer to transfered message
			 * @exception MessagingException is thrown if sending of message failed
			 * @exception SyncException is thrown if any of pthread calls fail
			 */
			void _send(Msg* pMsg) throw (CppSamplesException);

			/**
			 * internal connection closed callback
			 * exception SyncException is thrown in case any of pthread calls fail
			 */
			void _connectionClosed() throw (CppSamplesException);


			/**
			 * close this socket
			 * @return result of socket close
			 */
			bool close()
			{
				bool ret = false;
				if (! ::close(fd_))
				{
					ret = true;
				}

				_connectionClosed();
				return ret;
			}

			/**
			 * socket file descriptor
			 */
            int         fd_;

			/**
			 * socket type
			 */
			SocketType  type_;

			/**
			 * address of socket
			 */
			union addr
			{
					struct sockaddr_in	tcpAddr_;
					struct sockaddr_un 	udAddr_;
					struct sockaddr_in	udpAddr_;
			}   addr_;


	};
}

#endif
