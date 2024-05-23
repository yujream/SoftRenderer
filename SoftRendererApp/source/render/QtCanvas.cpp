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
		QtRender::rasterlizedDDALine(p1, p2, line);
		break;
	case DrawLineType::DLT_Mid:
		QtRender::rasterlizedMidLine(p1, p2, line);
		break;
	case DrawLineType::DLT_Brensanham:
		QtRender::rasterlizedBrensanhamLine(p1, p2, line);
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

void QtCanvas::drawTriangle(const QtPoint& p1, const QtPoint& p2, const QtPoint& p3)
{
	std::vector<QtPoint> triangle;
	QtRender::rasterlizedTriangle(p1, p2, p3, triangle);

	for (const QtPoint& point : triangle)
	{
		drawPoint(point);
	}
}

void QtCanvas::drawImage(const char* path)
{
	std::vector<QtPoint> pixels;
	QtRender::rasterlizedImage(path, pixels);

	for (const QtPoint& point : pixels)
	{
		drawPoint(point);
	}
}
