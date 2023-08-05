#ifdef _WIN32
#include <Windows.h>
#include <psapi.h>
#endif

#include "NoTabBarFormLogin.h"
#include "Utility.h"

NoTabBarFormLogin::NoTabBarFormLogin( MainForm& parentForm,bool isModal )
	:
	NoTabBarFormBase( "LogIn",
	( isModal ) ?
	CENTER_FORM_MODAL( 600,300,parentForm )
	: CENTER_FORM( 600,300 ),
	form::appear::decorate<>{},
	( isModal ) ? parentForm.handle() : NULL ),
	m_pParentForm( parentForm )
{
	MainSetup( "vertical	<			weight = 19% placeEmpty_00>"
			   "vertical	<			weight = 40% placeTextBox gap = 2%>"
			   "			<			weight = 2% placeEmpty_01>"
			   "			<			weight = 20% placeButtons gap = 2%>"
			   "			<			weight = 19% placeEmpty_02>",isModal );

	//Disable close button.
#ifdef __linux__ 
	this->events().unload( []( const arg_unload& arg )
	{
		arg.cancel = true;
	} );
#elif _WIN32
	auto sysm = ::GetSystemMenu( ( HWND )this->native_handle(),false );
	::RemoveMenu( sysm,::GetMenuItemCount( sysm ) - 1,MF_BYPOSITION );
#endif
}

NoTabBarFormLogin::~NoTabBarFormLogin()
{
}

void NoTabBarFormLogin::InitMainForm()
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

		std::string basePath = NOTABBARFORM_LOGIN_FILEPATH_BASE;
		std::vector<std::string> userAndPassword = FIO_ReadFromFileToVector( basePath + FILE_PASSWORD );

		std::string userString, passwordString;

		m_vTextBoxes[ 0 ]->getline( 0,userString );
		m_vTextBoxes[ 1 ]->getline( 0,passwordString );

		if( userAndPassword[ 0 ] == userString &&
			userAndPassword[ 1 ] == passwordString )
		{
			m_pParentForm.ChangeTabPage( 3,8 );
			this->close();
		}

	} );

	pCurBtn = m_vButtons[ 1 ];
	m_place.field( "placeButtons" ) << *pCurBtn;
	pCurBtn->events().click( [ this ](){

		this->close();

	} );

	// TODO: setup textBoxes

	auto pTextBox = std::make_shared<textbox>( *this );
	m_place.field( "placeTextBox" ) << *pTextBox;
	m_vTextBoxes.push_back( pTextBox );

	pTextBox = std::make_shared<textbox>( *this );
	m_place.field( "placeTextBox" ) << *pTextBox;
	m_vTextBoxes.push_back( pTextBox );
}

void NoTabBarFormLogin::UpdateStringsWidgets()
{
	std::string basePath = NOTABBARFORM_LOGIN_FILEPATH_BASE + GET_CURLANGUAGE_STR + "/";

	//----------//
        //  OTHERS  //
        //----------//

        std::vector<std::string> otherStrings = FIO_ReadFromFileToVector( basePath + FILE_OTHERS );

        this->caption( otherStrings[ 0 ] );

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

	//-----------//
	// TEXTBOXES //
	//-----------//

	std::vector<std::string> tetxboxStrings = FIO_ReadFromFileToVector( basePath + FILE_TEXTBOXES );

	auto pCurTextBox = m_vTextBoxes[ 0 ];
	auto pCurTextBoxText = tetxboxStrings[ 0 ];
	pCurTextBox->tip_string( pCurTextBoxText ).multi_lines( false );

	pCurTextBox = m_vTextBoxes[ 1 ];
	pCurTextBoxText = tetxboxStrings[ 1 ];
	pCurTextBox->tip_string( pCurTextBoxText ).multi_lines( false ).mask( '*' );
}

void NoTabBarFormLogin::UpdateStringsModalForms()
{
}
