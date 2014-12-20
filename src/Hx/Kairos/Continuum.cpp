//////////////////////////////////////////////////////////////////////////////
//
// Hx
// --
//
// Kairos
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

#include "Continuum.hpp"

namespace hx
{
	namespace Kairos
	{

Continuum::Continuum():
m_stopwatch(),
m_time(),
m_speed(1.0)
{
}

void Continuum::reset()
{
	m_time.zero();
	m_speed = 1.0;
	m_stopwatch.restart();
}

void Continuum::go()
{
	m_stopwatch.resume();
}

void Continuum::stop()
{
	m_stopwatch.pause();
}

void Continuum::setSpeed(double speed)
{
	updateTime();
	m_speed = speed;
}

double Continuum::getSpeed()
{
	return m_speed;
}

Duration Continuum::getTime()
{
	updateTime();
	return m_time;
}




// PRIVATE

inline void Continuum::updateTime()
{
	const bool isStopped{ m_stopwatch.isPaused() };
	m_time += m_stopwatch.restart() * m_speed;
	if (isStopped)
		m_stopwatch.stop();
}





	} // namespace Kairos
} // namespace hx