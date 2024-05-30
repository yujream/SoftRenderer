#include "render/QtCanvas.h"
#include <QDebug>

#include "core/QtImage.h"

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
	m_canvasBuffer->fill(0x00000000);
}

void QtCanvas::drawPoint(const QtPoint& point)
{
	QtColor dstColor = point.getColor();
	if (m_enableBlending)
	{
		// 颜色混合
		QtColor srcColor = m_canvasBuffer->getPixel(point.cx(), point.cy());

		float weight = static_cast<float>(srcColor.m_alpha) / 255.f;
		dstColor.m_red = static_cast<unsigned char>(static_cast<float>(srcColor.m_red) * weight + static_cast<float>(dstColor.m_red) * (1.f - weight));
		dstColor.m_green = static_cast<unsigned char>(static_cast<float>(srcColor.m_green) * weight + static_cast<float>(dstColor.m_green) * (1.f - weight));
		dstColor.m_blue = static_cast<unsigned char>(static_cast<float>(srcColor.m_blue) * weight + static_cast<float>(dstColor.m_blue) * (1.f - weight));
		dstColor.m_alpha = static_cast<unsigned char>(static_cast<float>(srcColor.m_alpha) * weight + static_cast<float>(dstColor.m_alpha) * (1.f - weight));
	}
	m_canvasBuffer->setPixel(point.cx(), point.cy(), dstColor);
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

	if (nullptr != m_texture)
	{
		for (QtPoint& point : triangle)
		{
			const QtColor& color = sampleTexture(point.cu(), point.cv());
			point.setColor(color);
			drawPoint(point);
		}
	}
	else
	{
		for (const QtPoint& point : triangle)
		{
			drawPoint(point);
		}
	}
}

void QtCanvas::drawImage(const char* path, int x, int y)
{
	std::vector<QtPoint> pixels;
	QtRender::rasterlizedImage(path, pixels);

	for (QtPoint& point : pixels)
	{
		point.setXY(point.cx() + x, point.cy() + y);
		drawPoint(point);
	}
}

void QtCanvas::drawImageWithAlpha(const char* path, int x, int y, unsigned char alpha)
{
	std::vector<QtPoint> pixels;
	QtRender::rasterlizedImage(path, pixels);

	for (QtPoint& point : pixels)
	{
		point.setXY(point.cx() + x, point.cy() + y);
		point.setAlpha(alpha);
		drawPoint(point);
	}
}

void QtCanvas::setBlendingEnabled(bool enable)
{
	m_enableBlending = enable;
}

bool QtCanvas::blendingEnable() const
{
	return m_enableBlending;
}

void QtCanvas::setTexture(QtImage* texture)
{
	m_texture = texture;
}

QtColor QtCanvas::sampleTexture(float u, float v)
{
	int x = static_cast<int>(std::round(static_cast<float>(m_texture->width() - 1) * u));
	int y = static_cast<int>(std::round(static_cast<float>(m_texture->height() - 1) * v));
	return m_texture->pixel(x, y);
}
