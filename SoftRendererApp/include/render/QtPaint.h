#ifndef __QT_PAINT_H__
#define __QT_PAINT_H__

#include "core/QtColor.h"

class QtPaint
{
public:
	explicit QtPaint();

public:
	void setColor(const QtColor& color);
	QtColor getColor();

private:
	QtColor m_drawColor;
};

#endif