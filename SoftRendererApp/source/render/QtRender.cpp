#include "render/QtRender.h"
#include "Eigen/Eigen"
#include <cmath>

#include "algorithm/QtMathLibrary.h"
#include "core/QtImage.h"
#include "MathHeader.h"

// 获取插值
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

void InterpolationTriangle(const QtPoint& pa, const QtPoint& pb, const QtPoint& pc, QtPoint& p)
{
	Eigen::Vector3i AB(pb.cx() - pa.cx(), pb.cy() - pa.cy(), 0);
	Eigen::Vector3i AC(pc.cx() - pa.cx(), pc.cy() - pa.cy(), 0);
	const float abcArea = static_cast<float>(AB.cross(AC).z());

	Eigen::Vector3i PA(pa.cx() - p.cx(), pa.cy() - p.cy(), 0);
	Eigen::Vector3i PB(pb.cx() - p.cx(), pb.cy() - p.cy(), 0);
	Eigen::Vector3i PC(pc.cx() - p.cx(), pc.cy() - p.cy(), 0);
	const float bpcArea = static_cast<float>(PB.cross(PC).z());
	const float apcArea = static_cast<float>(PC.cross(PA).z());
	const float apbArea = static_cast<float>(PA.cross(PB).z());

	const float alpha = bpcArea / abcArea;
	const float beta = apcArea / abcArea;
	const float gamma = apbArea / abcArea;

	const QtColor& ca = pa.getColor();
	const QtColor& cb = pb.getColor();
	const QtColor& cc = pc.getColor();

	p.setColor(QtColor(	
		static_cast<unsigned char>(alpha * static_cast<float>(ca.m_red) + beta * static_cast<float>(cb.m_red) + gamma * static_cast<float>(cc.m_red)),
		static_cast<unsigned char>(alpha * static_cast<float>(ca.m_green) + beta * static_cast<float>(cb.m_green) + gamma * static_cast<float>(cc.m_green)),
		static_cast<unsigned char>(alpha * static_cast<float>(ca.m_blue) + beta * static_cast<float>(cb.m_blue) + gamma * static_cast<float>(cc.m_blue)),
		static_cast<unsigned char>(alpha * static_cast<float>(ca.m_alpha) + beta * static_cast<float>(cb.m_alpha) + gamma * static_cast<float>(cc.m_alpha))
	));

	// uv插值
	p.setU(alpha * pa.cu() + beta * pb.cu() + gamma * pc.cu());
	p.setV(alpha * pa.cv() + beta * pb.cv() + gamma * pc.cv());
}

void QtRender::rasterlizedDDALine(const QtPoint& p1, const QtPoint& p2, std::vector<QtPoint>& line)
{
	line.clear();

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
		QtColor alphaColor = QtMathLibrary::lerpColor(p1.getColor(), p2.getColor(), alpha);

		QtPoint point(std::lround(x), std::lround(y), alphaColor);
		line.emplace_back(point);

		x += xIncreased;
		y += yIncreased;
	}
}

