#include "algorithm/QtMathLibrary.h"

QtColor QtMathLibrary::lerpColor(const QtColor& color1, const QtColor& color2, const float alpha)
{
	QtColor color;
	color.m_red = static_cast<unsigned char>(static_cast<float>(color1.m_red) + static_cast<float>(color2.m_red - color1.m_red) * alpha);
	color.m_green = static_cast<unsigned char>(static_cast<float>(color1.m_green) + static_cast<float>(color2.m_green - color1.m_green) * alpha);
	color.m_blue = static_cast<unsigned char>(static_cast<float>(color1.m_blue) + static_cast<float>(color2.m_blue - color1.m_blue) * alpha);
	color.m_alpha = static_cast<unsigned char>(static_cast<float>(color1.m_alpha) + static_cast<float>(color2.m_alpha - color1.m_alpha) * alpha);
	return color;
}
