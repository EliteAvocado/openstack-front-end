#pragma once

#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>

#include "TabPageBase.h"

#include "GUIToClient.h"

class TabPageWindows : public TabPageBase
{
public:
	TabPageWindows( window wd,MainFormBase* parentForm );
	~TabPageWindows();
protected:
	void InitTabPage();
	void UpdateStringsWidgets();
	void UpdateStringsModalForms();
private:
	std::vector<std::shared_ptr<button>> m_vButtons;
	std::vector<std::shared_ptr<label>>  m_vLabels;
	GUIToClient m_gtc;
};

