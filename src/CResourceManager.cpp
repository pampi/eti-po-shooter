#include "headers.h"

const char *BUTTON_SECTION="buttons";
const char *TEXT_SECTION="texts";
const char *IMAGE_SECTION="images";
const char *EMPTY="";

const char korektor[] = " ,.-";

CResourceManager::CResourceManager() 
{
	m_font = new sf::Font();
	this->pTmxMap = NULL;
}

const sf::Image & CResourceManager::getImage(const std::string & filename)
{ 
	//	//	checking is image exist in memory
	for(std::map<std::string, sf::Image>::const_iterator it = m_images.begin(); it != m_images.end(); it++)
	{
		if(filename == it->first)
			return it->second;
	}

	//	//	if not found nothing, use default blank
	sf::Image _image;
	m_images[filename] = _image;
	gLogger << gLogger.LOG_ERROR<< (std::string("getImage() - Image Not Found: ")+filename).c_str();
	return m_images[filename];
}

bool CResourceManager::loadImage(const std::string & filename)
{
	sf::Image _image;
	if( _image.loadFromFile(filename) )
	{
		m_images[filename] = _image;
		gLogger << gLogger.LOG_INFO << (std::string("Image loaded. Name: ")+filename).c_str();
		return true;
	}
	return false;
}

int CResourceManager::getMapSize()
{
	return (int)m_images.size();
}

void CResourceManager::deleteImage(const std::string & filename)
{
    std::map<std::string, sf::Image>::iterator it = m_images.find(filename);
	if( it != m_images.end() )
	{
		m_images.erase( it );
	}
}

const sf::Font & CResourceManager::getFont() 
{
	return *m_font;
}

void CResourceManager::setDefaultFont(const char* path)
{
	if( !m_font->loadFromFile(path) )
	{
		gLogger << gLogger.LOG_ERROR << (std::string("Unable to load font. Path: ")+path).c_str();
	}
	else
	{
		gLogger << gLogger.LOG_INFO << (std::string("Font loaded. Path: ")+path).c_str();
	}
}

void CResourceManager::clearResources()
{
    //oczyszczanie mordoru
    while(!this->m_guiElements.empty())
    {
        CGuiElement *pGuiElement= *this->m_guiElements.begin();
        switch(pGuiElement->type)
        {
            case CGuiElement::GUI_BUTTON:
                {
                    CButton *btnToDel=static_cast<CButton *>(pGuiElement);
                    delete btnToDel;
                }
                break;
            default:
                gLogger << gLogger.LOG_ERROR << "Unkown size of memory block, it's impossible to free memory! Be careful, you're leaking memory!";
                break;
        }

        //delete *(this->m_guiElements.begin());
        this->m_guiElements.pop_front();
    }
}

std::list<class CGuiElement*> *CResourceManager::getGuiList()
{
	return &m_guiElements;
}

CButton *CResourceManager::findButton(const char *id)
{
    CButton *ret_val=0;   //return value
    if(id)
    {
        std::string str_id=id;
        for(std::list<CGuiElement *>::iterator i=m_guiElements.begin(); i!=m_guiElements.end(); i++)    //kochany STL :*
        {
            if((*i)->type==CGuiElement::GUI_BUTTON)
            {
                CButton *btn=static_cast<CButton *>(*i);
                if(btn->getID()->compare(str_id)==0)
                {
                    ret_val=btn;
                    break;
                }
            }
        }
    }
    return ret_val;
}

