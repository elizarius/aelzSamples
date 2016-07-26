#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/tcp.h>

#include "Socket.h"
#include  "UdpSocket.h"

#include  "SocketWriter.h"


namespace cpp_samples
{

SocketWriter::SocketWriter(Socket* pSocket) : socketPtr_(pSocket), closed_(false), udpMsgBuffer_(0), udpMsgSize_(0)
{
	initialize();
}

SocketWriter::~SocketWriter()
{
    if (udpMsgBuffer_) delete udpMsgBuffer_;
    udpMsgBuffer_ = 0;
    udpMsgSize_ = 0;
}


int
SocketWriter::writeData(TransportData* pTransportData)
	throw (SyncException)
{
	Guard<FastLock>	gaurd(lock_);

    if (closed_)
    {
        return FAILED;
    }

	transportDataPtr_ = pTransportData;

	// get vector information
	msgVecPtr_ = transportDataPtr_->getIOVector(msgVecLen_, totalMsgLen_);
	
	// get message length
	nleft_ = totalMsgLen_; 

	// prepare message for writing
	struct msghdr mhdr;
	mhdr.msg_name = 0;
	mhdr.msg_namelen = 0;
	mhdr.msg_iov = msgVecPtr_;
	mhdr.msg_iovlen = msgVecLen_;

	while (nleft_ > 0)
	{
        int nwritten;

        nwritten = doWrite(mhdr, BLOCKING);


		if(0 == nwritten)
		{
			TRACER(TRC_WARNING) << "SocketWriter (" << this << ") socket was closed for writing" << std::endl;
			initialize();
			return FAILED;
		}

		if(nwritten < 0)
		{
			if (EINTR == errno)
			{
				TRACER(TRC_DEBUG) << "SocketWriter ("
						  << this
						  << ") got error EINTR"
						  << std::endl;
			}
			else
			{
				TRACER(TRC_WARNING) << "SocketWriter (" << this << ") got error " << errno << " while writing to socket" << std::endl;
				initialize();
				return FAILED;
			}
		}
		nleft_ -= nwritten;

		if (nleft_ > 0)
		{
			int _offset = 0;
			int _totalLength = 0;

			for (int j=msgVecLen_-1; j>=0; --j)
			{
				_totalLength += msgVecPtr_[j].iov_len;
				if (_totalLength > nleft_)
				{
					// part of the vector is written
					_offset = _totalLength - nleft_;
					adjustedSize_ = msgVecPtr_[j].iov_len - _offset;
					adjustedPointer_ = static_cast<__ptr_t>
						(static_cast<char*>(msgVecPtr_[j].iov_base) + 
						 		 _offset);
					index_ = j;
					iovector_[index_].iov_base = adjustedPointer_;
					iovector_[index_].iov_len = adjustedSize_;
					break;
				}

				iovector_[j].iov_base = msgVecPtr_[j].iov_base;
				iovector_[j].iov_len = msgVecPtr_[j].iov_len;
			}
			mhdr.msg_name = 0;
			mhdr.msg_namelen = 0;
			mhdr.msg_iov = iovector_ + index_;
			mhdr.msg_iovlen = msgVecLen_ - index_;
		}
	}

	/** ok message send successfully */
	initialize();

	return COMPLETED;
}

int
SocketWriter::writeData(TransportData* pTransportData, sockaddr* addr)
	throw (SyncException)
{
	Guard<FastLock>	gaurd(lock_);

    if (closed_)
    {
        return FAILED;
    }

	transportDataPtr_ = pTransportData;

	// get vector information
	msgVecPtr_ = transportDataPtr_->getIOVector(msgVecLen_, totalMsgLen_);
	
	// get message length
	nleft_ = totalMsgLen_; 

	// prepare message for writing
	struct msghdr mhdr;
	mhdr.msg_name = 0;
	mhdr.msg_namelen = 0;
	mhdr.msg_iov = msgVecPtr_;
	mhdr.msg_iovlen = msgVecLen_;

    if(socketPtr_->getType() == ST_UDP)
    {
        if (!udpMsgBuffer_ || udpMsgSize_ < totalMsgLen_)
        {
            if (udpMsgBuffer_) delete[] udpMsgBuffer_;
            udpMsgBuffer_ = new char[totalMsgLen_];
            udpMsgSize_ = totalMsgLen_;
        }
        int index = 0;
        for (unsigned int i=0; i<msgVecLen_; i++)
        {
            memcpy(udpMsgBuffer_+index, msgVecPtr_[i].iov_base, msgVecPtr_[i].iov_len); 
            index += msgVecPtr_[i].iov_len;
        }
    }

    char* buffIndex = udpMsgBuffer_;
	while (nleft_ > 0)
	{
        int nwritten;
        nwritten = doSend(buffIndex, nleft_, addr,BLOCKING);

		if(0 == nwritten)
		{
			TRACER(TRC_WARNING) << "SocketWriter (" << this << ") socket was closed for writing" << std::endl;
			initialize();
			return FAILED;
		}

		if(nwritten < 0)
		{
			if (EINTR == errno)
			{
				TRACER(TRC_DEBUG) << "SocketWriter ("
						  << this
						  << ") got error EINTR"
						  << std::endl;
			}
			else
			{
				TRACER(TRC_WARNING) << "SocketWriter (" << this << ") got error " << errno << " while writing to socket" << std::endl;
				initialize();
				return FAILED;
			}
		}
		nleft_ -= nwritten;
        buffIndex += nwritten;
	}

	/** ok message send successfully */
	initialize();

	return COMPLETED;
}

int 
SocketWriter::doWrite(struct msghdr& mhdr, WriteMode aWM)
{
	int result = 0;
	if (aWM == SocketWriter::NON_BLOCKING)
    {
	   result = this->send(&mhdr, MSG_DONTWAIT | MSG_NOSIGNAL );
    }
	else
	{
	  result = this->send(&mhdr, MSG_NOSIGNAL);

		if (result <= 0)
		{
			TRACER(TRC_WARNING) << "SocketWriter (" << this << ") got error " << errno << " when writing to socket" << std::endl;
		}
	}

	return result;
	
}
int 
SocketWriter::doSend(char* msg, int size, sockaddr* addr, WriteMode aWM)
{
	int result = 0;
	if (aWM == SocketWriter::NON_BLOCKING)
    {
	   result = this->sendTo(msg, size, addr, MSG_DONTWAIT | MSG_NOSIGNAL );
    }
	else
	{
	  result = this->sendTo(msg, size, addr, MSG_NOSIGNAL);

		if (result <= 0)
		{
			TRACER(TRC_WARNING) << "SocketWriter (" << this << ") got error " << errno << " when writing to socket" << std::endl;
		}
	}

	return result;

}
	

int 
SocketWriter::send(struct msghdr* mhdr, int flags) const
{
    int nwritten;
        nwritten = writev(socketPtr_->getFD(), mhdr->msg_iov, mhdr->msg_iovlen);

    return nwritten;
}

int 
SocketWriter::sendTo(char* msg, int size, sockaddr* addr ,int flags) const
{
    int nwritten;
        nwritten = sendto(socketPtr_->getFD(),msg, size,flags, addr, sizeof(*addr));

    return nwritten;
}

void
SocketWriter::close()
{
	Guard<FastLock>	gaurd(lock_);
    closed_ = true;
}

} // end of namespace

