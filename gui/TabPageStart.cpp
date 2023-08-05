#include "TabPageStart.h"


TabPageStart::TabPageStart( window wd,MainFormBase* parentForm )
	:
	TabPageBase( wd,parentForm )
{
	MainSetup( "vertical	<			weight = 20% placeEmpty_00>"
			   "			<vertical	weight = 70% <placeLabelMessageHead> <placeLabelMessage> margin = [ 20%,20%,20%,20% ]>"
			   "			<			weight = 10% placeEmpty_01>" );
}


TabPageStart::~TabPageStart()
{
}


void TabPageStart::InitTabPage()
{
	for( int i = 0; i < 2; ++i )
	{
		auto p = std::make_shared<label>( *this );
		m_vLabels.push_back( p );
	}

	auto pCurLbl = m_vLabels[ 0 ];
	m_place.field( "placeLabelMessageHead" ) << *pCurLbl;

	pCurLbl = m_vLabels[ 1 ];
	m_place.field( "placeLabelMessage" ) << *pCurLbl;
}

void TabPageStart::UpdateStringsWidgets()
{
	std::string basePath = TABPAGE_START_FILEPATH_BASE + GET_CURLANGUAGE_STR + "/";

	//--------//
	// LABELS //
	//--------//

	std::vector<std::string> labelStrings = FIO_ReadFromFileToVector( basePath + FILE_LABELS );

	auto pCurLbl = m_vLabels[ 0 ];
	auto pCurLblText = labelStrings[ 0 ];
	pCurLbl->format( true );
	pCurLbl->caption( ( "<bold,size=16>" + pCurLblText + "</>" ) );

	pCurLbl = m_vLabels[ 1 ];
	pCurLblText = labelStrings[ 1 ];	
	pCurLbl->format( true );
	pCurLbl->caption( ( "<bold,size=12>" + pCurLblText + "</>" ) );

}

void TabPageStart::UpdateStringsModalForms()
{
}
