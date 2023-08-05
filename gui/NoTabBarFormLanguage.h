#pragma once

#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/label.hpp>

#include "NoTabBarFormBase.h"
#include "MainForm.h"

class NoTabBarFormLanguage : public NoTabBarFormBase
{
public:
	NoTabBarFormLanguage( MainForm& parentForm,unsigned int curLanguage,bool isModal = false );
	~NoTabBarFormLanguage();
protected:
	void InitMainForm(); 
	void UpdateStringsWidgets();
	void UpdateStringsModalForms();
public: 
	MainForm&								m_pParentForm;
	unsigned int							m_iCurSelectedIndex;
private:
	std::vector<std::shared_ptr<button>>	m_vButtons;
	std::vector<std::shared_ptr<combox>>	m_vComboBoxes;
	std::vector<std::shared_ptr<label>>		m_vLabels;
};

