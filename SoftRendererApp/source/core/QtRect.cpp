#include "core/QtRect.h"

QtRect::QtRect()
	: m_left(0), m_top(0), m_right(0), m_bottom(0)
{

}

QtRect::QtRect(int left, int top, int right, int bottom)
	: m_left(left), m_top(top), m_right(right), m_bottom(bottom)
{
	
}

QtRect::QtRect(const QtPoint& leftTop, int width, int height)
{
	m_left = leftTop.cx();
	m_top = leftTop.cy();
	m_right = m_left + width;
	m_bottom = m_top + height;
}

int& QtRect::rLeft()
{
	return m_left;
}

int& QtRect::rRight()
{
	return m_right;
}

int& QtRect::rTop()
{
	return m_top;
}

int& QtRect::rBottom()
{
	return m_bottom;
}

int QtRect::left()
{
	return m_left;
}

int QtRect::right()
{
	return m_right;
}

int QtRect::top()
{
	return m_top;
}

int QtRect::bottom()
{
	return m_bottom;
}

const int& QtRect::cLeft()
{
	return m_left;
}

const int& QtRect::cRight()
{
	return m_right;
}

const int& QtRect::cTop()
{
	return m_top;
}

const int& QtRect::cBottom()
{
	return m_bottom;
}

QtRect QtRectUtil::boundingBox(const QtPointList& pointList)
{
	QtRect rect(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(),
		std::numeric_limits<int>::min(), std::numeric_limits<int>::min());
	if (pointList.empty())
	{
		return rect;
	}

	for (const QtPoint& point : pointList)
	{
		rect.rLeft() = std::min(rect.cLeft(), point.cx());
		rect.rRight() = std::max(rect.cRight(), point.cx());
		rect.rTop() = std::min(rect.cTop(), point.cy());
		rect.rBottom() = std::max(rect.cBottom(), point.cy());
	}

	return rect;
}
