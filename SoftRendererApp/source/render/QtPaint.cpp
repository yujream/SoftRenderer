#include "render/QtPaint.h"

QtPaint::QtPaint()
	: m_drawColor(0x000000ff)
{
	
}

void QtPaint::setColor(const QtColor& color)
{
	m_drawColor = color;
}

QtColor QtPaint::getColor()
{
	return m_drawColor;
}
