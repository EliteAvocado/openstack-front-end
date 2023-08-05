#include "TabPageLinuxExpert.h"

TabPageLinuxExpert::TabPageLinuxExpert( window wd,MainFormBase* parentForm )
	:
	TabPageBase( wd,parentForm ),
	m_curTemplateIndex( 0 )
{
	MainSetup( "vertical	<			weight = 19% placeEmpty_00>"
			   "			<			weight = 40% <vertical <placeComboBoxLabel> <placeComboBox> margin = 5%> <vertical <placeInfoLabel> <placeLabel> margin = 5%>>"
			   "			<			weight = 2% placeEmpty_01>"
			   "			<			weight = 20% placeButtons gap = 2%>"
			   "			<			weight = 19% placeEmpty_02>" );

}


TabPageLinuxExpert::~TabPageLinuxExpert()
{
}


void TabPageLinuxExpert::InitTabPage()
{
        // setup gtc

        m_gtc.Initialize( TABPAGE_LINUXEXPERT_FILEPATH_BASE );
        m_gtc.FetchRequests();
        m_gtc.GetInstancesByOS();

	// TODO: setup buttons

	for( int i = 0; i < 2; ++i )
	{
		auto p = std::make_shared<button>( *this );
		m_vButtons.push_back( p );
	}

	auto pCurBtn = m_vButtons[ 0 ];
	m_place.field( "placeButtons" ) << *pCurBtn;
	pCurBtn->events().click( [ this ]{

                m_gtc.ConnectToInstance( m_curTemplateIndex );

                // DC:
                m_gtc.DisconnectFromInstance();
		m_parent->ChangeTabPage( 1,1 );
		m_parent->SwitchToTabPage( 0 );

	} );

	pCurBtn = m_vButtons[ 1 ];
	m_place.field( "placeButtons" ) << *pCurBtn;
	pCurBtn->events().click( [ this ](){

		m_parent->ChangeTabPage( 1,1 );

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

void TabPageLinuxExpert::UpdateStringsWidgets()
{
	std::string basePath = TABPAGE_LINUXEXPERT_FILEPATH_BASE + GET_CURLANGUAGE_STR + "/";

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

	//std::vector<std::string> comboboxStrings = FIO_ReadFromFileToVector( basePath + FILE_COMBOBOXES );

	m_vComboBoxes[ 0 ]->clear();
	/*
	for( auto & i : comboboxStrings )
	{
		m_vComboBoxes[ 0 ]->push_back( i );
	}
	*/
	//std::cout << m_gtc.m_instances.size() << std::endl;

	for( int i = 0; i < m_gtc.m_instances.size(); ++i )
	{
		m_vComboBoxes[ 0 ]->push_back( m_gtc.m_instances[ i ].GetName() );
	}


	m_vComboBoxes[ 0 ]->events().selected.clear();
	m_vComboBoxes[ 0 ]->events().selected( [ this,labelStrings ]( const nana::arg_combox& acmb ) mutable
	{
		// std::string lblStr = m_vComboBoxes[ 0 ]->text( acmb.widget.option() );
		// m_vLabels[ 2 ]->caption( ( labelStrings[ 2 ] + lblStr ) );

		m_curTemplateIndex = acmb.widget.option();
                m_vLabels[ 2 ]->caption( m_gtc.m_instances[ m_curTemplateIndex ].GetDesc() );
	} );

	// set defaultValue
	m_vComboBoxes[ 0 ]->option( 0 );
}

void TabPageLinuxExpert::UpdateStringsModalForms()
{
}
