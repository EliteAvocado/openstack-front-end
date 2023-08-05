#include "Message.h"

#include <iostream>

Message::Message()
	:
	m_lengthBody( 0 )
{
}


const char* Message::Data() const
{
	Logger::__instance().LogLine( "Message::Data()" );
	
	return m_data;
}


char* Message::Data()
{
	Logger::__instance().LogLine( "Message::Data()" );

	return m_data;
}


std::size_t Message::GetLengthFull() const
{
	Logger::__instance().LogLine( "Message::GetLengthFull()" );

	return LENGTH_HEADER + m_lengthBody;
}


const char* Message::Body() const
{
	Logger::__instance().LogLine( "Message::Body()" );

	return LENGTH_HEADER + m_data;
}


char* Message::Body()
{
	Logger::__instance().LogLine( "Message::Body()" );

	return LENGTH_HEADER + m_data;
}


std::size_t Message::GetLengthBody() const
{
	Logger::__instance().LogLine( "Message::GetLengthBody()" );

	return m_lengthBody;
}


void Message::SetLengthBody( std::size_t length )
{
	Logger::__instance().LogLine( "Message::SetLengthBody()" );

	m_lengthBody = ( length > LENGTH_BODY_MAX ) ? LENGTH_BODY_MAX : length;
}


bool Message::DecodeHeader()
{
	Logger::__instance().LogLine( "Message::DecodeHeader()" );
	
	char header[ LENGTH_HEADER + 1 ] = "";
	std::strncat( header,m_data,LENGTH_HEADER );
	m_lengthBody = std::atoi( header );

	if( m_lengthBody > LENGTH_BODY_MAX )
	{
		m_lengthBody = 0;
		return false;
	}

	return true;
}


void Message::EncodeHeader()
{
	Logger::__instance().LogLine( "Message::EncodeHeader()" );

	char header[ LENGTH_HEADER + 1 ] = "";
	std::sprintf( header,"%4d",static_cast<int>( m_lengthBody ) );
	std::memcpy( m_data,header,LENGTH_HEADER );
}

void Message::Clear()
{
	memset( m_data,0,sizeof m_data );
}
