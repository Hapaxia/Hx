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

template <typename T, typename alphaT>
// Linear Tween (interpolation) of two values using a given "alpha" value of the "blend amount"
// Type alphaT should be a POD type in range 0 to 1.
// Type T must have required operators available (*, +)
// and be able to be multiplied (scaled) by a POD type (alpha)
T linear(T start, T end, alphaT alpha)
{
	return static_cast<T>(start * (1 - alpha) + end * alpha); // blend from low to high using alpha
}

template <typename T, typename alphaT, typename amountT>
// Eases Tween in and out by "amount". An amount of zero is a linear Tween
T easeInOut(T start, T end, alphaT alpha, amountT amount)
{
	double strength{ static_cast<double>(amount)+1 }; // use range from 1 (straight line) in calculations instead of supplied 0
	double pow1{ pow(alpha, strength) };
	double pow2{ pow(1 - alpha, strength) };
	double eased{ pow1 / (pow1 + pow2) };
	return linear(start, end, eased);
}

template <typename T, typename alphaT, typename amountT>
// Eases Tween in by "amount". An amount of zero is a linear Tween
T easeIn(T start, T end, alphaT alpha, amountT amount)
{
	return easeInOut(start, end + (end - start), alpha / 2, amount);
}

template <typename T, typename alphaT, typename amountT>
// Eases Tween out by "amount". An amount of zero is a linear Tween
T easeOut(T start, T end, alphaT alpha, amountT amount)
{
	return easeInOut(start - (end - start), end, 0.5 + alpha / 2, amount);
}

template <typename T, typename alphaT, typename amountT>
// Eases Tween in by "in" and out by "out". Zero means no easing. If in and out are both zero, it becomes a linear Tween
T oldEase(T start, T end, alphaT alpha, amountT in, amountT out)
{
	T easedIn{ easeIn(start, end, alpha, in) };
	T easedOut{ easeOut(start, end, alpha, out) };
	return linear(easedIn, easedOut, alpha);
}

template <typename T, typename alphaT>
// "Smoothstep" as found at http://guihaire.com/code/?p=229
T quickerEase(T start, T end, alphaT alpha)
{
	return linear(start, end, alpha * alpha * (3 - 2 * alpha));
}

template <typename T, typename alphaT>
// "Smootherstep" as found at http://guihaire.com/code/?p=229
T quickEase(T start, T end, alphaT alpha)
{
	return linear(start, end, alpha * alpha * alpha * (10 + alpha * (6 * alpha - 15)));
}