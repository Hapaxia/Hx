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

#ifndef HX_KAIROS_DURATION_HPP
#define HX_KAIROS_DURATION_HPP

#include <ostream>

namespace hx
{
	namespace Kairos
	{

// time duration
class Duration
{
public:
	long long int nano{ 0 };

	Duration();
	Duration(long long int nanoseconds);
	Duration(long int microseconds);
	Duration(int milliseconds);
	Duration(double seconds);
	Duration zero();
	long long int asNanoseconds();
	long int asMicroseconds();
	int asMilliseconds();
	double asSeconds();
	double asMinutes();
	double asHours();

	void setFromHours(double hours);
	void setFromMinutes(double minutes);
	void setFromSeconds(double seconds);
	void setFromMilliseconds(int milliseconds);
	void setFromMicroseconds(long int microseconds);
	void setFromNanoseconds(long long int nanoseconds);

	Duration operator+(const Duration& offset);
	Duration operator-(const Duration& offset);
	template <typename T>
	Duration operator*(const T& scale);
	template <typename T>
	Duration operator/(const T& divisor);
	template <typename T>
	Duration& operator+=(const T& offset);
	template <typename T>
	Duration& operator-=(const T& offset);
	template <typename T>
	Duration& operator*=(const T& scale);
	template <typename T>
	Duration& operator/=(const T& divisor);
	bool operator<(const Duration& rhs);
	bool operator>(const Duration& rhs);
	friend std::ostream& operator<<(std::ostream& out, const Duration& duration);
};

template <typename T>
Duration Duration::operator*(const T& scale)
{
	Duration returnDuration{ *this };
	returnDuration.nano = static_cast<long long int>(returnDuration.nano * scale);
	return returnDuration;
}

template <typename T>
Duration Duration::operator/(const T& divisor)
{
	Duration returnDuration{ *this };
	returnDuration.nano = static_cast<long long int>(returnDuration.nano / divisor);
	return returnDuration;
}

template <typename T>
Duration& Duration::operator+=(const T& offset)
{
	*this = *this + offset;
	return *this;
}

template <typename T>
Duration& Duration::operator-=(const T& offset)
{
	*this = *this - offset;
	return *this;
}

template <typename T>
Duration& Duration::operator*=(const T& scale)
{
	*this = *this * scale;
	return *this;
}

template <typename T>
Duration& Duration::operator/=(const T& divisor)
{
	*this = *this / divisor;
	return *this;
}

	} // namespace Kairos
} // namespace hx

#endif // HX_KAIROS_DURATION_HPP