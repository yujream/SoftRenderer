#include "core/QtImage.h"
#include "core/QtColor.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

QtImage::QtImage(int width, int height, int channels, QtColor* data)
	: m_width(width), m_height(height), m_channels(channels)
{
	m_data = new QtColor[width * height]();
	if (nullptr != data)
	{
		memcpy(m_data, data, width * height * sizeof(QtColor));
	}
}

QtImage::~QtImage()
{
	if (nullptr != m_data)
	{
		delete m_data;
		m_data = nullptr;
	}
}

QtColor* QtImage::data() const
{
	return m_data;
}

int QtImage::width() const
{
	return m_width;
}

int QtImage::height() const
{
	return m_height;
}

QtColor QtImage::pixel(int x, int y) const
{
	return m_data[y * m_width + x];
}


QtImage* QtImageUtils::createImage(const char* path)
{
	int width = 0;
	int height = 0;
	int channels = 0;
	unsigned char* data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);

	return new QtImage(width, height, channels, reinterpret_cast<QtColor*>(data));
}
