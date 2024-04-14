#ifndef __QT_PAINT_H__
#define __QT_PAINT_H__
#include <vector>

#include "core/QtPoint.h"

/*
 * 提供对外接口，传入离散点，返回光栅化后的像素数组
 */

class QtRender
{
public:
	explicit QtRender();
	~QtRender();

public:
	// DDA 算法
	static void drawDDALine(const QtPoint& p1, const QtPoint& p2, std::vector<QtPoint>& line);
	// 中点画线
	static void drawMidLine(const QtPoint& p1, const QtPoint& p2, std::vector<QtPoint>& line);
	// drawBrensanhamLine 算法
	static void drawBrensanhamLine(const QtPoint& p1, const QtPoint& p2, std::vector<QtPoint>& line);
};

#endif