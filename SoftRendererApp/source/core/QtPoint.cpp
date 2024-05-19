#include "core/QtPoint.h"

#include <algorithm>

QtPoint::QtPoint(int x, int y, const QtColor& color)
{
	m_xy[0] = x;
	m_xy[1] = y;
	m_color = color;
}

QtPoint::~QtPoint()
{

}

void QtPoint::setXY(int x, int y)
{
	m_xy[0] = x;
	m_xy[1] = y;
}

void QtPoint::setX(int x)
{
	m_xy[0] = x;
}

void QtPoint::setY(int y)
{
	m_xy[1] = y;
}

void QtPoint::setColor(const QtColor& color)
{
	m_color = color;
}

const QtColor& QtPoint::getColor() const
{
	return m_color;
}

int QtPoint::x()
{
	return m_xy[0];
}

int QtPoint::y()
{
	return m_xy[1];
}

const int QtPoint::cx() const
{
	return m_xy[0];
}

const int QtPoint::cy() const
{
	return m_xy[1];
}

int& QtPoint::rx()
{
	return m_xy[0];
}

int& QtPoint::ry()
{
	return m_xy[1];
}

void QtPointUtil::InterpolationPoint(const QtPoint& p1, const QtPoint& p2, float alpha, QtPoint& outPoint)
{
	alpha = std::clamp(alpha, 0.f, 1.f);
	outPoint.setX(p2.cx() * alpha + p1.cx() * (1 - alpha));
	outPoint.setY(p2.cy() * alpha + p1.cy() * (1 - alpha));

	QtColor alphaColor;
	QtColorUtil::InterpolationColor(p1.getColor(), p2.getColor(), alpha, alphaColor);
	outPoint.setColor(alphaColor);
}
