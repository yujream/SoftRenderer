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

	void setUV(float u, float v);
	void setU(float u);
	void setV(float v);

	void setColor(const QtColor& color);
	const QtColor& getColor()const;

	void setAlpha(const unsigned char alpha);

	int x();
	int y();
	const int cx() const;
	const int cy() const;
	int& rx();
	int& ry();

	float u();
	float v();
	const float cu() const;
	const float cv() const;
	float& ru();
	float& rv();

private:
	std::array<int, 2> m_xy;
	std::array<float, 2> m_uv;
	QtColor m_color;
};

using QtPointList = std::vector<QtPoint>;

class QtPointUtil
{
public:
	static void InterpolationPoint(const QtPoint& p1, const QtPoint& p2, float alpha, QtPoint& outPoint);
};

#endif