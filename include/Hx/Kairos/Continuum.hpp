//////////////////////////////////////////////////////////////////////////////
//
// Hx
// --
//
// Kairos
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

#ifndef HX_KAIROS_CONTINUUM_HPP
#define HX_KAIROS_CONTINUUM_HPP

#include "Stopwatch.hpp"

namespace hx
{
	namespace Kairos
	{

class Continuum
{
public:
	Continuum();
	void reset();
	void go();
	void stop();
	void setSpeed(double speed);
	double getSpeed();
	Duration getTime();

private:
	Stopwatch m_stopwatch;
	Duration m_time;
	double m_speed;
	//double m_isPaused;

	inline void updateTime();
};

	} // namespace Kairos
} // namespace hx
#endif // HX_KAIROS_CONTINUUM_HPP