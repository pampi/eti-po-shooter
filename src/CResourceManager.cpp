#include "headers.h"

const char *BUTTON_SECTION="buttons";
const char *TEXT_SECTION="texts";
const char *IMAGE_SECTION="images";
const char *EMPTY="";

const char korektor[] = " ,.-";

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
	gLogger << gLogger.LOG_ERROR<< "getImage() - Image Not Found: " << filename.c_str();
	return m_images[filename];
}

bool CResourceManager::loadImage(const std::string & filename)
{
	sf::Image _image;
	if( _image.loadFromFile(filename) )
	{
		m_images[filename] = _image;
		gLogger << gLogger.LOG_INFO << "Image loaded. Name: " << filename.c_str();
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

CResourceManager::CResourceManager() 
{
	m_font = new sf::Font();
	//setDefaultFont();
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
						 //sscanf(xml_child->Attribute("hover_color"), "%hhu%hhu%hhu%hhu", &hover_color.r, &hover_color.g, &hover_color.b, &hover_color.a);
						int l=0;
						tmp_buffer = strtok( const_cast<char*>( xml_child->Attribute("normal_color") ), korektor);
						while( tmp_buffer != NULL )
						{
							tab_color[l] = static_cast<sf::Uint8>( strtoul(tmp_buffer, NULL, 10) );
							//printf("%d ", tab_color[l]); // Debil poprostu DEBIL
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
							//printf("%d ", tab_color[l]); // Debil poprostu DEBIL
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
						hide=xml_child->IntAttribute("hidden");
					}

                    if(xml_child->Attribute("position"))
                    {
                        //sscanf(xml_child->Attribute("position"),"%f%f", &pos.x, &pos.y);
						tmp_buffer = strtok( const_cast<char*>( xml_child->Attribute("position") ), " ");
						pos->x = static_cast<float>( atof(tmp_buffer) );

						tmp_buffer = strtok( NULL, " ");
						pos->y = static_cast<float>( atof(tmp_buffer) );
						
						//printf("%.2f|%.2f ", pos.x, pos.y);
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

void CResourceManager::clearResources()
{
    //oczyszczanie mordoru
    while(!this->m_guiElements.empty())
    {
        delete *(this->m_guiElements.begin());
        this->m_guiElements.pop_front();
    }
}

std::list<class CGuiElement*> *CResourceManager::getGuiList()
{
	return &m_guiElements;
}
