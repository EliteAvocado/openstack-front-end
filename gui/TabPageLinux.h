#pragma once

#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>

#include "TabPageBase.h"
#include "GUIToClient.h"

class TabPageLinux : public TabPageBase
{
public:
	TabPageLinux( window wd,MainFormBase* parentForm );
	~TabPageLinux();
protected:
	void InitTabPage();
	void UpdateStringsWidgets();
	void UpdateStringsModalForms();
private:
	std::vector<std::shared_ptr<button>> m_vButtons;
	std::vector<std::shared_ptr<label>>  m_vLabels;
	GUIToClient m_gtc;
};

