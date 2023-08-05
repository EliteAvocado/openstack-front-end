#pragma once

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>

#include "SessionParticipant.h"

using boost::asio::ip::tcp;

class SessionGroup
{
public:
	void Join( std::shared_ptr<SessionParticipant> participant );
	void Leave( std::shared_ptr<SessionParticipant> participant );
	void Deliver( const Message& msg,std::shared_ptr<SessionParticipant> index );
private:
	enum
	{
		RECENT_MSG_MAX = 100
	};
	std::set<std::shared_ptr<SessionParticipant>> m_participants;
	std::deque<Message> m_recentMsgQueue;
};