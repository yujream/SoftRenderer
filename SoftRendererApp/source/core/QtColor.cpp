#include "core/QtColor.h"

QtColor::QtColor(unsigned color) : m_color(color)
{
	
}

QtColor::QtColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	: m_red(red), m_green(green), m_blue(blue),  m_alpha(alpha)
{
	
}

void QtColor::setColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	m_red = red;
	m_green = green;
	m_blue = blue;
	m_alpha = alpha;
}
