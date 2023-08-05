#pragma once

#include <string>

class Instance
{
public:
	Instance( std::string templateID,std::string name,std::string desc )
	{
		m_templateID = templateID;
		m_name = name;
		m_desc = desc;
	}
	std::string GetTemplateID()
	{
		return m_templateID;
	}
	std::string GetName()
	{
		return m_name;
	}
 	std::string GetDesc()
	{
		return m_desc;
	}
	std::string GetInstanceID()
        {
                return m_instanceID;
        }
 	void SetInstanceID( std::string instanceID )
        {
                m_instanceID = instanceID;
        }
private:
	std::string m_templateID;
	std::string m_instanceID;
	std::string m_name;
	std::string m_desc;
};