void CResourceManager::loadLevel(int lvl)
{
    char file_path[512];
    ::tinyxml2::XMLDocument xml_level;

    sprintf(file_path, "res/level/%d/resource.xml", lvl);

    clearResources();

    if(xml_level.LoadFile(file_path) == ::tinyxml2::XML_NO_ERROR)
    {
        ::tinyxml2::XMLElement *xml_root=xml_level.FirstChildElement("gui");
        if(xml_root)
        {
            gLogger << gLogger.LOG_INFO << (std::string(file_path)+" Resource root exist!").c_str();

            ::tinyxml2::XMLElement *xml_child=NULL;
            ::tinyxml2::XMLElement *xml_buttons=xml_root->FirstChildElement(BUTTON_SECTION);
            ::tinyxml2::XMLElement *xml_texts=xml_root->FirstChildElement(TEXT_SECTION);
            ::tinyxml2::XMLElement *xml_images=xml_root->FirstChildElement(IMAGE_SECTION);
            if(xml_buttons)
            {
                const char* text_buffer;
                const char* action_buffer;
                const char* id_buffer;
				char *tmp_buffer;
				sf::Uint8 tab_color[4];
                sf::Color normal_color;
                sf::Color hover_color;
                int hide;
                sf::Vector2f *pos = new sf::Vector2f;
                unsigned char_size;
                int n=0;

                xml_child=xml_buttons->FirstChildElement("button");

                while(xml_child)
                {
                    //wartosci domyslne
                    text_buffer=action_buffer=id_buffer=EMPTY;
                    hide=1;
                    char_size=12;
                    pos->x=pos->y=0.0f;
                    normal_color=sf::Color::Red;
                    normal_color=sf::Color::Green;

                    //ladowanie danych
                    if(xml_child->Attribute("id")) id_buffer=xml_child->Attribute("id");
                    if(xml_child->Attribute("text")) text_buffer=xml_child->Attribute("text");
                    if(xml_child->Attribute("action")) action_buffer=xml_child->Attribute("action");
                    if(xml_child->Attribute("normal_color"))
                    { 
						int l=0;
						tmp_buffer = strtok( const_cast<char*>( xml_child->Attribute("normal_color") ), korektor);
						while( tmp_buffer != NULL )
						{
							tab_color[l] = static_cast<sf::Uint8>( strtoul(tmp_buffer, NULL, 10) );
							tmp_buffer = strtok( NULL, korektor);
							l++;
						}
						normal_color.r = tab_color[0];
						normal_color.g = tab_color[1];
						normal_color.b = tab_color[2];
						normal_color.a = tab_color[3];
                    }

                    if(xml_child->Attribute("hover_color"))
                    {
                        //sscanf(xml_child->Attribute("hover_color"), "%hhu%hhu%hhu%huh", &normal_color.r, &normal_color.g, &normal_color.b, &normal_color.a);
						int l=0;
						tmp_buffer = strtok( const_cast<char*>( xml_child->Attribute("hover_color") ), korektor);
						while( tmp_buffer != NULL )
						{
							tab_color[l] = static_cast<sf::Uint8>( strtoul(tmp_buffer, NULL, 10) );
							tmp_buffer = strtok( NULL, korektor);
							l++;
						}
						hover_color.r = tab_color[0];
						hover_color.g = tab_color[1];
						hover_color.b = tab_color[2];
						hover_color.a = tab_color[3];
                    }

                    if(xml_child->Attribute("hidden"))
					{
						xml_child->QueryIntAttribute("hidden", &hide);
					}

                    if(xml_child->Attribute("position"))
                    {
                        tmp_buffer = strtok( const_cast<char*>( xml_child->Attribute("position") ), " ");
						pos->x = static_cast<float>( atof(tmp_buffer) );

						tmp_buffer = strtok( NULL, " ");
						pos->y = static_cast<float>( atof(tmp_buffer) );
						
                    }
                    if(xml_child->Attribute("size")) char_size=xml_child->UnsignedAttribute("size");

                    //printf("%d)BUTTON|%s|%s|%s\n", n, id_buffer, text_buffer, action_buffer);  //DEBUG

                    //wrzuc do pierscien do mordoru
                    this->m_guiElements.push_back((CGuiElement*)(new CButton(CGuiElement::GUI_BUTTON, sf::Vector2f(pos->x, pos->y), char_size, text_buffer, action_buffer, id_buffer, (bool)(hide!=0), normal_color, sf::Color::Yellow)));

                    //bierz nastepny element
                    xml_child=xml_child->NextSiblingElement("button");
                    n++;
                }
                printf("%d buttons parsed!\n", n);  //DEBUG
            }
            if(xml_texts)
            {
                //STATYCZNY TEXT
                //TO DO
            }
            if(xml_images)
            {
                //TEKSTURKI WYKORZYSTANE W POZIOMIE
                //TO DO
            }
        }
        else gLogger << gLogger.LOG_WARNING << file_path << "There's no resource root!";

        char script_path[512];
        sprintf(script_path, "res/level/%d/script.lua", lvl);

        if(!CScreenManager::GetInstance()->GetGame()->loadScript(script_path))
        {
            gLogger << gLogger.LOG_INFO << "Script loaded successfully!";
            CScreenManager::GetInstance()->GetGame()->callScriptFunction("greet_the_world");
        }
        else gLogger << gLogger.LOG_ERROR << "Failed to load script!";
    }
}

