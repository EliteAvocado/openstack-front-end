#include "NoTabBarFormBase.h"

NoTabBarFormBase::NoTabBarFormBase( std::string caption ) 
	:
	NoTabBarFormBase( caption,CENTER_FORM( WNDWIDTH,WNDHEIGHT ) )
{
}

NoTabBarFormBase::NoTabBarFormBase( std::string caption,const rectangle& rec,const appearance& app,const window& wnd )
	:
	form( wnd,rec,app )
{
	this->caption( ( caption ) );
}

NoTabBarFormBase::~NoTabBarFormBase()
{
}

void NoTabBarFormBase::MainSetup( const char* placeDiv,bool isModal )
{
	m_place.bind( *this );
	m_place.div( placeDiv );

	InitMainForm();
	UpdateStrings();

	m_place.collocate();

	if( isModal )
		API::modal_window( *this );
}

void NoTabBarFormBase::UpdateStrings()
{
	UpdateStringsWidgets();
	UpdateStringsModalForms();
}
