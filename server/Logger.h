#pragma once

#include <string>
#include <iostream>

#define LOGGING_ON 1

class Logger
{
public:
	static Logger& __instance()
	{
		static Logger l;
		return l;
	}
	void Log( std::string content )
	{
//#if defined( _DEBUG ) && defined( LOGGING_ON )
		std::cout << content;
//#endif
	}
	void LogLine( std::string content )
	{
//#if defined( _DEBUG ) && defined( LOGGING_ON )
		Log( content );
		std::cout << std::endl;
//#endif
	}
private:
	Logger() {}
	Logger( Logger const& )			= delete;
	void operator=( Logger const& ) = delete;
};
