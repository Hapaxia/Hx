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
// returns the highest value in a pair
inline T max(const T& a, const T& b)
{
	return a > b ? a : b;
}

template<class T>
// returns the lowest value in a pair
inline T min(const T& a, const T& b)
{
	return a < b ? a : b;
}

template<class T>
// returns the highest value of a vector
T max(const std::vector<T>& vector)
{
	if (vector.size() == 0)
		return;
	T result{ vector[0] };
	for (unsigned int i{ 1 }; i < vector.size(); ++i)
		result = max(result, vector[i]);
	return result;
}

template<class T>
// returns the lowest value of a vector
T min(const std::vector<T>& vector)
{
	if (vector.size() == 0)
		return;
	T result{ vector[0] };
	for (unsigned int i{ 1 }; i < vector.size(); ++i)
		result = min(result, vector[i]);
	return result;
}

template<class T>
// swaps two values
void swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

template<class T>
// order two values (low - high)
inline void orderLowHigh(T& low, T& high)
{
	if (low > high)
		swap(low, high);
}

template<class T>
// if value is outside of range [min, max], adjust to the closest value in the range
T clamp(const T& value, T min, T max)
{
	orderLowHigh(min, max);
	if (value > max)
		return max;
	return value < min ? min : value;
}

template<class T>
// if value is outside of range [min, max], adjust to the furthest value in the range
T clampLoop(const T& value, T min, T max)
{
	orderLowHigh(min, max);
	if (value > max)
		return min;
	return value < min ? max : value;
}

template<class T>
// if value is outside of range [min, max), adjust by stepping back by size of range (keeping position in range after removing multiples of range)
// note: max is not included in the range
T clampCycle(T value, T min, T max)
{
	orderLowHigh(min, max);
	const T range = (max - min);
	if (value > max)
	{
		while (value >= max)
			value -= range;
	}
	else if (value < min)
	{
		while (value < min)
			value += range;
	}
	return value;
}

template<class T>
// returns true if with the range [min, max] (boundaries included) and false if outside
inline bool inRange(const T& value, const T& min, const T& max)
{
	return ((value >= min) && (value <= max));
}

template<class T>
// returns true if within the range (min, max) (boundaries not included) and false if outside
inline bool withinRange(const T& value, const T& min, const T& max)
{
	return ((value > min) && (value < max));
}

template<class T>
// switches/toggles parameter (b = !b) and also returns the result
// e.g. a = !b, a becomes opposite of b. a = toggle(b), a becomes opposite of what b was but b is now identical to a.
T toggle(T& b)
{
	b = !b;
	return b;
}

template<class T>
// 'pulls' a range using a hook (if hook is outside range). keeping size will move the range; not keeping size will stretch the range (move just one boundary)
void pullRange(T& low, T& high, const T& hook, bool keepSize = false)
{
	orderLowHigh(low, high);
	if (hx::inRange(low, high, hook))
		return;
	T range = high - low;
	if (hook < low)
	{
		low = hook;
		if (keepSize)
			high = low + range;
	}
	else if (hook > high)
	{
		high = hook;
		if (keepSize)
			low = high - range;
	}
}

template <class IntegerType>
IntegerType intFromBytes(IntegerType& result, const unsigned char* bytes, bool isLittleEndian)
{
	result = 0;
	if (isLittleEndian)
		for (int n{ sizeof(result) }; n >= 0; --n)
			result = (result << 8) + bytes[n];
	else
		for (unsigned int n{ 0 }; n < sizeof(result); ++n)
			result = (result << 8) + bytes[n];
	return result;
}

/*
template <class IntegerType>
IntegerType intFromBytes(IntegerType& result, const unsigned char* bytes, unsigned int rangeSize, unsigned int rangeStart, bool isLittleEndian)
{
	result = 0;
	if (isLittleEndian)
		for (int n{ rangeSize }; n >= 0; --n)
			result = (result << 8) + bytes[n];
	else
		for (unsigned int n{ 0 }; n < rangeSize; ++n)
			result = (result << 8) + bytes[n];
	return result;
}
*/


