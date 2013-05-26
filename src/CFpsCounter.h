#ifndef FPS_HPP
#define FPS_HPP

#include "headers.h"

#ifndef gFPS
#define gFPS CFpsCounter::GetReference()
#endif

class CFpsCounter: public TSingleton<CFpsCounter>
{ 
public:
	CFpsCounter() : m_Frame(0), m_Fps(0) {}

	/// Wywyoływane na końcu każdej klatki
	void update()
	{
		if(m_Clock.getElapsedTime().asSeconds() >= 1.f)
		{
			m_Fps = m_Frame;
			m_Frame = 0;
			m_Clock.restart();
		}
 
		++m_Frame;
	}

	/// Zwraca aktualną ilość FPS
	const unsigned int getFPS() const 
	{ 
		return m_Fps; 
	}

private:
	unsigned int m_Frame;
	unsigned int m_Fps;
	sf::Clock m_Clock;
};
#endif // FPS_HPP
