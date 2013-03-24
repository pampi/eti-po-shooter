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
#include <boost/property_tree/ini_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

// Zewnętrzne
#include "lua5.2/lua.hpp"

// Nasze:
#include "TSingleton.hpp"
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



//Tu był item "Puszka pandory"
extern std::list<class CButton*> gButtonClicked;

#endif

// Dane do CLogger [Loggera]
#define LOGPATH "log.txt"
#define ENGINEVERSION "0.4.5"

// Dane do CSettingsParser
#define SETTINGSPATH "res/misc/config.ini"

// Dane do czcionki
#define PATHTOFONT "res/misc/HelveticaWorld.ttf"

// Czy wyświetlać debug dane
#define DRAWDEBUG 1
