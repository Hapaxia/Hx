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

#include "Duration.hpp"

namespace hx
{
	namespace Kairos
	{

Duration::Duration()
{
	zero();
}

Duration::Duration(long long int nanoseconds)
{
	nano = nanoseconds;
}

Duration::Duration(long int microseconds)
{
	nano = microseconds * 1000;
}

Duration::Duration(int milliseconds)
{
	nano = milliseconds * 1000000;
}

Duration::Duration(double seconds)
{
	nano = static_cast<long long int>(seconds * 1000000000.0);
}

Duration Duration::zero()
{
	Duration returnDuration{ *this };
	returnDuration.nano = nano;
	nano = 0;
	return returnDuration;
}

long long int Duration::asNanoseconds()
{
	return nano;
}

long int Duration::asMicroseconds()
{
	return static_cast<long int>(nano / 1000);
}

int Duration::asMilliseconds()
{
	return static_cast<int>(nano / 1000000);
}

double Duration::asSeconds()
{
	return static_cast<double>(nano) / 1000000000.0;
}

double Duration::asMinutes()
{
	return asSeconds() / 60.0;
}

double Duration::asHours()
{
	return asMinutes() / 24.0;
}



void Duration::setFromHours(double hours)
{
	nano = static_cast<long long int>(hours * 3600000000000.0);
}

void Duration::setFromMinutes(double minutes)
{
	nano = static_cast<long long int>(minutes * 60000000000.0);
}

void Duration::setFromSeconds(double seconds)
{
	nano = static_cast<long long int>(seconds * 1000000000.0);
}

void Duration::setFromMilliseconds(int milliseconds)
{
	nano = milliseconds * 1000000;
}

void Duration::setFromMicroseconds(long int microseconds)
{
	nano = microseconds * 1000;
}

void Duration::setFromNanoseconds(long long int nanoseconds)
{
	nano = nanoseconds;
}





Duration Duration::operator+(const Duration& offset)
{
	Duration returnDuration{ *this };
	returnDuration.nano += offset.nano;
	return returnDuration;
}

Duration Duration::operator-(const Duration& offset)
{
	Duration returnDuration{ *this };
	returnDuration.nano -= offset.nano;
	return returnDuration;
}

bool Duration::operator<(const Duration& rhs)
{
	return nano < rhs.nano;
}

bool Duration::operator>(const Duration& rhs)
{
	return nano > rhs.nano;
}

std::ostream& operator<<(std::ostream& out, const Duration& duration)
{
	double seconds = static_cast<double>(static_cast<long double>(duration.nano) / 1000000000);
	out << seconds << " seconds";
	return out;
}

	} // namespace Kairos
} // namespace hx