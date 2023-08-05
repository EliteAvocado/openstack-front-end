#include "Client.h"

Client::Client( boost::asio::io_service& ioService,tcp::resolver::iterator endpointIterator,std::promise<bool>& promRdy,std::promise<std::string>& promDone )
	:
	m_ioService( ioService ),
	m_socket( ioService ),
	m_promRdy( promRdy ),
	m_promDone( promDone )
{
	Connect( endpointIterator );
}

void Client::Send( const Message& msg )
{
	//this->m_funcptr = funcptr;

	Logger::__instance().LogLine( "Client::Send() - Outer" );

	m_ioService.post( 
		[ this,msg ]() 
		{
			Logger::__instance().LogLine( "Client::Send() - Inner" );
			
			bool writeInProgress = !m_writeMsgQueue.empty();
			m_writeMsgQueue.push_back( msg );
			if( !writeInProgress )
			{
				Logger::__instance().LogLine( "Client::Send() - Start Writing" );

				Write();
			}
		} 
	);
}


void Client::Close()
{
	Logger::__instance().LogLine( "Client::Close()" );
	
	m_ioService.post(
		[ this ]()
		{
			m_socket.close();
		}
	);
}


void Client::Connect( tcp::resolver::iterator endpointIterator )
{
	Logger::__instance().LogLine( "Client::Connect() - Outer" );

	boost::asio::async_connect( 
		m_socket,
		endpointIterator,
		[ this ]( boost::system::error_code ec,tcp::resolver::iterator )
		{
			Logger::__instance().LogLine( "Client::Connect() - Inner" );
			Logger::__instance().LogLine( ec.message() );

			if( !ec )
			{
				Logger::__instance().LogLine( "Client::Connect() - Start Reading Header" );

				ReadHeader();
			}
		}
	);
}


void Client::ReadHeader()
{
	Logger::__instance().LogLine( "Client::ReadHeader() - Outer" );

	m_promRdy.set_value( true );

	boost::asio::async_read(
		m_socket,
		boost::asio::buffer( m_readMsg.Data(),Message::LENGTH_HEADER ),
		[ this ]( boost::system::error_code ec,std::size_t )
		{
			Logger::__instance().LogLine( "Client::ReadHeader() - Inner" );

			if( !ec && m_readMsg.DecodeHeader() )
			{
				Logger::__instance().LogLine( "Client::ReadHeader() - Start Reading Body" );

				ReadBody();
			}
			else
			{
				Logger::__instance().LogLine( "Client::ReadHeader() - Close" );

				m_socket.close();
			}
		}
	);
}


void Client::ReadBody()
{
	Logger::__instance().LogLine( "Client::ReadBody() - Outer" );
	
	boost::asio::async_read(
		m_socket,
		boost::asio::buffer( m_readMsg.Body(),m_readMsg.GetLengthBody() ),
		[ this ]( boost::system::error_code ec,std::size_t )
		{
			Logger::__instance().LogLine( "Client::ReadBody() - Inner" );

			if( !ec )
			{
				Logger::__instance().LogLine( "Client::ReadBody() - Start Writing" );

				// Do something with received data

				//( this->*m_funcptr )( m_readMsg.Body(),m_readMsg.GetLengthBody() );
				m_promDone.set_value( m_readMsg.Body() );

				// just close the socket or else we get an error here

				m_socket.close();

				// Go Back to pushing and polling

				//ReadHeader();
			}
			else
			{
				Logger::__instance().LogLine( "Client::ReadBody() - Close" );

				m_socket.close();
			}
		}
	);
}


void Client::Write()
{
	Logger::__instance().LogLine( "Client::Write() - Outer" );	

	boost::asio::async_write(
		m_socket,
		boost::asio::buffer( m_writeMsgQueue.front().Data(),m_writeMsgQueue.front().GetLengthFull() ),
		[ this ]( boost::system::error_code ec,std::size_t )
		{
			Logger::__instance().LogLine( "Client::Write() - Inner" );

			if( !ec )
			{
				Logger::__instance().LogLine( "Client::Write() - Start Writing" );
				
				m_writeMsgQueue.pop_front();
				if( !m_writeMsgQueue.empty() )
				{
					Write();
				}
			}
			else
			{
				Logger::__instance().LogLine( "Client::Write() - Close" );

				m_socket.close();
			}
		}
	);
}


void Client::RequestUpdateData()
{
	Send( CreateMessage( "---------------- Best Test EUW ---------------" ) );
}


void Client::RequestConnectionData()
{}


Message Client::CreateMessage( std::string content )
{
	Message msg;
	msg.SetLengthBody( content.length() );
	std::memcpy( msg.Body(),content.c_str(),msg.GetLengthBody() );
	msg.EncodeHeader();

	return msg;
}

