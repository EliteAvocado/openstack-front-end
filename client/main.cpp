#include "Logger.h"
#include "ClientHelper.h"

#include "FileInputOutput.h"

#include "Instance.h"
#include "Utility.h"

/*
class MainHelper
{
public:
	MainHelper() {}
	void FetchRequests( std::string basePath )
	{
		m_requests.clear();

        	m_requests = FIO_ReadFromFileToVector( basePath + FILE_REQUESTS );
	}
	void GetInstancesByOS()
	{
		m_instances.clear();

		std::vector<std::string> instanceStrings = ClientHelper::__instance().SendRequest( m_requests[ 0 ] );

        	for( unsigned int i = 0; i < instanceStrings.size() - 2; i+=3 )
        	{
               		m_instances.push_back( Instance( instanceStrings[ i ],instanceStrings[ i+1 ],instanceStrings[ i+2 ] ) );
  		}
	}
	void ConnectToInstance( int instanceIndex )
	{
		std::vector<std::string> idIpPort = ClientHelper::__instance().SendRequest( m_requests[ 1 ] + m_instances[ instanceIndex ].GetTemplateID() + "#" + ClientHelper::__instance().GetClientID() );
                m_instanceID = std::to_string( std::stoi( idIpPort[ 0 ] ) ); // little hack because it seems like there is something like a newline in front
		Logger::__instance().LogLine( Utility::ExecuteCommand( "./Connect.sh " + idIpPort[ 1 ] + " " + idIpPort[ 2 ] ) );
	}
	void DisconnectFromInstance()
	{
		ClientHelper::__instance().SendRequest( m_requests[ 2 ] + m_instanceID );
	}
private:
	std::vector<std::string> m_requests;
	std::vector<Instance> m_instances;
	std::string m_instanceID;
};

int main( int argc,char* argv[] )
{
	MainHelper mh;

	mh.FetchRequests( TABPAGE_WINDOWSEXPERT_FILEPATH_BASE );
	mh.GetInstancesByOS();
	mh.ConnectToInstance( 0 );
	mh.DisconnectFromInstance();

	return 0;
}
*/

// pass request via commandline
int main( int argc,char* argv[] )
{
	//std::cout << argc << std::endl;
	// std::cout << ClientHelper::__instance().SendRequest( argv[ 1 ] );
	std::cout << ClientHelper::__instance().SendRequest_str( argv[ 1 ] );
	/*
	ClientHelper ch( argv[ 1 ],argv[ 2 ],argv[ 3 ],argv[ 4 ] );
	std::cout << ch.SendRequest_str( argv[ 5 ] );
	*/
        return 0;
}
