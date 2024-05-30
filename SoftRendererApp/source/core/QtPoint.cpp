#include "core/QtPoint.h"

#include <algorithm>

QtPoint::QtPoint(int x, int y, const QtColor& color)
{
	m_xy[0] = x;
	m_xy[1] = y;
	m_color = color;

	m_uv.fill(0);
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

void QtPoint::setUV(float u, float v)
{
	m_uv[0] = u;
	m_uv[1] = v;
}

void QtPoint::setU(float u)
{
	m_uv[0] = u;
}

void QtPoint::setV(float v)
{
	m_uv[1] = v;
}

void QtPoint::setColor(const QtColor& color)
{
	m_color = color;
}

const QtColor& QtPoint::getColor() const
{
	return m_color;
}

void QtPoint::setAlpha(const unsigned char alpha)
{
	m_color.m_alpha = alpha;
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

float QtPoint::u()
{
	return m_uv[0];
}

float QtPoint::v()
{
	return m_uv[1];
}

const float QtPoint::cu() const
{
	return m_uv[0];
}

const float QtPoint::cv() const
{
	return m_uv[1];
}

float& QtPoint::ru()
{
	return m_uv[0];
}

float& QtPoint::rv()
{
	return m_uv[1];
}

void QtPointUtil::InterpolationPoint(const QtPoint& p1, const QtPoint& p2, float alpha, QtPoint& outPoint)
{
	alpha = std::clamp(alpha, 0.f, 1.f);
	outPoint.setX(p2.cx() * alpha + p1.cx() * (1 - alpha));
	outPoint.setY(p2.cy() * alpha + p1.cy() * (1 - alpha));

	QtColor alphaColor;
	QtColorUtil::interpolationColor(p1.getColor(), p2.getColor(), alpha, alphaColor);
	outPoint.setColor(alphaColor);
}
