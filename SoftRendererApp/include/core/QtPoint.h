#ifndef __QT_POINT_H__
#define __QT_POINT_H__

#include <array>

#include "QtColor.h"

class QtPoint
{
public:
	explicit QtPoint(unsigned x = 0, unsigned y = 0, const QtColor& color = 0xff000000);
	~QtPoint();

public:
	void setXY(unsigned x, unsigned y);
	void setX(unsigned x);
	void setY(unsigned y);

	void setColor(const QtColor& color);
	const QtColor& getColor()const;

	unsigned x();
	unsigned y();
	const unsigned cx() const;
	const unsigned cy() const;
	unsigned& rx();
	unsigned& ry();

private:
	std::array<unsigned, 2> m_xy;
	QtColor m_color;
};

class QtPointUtil
{
public:
	static void InterpolationPoint(const QtPoint& p1, const QtPoint& p2, float alpha, QtPoint& outPoint);
};

#endif