#pragma once

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class Utility
{
public:
	std::string ExecuteCommand( const char* command );
};