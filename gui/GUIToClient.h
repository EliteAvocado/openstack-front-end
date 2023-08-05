#pragma once

#include "Logger.h"
#include "FileInputOutput.h"
#include "Instance.h"
#include "Utility.h"
#include "Globals.h"

class GUIToClient
{
public:
	GUIToClient() {} // default constructor
	GUIToClient( std::string basePath )
	{
		Initialize( basePath );
	}
	void Initialize( std::string basePath )
	{
		requestPath = basePath + FILE_REQUESTS;

		std::string configBasePath = CONFIG_FILEPATH;
        	std::vector<std::string> configVec = FIO_ReadFromFileToVector( configBasePath + FILE_CONFIG );

		//m_params = configVec[ 0 ] + " " + configVec[ 1 ] + " " + configVec[ 2 ] + " " + configVec[ 3 ];

        	m_delimiter = configVec[ 2 ][ 0 ];
		m_clientID = configVec[ 3 ];

	}
        void FetchRequests()
        {
                m_requests.clear();

                m_requests = FIO_ReadFromFileToVector( requestPath );
        }
        void GetInstancesByOS()
        {
                m_instances.clear();

                //std::vector<std::string> instanceStrings = StringToVec( Utility::ExecuteCommand( "boostclient " + m_params + " " + m_requests[ 0 ] ) );
		std::vector<std::string> instanceStrings = StringToVec( Utility::ExecuteCommand( "./boostclient " + m_requests[ 0 ] ) );

                for( unsigned int i = 0; i < instanceStrings.size() - 2; i+=3 )
                {
                        m_instances.push_back( Instance( instanceStrings[ i ],instanceStrings[ i+1 ],instanceStrings[ i+2 ] ) );
                }
        }
        void ConnectToInstance( int instanceIndex )
        {
                //std::vector<std::string> idIpPort = StringToVec( Utility::ExecuteCommand( "boostclient " + m_params + " " + m_requests[ 1 ] + m_instances[ instanceIndex ].GetTemplateID() + "#" + m_clientID ) );
                std::vector<std::string> idIpPort = StringToVec( Utility::ExecuteCommand( "./boostclient " + m_requests[ 1 ] + m_instances[ instanceIndex ].GetTemplateID() + "#" +  m_clientID ) );
		m_instanceID = std::to_string( std::stoi( idIpPort[ 0 ] ) ); // little hack because it seems like there is something like a newline in front
                Logger::__instance().LogLine( Utility::ExecuteCommand( "./Connect.sh " + idIpPort[ 1 ] + " " + idIpPort[ 2 ] ) );
        }
        void DisconnectFromInstance()
        {
                //Utility::ExecuteCommand( "client/boostclient " + m_params + " " + m_requests[ 2 ] + m_instanceID );
        	Utility::ExecuteCommand( "./boostclient " + m_requests[ 2 ] + m_instanceID );
	}
private:
	std::vector<std::string> StringToVec( std::string str )
	{
		std::vector<std::string> strVec;
		std::string s = "";
                std::istringstream ss( str );
                while( std::getline( ss,s,m_delimiter ) )
                {
                	strVec.push_back( s );
            	}

		return strVec;
	}
public:
	std::vector<Instance> m_instances;
private:
	std::string requestPath;
        std::vector<std::string> m_requests;
        //std::vector<Instance> m_instances;
        std::string m_instanceID;
	//std::string m_params;
	std::string m_clientID;
	char m_delimiter;
};

