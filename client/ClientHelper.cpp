#include "ClientHelper.h"

ClientHelper::ClientHelper()
{
	std::string basePath = CONFIG_FILEPATH;
	std::vector<std::string> configVec = FIO_ReadFromFileToVector( basePath + FILE_CONFIG );

	m_serverName = configVec[0];
	m_serverPort = configVec[1];
	m_delimiter = configVec[2][0];
	m_clientID = configVec[3];
}

/*
ClientHelper::ClientHelper( std::string serverName,std::string serverPort,std::string delimiter,std::string clientID )
	:
m_serverName( serverName ),
m_serverPort( serverPort ),
m_delimiter( delimiter[ 0 ] ),
m_clientID( clientID )
{
}
*/

std::vector<std::string> ClientHelper::SendRequest( std::string request )
{
	m_dataVec.clear();

	CallFunction( CreateMessage( request ),true );

	return m_dataVec;
}

std::string ClientHelper::SendRequest_str( std::string request )
{
	m_data = "";

	CallFunction( CreateMessage( request ),false );

	return m_data;
}

Message ClientHelper::CreateMessage( std::string content )
{
	Message msg;
	msg.SetLengthBody( content.length() );
	std::memcpy( msg.Body(),content.c_str(),msg.GetLengthBody() );
	msg.EncodeHeader();

	Logger::__instance().LogLine( "Content in Msg: " + content );

	return msg;
}


void ClientHelper::CallFunction( const Message& msg,bool to_vec )
{


	try
	{
		Logger::__instance().LogLine( "Start Client Stuff" );

		// setup for thread and client

		boost::asio::io_service ioService;

		tcp::resolver resolver( ioService );

		auto endpointIterator = resolver.resolve( { m_serverName,m_serverPort } );

		// create promises and futures

		std::promise<bool> promRdy;
		std::future<bool> futRdy = promRdy.get_future();

		std::promise<std::string> promDone;
		std::future<std::string> futDone = promDone.get_future();

		// initiate client

		Client myClient( ioService,endpointIterator,promRdy,promDone );

		// start thread

		std::thread myThread( 
			[ &ioService ]()
			{ 
				ioService.run(); 
			} 
		);

		// wait until connected to server and start doing stuff

		futRdy.wait();
		if( futRdy.get() )
		{
			Logger::__instance().LogLine( "----------------- READY -----------------" );
			myClient.Send( msg );
		}

		// wait until server replies and evaluate stuff

		futDone.wait();

		Logger::__instance().LogLine( "----------------- DONE -----------------" );
		//std::string data = futDone.get();
		//Logger::__instance().LogLine( data );

		// convert data to dataVector
		if( to_vec )
		{
			std::string s = "";
			std::istringstream ss( futDone.get() );
			while( std::getline( ss,s,m_delimiter ) )
			{
				m_dataVec.push_back( s );
			}
		}
		else
		{
			m_data = futDone.get();
		}

		// cleanup your garbage

		myClient.Close();
		myThread.join();
	}
	catch( std::exception& e )
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}

std::string ClientHelper::GetClientID()
{
	return m_clientID;
}
