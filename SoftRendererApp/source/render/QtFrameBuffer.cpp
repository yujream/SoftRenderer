#include "render/QtFrameBuffer.h"

#include <algorithm>

QtFrameBuffer::QtFrameBuffer(unsigned width, unsigned height, void* buffer)
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

void QtFrameBuffer::setPixel(unsigned x, unsigned y, const QtColor& color)
{
	unsigned pixelPos = y * m_width + x;
	m_colorBuffer[pixelPos] = color;
}

void QtFrameBuffer::fill(const QtColor& color)
{
	unsigned size = m_width * m_height;
	std::fill_n(m_colorBuffer, size, color);
}

unsigned QtFrameBuffer::width() const
{
	return m_width;
}

unsigned QtFrameBuffer::height() const
{
	return m_height;
}

QtColor* QtFrameBuffer::buffer() const
{
	return m_colorBuffer;
}
