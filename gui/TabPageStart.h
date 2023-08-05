#pragma once

#include <nana/gui/widgets/label.hpp>

#include "TabPageBase.h"

class TabPageStart : public TabPageBase
{
public:
	TabPageStart( window wd,MainFormBase* parentForm );
	~TabPageStart();
protected:
	void InitTabPage();
	void UpdateStringsWidgets();
	void UpdateStringsModalForms();
private:
	std::vector<std::shared_ptr<label>>  m_vLabels;
};

