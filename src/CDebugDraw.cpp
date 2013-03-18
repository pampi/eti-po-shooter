#include "headers.h"

CDebugDraw::CDebugDraw()
{
	m_text.setFont( gResources.getFont() );
	m_text.setCharacterSize(15U);
	m_string="";
	m_stringB="";
	m_stream.clear();
}

void CDebugDraw::draw(sf::RenderTarget & target)
{
	m_text.setString( m_stringB );
	m_text.setPosition(0,0 );
	target.draw(m_text);

	m_string = m_stream.str();
	m_text.setString( m_string );
	m_text.setPosition(0, 100);
	target.draw(m_text);

	m_stringB.clear();
}

void CDebugDraw::add(const int value, const char *comment)
{
	std::ostringstream tmp;
	tmp << comment << value << '\n';
	m_stringB += tmp.str();
}

void CDebugDraw::add(const float value, const char *comment)
{
	std::ostringstream tmp;
	tmp << comment << value << '\n';
	m_stringB += tmp.str();
}

void CDebugDraw::add(const char* value, const char *comment)
{
	std::ostringstream tmp;
	tmp << comment << value << '\n';
	m_stringB += tmp.str();
}