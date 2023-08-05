#pragma once

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include <nana/gui/widgets/panel.hpp>

#include "Globals.h"

using namespace nana;

class NoTabBarFormBase : public form
{
public:
	NoTabBarFormBase( std::string caption );
	NoTabBarFormBase( std::string caption,const rectangle& rec,const appearance& app = {},const window& wnd = {} );
	~NoTabBarFormBase();
public:
	void MainSetup( const char* placeDiv,bool isModal = false );
	void UpdateStrings();
protected:
	virtual void InitMainForm() = 0;
	virtual void UpdateStringsWidgets() = 0;
	virtual void UpdateStringsModalForms() = 0;
protected:
	place	m_place;
};

