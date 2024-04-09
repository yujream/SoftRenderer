#ifndef __QT_MATH_LIBRARY_H__
#define __QT_MATH_LIBRARY_H__

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
};

#endif // !__QT_MATH_LIBRARY_H__
