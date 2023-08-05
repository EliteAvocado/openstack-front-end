#include "FileInputOutput.h"

FileInputOutput::FileInputOutput()
{
}

FileInputOutput::~FileInputOutput()
{
}

// main functions
void FileInputOutput::__WriteToFile( std::string filePath,std::string contentString,bool append )
{
	std::ofstream fileStream( filePath,( append ) ? std::ios::app : std::ios::trunc );

	if( fileStream.is_open() )
	{
		fileStream <<  contentString;
		fileStream.close();
	}
}

std::string FileInputOutput::__ReadFromFile( std::string filePath )
{
	std::stringstream	content;
	std::string			curLine;
	std::ifstream		fileStream( filePath );

	if( fileStream.is_open() )
	{
		while( std::getline( fileStream,curLine ) )
		{
			content << curLine << '\n';
		}
		fileStream.close();
	}

	return content.str();
}

std::vector<std::string> FileInputOutput::__ReadFromFileToVector( std::string filePath )
{
	std::vector<std::string>	content;
	std::string					curLine;
	std::ifstream				fileStream( filePath );

	if( fileStream.is_open() )
	{
		while( std::getline( fileStream,curLine ) )
		{
			content.push_back( curLine );
		}
		fileStream.close();
	}

	return content;
}

std::wstring FileInputOutput::__ReadFromFile_WStr( std::string filePath )
{
	Widen<wchar_t>		to_wstring;
	std::stringstream	content;
	std::string			curLine;
	std::ifstream		fileStream( filePath );

	if( fileStream.is_open() )
	{
		while( std::getline( fileStream,curLine ) )
		{
			content << curLine << '\n';
		}
		fileStream.close();
	}

	return to_wstring( content.str() );
}

std::vector<std::wstring> FileInputOutput::__ReadFromFileToVector_WStr( std::string filePath )
{
	Widen<wchar_t>				to_wstring;
	std::vector<std::wstring>	content;
	std::string					curLine;
	std::ifstream				fileStream( filePath );

	if( fileStream.is_open() )
	{
		while( std::getline( fileStream,curLine ) )
		{
			content.push_back( to_wstring( curLine ) );
		}
		fileStream.close();
	}

	return content;
}

// utility functions:
std::string FileInputOutput::__VectorToString( std::vector<std::string> stringVector )
{
	std::ostringstream	oss;

	if( !stringVector.empty() )
	{
		std::copy( stringVector.begin(),stringVector.end() - 1,
				   std::ostream_iterator<std::string>( oss ) );
	}

	return oss.str();
}

std::vector<std::string> FileInputOutput::__StringsToVector( std::string strings,char delimiter )
{
	std::vector<std::string>	retVec;
	std::stringstream			ss( strings );
	std::string					curLine;

	while( getline( ss,curLine,delimiter ) )
	{
		retVec.push_back( curLine );
	}

	return retVec;
}
