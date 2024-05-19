#ifndef __QT_POINT_H__
#define __QT_POINT_H__

#include <array>
#include <vector>

#include "QtColor.h"

class QtPoint
{
public:
	explicit QtPoint(int x = 0, int y = 0, const QtColor& color = 0xff000000);
	~QtPoint();

public:
	void setXY(int x, int y);
	void setX(int x);
	void setY(int y);

	void setColor(const QtColor& color);
	const QtColor& getColor()const;

	int x();
	int y();
	const int cx() const;
	const int cy() const;
	int& rx();
	int& ry();

private:
	std::array<int, 2> m_xy;
	QtColor m_color;
};

using QtPointList = std::vector<QtPoint>;

class QtPointUtil
{
public:
	static void InterpolationPoint(const QtPoint& p1, const QtPoint& p2, float alpha, QtPoint& outPoint);
};

#endif