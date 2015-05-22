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

// Cubic Bezier calculator

// cubic bezier only (faster calculations than flexible order bezier)

// throws (char*) exception if point index is out of range during getPoint or setPoint
// these exceptions can be turned off with setThrowsExceptions(false);
// if point index is out of range for setPoint, the command is simply ignored i.e no point is set.
// if point index is out of range for getPoint, the first point is returned.
// the exceptions are to inform that these have occurred. no other feedback is given.

#ifndef HX_PLINTH_BEZIER_CUBIC_HPP
#define HX_PLINTH_BEZIER_CUBIC_HPP

#include "Bezier.hpp"
#include <vector>

namespace hx
{
	namespace Bezier
	{

class Cubic : public Bezier
{
public:
	Cubic();

private:
	virtual double calculate(const std::vector<double>& a, double t);
};

	} // namespace Bezier
} // namespace hx

#endif // HX_PLINTH_BEZIER_CUBIC_HPP