#include "SessionGroup.h"

void SessionGroup::Join( std::shared_ptr<SessionParticipant> participant )
{

	std::cout << "SessionGroup::Join()" << std::endl;

	m_participants.insert( participant );

	for( auto msg : m_recentMsgQueue )
	{
		participant->Deliver( msg );
	}	
}


void SessionGroup::Leave( std::shared_ptr<SessionParticipant> participant )
{

	std::cout << "SessionGroup::Leave()" << std::endl;

	m_participants.erase( participant );
}


void SessionGroup::Deliver( const Message& msg,std::shared_ptr<SessionParticipant> index )
{

	std::cout << "SessionGroup::Deliver()" << std::endl;

	/* ------------------------------------------------------------ */

	// Save All Messages and Resend them on Join

	//m_recentMsgQueue.push_back( msg );
	//while( m_recentMsgQueue.size() > RECENT_MSG_MAX )
	//{
	//	m_recentMsgQueue.pop_front();
	//}

	/* ------------------------------------------------------------ */

	// Send to one

	(*m_participants.find( index ))->Deliver( msg );

	/* ------------------------------------------------------------ */

	// Send to all

	/*
	for( auto participant : m_participants )
	{
		participant->Deliver( msg );
	}
	*/
}

