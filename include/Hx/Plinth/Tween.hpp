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

// Tween

// interpolation functions

#ifndef HX_PLINTH_TWEEN_HPP
#define HX_PLINTH_TWEEN_HPP

#include <math.h>

namespace hx
{
	namespace Tween
	{

template <typename T, typename alphaT>
// Linear Tween (interpolation) of two values using a given "alpha" value of the "blend amount"
// Type alphaT should be a POD type in range 0 to 1.
// Type T must have required operators available (*, +)
// and be able to be multiplied (scaled) by a POD type (alpha)
T linear(T start, T end, alphaT alpha);

template <typename T, typename alphaT, typename amountT>
// Eases Tween in and out by "amount". An amount of zero is a linear Tween
T easeInOut(T start, T end, alphaT alpha, amountT amount);

template <typename T, typename alphaT, typename amountT>
// Eases Tween in by "amount". An amount of zero is a linear Tween
T easeIn(T start, T end, alphaT alpha, amountT amount);

template <typename T, typename alphaT, typename amountT>
// Eases Tween out by "amount". An amount of zero is a linear Tween
T easeOut(T start, T end, alphaT alpha, amountT amount);

template <typename T, typename alphaT, typename amountT>
// Eases Tween in by "in" and out by "out". Zero means no easing. If in and out are both zero, it becomes a linear Tween
T oldEase(T start, T end, alphaT alpha, amountT in, amountT out);

template <typename T, typename alphaT>
// "Smoothstep" as found at http://guihaire.com/code/?p=229
T quickerEase(T start, T end, alphaT alpha);

template <typename T, typename alphaT>
// "Smootherstep" as found at http://guihaire.com/code/?p=229
T quickEase(T start, T end, alphaT alpha);

#include "Tween.inl"

	} // namespace Tween
} // namespace hx

#endif // HX_PLINTH_TWEEN_HPP