#ifndef __QT_MATH_LIBRARY_H__
#define __QT_MATH_LIBRARY_H__

#include "core/QtCore.h"

union QtColor;

namespace QtMath
{
	const double PI = 3.14159265358979323;
}

class QtMathLibrary
{
public:
	/// 颜色插值
	/// @param color1 颜色1
	/// @param color2 颜色2
	/// @param alpha 插值
	/// @return 插值后颜色
	static QtColor lerpColor(const QtColor& color1, const QtColor& color2, const float alpha);
};

#endif // !__QT_MATH_LIBRARY_H__
