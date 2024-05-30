#include "render/QtFrameBuffer.h"

#include <algorithm>

QtFrameBuffer::QtFrameBuffer(int width, int height, void* buffer)
	: m_width(width), m_height(height)
{
	m_colorBuffer = new QtColor[width * height]();
}

QtFrameBuffer::~QtFrameBuffer()
{
	if (nullptr != m_colorBuffer)
	{
		delete[] m_colorBuffer;
		m_colorBuffer = nullptr;
	}
}

void QtFrameBuffer::setPixel(int x, int y, const QtColor& color)
{
	if ((x < 0 || x > m_width - 1) || (y < 0 || y > m_height - 1))
	{
		return;
	}

	int pixelPos = y * m_width + x;
	m_colorBuffer[pixelPos] = color;
}

QtColor QtFrameBuffer::getPixel(int x, int y)
{
	if ((x < 0 || x > m_width - 1) || (y < 0 || y > m_height - 1))
	{
		return {};
	}

	int pixelPos = y * m_width + x;
	return m_colorBuffer[pixelPos];
}

void QtFrameBuffer::fill(const QtColor& color)
{
	int size = m_width * m_height;
	std::fill_n(m_colorBuffer, size, color);
}

int QtFrameBuffer::width() const
{
	return m_width;
}

int QtFrameBuffer::height() const
{
	return m_height;
}

QtColor* QtFrameBuffer::buffer() const
{
	return m_colorBuffer;
}