void CResourceManager::loadTmxMap(const std::string &pathToMapFile)
{
	boost::property_tree::ptree pt;
	bool _load=true;

	try
	{
		// jak plik nie istnieje to tylko rzuca wyjątkiem bo to void
		boost::property_tree::xml_parser::read_xml(pathToMapFile, pt);
	}
	catch(boost::exception const &)
	{
		_load = false;
		gLogger << gLogger.LOG_ERROR << "Unable to load filemap TmX";
		std::cout<<"File Tmx not found. Map not loaded"<<std::endl;
	}

	if(_load)
	{
		TmxMap* map = new TmxMap();

		// weź atrybut width z elementu map<to bedzie int>, domyślnie daj mu wartość 0
		map->width = pt.get<int>( "map.<xmlattr>.width", 0);
		map->height = pt.get<int>( "map.<xmlattr>.height", 0);
		map->tileWidth = pt.get<int>( "map.<xmlattr>.tilewidth", 0);
		map->tileHeight = pt.get<int>( "map.<xmlattr>.tileheight", 0);
	
		// przejedź sie po wszystkich dzieciach <map> w drzewie/xml
		BOOST_FOREACH( boost::property_tree::ptree::value_type &v, pt.get_child("map") )
		{
			// jak trafiliśmy na <tileset> w rodzicu <map>
			if( v.first == "tileset" )
			{
				TmxMapTileset *tileset = new TmxMapTileset();

				tileset->firstGid = v.second.get<int>("<xmlattr>.firstgid", 0);
				tileset->name = v.second.get<std::string>("<xmlattr>.name", "");
				tileset->tileWidth = v.second.get<int>("<xmlattr>.tilewidth", 0);
				tileset->tileHeight = v.second.get<int>("<xmlattr>.tileheight", 0);
				tileset->spacing = v.second.get<int>("<xmlattr>.spacing",0);
				tileset->margin = v.second.get<int>("<xmlattr>.margin",0);

				// jak czytasz stringa, do domyślny argument też musi byc jako string
				tileset->filename = v.second.get<std::string>("image.<xmlattr>.source", " ");

				tileset->imageHeight = v.second.get<int>("image.<xmlattr>.height", 0);
				tileset->imageWidth = v.second.get<int>("image.<xmlattr>.width", 0);
				tileset->trans = v.second.get<std::string>("image.<xmlattr>.trans", "");

				std::cout << "Tileset " << tileset->name << " filename " << tileset->filename << std::endl;

				map->tilesets.push_back( tileset );
			}
		}
	
		BOOST_FOREACH( boost::property_tree::ptree::value_type &v, pt.get_child("map") ) 
		{
			if( v.first == "layer" )
			{
				TmxMapLayer *layer = new TmxMapLayer();

				layer->name = v.second.get<std::string>("<xmlattr>.name");
				layer->width = v.second.get<int>("<xmlattr>.width");
				layer->height = v.second.get<int>("<xmlattr>.height");

				std::string csv = v.second.get<std::string>("data");

				std::cout << "Layer " << layer->name << " width " << layer->width << " height " << layer->height << std::endl;

				//layer->data = new int[ layer->width * layer->height];

				typedef boost::char_separator <char> sep;
				typedef boost::tokenizer<sep> tk;

				// dzieli string "csv" na wyrazy gdzie separatory masz niżej i zapisuje w tk
				tk tokens(csv, sep("\n,"));

				int index = 0;
				int _row = 0;
				int _col = 1;
				std::vector<int> _tmp;

				// @mam wyjebane na cały doł. Pierdoliłem się z głupim wypisaniem prawie 3h
				// zasraj vektor vektorami
				for(int i=0; i<layer->height; i++)
				{
					layer->data.push_back( std::vector<int>(layer->width) );
				}

				for( tk::iterator i = tokens.begin(); i != tokens.end(); ++i)
				{
					//std::cout<<*i<<" ";
					_col++;
					_tmp.push_back( boost::lexical_cast<int>(*i) );

					if(_col > layer->width)
					{
						//std::cout<<"\n";
						_col=1;
						layer->data[_row] = _tmp;
						_row++;
						_tmp.clear();
					}
					
				}
				
				
				map->layers.push_back( layer );
			}	
		}

		BOOST_FOREACH( boost::property_tree::ptree::value_type &v, pt.get_child("map") ) 
		{
			if ( v.first == "objectgroup" ) 
			{
				TmxMapObjectGroup* group = new TmxMapObjectGroup();
            
				group->name = v.second.get<std::string>("<xmlattr>.name");
				group->width = v.second.get<int>("<xmlattr>.width");
				group->height = v.second.get<int>("<xmlattr>.height");
				group->visable =  v.second.get<bool>("<xmlattr>.visible", 0) ;
            
				//std::cout << "group " << group->name << std::endl;
            
				// przejedź się po wszystkich elementach w <objectgroup>
				BOOST_FOREACH( boost::property_tree::ptree::value_type &o, v.second ) 
				{
					if ( o.first == "object" ) 
					{
						TmxMapObject* object = new TmxMapObject();
                    
						//object->name = o.second.get<std::string>( "<xmlattr>.name" ); // się poprawi jeszcze
						object->x = o.second.get<int>( "<xmlattr>.x" );
						object->y = o.second.get<int>( "<xmlattr>.y" );
						object->width = o.second.get<int>( "<xmlattr>.width" );
						object->height = o.second.get<int>( "<xmlattr>.height" );
                    
						//std::cout << "object " << object->name << " at " << object->x << ", " << object->y << std::endl;
                    
						group->objects.push_back( object );
					}
				} // end boost_foreach
            
				map->objects.push_back( group );
			} // end if objectgroup
		} // end boost_foreach

		this->pTmxMap = map;
	}
}

