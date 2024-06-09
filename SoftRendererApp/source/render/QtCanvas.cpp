#include "render/QtCanvas.h"
#include <QDebug>

#include "algorithm/QtMathLibrary.h"
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
			const QtColor& color = m_enableBilinearity ? sampleBilinearity(point.cu(), point.cv()) : sampleTexture(point.cu(), point.cv());
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

void QtCanvas::setBilinearityEnabled(bool enable)
{
	m_enableBilinearity = enable;
}

bool QtCanvas::blendingEnable() const
{
	return m_enableBlending;
}

bool QtCanvas::bilinearity() const
{
	return m_enableBilinearity;
}

void QtCanvas::setTexture(QtImage* texture)
{
	m_texture = texture;
}

QtColor QtCanvas::sampleTexture(float u, float v)
{
	if (nullptr == m_texture)
	{
		return {};
	}
	int x = static_cast<int>(std::round(static_cast<float>(m_texture->width() - 1) * u));
	int y = static_cast<int>(std::round(static_cast<float>(m_texture->height() - 1) * v));
	return m_texture->pixel(x, y);
}

QtColor QtCanvas::sampleBilinearity(float u, float v)
{
	if (nullptr == m_texture)
	{
		return {};
	}

	float x = u * static_cast<float>(m_texture->width() - 1);
	float y = v * static_cast<float>(m_texture->height() - 1);

	/*
	 *              |
	 *  left top    |  right top
	 *	———————————————————————————
	 *              |
	 *	left bottom |  right bottom
	 *              |
	 */
	int left = std::floor(x);
	int right = std::ceil(x);
	int top = std::floor(y);
	int bottom = std::ceil(y);

	// 获取四个位置的像素坐标
	QtColor leftTopPos = m_texture->pixel(left, top);
	QtColor leftBottomPos = m_texture->pixel(left, bottom);
	QtColor rightTopPos = m_texture->pixel(right, top);
	QtColor rightBottomPos = m_texture->pixel(right, bottom);

	// 第一次插值
	float yScale = (top == bottom) ? 1.f : (y - static_cast<float>(top)) / static_cast<float>(bottom - top);

	QtColor leftColor = QtMathLibrary::lerpColor(leftTopPos, leftBottomPos, yScale);
	QtColor rightColor = QtMathLibrary::lerpColor(rightTopPos, rightBottomPos, yScale);

	// 第二次插值
	float xScale = (left == right) ? 1.f : (x - static_cast<float>(left)) / static_cast<float>(right - left);
	return QtMathLibrary::lerpColor(leftColor, rightColor, xScale);
}
