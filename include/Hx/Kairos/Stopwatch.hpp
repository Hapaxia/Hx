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

// WARNING: C++11 or later required (uses <chrono>)

// Pausable stopwatch

#ifndef HX_KAIROS_STOPWATCH_HPP
#define HX_KAIROS_STOPWATCH_HPP

#include <chrono>
#include "Duration.hpp"

namespace hx
{
	namespace Kairos
	{

using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;

class Stopwatch
{
public:
	Stopwatch();
	Duration getTime(); // returns the current time
	Duration restart(); // resets time to zero and starts the timer
	Duration pause(); // stops timer
	Duration resume(); // starts timer
	Duration stop(); // stops timer and resets time to zero
	bool isPaused();

private:
	high_resolution_clock::time_point m_startTime;
	bool m_isPaused;
	Duration m_accumulatedDuration;
};

	} // namespace Kairos
} // namespace hx

#endif // HX_KAIROS_STOPWATCH_HPP