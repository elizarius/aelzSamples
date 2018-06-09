#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_


#include  "Socket.h"
#include  "MessagingException.h"
#include  "SyncException.h"

namespace cpp_samples
{
	class UdpSocket: public Socket
	{
        friend class SocketReader;

		public:
            UdpSocket();

            virtual ~UdpSocket();

			virtual void messageReceived(Msg* msg, sockaddr* senderAddr) throw()
			{
				delete msg;
                memset(&senderAddr,0,sizeof(senderAddr));
			}

			/**
			 * This is the callback that is used to report received request
			 * messages to application. The default implementation of this
			 * method is to delete the received request message.
			 * @param msg a pointer to request message
			 * @implemented 1
			 */
			virtual void requestReceived(Msg* msg, sockaddr* senderAddr) throw()
			{
				delete msg;
                memset(&senderAddr,0,sizeof(senderAddr));
			}

			/**
			 * send a normal message
			 * @param pMsg a pointer to transfered message, note that the life time of message is kept in the application i.e. the application needs to delete the message after this call returns.
			 * @exception MessagingException is thrown if sending of message failed
			 * @exception SyncException is thrown if any of pthread calls fail
			 * @implemented 1
			 */
			void send(Msg* pMsg, sockaddr* recvAddr) throw (MessagingException, SyncException);

			/**
			 * send a reply to some request, note that the life time of reply message is kept in the application i.e. the application needs to delete the message after this call returns.
			 * @param reqID the id of the request to which the reply is send.
			 * @param pMsg a pointer to reply message.
			 * @exception MessagingException is thrown if sending of message failed
			 * @exception SyncException is thrown if any of pthread calls fail
			 * @implemented 1
			 */
			void sendReply(unsigned int reqID, Msg* pMsg, sockaddr* recvAddr) throw (MessagingException, SyncException);

			/**
			 * send a request, note that the life time of request message is kept in the application i.e. the application needs to delete the message after this call returns.
			 * @param pMsg a pointer to request message
			 * @return a handle to request monitor object, this handle can be used to block the caller till the reply is received.
			 * @exception MessagingException is thrown if sending of request message failed.
			 * @exception SyncException is thrown if any of pthread calls fail
			 * @implemented 1
			 */
			RequestMonitorHandle sendRequest(Msg* pMsg, sockaddr* recvAddr) throw (MessagingException, SyncException);

        private:
             /**
			 * internal message received callback
			 * @param pMsg a pointer to received message
			 * @exception SyncException is thrown if any of pthread calls fail
			 * @implemented 1
			 */
            void _messageReceived(Msg* pMsg, sockaddr* addr) throw (SyncException);

             /**
			 * internal interface for sending message
			 * @param pMsg a pointer to transfered message
			 * @exception MessagingException is thrown if sending of message failed
			 * @exception SyncException is thrown if any of pthread calls fail
			 * @implemented 1
			 */
            void _send(Msg* pMsg, sockaddr* addr) throw (MessagingException, SyncException);
	};
}

#endif
