#include "Server.h"

Server::Server( boost::asio::io_service& ioService,const tcp::endpoint& endpoint )
	:
	m_acceptor( ioService,endpoint ),
	m_socket( ioService )
{
	Accept();
}


void Server::Accept()
{
	
	std::cout << "Server::Accept() - Outer" << std::endl;

	m_acceptor.async_accept(  
		m_socket,
		[ this ]( boost::system::error_code ec )
		{

			std::cout << "Server::Accept() - Inner" << std::endl;

			if( !ec )
			{
				std::make_shared<Session>( std::move( m_socket ),m_sessionGroup )->Start();
			}

			Accept();
		}
	);
	
}

