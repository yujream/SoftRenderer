#include "algorithm/QtMathLibrary.h"

double QtMathLibrary::deg2rad(const double theta)
{
	return 0.01745329251994329 * theta;
}

double QtMathLibrary::fraction(double v)
{
	return v - static_cast<int>(v);
}

QtColor QtMathLibrary::lerpColor(const QtColor& color1, const QtColor& color2, const float alpha)
{
	QtColor color;
	color.m_red = static_cast<unsigned char>(static_cast<float>(color2.m_red) * alpha + static_cast<float>(color1.m_red) * (1 - alpha));
	color.m_green = static_cast<unsigned char>(static_cast<float>(color2.m_green) * alpha + static_cast<float>(color1.m_green) * (1 - alpha));
	color.m_blue = static_cast<unsigned char>(static_cast<float>(color2.m_blue) * alpha + static_cast<float>(color1.m_blue) * (1 - alpha));
	color.m_alpha = static_cast<unsigned char>(static_cast<float>(color2.m_alpha) * alpha + static_cast<float>(color1.m_alpha) * (1 - alpha));
	return color;
}
