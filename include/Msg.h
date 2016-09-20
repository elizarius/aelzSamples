#ifndef CPP_SAMPLES_MSG_H_
#define CPP_SAMPLES_MSG_H_

#include <iostream>

namespace cpp_samples
{
	enum MsgType
	{
		MT_NORMAL = 0,
		MT_REQUEST,
		MT_REPLY
	};


/**
 *
 * This class describes the message container that can be transfered with this
 * messaging facility
 *
 */
    class Msg
	{
        friend class Socket;

		public:
  /**
   *
   * constructor
   * This is the constructor of Msg object
   *
   * @param number the unique number of the message
   * @param dataBuffer a pointer to the array containing message data
   * @param length the length of the message byte stream
   */
			Msg(unsigned int number,
				unsigned int length,
				char* dataBuffer);

  /**
   * This is the destructor of Msg object
   */
            ~Msg(){}

  /**
   *
   * This operation is used to get a pointer to the buffer containing message data
   *
   * @return a pointer to the data buffer
   *
   */
			char* getData()
			{
				return dataPtr_;
			}

  /**
   *
   * This operation is used to get the message number
   *
   * @return the message number
   *
   */
			unsigned int getNumber() const
			{
				return number_;
			}

  /**
   *
   * This operation is used to get the length of message data buffer
   *
   * @return the message size in bytes
   *
   */
			unsigned int getLength() const
			{
				return length_;
			}

  /**
   *
   * This operation is used to get the message ID, this id is only used to send a reply to some request
   *
   * @return the ID of the message
   *
   */
			unsigned int getID() const
			{
				return id_;include/Msg.h
			}

		private:
			/** disable copy and assignment */
			Msg(const Msg&);
			const Msg& operator=(const Msg&);

			//void setID(unsigned int id);

			unsigned int 		number_;
			unsigned int 		id_;

			char*				dataPtr_;
			unsigned int		length_;
			MsgType				type_;
	};
} // end namespace
#endif
