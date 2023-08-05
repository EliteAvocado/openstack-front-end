#include "TabPageBase.h"


TabPageBase::TabPageBase( window wd,MainFormBase* parentForm )
	: 
	panel<false>( wd ),
	m_parent( parentForm )
{
}


TabPageBase::~TabPageBase()
{
}


void TabPageBase::MainSetup( const char* placeDiv )
{
	m_place.bind( *this );
	m_place.div( placeDiv );

	InitTabPage();

	m_place.collocate();
}

void TabPageBase::UpdateStrings()
{
	UpdateStringsWidgets();
	UpdateStringsModalForms();
}
