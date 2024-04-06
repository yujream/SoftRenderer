#include "algorithm/QtMathLibrary.h"

double QtMathLibrary::deg2rad(const double theta)
{
	return 0.01745329251994329 * theta;
}

double QtMathLibrary::fraction(double v)
{
	return v - static_cast<int>(v);
}
