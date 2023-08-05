#include "MainForm.h"

#include "TabPageStart.h"

#include "TabPageLinux.h"
#include "TabPageLinuxExpert.h"

#include "TabPageWindows.h"
#include "TabPageWindowsExpert.h"

#include "TabPageTerminalSimulator.h"
#include "TabPageTerminalSimulatorL.h"

#include "TabPageAdditionalFunctions.h"
#include "TabPageAdditionalFunctionsSetPwd.h"

#include "NoTabBarFormLanguage.h"

#ifdef _WIN32
#include <Windows.h>
#include <psapi.h>
#endif

#include <nana/gui/widgets/listbox.hpp>

MainForm::MainForm( const window& wnd )
	:
	MainFormBase( "GUI Prototype",CENTER_FORM( 800,600 ),form::appear::decorate<>{},wnd )
{
	MainSetup(	"vertical	<weight = 5% placeEmpty_00>"
				"			<weight = 10% buttons margin = [3%,5%,3%,5%] gap = 10%>"
				"			<weight = 5% placeEmpty_01>"
				"			<weight = 10% tab margin = [1%,1%,1%,1%] >"
				"			<weight = 70% tab_frame margin = 10%>" );

	//Disable close button.
#ifdef __linux__ 
	this->events().unload( []( const arg_unload& arg )
	{
		arg.cancel = true;
	} );
#elif _WIN32
	auto sysm = ::GetSystemMenu( (HWND)this->native_handle(),false );
	::RemoveMenu( sysm,::GetMenuItemCount( sysm ) - 1,MF_BYPOSITION );
#endif
	
	// reset all changed pages on tabPageSwitch
	m_tabBar.events().click( [this]{
	
		int cur = m_tabBar.activated();
		
		for( unsigned int i = 1; i < m_tabBar.length(); ++i )
		{
			if( m_vTabPageDistribution[ i ] != i )
			{
				ChangeTabPage( i,i );
			}
		}

		m_tabBar.activated( cur );
	
	} );
}


MainForm::~MainForm()
{
}


void MainForm::InitMainForm()
{
	for( int i = 0; i < 3; ++i )
	{
		auto p = std::make_shared<button>( *this );
		m_vButtons.push_back( p );
		m_place.field( "buttons" ) << *p;
	}
	
	m_vButtons[ 2 ]->events().click( [ this ]{

		NoTabBarFormLanguage fm( *this,GET_CURLANGUAGE_NUM,true );

	} );
}

void MainForm::ChangeLaguage( unsigned int language )
{
	if( GET_CURLANGUAGE_NUM != language )
	{		
		// Update language file
		FIO_WriteToFile( FILE_CUR_LANGUAGE,std::to_string( language ),false );
		
		// UpdateLanguage
		UpdateStrings();

		// UpdateLanguage for all tabPages
		// ...
	}
}

void MainForm::UpdateStringsWidgets()
{
	std::string basePath = MAINFORM_FILEPATH_BASE + GET_CURLANGUAGE_STR + "/";

	//----------//
        //  OTHERS  //
        //----------//

        std::vector<std::string> otherStrings = FIO_ReadFromFileToVector( basePath + FILE_OTHERS );

	for( int i = 0; i < m_tabBar.length(); ++i )
	{
		m_tabBar.text( i,otherStrings[ i ] );
	}

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

	pCurBtn = m_vButtons[ 2 ];
	pCurBtnText = buttonStrings[ 2 ];
	pCurBtn->caption( ( pCurBtnText ) );
}

void MainForm::UpdateStringsModalForms()
{
	std::string basePath = MAINFORM_FILEPATH_BASE + GET_CURLANGUAGE_STR + "/";

	std::vector<std::string> modalformStrings = FIO_ReadFromFileToVector( basePath + FILE_MODALFORMS );
	
	auto pCurBtn = m_vButtons[ 0 ];
	pCurBtn->events().click.clear();
	pCurBtn->events().click( [ this,modalformStrings ]{

		msgbox mb( *this,modalformStrings[ 0 ],msgbox::yes_no );
		mb.icon( mb.icon_question );
		mb << modalformStrings[ 1 ];
		if( mb.pick_yes == mb() )
			API::exit();

	} );

	pCurBtn = m_vButtons[ 1 ];
	pCurBtn->events().click.clear();
	pCurBtn->events().click( [ this,modalformStrings ]{

		msgbox mb( *this,modalformStrings[ 2 ],msgbox::yes_no );
		mb.icon( mb.icon_question );
		mb << modalformStrings[ 3 ];
		if( mb.pick_yes == mb() )
			API::exit();

	} );
}

void MainForm::PreAttachTabBar()
{
	ADD_PAGE( "Start",TabPageStart ); 
	ADD_PAGE( "Linux",TabPageLinux );
	ADD_PAGE( "Windows",TabPageWindows );
	ADD_PAGE( "Terminal Simulator",TabPageTerminalSimulator );
	ADD_PAGE( "Weitere Funktionen",TabPageAdditionalFunctions );
}


void MainForm::PostAttachTabBar()
{
	ADD_PAGE_POST( TabPageLinuxExpert );
	ADD_PAGE_POST( TabPageWindowsExpert );
	ADD_PAGE_POST( TabPageAdditionalFunctionsSetPwd );
	ADD_PAGE_POST( TabPageTerminalSimulatorL );
}
