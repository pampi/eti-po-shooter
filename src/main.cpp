#include "headers.h"

CLogger gLogger;
//CSettingsParser gSettings;

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	CSettingsParser settings("settings.txt");
	
	int width=0, height=0;
	//settings.Get("width", &width);
	//settings.Get("height", &height);
	float kupa=0;
	//settings.Get("g", &kupa);
	std::string player="N";
	settings.Get("player", &player);
	bool lol=false;
	//settings.Get("use30hz", &lol);
	std::cout<<width <<" "<< height <<" "<< kupa <<" "<< player <<" "<< lol;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

	return 0;
}