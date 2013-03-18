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
#include <cstdio>

// Biblioteki SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Biblioteki BOOST
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

// Zewnêtrzne
#include "lua5.2/lua.hpp"
#include "tinyxml2/tinyxml2.h"

// Nasze:
#include "CLogger.h"
#include "CSettingsParser.h"
#include "CFpsCounter.h"
#include "CDebugDraw.h"
#include "CInputHandler.h"
#include "CScreen.h"
#include "CScreenManager.h"
#include "CResourceManager.h"
#include "CSoundManager.h"
#include "CScript.h"
#include "CGame.h"
#include "CGuiElement.h"
#include "CButton.h"
#include "CTextBox.h"
#include "API4Lua.h"
#include "CTmxMap.h"



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
// Globalna lista przyciskow do obsluzenia
extern std::list<class CButton*> gButtonClicked;

#endif

// Dane do CLogger [Loggera]
#define LOGPATH "log.txt"
#define ENGINEVERSION "0.1.0"

// Dane do CSettingsParser
#define MAXBUFFERWIDTH 100
#define SETTINGSPATH "res/misc/config.ini"

// Dane do czcionki
#define PATHTOFONT "res/misc/HelveticaWorld.ttf"

// Czy wyœwietlaæ debug dane
#define DRAWDEBUG 1
