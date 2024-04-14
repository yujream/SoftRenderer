#include "core/QtColor.h"

#include <algorithm>

QtColor::QtColor(unsigned color) : m_color(color)
{
	
}

QtColor::QtColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	: m_red(red), m_green(green), m_blue(blue),  m_alpha(alpha)
{
	
}

void QtColor::setColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	m_red = red;
	m_green = green;
	m_blue = blue;
	m_alpha = alpha;
}

void QtColorUtil::InterpolationColor(const QtColor& startColor, const QtColor& endColor, float alpha, QtColor& outColor)
{
	alpha = std::clamp(alpha, 0.f, 1.f);

	// 对 rgba 进行插值
	outColor.m_red = endColor.m_red * alpha + startColor.m_red * (1 - alpha);
	outColor.m_green = endColor.m_green * alpha + startColor.m_green * (1 - alpha);
	outColor.m_blue = endColor.m_blue * alpha + startColor.m_blue * (1 - alpha);
	outColor.m_alpha = endColor.m_alpha * alpha + startColor.m_alpha * (1 - alpha);
}
