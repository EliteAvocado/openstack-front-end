#pragma once

#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>

#include "TabPageBase.h"

class TabPageTerminalSimulatorL : public TabPageBase
{
public:
	TabPageTerminalSimulatorL( window wd,MainFormBase* parentForm );
	~TabPageTerminalSimulatorL();
protected:
	void InitTabPage();
	void UpdateStringsWidgets();
	void UpdateStringsModalForms();
public:
	MainFormBase*						 m_pParentForm;
private:
	std::vector<std::shared_ptr<button>> m_vButtons;
	std::vector<std::shared_ptr<label>>  m_vLabels;
};

