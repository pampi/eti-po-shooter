#ifndef SETPARSER_H
#define SETPARSER_H
#include "headers.h"

/*
################### README #####################
Jak używać:

	// Stwórz obiekt
	CSettingsParser settings("settings.dat"); <- albo tak z wartościami z headers.h


	// Czytanie danych [nowa wersja]
	typ zwracany var = settings.Get<typ zwracany>("Sekcja.Klucz"),domyślna wartość)

	// Zapis danych [nowa wersja]
	settings.Set<TYP>("Sekcja.Klucz",wartość taka jak TYP)

	// Przykładowy plik wynikowy
	# linie z hashem[#] beda ignorowane
	# spacje też będą ignorowane

	[WindowSize] <- Sekcja
	width = 1280 <- Klucz = Wartość
	height = 720

	[WindowTitle]
	title = Nobody expected...

	[WindowSettings]
	style=1
	depthBuffer = 0
	stencilBuffer = 0
	antialiasing = 2
	framerateLimit = 60

################################################
*/

#ifndef gSettings
#define gSettings CSettingsParser::GetReference()
#endif


class CSettingsParser: public TSingleton<CSettingsParser>
{
protected:
	boost::property_tree::ptree pt;
	bool m_IsChanged;
	std::string m_Filename;

	void ReadByBoost();
	void WriteByBoost();

public:
	CSettingsParser(std::string file = SETTINGSPATH);
	~CSettingsParser();

	template <typename T>
	// @param = SectionName.key @defaultValue = value to set if current key wasn't found
	T Get(const std::string param, const T defaultValue)
	{
		T ret_val;
		try
		{
			ret_val = pt.get<T>(param, defaultValue);
			return ret_val;
		}
		catch(boost::property_tree::ptree_error const &e)
        {
            gLogger<< CLogger::LOG_ERROR << e.what();
			return ret_val = defaultValue;
		}
	}

	template <typename T>
	//@param = SectionName.key @value = value to set
	void Set(const std::string param, const T value)
	{
		try
		{
			pt.put(param, value);
			m_IsChanged = true;
		}
		catch(boost::property_tree::ptree_error const &e)
		{
            gLogger << CLogger::LOG_ERROR << e.what();
		}
	}

	bool IsChanged();
};
#endif
