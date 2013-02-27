#ifndef CLOGGER_H
#define CLOGGER_H
#include "headers.h"

/*
################### README #####################
Jak u�ywa�:

	// Stw�rz obiekt
    CLogger myLog ("1.0.4.2", "testfile.txt");
	CLogger myLog (); <- albo tak z warto�ciami z headers.h

    // Strumieniowe zapisywanie danych
    myLog << myLog::LOG_WARNING << "Hey! ... This is a warning message!";
    myLog << myLog::e_logType::LOG_ERROR << "WOW! Something really wrong is happening here!";
    myLog << "This is just a simple text";

	//Tak b�dzie wygl�da� plik wynikowy
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

public:
	enum elogType { LOG_ERROR, LOG_WARNING, LOG_INFO };

	CLogger (const char *engine_version = ENGINEVERSION, const char *filename = LOGPATH)
	{
		m_File.open(filename);

		if(m_File.is_open())
		{
			m_File << "Engine Version: " << ENGINEVERSION << std::endl;
			m_File << "File log created" << std::endl << std::endl;
		}
	}


	friend CLogger& operator<<(CLogger &logger, const char *text)
	{
		logger.m_File << text << std::endl;
		return logger;
	}

	friend CLogger& operator<<(CLogger &logger, const elogType logType)
	{
		switch (logType)
		{
			case CLogger::LOG_ERROR :
				{
					logger.m_File << "[ERROR]: ";
					logger.m_numErrors++;
					break;
				}

			case CLogger::LOG_WARNING :
				{
					logger.m_File << "[WARNING]: ";
					logger.m_numWarnings++;
					break;
				}

			default:
				{
					logger.m_File << "[INFO]: ";
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

			m_File << m_numWarnings << " warnings" << std::endl;
			m_File << m_numErrors << " errors" << std::endl;

			m_File.close();
		}
	}
};
#endif