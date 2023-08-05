#pragma once

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include "Message.h"
#include "Logger.h"

#include <future>

using boost::asio::ip::tcp;

class Client
{
public:
	Client( boost::asio::io_service& ioService,tcp::resolver::iterator endpointIterator,std::promise<bool>& promRdy,std::promise<std::string>& promDone );
	
	void Send( const Message& msg );
	void Close();
private:
	// Server Client Interaction
	void Connect( tcp::resolver::iterator endpointIterator );
	void ReadHeader();
	void ReadBody();
	void Write();
	Message CreateMessage( std::string content );
public:
	// Helper
	void RequestUpdateData();
	void RequestConnectionData();
	//bool ConnectToVM();	// in helper class
	//void OnUpdate();		// in helper class
private:
	boost::asio::io_service&	m_ioService;
	tcp::socket					m_socket;
	Message 					m_readMsg;
	std::deque<Message> 		m_writeMsgQueue;
	//void ( Client::*m_funcptr ) ( std::string,size_t );
	std::promise<bool>&			m_promRdy;
	std::promise<std::string>&	m_promDone;
};