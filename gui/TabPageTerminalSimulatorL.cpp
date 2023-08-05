#include "TabPageTerminalSimulatorL.h"
#include "Utility.h"

TabPageTerminalSimulatorL::TabPageTerminalSimulatorL( window wd,MainFormBase* parentForm )
	:
	TabPageBase( wd,parentForm )
{
	MainSetup( "vertical	<			weight = 19% placeEmpty_00>"
			   "			<			weight = 10% placeLabelHead margin = [0%,5%,0%,5%]>"
			   "			<			weight = 20% placeLabel margin = [0%,5%,0%,5%]>"
			   "			<			weight = 2% placeEmpty_01>"
			   "			<			weight = 20% placeButton>"
			   "			<			weight = 19% placeEmpty_02>" );
}


TabPageTerminalSimulatorL::~TabPageTerminalSimulatorL()
{
}


void TabPageTerminalSimulatorL::InitTabPage()
{
	for( int i = 0; i < 1; ++i )
	{
		auto p = std::make_shared<button>( *this );
		m_vButtons.push_back( p );
	}

	auto pCurBtn = m_vButtons[ 0 ];
	m_place.field( "placeButton" ) << *pCurBtn;
	pCurBtn->events().click( [ this ]{

		Utility::ExecuteCommand( "gnome-terminal" );

	} );

	for( int i = 0; i < 2; ++i )
	{
		auto p = std::make_shared<label>( *this );
		m_vLabels.push_back( p );
	}

	auto pCurLbl = m_vLabels[ 0 ];
	m_place.field( "placeLabelHead" ) << *pCurLbl;

	pCurLbl = m_vLabels[ 1 ];
	m_place.field( "placeLabel" ) << *pCurLbl;
}

void TabPageTerminalSimulatorL::UpdateStringsWidgets()
{
	std::string basePath = TABPAGE_TERMINALSIMULATORL_FILEPATH_BASE + GET_CURLANGUAGE_STR + "/";

	//---------//
	// BUTTONS //
	//---------//

	std::vector<std::string> buttonStrings = FIO_ReadFromFileToVector( basePath + FILE_BUTTONS );

	auto pCurBtn = m_vButtons[ 0 ];
	auto pCurBtnText = buttonStrings[ 0 ];
	pCurBtn->caption( ( pCurBtnText ) );

	//--------//
	// LABELS //
	//--------//

	std::vector<std::string> labelStrings = FIO_ReadFromFileToVector( basePath + FILE_LABELS );

	auto pCurLbl = m_vLabels[ 0 ];
	auto pCurLblText = labelStrings[ 0 ];
	pCurLbl->format( true );
	pCurLbl->caption( ( "<bold,size=12>" + pCurLblText + "</>" ) );

	pCurLbl = m_vLabels[ 1 ];
	pCurLblText = labelStrings[ 1 ];
	pCurLbl->caption( ( pCurLblText ) );
}

void TabPageTerminalSimulatorL::UpdateStringsModalForms()
{
}
