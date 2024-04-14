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

void QtCanvas::drawPoint(const QtPoint& point)
{
	m_canvasBuffer->setPixel(point.cx(), point.cy(), point.getColor());
}

void QtCanvas::drawLine(const QtPoint& p1, const QtPoint& p2, DrawLineType type)
{
	std::vector<QtPoint> line;
	switch (type)
	{
	case DrawLineType::DLT_DDA:
		QtRender::drawDDALine(p1, p2, line);
		break;
	case DrawLineType::DLT_Mid:
		break;
	case DrawLineType::DLT_Brensanham:
		QtRender::drawBrensanhamLine(p1, p2, line);
		break;
	default:
		break;
	}

	if (line.empty())
	{
		return;
	}

	for (const QtPoint& point : line)
	{
		drawPoint(point);
	}
}
