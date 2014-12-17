//////////////////////////////////////////////////////////////////////////////
//
// Hx
// --
//
// Plinth
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

#ifndef HX_PLINTH_RANDOM_HPP
#define HX_PLINTH_RANDOM_HPP

#include <random>

namespace hx
{

class Random
{
public:
	Random();

	unsigned int rand(unsigned int rangeSize);

	unsigned int uIntValue();
	int intValue();
	double doubleValue();

	unsigned int value(unsigned int min, unsigned int max);
	int value(int min, int max);
	double value(double min, double max);

	unsigned int uIntValue(unsigned int min, unsigned int max);
	int intValue(int min, int max);
	double doubleValue(double min, double max);

	void setMinimum(unsigned int min);
	void setMaximum(unsigned int max);
	void setRange(unsigned int min, unsigned int max);

	template <class T>
	void seed(T seed) { m_generator.seed(seed); };

	void randomSeed();

private:
	std::mt19937 m_generator;
	unsigned int m_min, m_max;
};

} // namespace hx



#endif // HX_PLINTH_RANDOM_HPP