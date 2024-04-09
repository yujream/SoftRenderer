#include "render/QtCanvas.h"
#include <QDebug>

QtCanvas::QtCanvas(QObject* parent)
	: QObject(parent)
{
}

QtCanvas::~QtCanvas()
{

}

bool QtCanvas::newCanvas(unsigned width, unsigned height)
{
	m_canvasBuffer = new QtFrameBuffer(width, height);
	if (nullptr == m_canvasBuffer)
	{
		return false;
	}

	return true;
}

void* QtCanvas::getCanvas() const
{
	return m_canvasBuffer->buffer();
}

void QtCanvas::clear()
{
	m_canvasBuffer->fill(0xff000000);
}

void QtCanvas::drawPoint(unsigned x, unsigned y, const QtColor& color)
{
	m_canvasBuffer->setPixel(x, y, color);
}
