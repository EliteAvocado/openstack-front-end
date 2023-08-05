#pragma once

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include <nana/gui/widgets/panel.hpp>

#include "Globals.h"

using namespace nana;

class MainFormBase : public form
{
public:
	MainFormBase( std::string caption );
	MainFormBase( std::string caption,const rectangle& rec,const appearance& app = {},const window& wnd = {} );
	virtual ~MainFormBase();
public:
	void ChangeTabPage( int tabBarIndex,int tabPageIndex,bool dropOther = true,bool setFocus = true );
	void SwitchToTabPage( int tabBarIndex );
	void MainSetup( const char* placeDiv,bool isModal = false,int startTabPageIndex = 0,const char* tabDivName = "tab",const char* tabBarDivName = "tab_frame" );
	void UpdateStrings();
protected:
	virtual void InitMainForm()		= 0;
	virtual void PreAttachTabBar()	= 0; // add all pages that should be attached at start
	virtual void PostAttachTabBar() = 0; // add all pages that should be accessible at runtime but shouldn't be shown from the get-go
	virtual void UpdateStringsWidgets() = 0;
	virtual void UpdateStringsModalForms() = 0;
private:
	void InitTabBar( int startTabPageIndex = 0,const char* tabDivName = "tab" );
protected:
	place										m_place;
	tabbar<std::string>							m_tabBar;
	std::vector<std::shared_ptr<panel<false>>>	m_vTabPages;
	//std::vector<std::shared_ptr<TabPageBase>>	m_vTabPages;
	const char*									m_tabBarDivName;
	std::vector<int>							m_vTabPageDistribution;
};

