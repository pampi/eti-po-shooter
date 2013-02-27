#ifndef HEADERS_H
#define HEADERS_H

// Biblioteki STL
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>

// Biblioteki SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Nasze:
#include "CLogger.h"
#include "CSettingsParser.h"

// Zewnêtrzne



// Globalny logger
extern CLogger gLogger;
//extern CSettingsParser gSettings;

#endif

// Dane do CLogger [Loggera]
#define LOGPATH "log.txt"
#define ENGINEVERSION "0.0.1"

// Dane do CSettingsParser
#define MAXBUFFERWIDTH 100
#define SETTINGSPATH "config.ini"