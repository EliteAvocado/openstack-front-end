#pragma once

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class Utility
{
public:
	static std::string ExecuteCommand( const char* command );
	static std::string ExecuteCommand( std::string command );
};
