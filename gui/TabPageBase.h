#pragma once

#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/place.hpp>

#include "Globals.h"
#include "MainFormBase.h"

using namespace nana;

class TabPageBase : public panel<false>
{
public:
	TabPageBase( window wd,MainFormBase* parentForm );
	~TabPageBase();
public:
	void MainSetup( const char* placeDiv );
	void UpdateStrings();
protected:
	virtual void InitTabPage() = 0;
	virtual void UpdateStringsWidgets() = 0;
	virtual void UpdateStringsModalForms() = 0;
public:
	MainFormBase*		m_parent;
protected:
	place				m_place;
};

