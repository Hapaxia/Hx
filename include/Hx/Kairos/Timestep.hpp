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

#ifndef HX_KAIROS_TIMESTEP_HPP
#define HX_KAIROS_TIMESTEP_HPP

#include "Continuum.hpp"

namespace hx
{
	namespace Kairos
	{

class Timestep
{
public:
	Timestep();
	void setStep(double step);
	double getStep();
	float getStepAsFloat();
	void resetTime();
	bool isUpdateRequired();
	double getInterpolationAlpha();
	float getInterpolationAlphaAsFloat();
	void addFrame();
	double getOverall(); // amount of time processed (whole steps only)
	float getOverallAsFloat();
	double getTime(); // amount of time accumulated
	float getTimeAsFloat();
	void setMaxAccumulation(double maxAccumulation);
	void setTimeSpeed(double timeSpeed);
	double getTimeSpeed();
	void pause();
	void unpause();
	bool isPaused();

private:
	hx::Kairos::Continuum m_continuum;
	double m_step;
	double m_accumulator;
	double m_overall;
	double m_maxAccumulation;
	double m_timeSpeed;

	bool shouldBeZero(double a);
};

	} // namespace Kairos
} // namespace hx

#endif // HX_KAIROS_TIMESTEP_HPP