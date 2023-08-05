#pragma once

#include "Message.h"

class SessionParticipant
{
public:
	virtual ~SessionParticipant() {}
	virtual void Deliver( const Message& msg ) = 0;
};
