#pragma once

#include "SessionGroup.h"

class Session : public SessionParticipant,public std::enable_shared_from_this<Session>
{
public:
	Session( tcp::socket socket,SessionGroup& group );
	void Start();
	void Deliver( const Message& msg );
private:
	void ReadHeader();
	void ReadBody();
	void Write();
private:
	tcp::socket m_socket;
	SessionGroup& m_group;
	Message m_readMsg;
	std::deque<Message> m_writeMsgQueue;
};