#pragma once

#include <memory>
#include <vector>

#include <nana/gui/widgets/button.hpp>

#include "MainFormBase.h"

class MainForm : public MainFormBase
{
public:
	MainForm( const window& wnd = {} );
	~MainForm();
	void ChangeLaguage( unsigned int language );
protected:
	void InitMainForm();
	void PreAttachTabBar(); // add all pages that should be attached at start
	void PostAttachTabBar(); // add all pages that should be accessible at runtime but shouldn't be shown from the get-go
	void UpdateStringsWidgets();
	void UpdateStringsModalForms();
private:
	std::vector<std::shared_ptr<button>> m_vButtons;
};

