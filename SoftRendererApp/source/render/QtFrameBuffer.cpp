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
	int pixelPos = y * m_width + x;
	m_colorBuffer[pixelPos] = color;
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
