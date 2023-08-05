#include <vector>
#include <string>
#include <iostream>

#include "Server.h"
#include "FileInputOutput.h"
#include "Globals.h"

int main( int argc,char* argv[] )
{
	try
	{
/*
		if( argc < 2 )
		{
			std::cerr << "Usage: chat_server <port> [<port> ...]\n";
			return 1;
		}
*/

		std::string basePath = CONFIG_FILEPATH;
        	std::vector<std::string> serverPorts = FIO_ReadFromFileToVector( basePath + FILE_SERVERS );

        	//m_serverName = configVec[0];
        	//m_serverPort = configVec[1];
        	//m_delimiter = configVec[2][0];

		boost::asio::io_service ioService;

		std::cout << "Start Server Stuff" << std::endl;

		std::list<Server> servers;
		for( int i = 0; i < argc; ++i )
		{
			tcp::endpoint endpoint( tcp::v4(),std::atoi( serverPorts[ i ].c_str() ) );
			servers.emplace_back( ioService,endpoint );
		}

		ioService.run();
	}
	catch( std::exception& e )
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
