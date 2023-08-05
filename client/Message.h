#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Logger.h"

class Message
{
public:
	Message();

	const char* Data() const;
	char* Data();

	std::size_t GetLengthFull() const;

	const char* Body() const;
	char* Body();

	std::size_t GetLengthBody() const;
	void SetLengthBody( std::size_t length );

	bool DecodeHeader();
	void EncodeHeader();

	void Clear();
public:
	enum
	{
		LENGTH_HEADER = 4
	};
	enum
	{
		LENGTH_BODY_MAX = 1024
	};
private:
	char m_data[ LENGTH_HEADER + LENGTH_BODY_MAX ];
	std::size_t m_lengthBody;
};
