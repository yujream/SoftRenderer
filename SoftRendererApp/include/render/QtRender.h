#ifndef __QT_PAINT_H__
#define __QT_PAINT_H__
#include <vector>

#include "core/QtCore.h"

/*
 * 提供对外接口，传入离散点，返回光栅化后的像素数组
 */

class QtRender
{
public:
	explicit QtRender() = default;
	~QtRender() = default;

public:
	// DDA 算法
	static void rasterlizedDDALine(const QtPoint& p1, const QtPoint& p2, std::vector<QtPoint>& line);
	// 中点画线
	static void rasterlizedMidLine(const QtPoint& p1, const QtPoint& p2, std::vector<QtPoint>& line);
	// rasterlizedBrensanhamLine 算法
	static void rasterlizedBrensanhamLine(const QtPoint& p1, const QtPoint& p2, std::vector<QtPoint>& line);

	// 三角形光栅化
	static void rasterlizedTriangle(const QtPoint& p1, const QtPoint& p2, const QtPoint& p3, std::vector<QtPoint>& triangle);

	// 图片光栅化
	static void rasterlizedImage(const char* path, std::vector<QtPoint>& pixels);
};

#endif