void QtRender::rasterlizedMidLine(const QtPoint& p1, const QtPoint& p2, std::vector<QtPoint>& line)
{
	line.clear();

	int x0 = p1.cx();
	int x1 = p2.cx();
	int y0 = p1.cy();
	int y1 = p2.cy();
	int a, b, d1, d2, d, x, y; float m;
	if (x1 < x0) { d = x0, x0 = x1, x1 = d; d = y0, y0 = y1, y1 = d; }
	a = y0 - y1, b = x1 - x0;
	if (b == 0) m = -1 * a * 100;
	else m = (float)a / (x0 - x1); x = x0, y = y0;
	float alpha = getInterpolation(p1, QtPoint(x, y), p2);
	QtColor alphaColor = QtMathLibrary::lerpColor(p1.getColor(), p2.getColor(), alpha);

	QtPoint point(x, y, alphaColor);
	line.emplace_back(point);
	if (m >= 0 && m <= 1)
	{
		d = 2 * a + b; d1 = 2 * a, d2 = 2 * (a + b);
		while (x < x1)
		{
			if (d <= 0) { x++, y++, d += d2; }
			else { x++, d += d1; }
			float alpha = getInterpolation(p1, QtPoint(x, y), p2);
			QtColor alphaColor = QtMathLibrary::lerpColor(p1.getColor(), p2.getColor(), alpha);

			QtPoint point(x, y, alphaColor);
			line.emplace_back(point);
		}
	}
	else if (m <= 0 && m >= -1)
	{
		d = 2 * a - b; d1 = 2 * a - 2 * b, d2 = 2 * a;
		while (x < x1)
		{
			if (d > 0) { x++, y--, d += d1; }
			else { x++, d += d2; }
			float alpha = getInterpolation(p1, QtPoint(x, y), p2);
			QtColor alphaColor = QtMathLibrary::lerpColor(p1.getColor(), p2.getColor(), alpha);

			QtPoint point(x, y, alphaColor);
			line.emplace_back(point);
		}
	}
	else if (m > 1)
	{
		d = a + 2 * b; d1 = 2 * (a + b), d2 = 2 * b;
		while (y < y1)
		{
			if (d > 0) { x++, y++, d += d1; }
			else { y++, d += d2; }
			float alpha = getInterpolation(p1, QtPoint(x, y), p2);
			QtColor alphaColor = QtMathLibrary::lerpColor(p1.getColor(), p2.getColor(), alpha);

			QtPoint point(x, y, alphaColor);
			line.emplace_back(point);
		}
	}
	else
	{
		d = a - 2 * b; d1 = -2 * b, d2 = 2 * (a - b);
		while (y > y1)
		{
			if (d <= 0) { x++, y--, d += d2; }
			else { y--, d += d1; }
			float alpha = getInterpolation(p1, QtPoint(x, y), p2);
			QtColor alphaColor = QtMathLibrary::lerpColor(p1.getColor(), p2.getColor(), alpha);

			QtPoint point(x, y, alphaColor);
			line.emplace_back(point);
		}
	}
}

void QtRender::rasterlizedBrensanhamLine(const QtPoint& p1, const QtPoint& p2, std::vector<QtPoint>& line)
{
	line.clear();

	int dx = p2.cx() - p1.cx();                // x偏移量
	int dy = p2.cy() - p1.cy();                // y偏移量
	int ux = (dx > 0) ? 1 : -1;                // x伸展方向
	int uy = (dy > 0) ? 1 : -1;                // y伸展方向

	dx = abs(dx);
	dy = abs(dy);

	int dx2 = dx << 1;   // x偏移量乘2
	int dy2 = dy << 1;   // y偏移量乘2


	int x = p1.cx();  // 起点x坐标
	int y = p1.cy();  // 起点y坐标

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
			QtColor alphaColor = QtMathLibrary::lerpColor(p1.getColor(), p2.getColor(), alpha);

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
			QtColor alphaColor = QtMathLibrary::lerpColor(p1.getColor(), p2.getColor(), alpha);

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

void QtRender::rasterlizedTriangle(const QtPoint& p1, const QtPoint& p2, const QtPoint& p3,
	std::vector<QtPoint>& triangle)
{
	triangle.clear();

	// 计算三角形包围盒
	QtRect boundingBox = QtRectUtil::boundingBox({ p1, p2, p3 });

	// 在包围盒内计算在三角形内的像素点
	for (int y(boundingBox.cTop()); y <= boundingBox.cBottom(); ++y)
	{
		for (int x(boundingBox.cLeft()); x <= boundingBox.cRight(); ++x)
		{
			Eigen::Vector3i v1(p1.cx() - x, p1.cy() - y, 0);
			Eigen::Vector3i v2(p2.cx() - x, p2.cy() - y, 0);
			Eigen::Vector3i v3(p3.cx() - x, p3.cy() - y, 0);

			const double cross1 = v1.cross(v2).z();
			const double cross2 = v2.cross(v3).z();
			const double cross3 = v3.cross(v1).z();

			bool bConsistency = ((cross1 > 0) == (cross2 > 0)) && ((cross2 > 0) == (cross3 > 0));
			if (bConsistency)
			{
				QtPoint point(x, y);
				InterpolationTriangle(p1, p2, p3, point);
				triangle.emplace_back(point);
			}
		}
	}
}

void QtRender::rasterlizedImage(const char* path, std::vector<QtPoint>& pixels)
{
	QtImage* image = QtImageUtils::createImage(path);
	if (nullptr == image)
	{
		return;
	}

	pixels.clear();

	QtColor* data = image->data();
	for (int i = 0; i < image->width(); ++i)
	{
		for (int j = 0; j < image->height(); ++j)
		{
			
			QtPoint point(i, j, data[j * image->width() + i]);
			pixels.emplace_back(point);
		}
	}
}

