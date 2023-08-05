#include "MainFormBase.h"
#include "TabPageBase.h"

MainFormBase::MainFormBase( std::string caption )
	:
	MainFormBase( caption,CENTER_FORM( WNDWIDTH,WNDHEIGHT ) )
{
}

MainFormBase::MainFormBase( std::string caption,const rectangle& rec,const appearance& app,const window& wnd )
	:
	form( wnd,rec,app )
{
	this->caption( ( caption ) );
}


MainFormBase::~MainFormBase()
{
}


void MainFormBase::MainSetup( const char* placeDiv,bool isModal,int startTabPageIndex,const char* tabDivName,const char* tabBarDivName )
{
	m_tabBarDivName = tabBarDivName;

	m_place.bind( *this );
	m_place.div( placeDiv );

	InitMainForm();
	InitTabBar( startTabPageIndex,tabDivName );
	UpdateStrings();
	
	m_place.collocate();

	if( isModal )
		API::modal_window( *this );
}

void MainFormBase::UpdateStrings()
{
	UpdateStringsWidgets();
	UpdateStringsModalForms();
	for( auto & i : m_vTabPages )
	{
		std::dynamic_pointer_cast<TabPageBase>( i )->UpdateStrings();
	}
}

void MainFormBase::InitTabBar( int startTabPageIndex,const char* tabDivName )
{	
	m_tabBar.create( *this );
	m_place.field( tabDivName ) << m_tabBar;

	PreAttachTabBar();

	std::size_t index = 0;
	for( auto & i : m_vTabPages )
	{
		m_tabBar.attach( index++,*i );
		m_place.field( m_tabBarDivName ).fasten( *i );   //Fasten the tab pages
	}

	PostAttachTabBar();

	m_tabBar.activated( startTabPageIndex );
}

void MainFormBase::ChangeTabPage( int tabBarIndex,int tabPageIndex,bool dropOther,bool setFocus )
{
	m_tabBar.attach( tabBarIndex,*m_vTabPages[ tabPageIndex ],dropOther );
	m_vTabPages[ m_vTabPageDistribution[ tabBarIndex ] ]->hide();

	if( setFocus )
		m_tabBar.activated( tabBarIndex ); 
	
	m_vTabPageDistribution[ tabBarIndex ] = tabPageIndex;

	m_place.collocate();
}

void MainFormBase::SwitchToTabPage( int tabBarIndex )
{
	m_tabBar.activated( tabBarIndex );
}

