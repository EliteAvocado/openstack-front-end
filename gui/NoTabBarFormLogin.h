#pragma once

#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>

#include "NoTabBarFormBase.h"
#include "MainForm.h"

class NoTabBarFormLogin : public NoTabBarFormBase
{
public:
	NoTabBarFormLogin( MainForm& parentForm,bool isModal = false );
	~NoTabBarFormLogin();
protected:
	void InitMainForm();
	void UpdateStringsWidgets();
	void UpdateStringsModalForms();
public:
	MainForm&								m_pParentForm;
	unsigned int							m_iCurSelectedIndex;
private:
	std::vector<std::shared_ptr<button>>	m_vButtons;
	std::vector<std::shared_ptr<textbox>>	m_vTextBoxes;
};
