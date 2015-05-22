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

#include "Clock.hpp"

namespace hx
{
	namespace Kairos
	{

Clock::Clock()
{
}

Clock::Time Clock::getCurrentTime()
{
	return{ getCurrentHour(), getCurrentMinute(), getCurrentSecond() };
}

unsigned int Clock::getCurrentHour()
{
	return static_cast<unsigned int>(getCurrentTimePointInSeconds() % m_secondsInOneDay / m_secondsInOneHour);
}

unsigned int Clock::getCurrentMinute()
{
	return static_cast<unsigned int>(getCurrentTimePointInSeconds() % m_secondsInOneHour / m_secondsInOneMinute);
}

unsigned int Clock::getCurrentSecond()
{
	return static_cast<unsigned int>(getCurrentTimePointInSeconds() % m_secondsInOneMinute);
}



// PRIVATE

unsigned long long int Clock::getCurrentTimePointInSeconds()
{
	using std::chrono::system_clock;
	system_clock::time_point timePoint = system_clock::now();
	system_clock::duration duration = timePoint.time_since_epoch();
	return duration.count() * system_clock::period::num / system_clock::period::den;
}

	} // namespace Kairos
} // namespace hx
