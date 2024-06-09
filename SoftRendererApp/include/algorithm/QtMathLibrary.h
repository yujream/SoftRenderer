#ifndef __QT_MATH_LIBRARY_H__
#define __QT_MATH_LIBRARY_H__

#include <vector>

#include "core/QtCore.h"

namespace QtMath
{
	const double PI = 3.14159265358979323;
}

class QtMathLibrary
{
public:
	/// <summary>
	/// 角度转弧度
	/// </summary>
	/// <param name="theta"> 角度值 </param>
	/// <returns> 弧度值 </returns>
	static double deg2rad(const double theta);

	/// <summary>
	/// 取小数部分
	/// </summary>
	/// <param name="v"> 浮点数 </param>
	/// <returns></returns>
	static double fraction(double v);

	/// 颜色插值
	/// @param color1 颜色1
	/// @param color2 颜色2
	/// @param alpha 插值
	/// @return 插值后颜色
	static QtColor lerpColor(const QtColor& color1, const QtColor& color2, const float alpha);
};

#endif // !__QT_MATH_LIBRARY_H__
