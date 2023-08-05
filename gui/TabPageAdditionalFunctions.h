#pragma once

#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>

#include "TabPageBase.h"

class TabPageAdditionalFunctions : public TabPageBase
{
public:
	TabPageAdditionalFunctions( window wd,MainFormBase* parentForm );
	~TabPageAdditionalFunctions();
protected:
	void InitTabPage(); 
	void UpdateStringsWidgets();
	void UpdateStringsModalForms();
private:
	std::vector<std::shared_ptr<button>> m_vButtons;
	std::vector<std::shared_ptr<label>>  m_vLabels;
};

