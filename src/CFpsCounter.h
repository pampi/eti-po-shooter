#ifndef FPS_HPP
#define FPS_HPP

#include "headers.h"

class CFpsCounter
{ 
public:
	CFpsCounter() : m_Frame(0), m_Fps(0) {}

	/// Wywyo�ywane na ko�cu ka�dej klatki
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

	/// Zwraca aktualn� ilo�� FPS
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