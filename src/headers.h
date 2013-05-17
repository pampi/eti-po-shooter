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
#include <cmath>

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
#include <boost/thread.hpp>

// Biblioteki Thor
#include <Thor/Config.hpp>
#include <Thor/Resources.hpp>

// Zewnętrzne
#include "lua5.2/lua.hpp"

// Nasze:
#include "TSingleton.hpp"
#include "CLogger.hpp"
#include "CSettingsParser.hpp"
#include "CFpsCounter.hpp"
#include "CDebugDraw.hpp"
#include "CQuadTree.h"
#include "CInputHandler.hpp"
#include "CScreen.hpp"
#include "CScreenManager.hpp"
#include "CResourceManager.hpp"
#include "CSoundManager.hpp"
#include "CScript.hpp"
#include "CGame.hpp"
#include "CGuiElement.hpp"
#include "CTextBox.hpp"
#include "CButton.hpp"
#include "API4Lua.hpp"
#include "CTmxMap.hpp"
#include "CAnimation.hpp"
#include "CAnimatedSprite.hpp"
#include "CActor.hpp"
#include "CPlayer.hpp"





// lista naciśniętych buttonów
extern std::list<class CButton*> gButtonClicked;

#endif

// Dane do CLogger [Loggera]
#define LOGPATH "log.txt"
#define ENGINEVERSION "0.5.5"

// Dane do CSettingsParser
#define SETTINGSPATH "res/misc/config.ini"

// Dane do czcionki
#define PATHTOFONT "res/misc/HelveticaWorld.ttf"