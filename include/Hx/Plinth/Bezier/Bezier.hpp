//////////////////////////////////////////////////////////////////////////////
//
// Hx
// --
//
// Plinth
//
// Copyright(c) 2014 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty.In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

// Bezier calculator base

// to be inherited and calculations implemented
// calculation provided here are slower but more flexible (can change orders and also do high orders)

// constructor should also be re-implemented to resize the bezier to the required number of points:
// e.g.
// ctor() { init(); resize(3); }
// for a quadratic bezier (3 points)
// "ctor" is the name of the constructor

// throws (char*) exception if point index is out of range during getPoint or setPoint
// these exceptions can be turned off with setThrowsExceptions(false);
// if point index is out of range for setPoint, the command is simply ignored i.e no point is set.
// if point index is out of range for getPoint, the first point is returned.
// the exceptions are to inform that these have occurred. no other feedback is given.

#ifndef HX_PLINTH_BEZIER_BEZIER_HPP
#define HX_PLINTH_BEZIER_BEZIER_HPP

#include <vector>

namespace hx
{
	namespace Bezier
	{

		class Bezier
{
public:
	const unsigned int defaultNumberOfPoints{ 2 };

	struct Point
	{
		double x, y;
	};

	Bezier();
	void init();
	void resize(unsigned int numberOfPoints);
	void reset();
	void setPoint(unsigned int index, const Point& point);
	void setAllPoints(const Point& point);
	Point getPoint(unsigned int pointIndex);

	void setThrowsExceptions(bool doesThrow);
	bool getThrowsExceptions();

	// I want to develop this (solveYForX) to allow a starting point (and, preferably, a range) to be passed as a parameter.
	// This would basically just set minimum, maximum, and middle.
	// Just a range (no starting point) should be allowed to be passed too (would automatically start from the centre of the range).
	// Also, solveXForY should be easily adapted from this.
	double solveYForX(double x); 

	double getX(double t);
	double getY(double t);

private:
	bool m_throwExceptions;
	std::vector<Point> m_points;
	std::vector<double> m_weights;

	virtual double calculate(const std::vector<double>& a, double t);
	double calculateX(double t);
	double calculateY(double t);
	double binomialCoefficient(unsigned int n, unsigned int k);
	double power(double a, int b);
};

	} // namespace Bezier
} // namespace hx

#endif // HX_PLINTH_BEZIER_BEZIER_HPP