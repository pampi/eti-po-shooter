#include "headers.h"

const char *BUTTON_SECTION="buttons";
const char *TEXT_SECTION="texts";
const char *IMAGE_SECTION="images";
const char *EMPTY="";

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
    gLogger << CLogger::LOG_ERROR<< std::string("getImage() - Image Not Found: ")+filename;
	return m_images[filename];
}

bool CResourceManager::loadImage(const std::string & filename)
{
	sf::Image _image;
	if( _image.loadFromFile(filename) )
	{
		m_images[filename] = _image;
        gLogger << CLogger::LOG_INFO << std::string("Image loaded. Name: ")+filename;
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
        gLogger << CLogger::LOG_ERROR << std::string("Unable to load font. Path: ")+path;
	}
	else
	{
        gLogger << CLogger::LOG_INFO << std::string("Font loaded. Path: ")+path;
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
                gLogger << CLogger::LOG_ERROR << "Unkown size of memory block, it's impossible to free memory! Be careful, you're leaking memory!";
                break;
        }

        //delete *(this->m_guiElements.begin());
        this->m_guiElements.pop_front();

        if( !gButtonClicked.empty() ) gButtonClicked.clear();
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
    boost::property_tree::ptree drzewko;

    sprintf(file_path, "res/level/%d/resource.xml", lvl);

    clearResources();

    try
        {
            boost::property_tree::xml_parser::read_xml(file_path, drzewko);

            //after catch
            BOOST_FOREACH( boost::property_tree::ptree::value_type &root, drzewko.get_child("gui") )
            {
                if(root.first == "buttons")
                {
                    int n=0;
                    BOOST_FOREACH( boost::property_tree::ptree::value_type &button, root.second)
                    {
                        if(button.first == "button")
                        {
                        n++;
                        std::string text_buffer = button.second.get<std::string>("<xmlattr>.text","");
                        std::string action_buffer = button.second.get<std::string>("<xmlattr>.action", "");
                        std::string id_buffer = button.second.get<std::string>("<xmlattr>.id","");
                        sf::Color hover_color;
                        unsigned int tab_color[4];
                        sf::Color normal_color;
                        sf::Vector2f pos;

                        //Normal Color
                        std::istringstream iss_color(button.second.get<std::string>("<xmlattr>.normal_color","255 0 0 255"));
                        iss_color >> tab_color[0] >> tab_color[1] >> tab_color[2] >> tab_color[3];

                        normal_color.r = tab_color[0]&0xFF;
                        normal_color.g = tab_color[1]&0xFF;
                        normal_color.b = tab_color[2]&0xFF;
                        normal_color.a = tab_color[3]&0xFF;

                        //Hover Color
                        std::istringstream iss_hoverColor(button.second.get<std::string>("<xmlattr>.hover_color","255 255 0 255"));
                        iss_hoverColor >> tab_color[0] >> tab_color[1] >> tab_color[2] >> tab_color[3];

                        hover_color.r = tab_color[0]&0xFF;
                        hover_color.g = tab_color[1]&0xFF;
                        hover_color.b = tab_color[2]&0xFF;
                        hover_color.a = tab_color[3]&0xFF;

                        //hidden?
                        int hide = button.second.get<int>("<xmlattr>.hidden", 0);

                        //font size
                        unsigned char_size = button.second.get<unsigned>("<xmlattr>.size", 12);

                        //Position
                        std::istringstream iss_position(button.second.get<std::string>("<xmlattr>.position","0.0 0.0"));
                        iss_position >> pos.x >> pos.y;

                        this->m_guiElements.push_back((CGuiElement*)(new CButton(CGuiElement::GUI_BUTTON, pos, char_size, text_buffer, action_buffer, id_buffer, (bool)(hide!=0), normal_color, hover_color)));
                        }
                    }
                    printf("%d buttons parsed!\n", n);
                }
                else if(root.first == "texts")
                {
                    //
                }
                else if(root.first == "images")
                {
                    //
                }
            }

            char script_path[512];
            sprintf(script_path, "res/level/%d/script.lua", lvl);

            if(!CScreenManager::GetInstance()->GetGame()->loadScript(script_path))
            {
                gLogger << CLogger::LOG_INFO << std::string("Script ")+script_path+" loaded successfully!";
                CScreenManager::GetInstance()->GetGame()->callScriptFunction("greet_the_world");
            }
            else gLogger << CLogger::LOG_ERROR << std::string("Failed to load ")+script_path+" script!";
        }
        catch(boost::property_tree::xml_parser_error const &e)
        {
            gLogger << CLogger::LOG_ERROR << e.what();
        }
}

void CResourceManager::loadTmxMap(const std::string &pathToMapFile)
{
	if(pTmxMap)
		delete pTmxMap;

	try
	{
		boost::property_tree::ptree pt;

		boost::property_tree::xml_parser::read_xml(pathToMapFile, pt);
	
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
	catch(boost::property_tree::xml_parser_error const &e)
	{
        gLogger << CLogger::LOG_ERROR << e.what();
		std::cout<<"File Tmx not found. Map not loaded"<<std::endl;
	}
}

void CResourceManager::generateTextureMap()
{
	sf::RenderTexture *rendtex = new sf::RenderTexture();
	rendtex->create( pTmxMap->width * pTmxMap->tileWidth, pTmxMap->height * pTmxMap->tileHeight );
	
	sf::IntRect rect,rect2;

	int _gid=0;
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
