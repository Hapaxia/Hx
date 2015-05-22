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

#ifndef HX_PLINTH_COLOR_HPP
#define HX_PLINTH_COLOR_HPP

#include "Generic.hpp"
#include "Math.hpp"
#include "NumberBase.hpp"
#include "Random.hpp"
#include "Strings.hpp"
#include "Tween.hpp"
#include <string>
#include <vector>
#include <math.h>

// debugging
#include <iostream>

namespace hx
{
	namespace Color
	{

// RGB = Red, Green, Blue
struct Rgb
{
	double r, g, b;
};

// HSL = Hue, Saturation, Lightness
struct Hsl
{
	double h, s, l;
};

// HSV = Hue, Saturation, Value
struct Hsv
{
	double h, s, v;
};

// CYM = Cyan, Magenta, Yellow
struct Cmy
{
	double c, m, y;
};

// CMYK = Cyan, Magenta, Yellow, Key(blacK)
struct Cmyk
{
	double c, m, y, k;
};

double relativeLuminance(Rgb rgb);

Cmy cmyFromRgb(const Rgb& rgb);
Rgb rgbFromCmy(const Cmy& cmy);
Cmyk cmykFromRgb(const Rgb& rgb);
Rgb rgbFromCymk(const Cmyk& cmyk);
Hsl hslFromRgb(const Rgb& rgb);
Hsv hsvFromRgb(const Rgb& rgb);
Rgb rgbFromCmh(double c, double m, double h); // internal conversion code used by both rgbFromHsl and rgbFromHsv
Rgb rgbFromHsl(const Hsl& hsl);
Rgb rgbFromHsv(const Hsv& hsv);

std::string hexFromRgb(const Rgb& rgb); // output is base 256 i.e. components have a range of [00, FF]. 6 characters long and lowercase.
Rgb rgbFromHex(std::string hex); // must be 6 or fewer characters long e.g. FF230C (less than 6 characters will be padding with zeroes). base 256 is assumed i.e. components are assumed to have a range of [00, FF]
Rgb rgbFromValue(long int value); // base 256 is assumed i.e. components are assumed to have a range of [0, 255]

Rgb trivialRandomColor();
Rgb standardRandomColor();

	} // namespace Color
} // namespace hx

#endif // HX_PLINTH_COLOR_HPP