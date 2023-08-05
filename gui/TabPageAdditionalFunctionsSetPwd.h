#pragma once

#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>

#include "TabPageBase.h"

class TabPageAdditionalFunctionsSetPwd : public TabPageBase
{
public:
	TabPageAdditionalFunctionsSetPwd( window wd,MainFormBase* parentForm );
	~TabPageAdditionalFunctionsSetPwd();
protected:
	void InitTabPage();
	void UpdateStringsWidgets();
	void UpdateStringsModalForms();
private:
	std::vector<std::shared_ptr<button>> m_vButtons;
	std::vector<std::shared_ptr<label>>  m_vLabels;
};