void CResourceManager::generateTextureMap()
{
	sf::RenderTexture *rendtex = new sf::RenderTexture();
	rendtex->create( pTmxMap->width * pTmxMap->tileWidth, pTmxMap->height * pTmxMap->tileHeight );
	
	sf::IntRect rect,rect2;

	int _gid=0;
	bool loaded=false;
	TmxMapTileset *tilset=0, *ptilset = 0;
	int NUM_COL=0;
	sf::Texture _tex;

	for(int row = 0; row < pTmxMap->height; row++)
	{
		for(int col = 0; col <pTmxMap->width; col++)
		{
			_gid = pTmxMap->layers.front()->data[row][col];

			// jeżeli jest to nieokreślony gid to leć dalej
			if(_gid == 0)
				continue;
			
			// szuka którego tilesetu użyć do aktualnego gida
			tilset = pTmxMap->findTileset(_gid);

			// normalizuje jego pozycje
			_gid-= tilset->firstGid;

			// jeżeli tileset się zmienił podczas ładowania kafelków to go załaduj, a jak nie to nie ładuj w koło tego samego
			if( ptilset != tilset )
				_tex.loadFromImage(getImage( tilset->filename ));

			ptilset = tilset;
			
			// określa ile kafelków mieści się w poziomie na tilsecie
			NUM_COL = tilset->imageWidth / tilset->tileWidth;

			// wybiera pozycje odpowiedniego kafla w tilesecie
			int tileset_col = _gid%NUM_COL;
			int tileset_row = _gid/NUM_COL;

			rect.left =tilset->margin + (tilset->spacing + tilset->tileWidth) * tileset_col;
			rect.top = tilset->margin + (tilset->spacing + tilset->tileHeight) * tileset_row;
			rect.width = tilset->tileWidth;
			rect.height = tilset->tileHeight;
			
			rect2.left = col * tilset->tileWidth;
			rect2.top = row * tilset->tileHeight;
			rect2.width = tilset->tileWidth;
			rect2.height = tilset->tileHeight;


			sf::Sprite sprite(_tex, rect);
			sprite.setPosition((float)rect2.left, (float)rect2.top);

			// narysuj nasz kafelek na texturce mapy
			rendtex->draw(sprite);

		}

	}
	rendtex->display();
	mapSprite = new sf::Sprite( rendtex->getTexture() );
	// tymczasowo przesunięta | JUST 4 DBUG
	mapSprite->move(100.f,50.f);
}