#include <errno.h>
#include <sstream>
#include <fstream>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include "Socket.h"
#include "UdpSocket.h"

#include <messaging/SocketReader.h>

namespace cpp_samples
{

SocketReader::SocketReader(Socket* pSocket)
	:  socketPtr_(pSocket)
{
	bytesReadSoFar_ = 0;
	lengthBytesReadSoFar_ = 0;
	newMessageBuffer_ = new char[4*1024];
	newMessageBufferSize_ = 4*1024;
	messagePtr_ = newMessageBuffer_;
	currentDataOffset_ = dataProcessingBuffer_;
	dataProcessingBufferSize_ = 2*1024;
	// dataProcessingBufferSize_ = 2*1024;
	dataBufferDataLength_ = 0;
	messageLength_ = 0;
	newMessage_ = true;
    memset( &Addr_, 0, sizeof(Addr_));
}

SocketReader::~SocketReader()
{
	delete[] newMessageBuffer_;
}

int
SocketReader::readDataBatch(ReadMode aRM)
{
	/** get as many messages as you can get */
	if (aRM == NON_BLOCKING)
	{
		dataBufferDataLength_ = 
	        this->recv(dataProcessingBuffer_, dataProcessingBufferSize_,
				MSG_DONTWAIT | MSG_NOSIGNAL);
	}
	else
	{
		dataBufferDataLength_ = 
		   this->recv(dataProcessingBuffer_, dataProcessingBufferSize_,
				MSG_NOSIGNAL);
	}

	while (1) 
	{
        
		if (dataBufferDataLength_ == 0)
		{
			return -1;
		}
		else if (dataBufferDataLength_ < 0)
		{
			if((EAGAIN != errno) && (EINTR != errno))
			{
				TRACER(TRC_WARNING) << "SocketReader (" << this << ") read on the socket returned error: " << errno <<  std::endl;
				// reinitialize every thing

				return -1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
        

			if (newMessage_)
			{
				bytesReadSoFar_ = 0;
				lengthBytesReadSoFar_ = 0;
				messagePtr_ = newMessageBuffer_;
				messageLength_ = 0;
				if ((currentDataOffset_ + NUMBEROFBYTESFORLENGTH) <= 
						dataProcessingBuffer_ + dataBufferDataLength_)
				{
					newMessage_ = false;
					messageLength_ = (unsigned int)ntohl(*((unsigned int*)currentDataOffset_));


					checkMsgBufferSize();

					// bytesReadSoFar_ = 0;
					bytesReadSoFar_ += NUMBEROFBYTESFORLENGTH;

					//currentDataOffset_ += NUMBEROFBYTESFORLENGTH;

					if (currentDataOffset_ < dataProcessingBuffer_+dataBufferDataLength_)
					{
						if (currentDataOffset_ + messageLength_ <=
								dataProcessingBuffer_ + dataBufferDataLength_)
						{

							memcpy(newMessageBuffer_, 
									currentDataOffset_, messageLength_);
							currentDataOffset_ += messageLength_;

							if (currentDataOffset_ == (dataProcessingBuffer_ + dataBufferDataLength_))
								currentDataOffset_ = dataProcessingBuffer_;
							newMessage_ = true;
						}
						else
						{
							/** this buffer contains part of the message */
							int lengthToEnd = 
								(int)((dataProcessingBuffer_+dataBufferDataLength_)-
								      currentDataOffset_);
							memcpy(newMessageBuffer_, currentDataOffset_, lengthToEnd);
							currentDataOffset_ += lengthToEnd;
							if (currentDataOffset_ == (dataProcessingBuffer_+dataBufferDataLength_)) 
								currentDataOffset_ = dataProcessingBuffer_;
							messagePtr_ += lengthToEnd;
							bytesReadSoFar_ = lengthToEnd;
							newMessage_ = false;
						}
					}
					else /** we must read the data part of the message */
					{
						newMessage_=false;
						currentDataOffset_ = dataProcessingBuffer_;
					}
				}
				else  
				{
					int lengthToEnd = (int)((dataProcessingBuffer_+dataBufferDataLength_)-currentDataOffset_);
					memcpy(messageLengthBuffer_, currentDataOffset_, lengthToEnd);
					lengthBytesReadSoFar_ = lengthToEnd;
					messageLength_ = 0;
					newMessage_ = false;
					currentDataOffset_ = dataProcessingBuffer_;

					/** adjust bytesReadSoFar */
					// bytesReadSoFar_ = lengthBytesReadSoFar_;
				}
			}
			else /** not a new message */
			{
				if (messageLength_ == 0)
				{
					if ((unsigned int)dataBufferDataLength_ < NUMBEROFBYTESFORLENGTH - lengthBytesReadSoFar_)
					{
						memcpy(messageLengthBuffer_+lengthBytesReadSoFar_, currentDataOffset_, dataBufferDataLength_);
						lengthBytesReadSoFar_ += dataBufferDataLength_;
						currentDataOffset_ = dataProcessingBuffer_;
						return 1;
					}

					/** continue getting message length!!! */
					memcpy(messageLengthBuffer_+lengthBytesReadSoFar_, currentDataOffset_, 
							NUMBEROFBYTESFORLENGTH-lengthBytesReadSoFar_);
					messageLength_ = (unsigned int)ntohl(*((unsigned int*)messageLengthBuffer_));

					checkMsgBufferSize();
					currentDataOffset_ += NUMBEROFBYTESFORLENGTH-lengthBytesReadSoFar_;

					// copy length information to messageBuffer */
					memcpy(newMessageBuffer_, messageLengthBuffer_, 
							NUMBEROFBYTESFORLENGTH);

					messagePtr_ += NUMBEROFBYTESFORLENGTH;

					bytesReadSoFar_ = NUMBEROFBYTESFORLENGTH;
					if (currentDataOffset_ == dataProcessingBuffer_ + dataBufferDataLength_) 
					{
						currentDataOffset_ = dataProcessingBuffer_;
						return 1;
					}
				}
				if ((currentDataOffset_ + messageLength_ - bytesReadSoFar_) <= 
						(dataProcessingBuffer_+dataBufferDataLength_))
				{
					memcpy(messagePtr_, currentDataOffset_, messageLength_-bytesReadSoFar_);
					currentDataOffset_ += messageLength_-bytesReadSoFar_;
					if (currentDataOffset_ == dataProcessingBuffer_+dataBufferDataLength_) 
						currentDataOffset_ = dataProcessingBuffer_;
					newMessage_ = true;
				}
				else
				{
					/** this buffer contains part of the message */
					int lengthToEnd = (int)((dataProcessingBuffer_+dataBufferDataLength_)-currentDataOffset_);

					memcpy(messagePtr_, currentDataOffset_, lengthToEnd);
					currentDataOffset_ += lengthToEnd;
					messagePtr_ += lengthToEnd;
					bytesReadSoFar_ += lengthToEnd;
					if (currentDataOffset_ == dataProcessingBuffer_ + dataBufferDataLength_) 
						currentDataOffset_ = dataProcessingBuffer_;
					newMessage_ = false;
				}
			}


			if (newMessage_)
			{

				// pass message to client
				try
				{
					/** NOTE!!! - > _messageBuffer should not be deleted by decoder */
					Msg* pMsg = TransportData::decode(newMessageBuffer_, messageLength_);
                    if(socketPtr_->getType() != ST_UDP)
                    {
					    socketPtr_->_messageReceived(pMsg);
                    }
                    else
                    {
					    dynamic_cast<UdpSocket*>(socketPtr_)->_messageReceived(pMsg,(sockaddr *)&Addr_);
                    }

				}
				catch (const SyncException& exp)
				{
					TRACER(TRC_ERROR) << "got exception " 
									  << exp
									  << std::endl;
					return 1;
				}
				catch (std::bad_alloc)
				{
					TRACER(TRC_ERROR) << "got std::bad_alloc exception" << std::endl;
					return 1;
				}
			}

			if (currentDataOffset_ == dataProcessingBuffer_)
			{
				return 1;
			}
		 }
	} // end of while
}

int 
SocketReader::recv(char *aData, int aLength, int flags) const
{
    int rc = 0;
    if(socketPtr_->getType() != ST_UDP)
    { 
       rc = ::recv(socketPtr_->getFD(), aData, aLength, flags);
    }
    else
    {
       socklen_t  AddrLen = sizeof(Addr_);
       rc = recvfrom(socketPtr_->getFD(), aData, aLength, flags, (struct sockaddr *)&Addr_, &AddrLen);
    }

    return rc;
}

void
SocketReader::dump(int index)
{
	std::stringstream fileName;
	fileName << "SocketReader.tmp."<<index<<std::endl;
	std::ofstream _file(fileName.str().c_str(), std::ios::out);
	_file<<"bytesReadSoFar_ "<<bytesReadSoFar_<<std::endl;
	_file<<"lengthBytesReadSoFar_ "<<lengthBytesReadSoFar_<<std::endl;
	_file<<"newMessageBuffer_ "<<(void*)(newMessageBuffer_)<<std::endl;
	_file<<"newMessageBufferSize_ "<<newMessageBufferSize_<<std::endl;
	_file<<"messagePtr_ "<<(void*)(messagePtr_)<<std::endl;
	_file<<"dataProcessingBufferSize_ "<<dataProcessingBufferSize_<<std::endl;
	_file<<"dataBufferDataLength_ "<<dataBufferDataLength_<<std::endl;
	_file<<"messageLength_ "<<messageLength_<<std::endl;
	_file<<"messageLengthBuffer_ "<<(void*)(messageLengthBuffer_)<<std::endl;
	_file<<"currentDataOffset_ "<<(void*)(currentDataOffset_)<<std::endl;
	_file<<"newMessage_ "<<newMessage_<<std::endl;

	/** contents of dataProcessingBuffer_ */
	for (unsigned int i=0; i<dataProcessingBufferSize_; i++)
	{
		_file<<(void*)(dataProcessingBuffer_+i)<<" dataProcessingBufferSize_["<<i<<"]="<<int(dataProcessingBuffer_[i])<<std::endl;
	}
	
	/** contents of messageLengthBuffer_ */
	for (int i=0; i<NUMBEROFBYTESFORLENGTH; i++)
	{
		_file<<(void*)(messageLengthBuffer_+i)<< " messageLengthBuffer_["<<i<<"]="<<int(messageLengthBuffer_[i])<<std::endl;
	}

	/** contents of newMessageBuffer_ */
	for (unsigned int i=0; i<newMessageBufferSize_; i++)
	{
		_file<<(void*)(newMessageBuffer_+i) << " newMessageBuffer_["<<i<<"]="<<int(newMessageBuffer_[i])<<std::endl;
	}

	_file.close();
}
} // end of namespace
	
