#pragma once

#include "Session.h"

class Server
{
public:
	Server( boost::asio::io_service& ioService,const tcp::endpoint& endpoint );
private:
	void Accept();
private:
	tcp::acceptor	m_acceptor;
	tcp::socket		m_socket;
	SessionGroup	m_sessionGroup;
};