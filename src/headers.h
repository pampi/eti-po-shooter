#ifndef HEADERS_H
#define HEADERS_H

// Biblioteki STL
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <ctime>

// Biblioteki SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Nasze:
#include "CLogger.h"
#include "CSettingsParser.h"
#include "CFpsCounter.h"
#include "CDebugDraw.h"
#include "CScreen.h"
#include "CScreenManager.h"
#include "CResourceManager.h"
#include "CGame.h"

// Zewnêtrzne



// Globalny logger
extern CLogger gLogger;
// Globalny parser
extern CSettingsParser gSettings;
// Globalny ResourceManager
extern CResourceManager gResources;
// Globalny licznik FPS
extern CFpsCounter gFPS;
// Globalny Debug Drawer
extern CDebugDraw gDDraw;

#endif

// Dane do CLogger [Loggera]
#define LOGPATH "log.txt"
#define ENGINEVERSION "0.0.1"

// Dane do CSettingsParser
#define MAXBUFFERWIDTH 100
#define SETTINGSPATH "config.ini"

// Dane do czcionki
#define PATHTOFONT "HelveticaLight.otf"

// Czy wyœwietlaæ debug dane
#define DRAWDEBUG 1