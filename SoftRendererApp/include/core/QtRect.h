#ifndef __QT_RECT_H__
#define __QT_RECT_H__

#include "QtPoint.h"

/*
 *  矩形类
 */

class QtRect
{
public:
	QtRect();
	QtRect(int left, int top, int right, int bottom);
	QtRect(const QtPoint& leftTop, int width, int height);

	int& rLeft();
	int& rRight();
	int& rTop();
	int& rBottom();

	int left();
	int right();
	int top();
	int bottom();

	const int& cLeft();
	const int& cRight();
	const int& cTop();
	const int& cBottom();

private:
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;
};

class QtRectUtil
{
public:
	static QtRect boundingBox(const QtPointList& pointList);
};

#endif