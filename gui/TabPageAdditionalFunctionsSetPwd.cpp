#include "TabPageAdditionalFunctionsSetPwd.h"
#include "Utility.h"

TabPageAdditionalFunctionsSetPwd::TabPageAdditionalFunctionsSetPwd( window wd,MainFormBase* parentForm )
	:
	TabPageBase( wd,parentForm )
{
	MainSetup( "vertical	<			weight = 19% placeEmpty_00>"
			   "			<			weight = 10% placeLabelHead margin = [0%,5%,0%,5%]>"
			   "			<			weight = 20% placeLabel margin = [0%,5%,0%,5%]>"
			   "			<			weight = 2% placeEmpty_01>"
			   "			<			weight = 20% placeButtons gap = 2%>"
			   "			<			weight = 19% placeEmpty_02>" );

}


TabPageAdditionalFunctionsSetPwd::~TabPageAdditionalFunctionsSetPwd()
{
}


void TabPageAdditionalFunctionsSetPwd::InitTabPage()
{
	// TODO: setup buttons

	for( int i = 0; i < 2; ++i )
	{
		auto p = std::make_shared<button>( *this );
		m_vButtons.push_back( p );
	}

	auto pCurBtn = m_vButtons[ 0 ];
	m_place.field( "placeButtons" ) << *pCurBtn;
	pCurBtn->events().click( [ this ]{

		//m_parent->ChangeTabPage( 4,4 );
		//m_parent->SwitchToTabPage( 0 );
		Utility::ExecuteCommand( "chromium-browser --app=https://studip.uni-halle.de --user-data-dir=/home/john/.config/chromium" );

	} );

	pCurBtn = m_vButtons[ 1 ];
	m_place.field( "placeButtons" ) << *pCurBtn;
	pCurBtn->events().click( [ this ](){

		//m_parent->ChangeTabPage( 4,4 );
		//m_parent->SwitchToTabPage( 0 );
		Utility::ExecuteCommand( "chromium-browser --app=https://studmail.uni-halle.de/gw/webacc --user-data-dir=/home/john/.config/chromium" );

	} );

	// TODO: setup labels

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

void TabPageAdditionalFunctionsSetPwd::UpdateStringsWidgets()
{
	std::string basePath = TABPAGE_ADDITIONALFUNCTIONSSETPWD_FILEPATH_BASE + GET_CURLANGUAGE_STR + "/";

	//---------//
	// BUTTONS //
	//---------//

	std::vector<std::string> buttonStrings = FIO_ReadFromFileToVector( basePath + FILE_BUTTONS );

	auto pCurBtn = m_vButtons[ 0 ];
	auto pCurBtnText = buttonStrings[ 0 ];
	pCurBtn->caption( ( pCurBtnText ) );

	pCurBtn = m_vButtons[ 1 ];
	pCurBtnText = buttonStrings[ 1 ];
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

void TabPageAdditionalFunctionsSetPwd::UpdateStringsModalForms()
{
}
