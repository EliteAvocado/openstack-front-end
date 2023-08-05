#include "Utility.h"

#include <iostream>

// executes a command and redirects the output

std::string Utility::ExecuteCommand( const char* command )
{
	char buffer[ 128 ];
	std::string result = "";

#ifdef __linux__ 
	std::shared_ptr<FILE> pipe( popen( command,"r" ),pclose );
#elif _WIN32
	std::shared_ptr<FILE> pipe( _popen( command,"r" ),_pclose );
#endif

	if( !pipe ) throw std::runtime_error( "popen() failed!" );
	while( !feof( pipe.get() ) ) 
	{
		if( fgets( buffer,128,pipe.get() ) != NULL )
		{
			result += buffer;
		}
	}

	return result;
}

std::string Utility::ExecuteCommand( std::string command )
{
	return ExecuteCommand( command.c_str() );
}
