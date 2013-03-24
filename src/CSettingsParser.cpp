#include "headers.h"

CSettingsParser::CSettingsParser(std::string file)
{
	m_Filename = file;
	ReadByBoost();
	m_IsChanged = false;
    gLogger << CLogger::LOG_INFO << "CSettingsParser konstruktor";
}

CSettingsParser::~CSettingsParser()
{
	if(IsChanged())
	{
		WriteByBoost();
	}
	pt.clear();
}

bool CSettingsParser::IsChanged()
{
	return m_IsChanged;
}

void CSettingsParser::ReadByBoost()
{
	try
	{
		boost::property_tree::ini_parser::read_ini(m_Filename, pt);
        gLogger << CLogger::LOG_INFO << "Boosted reading ini file COMPLETED";

	}
	catch(boost::property_tree::ptree_error const &e)
	{
        gLogger << CLogger::LOG_ERROR << e.what();
	}
}

void CSettingsParser::WriteByBoost()
{
	try
	{
		boost::property_tree::ini_parser::write_ini(m_Filename, pt);
	}
	catch(boost::property_tree::ptree_error const &e)
	{
        gLogger << CLogger::LOG_ERROR << e.what();
	}
	
}
