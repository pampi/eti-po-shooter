#ifndef CLOGGER_H
#define CLOGGER_H
#include "headers.h"

#pragma warning(disable: 4996)

/*
################### README #####################
Jak u¿ywaæ:

	// Stwórz obiekt
    CLogger myLog ("1.0.4.2", "testfile.txt");
	CLogger myLog (); <- albo tak z wartoœciami z headers.h

    // Strumieniowe zapisywanie danych
    myLog << myLog::LOG_WARNING << "Hey! ... This is a warning message!";
    myLog << myLog::e_logType::LOG_ERROR << "WOW! Something really wrong is happening here!";
    myLog << "This is just a simple text";

	//Tak bêdzie wygl¹da³ plik wynikowy
	Engine Version: 0.0.1
	File log created

	[WARNING]: Hey! ... This is a warning message!
	[ERROR]: WOW! Something really wrong is happening here!
	This is just a simple text


	1 warnings
	1 errors

################################################
*/

class CLogger
{
private:
	std::ofstream m_File;

	unsigned int m_numWarnings;
	unsigned int m_numErrors;
	unsigned int m_numInfos;

	char m_buffor[64];
	time_t m_czas;
	std::tm m_czasTM;
	

public:
	enum elogType { LOG_ERROR, LOG_WARNING, LOG_INFO };

	CLogger (const char *engine_version = ENGINEVERSION, const char *filename = LOGPATH)
	{
		std::time(&m_czas);
		m_czasTM = *localtime(&m_czas);
		setlocale( LC_ALL, "Polish");
		std::strftime(m_buffor, sizeof(m_buffor), "%#c", &m_czasTM);

		m_File.open(filename);

		if(m_File.is_open())
		{
			m_File << "Engine Version: " << ENGINEVERSION << std::endl;
			m_File << "File log created" << std::endl;
			m_File << "Created: " << m_buffor <<std::endl << std::endl << std::endl;
		}
		
	}


	friend CLogger& operator<<(CLogger &logger, const char *text)
    {
        std::time(&logger.m_czas);
        logger.m_czasTM = *localtime(&logger.m_czas);
		std::strftime(logger.m_buffor, sizeof(logger.m_buffor), "%H:%M:%S", &logger.m_czasTM);
		logger.m_File << "[" << logger.m_buffor << "] : " <<text << std::endl;
		return logger;
	}

	friend CLogger& operator<<(CLogger &logger, const elogType logType)
	{
		switch (logType)
		{
			case CLogger::LOG_ERROR :
				{
					logger.m_File << "[ERROR] ";
					logger.m_numErrors++;
					break;
				}

			case CLogger::LOG_WARNING :
				{
					logger.m_File << "[WARNING] ";
					logger.m_numWarnings++;
					break;
				}

			default:
				{
					logger.m_File << "[INFO] ";
					logger.m_numInfos++;
					break;
				}
		}
		return logger;
	}


	~CLogger()
	{
		if(m_File.is_open())
		{
			m_File << std::endl << std::endl;

			m_File << m_numInfos << " infos" << std::endl;
			m_File << m_numWarnings << " warnings" << std::endl;
			m_File << m_numErrors << " errors" << std::endl;

			m_File.close();
		}
	}
};
#endif
