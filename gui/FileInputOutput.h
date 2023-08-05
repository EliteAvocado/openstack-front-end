#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <algorithm>
#include <iterator>

#include "string2wstring.h"

class FileInputOutput
{
private:
	FileInputOutput();
	~FileInputOutput();
public:
	// main functions
	static void							__WriteToFile( std::string filePath,std::string contentString,bool append = true );
	static std::string					__ReadFromFile( std::string filePath );
	static std::vector<std::string>		__ReadFromFileToVector( std::string filePath );
	static std::wstring					__ReadFromFile_WStr( std::string filePath );
	static std::vector<std::wstring>	__ReadFromFileToVector_WStr( std::string filePath );

	// utility functions:
	static std::string					__VectorToString( std::vector<std::string> stringVector );
	static std::vector<std::string>		__StringsToVector( std::string strings,char delimiter = '\n' );
};

namespace
{
	inline void						FIO_WriteToFile( std::string filePath,std::string contentString,bool append = true )
	{ FileInputOutput::__WriteToFile( filePath,contentString,append ); }

	inline std::string					FIO_ReadFromFile( std::string filePath )
	{ return FileInputOutput::__ReadFromFile( filePath ); }

	inline std::vector<std::string>		FIO_ReadFromFileToVector( std::string filePath )
	{ return FileInputOutput::__ReadFromFileToVector( filePath ); }

	inline std::wstring					FIO_ReadFromFile_WStr( std::string filePath )
	{ return FileInputOutput::__ReadFromFile_WStr( filePath ); }

	inline std::vector<std::wstring>	FIO_ReadFromFileToVector_WStr( std::string filePath )
	{ return FileInputOutput::__ReadFromFileToVector_WStr( filePath ); }

	inline static std::string			FIO_VectorToString( std::vector<std::string> stringVector )
	{ return FileInputOutput::__VectorToString( stringVector ); }

	inline std::vector<std::string>		FIO_StringsToVector( std::string strings,char delimiter = '\n' )
	{ return FileInputOutput::__StringsToVector( strings,delimiter ); }
}
