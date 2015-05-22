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

#include "Random.hpp"

namespace hx
{

Random::Random():
m_min(0u),
m_max(100u)
{
	randomSeed();
}

Random::Random(unsigned int min, unsigned int max) :
m_min(min),
m_max(max)
{
	randomSeed();
}

unsigned int Random::rand(unsigned int rangeSize)
{
	return std::uniform_int_distribution<unsigned int>{0, rangeSize - 1}(m_generator);
}

unsigned int Random::uIntValue()
{
	return uIntValue(m_min, m_max);
}

int Random::intValue()
{
	return intValue(m_min, m_max);
}

double Random::doubleValue()
{
	return doubleValue(m_min, m_max);
}

unsigned int Random::value(unsigned int min, unsigned int max)
{
	return uIntValue(min, max);
}

int Random::value(int min, int max)
{
	return intValue(min, max);
}

double Random::value(double min, double max)
{
	return doubleValue(min, max);
}

unsigned int Random::uIntValue(unsigned int min, unsigned int max)
{
	if (min > max)
		hx::swap(min, max);
	return std::uniform_int_distribution<unsigned int>{min, max}(m_generator);
}

int Random::intValue(int min, int max)
{
	if (min > max)
		hx::swap(min, max);
	return static_cast<int>(std::uniform_int_distribution<int>{min, max}(m_generator));
}

double Random::doubleValue(double min, double max)
{
	if (min > max)
		hx::swap(min, max);
	return std::uniform_real_distribution<double>{min, max}(m_generator);
}

void Random::setMinimum(unsigned int min)
{
	m_min = min;
	if (m_min > m_max)
		hx::swap(m_min, m_max);
}

void Random::setMaximum(unsigned int max)
{
	m_max = max;
	if (m_min > m_max)
		hx::swap(m_min, m_max);
}

void Random::setRange(unsigned int min, unsigned int max)
{
	setMinimum(min);
	setMaximum(max);
}

void Random::randomSeed()
{
	std::random_device rd;
	m_generator.seed(rd());
}

} // namespace hx