#ifndef SETPARSER_H
#define SETPARSER_H
#include "headers.h"

/*
################### README #####################
Jak u�ywa�:

	// Stw�rz obiekt
    CSettingsParser settings("settings.dat");
	CSettingsParser settings("settings.dat"); <- albo tak z warto�ciami z headers.h

    // Czytanie danych 
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

	// Zapis danych
	settings.Set("title", "sfml tutorial");
	settings.Write(); <- wo�a� na samym ko�cu

	// Przyk�adowy plik wynikowy
	# linie z hashem[#] beda ignorowane
	# spacje te� b�d� ignorowane

	# screen size
	width = 1024
	height = 768

	# windows title
	title = sfml tutorial

	# phycics constants
	g = 9.81

	# player initials
	player = x

	# video mode
	use30hz = TRUE

################################################
*/


class CSettingsParser
{
protected:
	bool m_IsChanged;
	std::string m_Filename;
	std::vector< std::pair< std::string, std::string> > m_data;
	unsigned int m_Size, m_Max_width;

public:
	CSettingsParser(std::string file = SETTINGSPATH);
	CSettingsParser(std::string file, unsigned int width);
	~CSettingsParser();
		
	void Read();
	void Write();

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