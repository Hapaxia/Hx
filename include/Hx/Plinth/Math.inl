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

template<class T>
// returns angle given in degrees as radians
inline T radiansFromDegrees(T degrees)
{
	return static_cast<T>(static_cast<double>(degrees) * pi / 180);
}

template<class T>
// returns angle given in radians as degrees
inline T degreesFromRadians(T radians)
{
	return static_cast<T>(static_cast<double>(radians)* 180 / pi);
}

template<class T>
// mod (%) from floating point numbers
inline T mod(const T& a, const T& b)
{
	return a - (trunc(a / b) * b);
}

template<class T>
// returns the dot product of two vectors with the same number of elements
T dot(const std::vector<T>& a, const std::vector<T>& b)
{
	T result;
	if ((a.size() != b.size()) || (a.size() == 0))
		return result;

	for (unsigned int i{ 0 }; i < a.size() : ++i)
		result += a[i] * b[i];

	return result;
}

