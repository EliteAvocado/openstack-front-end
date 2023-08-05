#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "Client.h"
#include "Message.h"
#include "Logger.h"
#include "FileInputOutput.h"
#include "Globals.h"

class ClientHelper
{

// Singleton stuff
public:
	static ClientHelper& __instance()
	{
		static ClientHelper ch;
		return ch;
	}
private:
	ClientHelper();
	ClientHelper( ClientHelper const& )	= delete;
	void operator=( ClientHelper const& )	= delete;
// class specific stuff
/*
public:
	 ClientHelper();
	 ClientHelper( std::string serverName,std::string serverPort,std::string delimiter,std::string clientID );
*/
public:
	std::vector<std::string> SendRequest( std::string request );
	std::string SendRequest_str( std::string request );
	std::string GetClientID();
private:
	Message CreateMessage( std::string content );
	void CallFunction( const Message& msg,bool to_vec = false );
private:
	std::string m_serverName;
	std::string m_serverPort;
	char m_delimiter;
	std::string m_clientID;
	std::vector<std::string> m_dataVec;
	std::string m_data;
};
