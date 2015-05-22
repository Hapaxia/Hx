//////////////////////////////////////////////////////////////////////////////
//
// Hx
// --
//
// Plinth
//
// Copyright(c) 2015 M.J.Silk
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

#include "Bezier.hpp"

namespace hx
{
	namespace Bezier
	{

Bezier::Bezier()
{
	init();
	resize(defaultNumberOfPoints);
}

void Bezier::init()
{
	m_throwExceptions = true;
}

void Bezier::resize(unsigned int numberOfPoints)
{
	m_points.resize(numberOfPoints);
	m_weights.resize(numberOfPoints);
	reset();
}

void Bezier::reset()
{
	for (auto& point : m_points)
	{ // these braces are required
		point = { 0.0, 0.0 };
	}
	for (auto& weight : m_weights)
		weight = 0.0;
}

void Bezier::setPoint(unsigned int index, const Point& point)
{
	if (index >= m_points.size())
	{
		if (m_throwExceptions)
			throw "Bezier point index out of range.";
		return;
	}
	m_points[index] = point;
}

void Bezier::setAllPoints(const Point& point)
{
	for (auto& p : m_points)
		p = point;
}

Bezier::Point Bezier::getPoint(unsigned int index)
{
	if (index >= m_points.size())
	{
		if (m_throwExceptions)
			throw "Bezier point index out of range.";
		return m_points[0];
	}
	return m_points[index];
}

void Bezier::setThrowsExceptions(bool doesThrow)
{
	m_throwExceptions = doesThrow;
}

bool Bezier::getThrowsExceptions()
{
	return m_throwExceptions;
}

double Bezier::solveYForX(double x)
{
	// unfinished. see header.
	const unsigned int NUMBER_OF_ITERATIONS{ 100 }; // accuracy level (20 seems to be quite accurate. 2000 doesn't seem to be slow)
	double minimum{ 0.0 };
	double maximum{ 1.0 };
	double middle{ 0.5 }; // start tests from the centre
	for (unsigned int i{ 0 }; i < NUMBER_OF_ITERATIONS; ++i)
	{
		double result{ calculateX(middle) }; // get x for "middle" (current position along spline)
		if (result < x)
			minimum = middle;
		else if (result > x)
			maximum = middle;
		middle = (maximum + minimum) / 2;
	}
	return calculateY(middle); // return y for last "middle" along spline
}

double Bezier::getX(double t)
{
	return calculateX(t);
}

double Bezier::getY(double t)
{
	return calculateY(t);
}

// PRIVATE

double Bezier::calculate(const std::vector<double>& a, double t)
{
	if (a.size() < 2)
		return 0.0;
	double result{ 0.0 };
	for (unsigned int i{ 0 }; i < a.size(); ++i)
		result += a[i] * binomialCoefficient(a.size() - 1, i) * (power(1 - t, a.size() - 1 - i) * power(t, i));
	return result;

	/*
	// quicker, specific order calculations
	double t2{ 1 - t };
	if (a.size() == 5) // hypercubic/quartic
		return	a[0] * t2 * t2 * t2 * t2 +
				a[1] * 4 * t2 * t2 * t2 * t +
				a[2] * 6 * t2 * t2 * t * t +
				a[3] * 4 * t2 * t * t * t +
				a[4] * t * t * t * t;
	else if (a.size() == 4) // cubic
		return	a[0] * t2 * t2 * t2 +
				a[1] * 3 * t2 * t2 * t +
				a[2] * 3 * t2 * t * t +
				a[3] * t * t * t;
	else if (a.size() == 3) // quadratic
		return	a[0] * t2 * t2 +
				a[1] * 2 * t2 * t +
				a[2] * t * t;
	else if (a.size() == 2) // linear
		return	a[0] * t2 +
				a[1] * t;
	else
		return 0.0;
	*/
}

double Bezier::calculateX(double t)
{
	for (unsigned int i{ 0 }; i < m_points.size(); ++i)
		m_weights[i] = m_points[i].x;
	return calculate(m_weights, t);
}

double Bezier::calculateY(double t)
{
	for (unsigned int i{ 0 }; i < m_points.size(); ++i)
		m_weights[i] = m_points[i].y;
	return calculate(m_weights, t);
}

double Bezier::binomialCoefficient(unsigned int n, unsigned int k)
{
	double result{ 1.0 };
	for (unsigned int i{ 1 }; i <= k; ++i)
		result *= static_cast<double>(n + 1 - i) / i;
	return result;
}

// fast power function when exponent is low (<=10). can only take integer exponents and will return 1 if negative.
double Bezier::power(double a, int b)
{
	double result{ 1.0 };
	for (int i{ 0 }; i < b; ++i)
		result *= a;
	return result;
}

	} // namespace Bezier
}  // namespace hx