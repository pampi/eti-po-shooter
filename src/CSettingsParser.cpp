#include "headers.h"

CSettingsParser::CSettingsParser(std::string file)
{
	m_Filename = file;
	m_Max_width = MAXBUFFERWIDTH;
	m_Size = 0;
	Read();
	m_IsChanged = false;
}

CSettingsParser::CSettingsParser(std::string file, unsigned int width)
{
	m_Filename = file;
	m_Max_width = width;
	m_Size = 0;
	Read();
}

CSettingsParser::~CSettingsParser()
{
	if(IsChanged())
	{
		Write();
	}
	m_Filename.clear();
	m_data.clear();
}

bool CSettingsParser::IsChanged()
{
	return m_IsChanged;
}

void CSettingsParser::Read()
{
	std::ifstream in(m_Filename.c_str());
	if(!in.is_open())
	{
		gLogger << gLogger.LOG_ERROR << "Unable to read settings file";
		return;
	}

	std::string line, param, value;
	char *tmp;

	while( !in.eof())
	{
		tmp = new char[m_Max_width];
		in.getline(tmp, m_Max_width);
		line.assign(tmp);

		if(line.size() > 0 && line[0] != '#' )
		{
			unsigned int j = 0;
			unsigned int length = line.size();

			while(line[j] != ' ')
			{
				j++;
			}

			param = line.substr(0, j);

			while(line[j] == ' ' || line[j] == '=')
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
		}
		else
		{
			param = line;
			value = "";
		}

		m_data.push_back(make_pair(param, value));
		m_Size++;
	}
	in.close();
	m_IsChanged = true;
}

void CSettingsParser::Write()
{
	std::ofstream out(m_Filename.c_str());
	if(!out.is_open())
	{
		gLogger<< gLogger.LOG_ERROR << "Unable to write to settings file";
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

void CSettingsParser::Get(std :: string param, int* value)
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