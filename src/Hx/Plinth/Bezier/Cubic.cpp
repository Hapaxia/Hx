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

#include "Cubic.hpp"

namespace hx
{
	namespace Bezier
	{

Cubic::Cubic()
{
	init();
	resize(4); // number of control points in a cubic bezier
}

// PRIVATE

double Cubic::calculate(const std::vector<double>& a, double t)
{
	double t2{ 1 - t };
	return	a[0] * t2 * t2 * t2 +
			a[1] * 3 * t2 * t2 * t +
			a[2] * 3 * t2 * t * t +
			a[3] * t * t * t;
}

	} // namespace Bezier
}  // namespace hx