#ifndef HEADERS_H
#define HEADERS_H

// Biblioteki STL
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <ctime>

// Biblioteki SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Zewnêtrzne
#include "lua5.2/lua.hpp"
#include "tinyxml2/tinyxml2.h"

// Nasze:
//DEPRECATED
//do wypierdolenia
#include "CLogger.h"
#include "CSettingsParser.h"
#include "CFpsCounter.h"
#include "CDebugDraw.h"
#include "CScreen.h"
#include "CScreenManager.h"
#include "CResourceManager.h"
#include "CMainMenu.h"
#include "CScript.h"
#include "CGame.h"
#include "CTextButton.h"
#include "CMenuTextButton.h"
//koniec DEPRECATED


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
#define SETTINGSPATH "res/misc/config.ini"

// Dane do czcionki
#define PATHTOFONT "res/misc/HelveticaWorld.ttf"

// Czy wyœwietlaæ debug dane
#define DRAWDEBUG 1
