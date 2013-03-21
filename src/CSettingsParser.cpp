#include "headers.h"

CSettingsParser::CSettingsParser(std::string file)
{
	m_Filename = file;
	m_Max_width = MAXBUFFERWIDTH;
	m_Size = 0;
	ReadByBoost();
	m_IsChanged = false;
}

CSettingsParser::CSettingsParser(std::string file, unsigned int width)
{
	m_Filename = file;
	m_Max_width = width;
	m_Size = 0;
	ReadByBoost();
}

CSettingsParser::~CSettingsParser()
{
	if(IsChanged())
	{
		Write();
	}
	m_Filename.clear();
	m_data.clear();
	pt.clear();
}

bool CSettingsParser::IsChanged()
{
	return m_IsChanged;
}

void CSettingsParser::Read()
{
	gLogger << gLogger.LOG_INFO << "Config reading started...";

	std::ifstream in(m_Filename.c_str());
	if(!in.is_open())
	{
		gLogger << gLogger.LOG_ERROR << std::string("Unable to read config file. Path: "+m_Filename).c_str();
		return;
	}
	
	std::string line, param, value;
	std::string tmp2;
	
	while( std::getline(in, tmp2) )
	{
		/* 
		NIE POWINNO DZIAŁAĆ, ALE DZIAŁA. 
		DEAL WITH IT
		*/
		param = ""; 
		value = "";
		
		line.assign(tmp2);
		
		
		if(line.length() > 0  )
		{
			if(line[0] != '#')
			{
				unsigned int j = 0;
				unsigned int length = line.size();
			
				while(line[j] != ' ' && j < length )
				{
					j++;
				}
			
				param = line.substr(0, j);
			
				while((line[j] == ' ' || line[j] == '=') && j < length)
				{
					j++;
				}
			
				int a = j;
			
				while(j < length && (line[j] != ' ' || line[j] != '\n'))
				{
					j++;
				}
			
				int b = j;
				value = line.substr(a, b);

				m_data.push_back(make_pair(param, value));
				m_Size++;
			}
			else
			{
				continue;
			}
			
		}
		else
		{
			param = line;
			value = "";
		}
	
		
	}
	in.close();
	m_IsChanged = true;
	gLogger << gLogger.LOG_INFO << "Config reading finished...";
}

void CSettingsParser::ReadByBoost()
{
	try
	{
		boost::property_tree::ini_parser::read_ini(m_Filename, pt);
		gLogger << gLogger.LOG_INFO << "Boosted reading ini file COMPLETED";

	}
	catch(boost::exception const &)
	{
		gLogger << gLogger.LOG_ERROR << "Boosted reading ini file FAILED";
	}
}

void CSettingsParser::Write()
{
	gLogger << gLogger.LOG_INFO << "Config writing started...";
	std::ofstream out(m_Filename.c_str());
	if(!out.is_open())
	{
		gLogger<< gLogger.LOG_ERROR << "Unable to write to config file";
		return;
	}

	for(unsigned int i =0; i< m_Size -1; ++i)
	{
		if(m_data[i].first[0] == '#' || m_data[i].first[0] == 0)
		{
			out << m_data[i].first << std::endl;
		}
		else
		{
			out << m_data[i].first << " = " << m_data[i].second << std::endl;
		}
	}
	out.close();
	gLogger << gLogger.LOG_INFO << "Config writing finished...";
}

void CSettingsParser::Get(std :: string param, std :: string* value)
{
	for(size_t i = 0; i < m_Size; ++i)
	{
		if(m_data[i].first[0] == '#')
			continue;
		if(m_data[i].first == param)
		{
			*value = m_data[i].second;
			return;
		}
	}
}

void CSettingsParser::Get(std :: string param, bool* value)
{
	for(size_t i = 0; i < m_Size; ++i)
	{
		if(m_data[i].first[0] == '#')
			continue;
		if(m_data[i].first == param)
		{
			*value = ((m_data[i].second == "TRUE") ? true : false);
			return;
		}
	}
}

void CSettingsParser::Get(std :: string param, char* value)
{
	for(size_t i = 0; i < m_Size; ++i)
	{
		if(m_data[i].first[0] == '#')
			continue;
		if(m_data[i].first == param)
		{
			*value = m_data[i].second[0];
			return;
		}
	}
}

void CSettingsParser::Get(std :: string paramu, int *value)
{
	for(unsigned int i = 0; i < m_Size; ++i)
	{
		if(m_data[i].first[0] == '#')
		{
			continue;
		}
		if(m_data[i].first == paramu)
		{
			std::stringstream ss(m_data[i].second);
			ss >> *value;
			return;
		}
	}
}

void CSettingsParser::Get(std :: string param, float* value)
{
	for(size_t i = 0; i < m_Size; ++i)
	{
		if(m_data[i].first[0] == '#')
			continue;
		if(m_data[i].first == param)
		{
			std::stringstream ss(m_data[i].second);
			ss >> *value;
			return;
		}
	}
}

void CSettingsParser::Set(std :: string param, std :: string value)
{
	m_IsChanged = true;
	for(size_t i = 0; i < m_Size; ++i)
	{
		if(m_data[i].first[0] == '#')
			continue;
		if(m_data[i].first == param)
		{
			m_data[i].second = value;
			return;
		}
	}
}

void CSettingsParser::Set(std :: string param, bool value)
{
	m_IsChanged = true;
	for(size_t i = 0; i < m_Size; ++i)
	{
		if(m_data[i].first[0] == '#')
			continue;
		if(m_data[i].first == param)
		{
			m_data[i].second = (value) ? "TRUE" : "FALSE";
			return;
		}
	}
}

void CSettingsParser::Set(std :: string param, char value)
{
	m_IsChanged = true;
	for(size_t i = 0; i < m_Size; ++i)
	{
		if(m_data[i].first[0] == '#')
			continue;
		if(m_data[i].first == param)
		{
			std::string tmp = "";
			tmp = value;
			m_data[i].second = tmp;
			return;
		}
	}
}

void CSettingsParser::Set(std :: string param, int value)
{
	m_IsChanged = true;
	for(size_t i = 0; i < m_Size; ++i)
	{
		if(m_data[i].first[0] == '#')
			continue;
		if(m_data[i].first == param)
		{
			std::stringstream ss;
			ss << value;
			m_data[i].second = ss.str();
			return;
		}
	}
}

void CSettingsParser::Set(std :: string param, float value)
{
	m_IsChanged = true;
	for(size_t i = 0; i < m_Size; ++i)
	{
		if(m_data[i].first[0] == '#')
			continue;
		if(m_data[i].first == param)
		{
			std::stringstream ss;
			ss << value;
			m_data[i].second = ss.str();
			return;
		}
	}
}
