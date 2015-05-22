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

// Generic

// generic/common functions/structures

#ifndef HX_PLINTH_GENERIC_HPP
#define HX_PLINTH_GENERIC_HPP

#include <vector>

namespace hx
{

template<class T>
// returns the highest value in a pair
inline T max(const T& a, const T& b);

template<class T>
// returns the lowest value in a pair
inline T min(const T& a, const T& b);

template<class T>
// returns the highest value of a vector
T max(const std::vector<T>& vector);

template<class T>
// returns the lowest value of a vector
T min(const std::vector<T>& vector);

template<class T>
// swaps two values
void swap(T& a, T& b);

template<class T>
// order two values (low - high)
inline void orderLowHigh(T& low, T& high);

template<class T>
// if value is outside of range [min, max], adjust to the closest value in the range
T clamp(const T& value, T min, T max);

template<class T>
// if value is outside of range [min, max], adjust to the furthest value in the range
T clampLoop(const T& value, T min, T max);

template<class T>
// if value is outside of range [min, max), adjust by stepping back by size of range (keeping position in range after removing multiples of range)
// note: max is not included in the range
T clampCycle(T value, T min, T max);

template<class T>
// returns true if in the range [min, max] (boundaries included) and false if outside
inline bool inRange(const T& value, const T& min, const T& max);

template<class T>
// returns true if within the range (min, max) (boundaries not included) and false if outside
inline bool withinRange(const T& value, const T& min, const T& max);

template<class T>
// switches/toggles parameter (b = !b) and also returns the result
// e.g. a = !b, a becomes opposite of b. a = toggle(b), a becomes opposite of what b was but b is now identical to a.
T toggle(T& b);

template<class T, class R>
// 'pulls' a range using a hook (if hook is outside range). keeping size will move the range; not keeping size will stretch the range (move just one boundary)
void pullRange(T& low, T& high, const T& hook, bool keepSize = false);

template <class T>
struct Vector2
{
	T x, y;
};

template <class T>
struct Vector3
{
	T x, y, z;
};

using Vector2u = Vector2<unsigned int>;
using Vector2i = Vector2<int>;
using Vector2d = Vector2<double>;
using Vector3u = Vector3<unsigned int>;
using Vector3i = Vector3<int>;
using Vector3d = Vector3<double>;

template <class TInteger>
TInteger intFromBytes(TInteger& result, const unsigned char* bytes, bool isLittleEndian = true);
/*
template <class TInteger>
TInteger intFromBytes(TInteger& result, const unsigned char* bytes, unsigned int rangeSize = sizeof(bytes), unsigned int rangeStart = 0, bool isLittleEndian = true);
*/


#include "Generic.inl"

} // hx

#endif // HX_PLINTH_GENERIC_HPP