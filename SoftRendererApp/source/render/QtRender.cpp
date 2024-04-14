#include "render/QtRender.h"
#include <cmath>

float getInterpolation(const QtPoint& startPoint, const QtPoint& interpPoint, const QtPoint& endPoint)
{
	float alpha = 1.f;
	if (startPoint.cy() == endPoint.cy())
	{
		int molecule = interpPoint.cx() - startPoint.cx();
		int denominator = endPoint.cx() - startPoint.cx();
		alpha = std::abs(molecule * 1.0f) / std::abs(denominator * 1.0f);
	}
	else
	{
		int molecule = interpPoint.cy() - startPoint.cy();
		int denominator = endPoint.cy() - startPoint.cy();
		alpha = std::abs(molecule * 1.0f) / std::abs(denominator * 1.0f);
	}
	return alpha;
}

QtRender::QtRender()
{
	
}

QtRender::~QtRender()
{
}

void QtRender::drawDDALine(const QtPoint& p1, const QtPoint& p2, std::vector<QtPoint>& line)
{
	int dx = p2.cx() - p1.cx();
	int dy = p2.cy() - p1.cy();

	// 根据增量大小取沿轴方向
	int step = std::max(std::abs(dx), std::abs(dy));

	float xIncreased = dx * 1.0f / step;
	float yIncreased = dy * 1.0f / step;

	float x = static_cast<float>(p1.cx());
	float y = static_cast<float>(p1.cy());
	for (int i(0); i < step; i++)
	{
		float alpha = getInterpolation(p1, QtPoint(std::lround(x), std::lround(y)), p2);
		QtColor alphaColor;
		QtColorUtil::InterpolationColor(p1.getColor(), p2.getColor(), alpha, alphaColor);

		QtPoint point(std::lround(x), std::lround(y), alphaColor);
		line.emplace_back(point);

		x += xIncreased;
		y += yIncreased;
	}
}

void QtRender::drawMidLine(const QtPoint& p1, const QtPoint& p2, std::vector<QtPoint>& line)
{
}

void QtRender::drawBrensanhamLine(const QtPoint& p1, const QtPoint& p2, std::vector<QtPoint>& line)
{
	int dx = p2.cx() - p1.cx();                // x偏移量
	int dy = p2.cy() - p1.cy();                // y偏移量
	int ux = (p2.cx() - p1.cx() > 0) ? 1 : -1;                // x伸展方向
	int uy = (p2.cy() - p1.cy() > 0) ? 1 : -1;                // y伸展方向

	dx = abs(dx);
	dy = abs(dy);

	int dx2 = dx << 1;   // x偏移量乘2
	int dy2 = dy << 1;   // y偏移量乘2


	int x = p1.cx();  // 起点x坐标
	int y = p1.cy();  // 起点y坐标

	int t = (dx > dy) ? -dx : -dy;

	if (dx > dy)
	{
		// 以 x 为增量方向计算
		// e = -0.5
	    // 令 t = 2 * dx * e，等式两边同乘 2 * dx
	    // 2 * dx * e = 2 * dx * -0.5 = -dx
	    // 即 t = -dx;
		int t = -dx; 

		for (x = p1.cx(); x != p2.cx(); x += ux)
		{
			float alpha = getInterpolation(p1, QtPoint(x, y), p2);
			QtColor alphaColor;
			QtColorUtil::InterpolationColor(p1.getColor(), p2.getColor(), alpha, alphaColor);

			QtPoint point(x, y, alphaColor);
			line.emplace_back(point);

			// e = e + k, k = dy / dx
		    // 令 t = 2 * dx * e，等式两边同乘 2 * dx
		    // 2 * dx * e = 2 * dx * (e + dy / dx) = 2 * dx * e + 2 * dy
		    // t = t + 2 * dy;
			t = t + dy2; 
			if (t > 0)   
			{
				// e是整数且大于0时表示要取右上的点（否则是右下的点）
				// e = e - 1，将 e 维护在 [0,1] 区间
			    // 令 t = 2 * e * dx，等式两边同乘 2 * dx
			    // 2 * dx * e = 2 * dx * (e - 1) = 2 * dx * e - 2 * dx
			    // t = t - 2dx;
				y += uy;
				t = t - dx2;
			}
		}
	}
	else
	{
		// 以 y 为增量方向计算
		// e = -0.5
		// 令 t = 2 * dy * e，等式两边同乘 2 * dy
		// 2 * dy * e = 2 * dy * -0.5 = -dy
		// 即 t = -dy;
		int t = -dy;        
		for (y = p1.cy(); y != p2.cy(); y += uy)
		{
			float alpha = getInterpolation(p1, QtPoint(x, y), p2);
			QtColor alphaColor;
			QtColorUtil::InterpolationColor(p1.getColor(), p2.getColor(), alpha, alphaColor);

			QtPoint point(x, y, alphaColor);
			line.emplace_back(point);

			// e = e + 1/k, k = dx / dy
			// 令 t = 2 * dy * e，等式两边同乘 2 * dy
			// 2 * dy * e = 2 * dy * (e + dx / dy) = 2 * dy * e + 2 * dx
			// t = t + 2 * dx;
			t = t + dx2;    
			if (t > 0)     
			{
				// e是整数且大于0时表示要取右上的点（否则是右下的点）
				// e = e - 1，将 e 维护在 [0,1] 区间
				// 令 t = 2 * e * dy，等式两边同乘 2 * dy
				// 2 * dy * e = 2 * dy * (e - 1) = 2 * dy * e - 2 * dy
				// t = t - 2dy;
				x += ux;
				t = t - dy2;
			}
		}
	}
}

