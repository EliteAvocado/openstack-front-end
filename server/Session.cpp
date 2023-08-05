#include <vector>
#include <string>

#include "Session.h"

#include "Utility.h"
#include "FileInputOutput.h"
#include "Globals.h"

Session::Session( tcp::socket socket,SessionGroup& group )
	:
	m_socket( std::move( socket ) ),
	m_group( group )
{
}


void Session::Start()
{
	m_group.Join( shared_from_this() );
	ReadHeader();
}


void Session::Deliver( const Message& msg )
{

	std::cout << "Session::Deliver()" << std::endl;

	bool writeInProgress = !m_writeMsgQueue.empty();
	m_writeMsgQueue.push_back( msg );
	if( !writeInProgress )
	{
		Write();
	}
}


void Session::ReadHeader()
{

	std::cout << "Session::ReadHeader() - Outer" << std::endl;
	
	auto self( shared_from_this() );
	boost::asio::async_read(
		m_socket,
		boost::asio::buffer( m_readMsg.Data(),Message::LENGTH_HEADER ),
		[ this,self ]( boost::system::error_code ec,std::size_t )
		{

			std::cout << "Session::ReadHeader() - Inner" << std::endl;

			if( !ec && m_readMsg.DecodeHeader() )
			{

				std::cout << "Session::ReadHeader() - Start Decoding" << std::endl;

				ReadBody();
			}
			else
			{

				std::cout << "Session::ReadHeader() - Leave" << std::endl;

				m_group.Leave( shared_from_this() );
			}
		}
	);
}


void Session::ReadBody()
{

	std::cout << "Session::ReadBody() - Outer" << std::endl;

	auto self( shared_from_this() );
	boost::asio::async_read(
		m_socket,
		boost::asio::buffer( m_readMsg.Body(),m_readMsg.GetLengthBody() ),
		[ this,self ]( boost::system::error_code ec,std::size_t )
		{

			std::cout << "Session::ReadBody() - Inner" << std::endl;

			if( !ec )
			{

				std::cout << "Session::ReadBody() - Deliver" << std::endl;

				// 1. Do something with gotten data

				//std::cout.write( m_readMsg.Body(),m_readMsg.GetLengthBody() );
				//std::cout << "\n";

				std::string basePath = CONFIG_FILEPATH;
        			std::vector<std::string> configVec = FIO_ReadFromFileToVector( basePath + FILE_CONFIG );

				std::cout << basePath + FILE_CONFIG << std::endl;

        			std::string command = configVec[ 0 ];
        			char delimiter = configVec[ 1 ][ 0 ];

				// convert data to dataVector

                		std::string s = "";
				std::string fileWithParams = "";
                		std::istringstream ss( m_readMsg.Body() );
                		while( std::getline( ss,s,delimiter ) )
                		{
					fileWithParams += s;
					fileWithParams += " ";
		                }
				fileWithParams.pop_back();

				std::cout << "Command from config: " << command << std::endl;
				std::cout << "FileWithParams: " << fileWithParams << std::endl;


				// get the instance data
				Utility utils;
				command += " ";
				command += PHP_PATH;
				command += fileWithParams;

				std::cout << "------" << command << "------" << std::endl;

				std::string newMsgContent = utils.ExecuteCommand( command.c_str() );

				// 2. Create new Message
				
				//std::string newMsgContent = "Hallo;wie;geht's;denn;so;das;ist;ein;Teststring.";

				Message newMsg;
				newMsg.SetLengthBody( newMsgContent.length() );
				std::memcpy( newMsg.Body(),newMsgContent.c_str(),newMsg.GetLengthBody() );
				newMsg.EncodeHeader();

				// 3. Send it back
				
				m_group.Deliver( newMsg,self );

				// 4. Clear ReadMsg

				m_readMsg.Clear();

				// 5. Go back to polling stuff

				ReadHeader();
			}
			else
			{

				std::cout << "Session::ReadBody() - Leave" << std::endl;

				m_group.Leave( shared_from_this() );
			}
		}
	);
}


void Session::Write()
{
	std::cout << "Session::Write() - Outer" << std::endl;

	auto self( shared_from_this() );
	boost::asio::async_write(
		m_socket,
		boost::asio::buffer( m_writeMsgQueue.front().Data(),m_writeMsgQueue.front().GetLengthFull() ),
		[ this ]( boost::system::error_code ec,std::size_t )
		{

			std::cout << "Session::Write() - Inner" << std::endl;
			
			if( !ec )
			{

				std::cout << "Session::Write() - Start Writing" << std::endl;

				m_writeMsgQueue.pop_front();
				if( !m_writeMsgQueue.empty() )
				{
					Write();
				}
			}
			else
			{

				std::cout << "Session::Write() - Leave" << std::endl;

				m_group.Leave( shared_from_this() );
			}
		}
	);
}

