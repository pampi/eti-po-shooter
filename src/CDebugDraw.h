#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include "headers.h"

#ifndef gDDraw
#define gDDraw CDebugDraw::GetReference()
#endif

class CDebugDraw: public TSingleton<CDebugDraw>
{
private:
	std::ostringstream m_stream;
	sf::Text m_text;
	std::string m_string, m_stringB;

public:
	CDebugDraw();

	void draw(sf::RenderTarget & target);

	friend CDebugDraw& operator<<(CDebugDraw &drawer, const int value)
	{
		drawer.m_stream << value << '\n';
		return drawer;
	}

	friend CDebugDraw& operator<<(CDebugDraw &drawer, const float value)
	{
		drawer.m_stream << value << '\n';
		return drawer;
	}

	friend CDebugDraw& operator<<(CDebugDraw &drawer, const char* value)
	{
		drawer.m_stream << value << '\n';
		return drawer;
	}

	void add(const int value, const char *comment = "");
	void add(const float value, const char *comment = "");
	void add(const char* value, const char *comment = "");

};
#endif
