#pragma once

#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/label.hpp>

#include "TabPageBase.h"
#include "GUIToClient.h"

class TabPageWindowsExpert : public TabPageBase
{
public:
	TabPageWindowsExpert( window wd,MainFormBase* parentForm );
	~TabPageWindowsExpert();
protected:
	void InitTabPage();
	void UpdateStringsWidgets();
	void UpdateStringsModalForms();
private:
	std::vector<std::shared_ptr<button>> m_vButtons;
	std::vector<std::shared_ptr<combox>> m_vComboBoxes;
	std::vector<std::shared_ptr<label>>  m_vLabels;
	int m_curTemplateIndex;
	GUIToClient m_gtc;
};

