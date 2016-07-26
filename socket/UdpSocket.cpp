
#include "Socket.h"
#include "SocketReader.h"
#include "messaging/SocketWriter.h"
#include  "UdpSocket.h"

namespace cpp_samples
{

UdpSocket::UdpSocket() : Socket(ST_UDP)
{
}

UdpSocket::~UdpSocket()
{
}

void
UdpSocket::_messageReceived(Msg* pMsg,sockaddr* addr)
	throw (SyncException)
{
	if (pMsg->getID() && pMsg->type_ == MT_REPLY)
	{
        _receiveReply(pMsg);
	}
	else if (pMsg->getID() && pMsg->type_ == MT_REQUEST)
	{
		requestReceived(pMsg, addr);
	}
	else // normal message
	{
		messageReceived(pMsg, addr);
	}
}

void
UdpSocket::sendReply(unsigned int _reqID, Msg* pMsg,sockaddr* addr)
	throw (MessagingException, SyncException)
{
	if (!pMsg)
		throw EX_MESSAGINGEXCEPTION("invalid message");

	if (!_reqID)
		throw EX_MESSAGINGEXCEPTION("invalid request id");

	pMsg->id_ = _reqID;
	pMsg->type_ = MT_REPLY;

	_send(pMsg,addr);	
}

void
UdpSocket::send(Msg* pMsg,sockaddr* addr)
	throw (MessagingException, SyncException)
{
	pMsg->id_ = 0;
   _send(pMsg, addr);
}

void
UdpSocket::_send(Msg* pMsg,sockaddr* addr)
	throw (MessagingException, SyncException)
{
    TransportData transportData(pMsg);
    int rc = socketWriterPtr_->writeData(&transportData,addr);
    if (rc != SocketWriter::COMPLETED)
    {
          throw EX_MESSAGINGEXCEPTION_ERR("send failed", errno);
    }
}

RequestMonitorHandle
UdpSocket::sendRequest(Msg* pMsg,sockaddr* addr)
	throw (MessagingException, SyncException)
{
    RequestMonitorHandle handle = _storeRequest(pMsg);
	TransportData transportData(pMsg);
	int rc = socketWriterPtr_->writeData(&transportData,addr);

	if (rc != SocketWriter::COMPLETED)
	{
		_handleReqSendFailure(pMsg->id_);
		throw EX_MESSAGINGEXCEPTION_ERR("send failed", errno);
	}

	return handle;
}

}

