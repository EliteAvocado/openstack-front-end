#ifdef _WIN32
#include <Windows.h>
#include <psapi.h>
#endif

#include "NoTabBarFormLanguage.h"

NoTabBarFormLanguage::NoTabBarFormLanguage( MainForm& parentForm,unsigned int curLanguage,bool isModal )
	:
	NoTabBarFormBase(	"Sprachauswahl",
						( isModal ) ? 
						CENTER_FORM_MODAL( 400,200,parentForm )
						: CENTER_FORM( 400,200 ),
						form::appear::decorate<>{},
						(isModal) ? parentForm.handle() : NULL ),
	m_pParentForm( parentForm ),
	m_iCurSelectedIndex( curLanguage )
{
	MainSetup( "vertical	<			weight = 19% placeEmpty_00>"
			   "			<			weight = 40% <vertical <placeComboBoxLabel> <placeComboBox> margin = 5%> <vertical <placeInfoLabel> <placeLabel> margin = 5%>>"
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

NoTabBarFormLanguage::~NoTabBarFormLanguage()
{
}

void NoTabBarFormLanguage::InitMainForm()
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

		m_pParentForm.ChangeLaguage( m_iCurSelectedIndex );

		this->close();

	} );

	pCurBtn = m_vButtons[ 1 ];
	m_place.field( "placeButtons" ) << *pCurBtn;
	pCurBtn->events().click( [ this ](){

		this->close();

	} );

	// TODO: setup labels

	for( int i = 0; i < 3; ++i )
	{
		auto p = std::make_shared<label>( *this );
		m_vLabels.push_back( p );
	}

	auto pCurLbl = m_vLabels[ 0 ];
	m_place.field( "placeComboBoxLabel" ) << *pCurLbl;

	pCurLbl = m_vLabels[ 1 ];
	m_place.field( "placeInfoLabel" ) << *pCurLbl;

	pCurLbl = m_vLabels[ 2 ];
	m_place.field( "placeLabel" ) << *pCurLbl;

	// TODO: setup comboBoxes

	auto pComboBox = std::make_shared<combox>( *this );
	m_place.field( "placeComboBox" ) << *pComboBox;
	m_vComboBoxes.push_back( pComboBox );
}

void NoTabBarFormLanguage::UpdateStringsWidgets()
{
	std::string basePath = NOTABBARFORM_LANGUAGE_FILEPATH_BASE + GET_CURLANGUAGE_STR + "/";

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

	//--------//
	// LABELS //
	//--------//

	std::vector<std::string> labelStrings = FIO_ReadFromFileToVector( basePath + FILE_LABELS );

	auto pCurLbl = m_vLabels[ 0 ];
	auto pCurLblText = labelStrings[ 0 ];
	pCurLbl->format( true );
	pCurLbl->caption( ( "<bold,size=10>" + pCurLblText + "</>" ) );

	pCurLbl = m_vLabels[ 1 ];
	pCurLblText = labelStrings[ 1 ];
	pCurLbl->format( true );
	pCurLbl->caption( ( "<bold,size=10>" + pCurLblText + "</>" ) );

	pCurLbl = m_vLabels[ 2 ];
	pCurLblText = labelStrings[ 2 ];
	pCurLbl->caption( ( pCurLblText ) );

	//------------//
	// COMBOBOXES //
	//------------//

	std::vector<std::string> comboboxStrings = FIO_ReadFromFileToVector( basePath + FILE_COMBOBOXES );
	
	m_vComboBoxes[ 0 ]->clear();
	for( auto & i : comboboxStrings )
	{
		m_vComboBoxes[ 0 ]->push_back( i );
	}

	m_vComboBoxes[ 0 ]->events().selected.clear();
	m_vComboBoxes[ 0 ]->events().selected( [ this,labelStrings ]( const nana::arg_combox& acmb ) mutable
	{
		std::string lblStr = m_vComboBoxes[ 0 ]->text( acmb.widget.option() );

		this->m_iCurSelectedIndex = acmb.widget.option();

		m_vLabels[ 2 ]->caption( ( labelStrings[ 2 ] + lblStr ) );
	} );

	// set defaultValue
	m_vComboBoxes[ 0 ]->option( m_iCurSelectedIndex );
}

void NoTabBarFormLanguage::UpdateStringsModalForms()
{
}
