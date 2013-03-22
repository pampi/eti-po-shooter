#ifndef SETPARSER_H
#define SETPARSER_H
#include "headers.h"

#ifndef WIN32
extern CLogger gLogger;
#endif

/*
################### README #####################
Jak używać:

	// Stwórz obiekt
    CSettingsParser settings("settings.dat");
	CSettingsParser settings("settings.dat"); <- albo tak z wartościami z headers.h

    // Czytanie danych [stara wersja]
    int width, height;
	settings.Get("width", &width);
	settings.Get("height", &height);
	
	std::string str;
	settings.Get("title", &str);
	
	float gravity;
	settings.Get("g", &gravity);
	
	char ch;
	settings.Get("player", &ch);
	
	bool isLow;
	settings.Get("use30hz", &isLow);

	// Czytanie danych [nowa wersja]
	typ zwracany var = settings.GetBoosted<typ zwracany>("Sekcja.Klucz"),domyślna wartość)

	// Zapis danych <- jeszcze nie zboostowane
	settings.Set("title", "sfml tutorial");
	settings.Write(); <- wołać na samym końcu

	// Przykładowy plik wynikowy
	# linie z hashem[#] beda ignorowane
	# spacje też będą ignorowane

	[WindowSize]
	width = 1280
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


class CSettingsParser
{
protected:
	boost::property_tree::ptree pt;
	bool m_IsChanged;
	std::string m_Filename;
	std::vector< std::pair< std::string, std::string> > m_data;
	unsigned int m_Size, m_Max_width;

public:
	CSettingsParser(std::string file = SETTINGSPATH);
	CSettingsParser(std::string file, unsigned int width);
	~CSettingsParser();
		
	void Read();
	void ReadByBoost();
	void Write();

	template <typename T>
	T GetBoosted(const std::string param, const T defaultValue)
	{
		T ret_val;
		try
		{
			ret_val = pt.get<T>(param);
			return ret_val;
		}
		catch(boost::exception const &)
		{
			gLogger<< gLogger.LOG_ERROR << (std::string("Reading wrong section from config file. You typed: ")+param).c_str();
			return ret_val = defaultValue;
		}
	}

	bool IsChanged();

	void Get(std::string param, std :: string *value);
	void Get(std::string param, bool *value);
	void Get(std::string param, char *value);
	void Get(std::string param, int *value);
	void Get(std::string param, float *value);

	void Set(std::string param, std :: string value);
	void Set(std::string param, bool value);
	void Set(std::string param, char value);
	void Set(std::string param, int value);
	void Set(std::string param, float value);

};
#endif
