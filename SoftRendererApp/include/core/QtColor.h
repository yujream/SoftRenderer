#ifndef __QT_COLOR_H__
#define __QT_COLOR_H__

namespace HexColor
{
	constexpr unsigned red = 0xff0000ff;
	constexpr unsigned green = 0x00ff00ff;
	constexpr unsigned blue = 0x0000ffff;
}

union QtColor
{
	QtColor(unsigned int color = 0);

	QtColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);

	void setColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);

	struct
	{
		unsigned char m_red;
		unsigned char m_green;
		unsigned char m_blue;
		unsigned char m_alpha;
	};

	unsigned int m_color : 32;
};

#endif