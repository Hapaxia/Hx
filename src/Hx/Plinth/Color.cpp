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

#include "Color.hpp"

namespace hx
{
	namespace Color
	{

void relativeLuminance_calculateChannelLuminance(double& channel)
{
	if (channel <= 0.03928)
		channel /= 12.92;
	else
		channel = pow((channel + 0.055) / 1.055, 2.4);
}
double relativeLuminance(Rgb rgb)
{
	// sRGB colorspace relative luminance (http://www.w3.org/TR/WCAG20/#relativeluminancedef) (http://www.w3.org/TR/WCAG20/relative-luminance.xml)

	relativeLuminance_calculateChannelLuminance(rgb.r);
	relativeLuminance_calculateChannelLuminance(rgb.g);
	relativeLuminance_calculateChannelLuminance(rgb.b);
	return 0.2126 * rgb.r + 0.7152 * rgb.g + 0.0722 * rgb.b;
}

Cmy cmyFromRgb(const Rgb& rgb)
{
	return{ hx::clamp(1.0 - rgb.r, 0.0, 1.0), hx::clamp(1.0 - rgb.g, 0.0, 1.0), hx::clamp(1.0 - rgb.b, 0.0, 1.0) };
}

Rgb rgbFromCmy(const Cmy& cmy)
{
	return{ hx::clamp(1.0 - cmy.c, 0.0, 1.0), hx::clamp(1.0 - cmy.m, 0.0, 1.0), hx::clamp(1.0 - cmy.y, 0.0, 1.0) };
}

Cmyk cmykFromRgb(const Rgb& rgb)
{
	double k{ 1.0 - hx::clamp(hx::max(hx::max(rgb.r, rgb.g), rgb.b), 0.0, 1.0) };
	return
	{
		(1.0 - hx::clamp(rgb.r, 0.0, 1.0) - k) / (1.0 - k),
		(1.0 - hx::clamp(rgb.g, 0.0, 1.0) - k) / (1.0 - k),
		(1.0 - hx::clamp(rgb.b, 0.0, 1.0) - k) / (1.0 - k),
		k
	};
}

Rgb rgbFromCmyk(const Cmyk& cmyk)
{
	return
	{
		(1.0 - hx::clamp(cmyk.c, 0.0, 1.0)) * (1.0 - hx::clamp(cmyk.k, 0.0, 1.0)),
		(1.0 - hx::clamp(cmyk.m, 0.0, 1.0)) * (1.0 - hx::clamp(cmyk.k, 0.0, 1.0)),
		(1.0 - hx::clamp(cmyk.m, 0.0, 1.0)) * (1.0 - hx::clamp(cmyk.k, 0.0, 1.0))
	};
}

Hsl hslFromRgb(const Rgb& rgb)
{
	Hsl hsl;
	double max{ hx::clamp(hx::max(hx::max(rgb.r, rgb.g), rgb.b), 0.0, 1.0) };
	double min{ hx::clamp(hx::min(hx::max(rgb.r, rgb.g), rgb.b), 0.0, 1.0) };
	double range{ max - min };

	if (rgb.r > rgb.g && rgb.r > rgb.b)
		hsl.h = hx::mod((rgb.g - rgb.b) / range, 6.0) / 6.0;
	else if (rgb.g > rgb.r && rgb.r > rgb.b)
		hsl.h = (((rgb.b - rgb.r) / range) + 2.0) / 6.0;
	else
		hsl.h = (((rgb.r - rgb.g) / range) + 4.0) / 6.0;

	hsl.l = (max + min) / 2.0;

	if (range != 0.0)
		hsl.s = range / (1.0 - abs(2.0 * hsl.l - 1.0));
	else
		hsl.s = 0.0;

	return hsl;
}

Hsv hsvFromRgb(const Rgb& rgb)
{
	Hsv hsv;
	double max{ hx::clamp(hx::max(hx::max(rgb.r, rgb.g), rgb.b), 0.0, 1.0) };
	double min{ hx::clamp(hx::min(hx::max(rgb.r, rgb.g), rgb.b), 0.0, 1.0) };
	double range{ max - min };

	if (rgb.r > rgb.g && rgb.r > rgb.b)
		hsv.h = hx::mod((rgb.g - rgb.b) / range, 6.0) / 6.0;
	else if (rgb.g > rgb.r && rgb.r > rgb.b)
		hsv.h = (((rgb.b - rgb.r) / range) + 2.0) / 6.0;
	else
		hsv.h = (((rgb.r - rgb.g) / range) + 4.0) / 6.0;

	hsv.v = max;

	if (range != 0.0)
		hsv.s = range / max;
	else
		hsv.s = 0.0;

	return hsv;
}

// internal conversion code used by both rgbFromHsl and rgbFromHsv
Rgb rgbFromCmh(double c, double m, double h)
{
	Rgb rgb;

	double x{ c * (1.0 - hx::mod(abs(h * 6.0), 2.0) - 1.0) };

	if (h <= (1.0 / 6.0))
		rgb = { c, x, 0.0 };
	else if (h <= (2.0 / 6.0))
		rgb = { x, c, 0.0 };
	else if (h <= (3.0 / 6.0))
		rgb = { 0.0, c, x };
	else if (h <= (4.0 / 6.0))
		rgb = { 0.0, x, c };
	else if (h <= (5.0 / 6.0))
		rgb = { x, 0.0, c };
	else
		rgb = { c, 0.0, x };

	rgb.r += m;
	rgb.g += m;
	rgb.b += m;

	return rgb;
}

Rgb rgbFromHsl(const Hsl& hsl)
{
	const double c{ (1.0 - abs(2 * hsl.l - 1)) * hsl.s };
	return rgbFromCmh(c, hsl.l - c / 2.0, hsl.h);
	
	/*
	Rgb rgb;

	double c{ (1.0 - abs(2 * hsl.l - 1)) * hsl.s };
	double x{ c * (1.0 - hx::mod(abs(hsl.h * 6.0), 2.0) - 1.0) };
	double m{ hsl.l - c / 2.0 };

	if (hsl.h <= (1.0 / 6.0))
		rgb = { c, x, 0.0 };
	else if (hsl.h <= (2.0 / 6.0))
		rgb = { x, c, 0.0 };
	else if (hsl.h <= (3.0 / 6.0))
		rgb = { 0.0, c, x };
	else if (hsl.h <= (4.0 / 6.0))
		rgb = { 0.0, x, c };
	else if (hsl.h <= (5.0 / 6.0))
		rgb = { x, 0.0, c };
	else
		rgb = { c, 0.0, x };

	rgb.r += m;
	rgb.g += m;
	rgb.b += m;

	return rgb;
	*/
}

Rgb rgbFromHsv(const Hsv& hsv)
{
	double c{ hsv.v * hsv.s };
	return rgbFromCmh(c, hsv.v - c, hsv.h);

	/*
	Rgb rgb;

	double c{ hsv.v * hsv.s };
	double x{ c * (1.0 - hx::mod(abs(hsv.h * 6.0), 2.0) - 1.0) };
	double m{ hsv.v - c };

	if (hsv.h <= (1.0 / 6.0))
		rgb = { c, x, 0.0 };
	else if (hsv.h <= (2.0 / 6.0))
		rgb = { x, c, 0.0 };
	else if (hsv.h <= (3.0 / 6.0))
		rgb = { 0.0, c, x };
	else if (hsv.h <= (4.0 / 6.0))
		rgb = { 0.0, x, c };
	else if (hsv.h <= (5.0 / 6.0))
		rgb = { x, 0.0, c };
	else
		rgb = { c, 0.0, x };

	rgb.r += m;
	rgb.g += m;
	rgb.b += m;

	return rgb;
	*/
}

std::string hexFromRgb(const Rgb& rgb)
{
	const unsigned int baseMax{ 255 }; // base - 1
	std::vector<std::string> components
	{
		hx::hexFromDec(static_cast<int>(ceil(hx::clamp(rgb.r, 0.0, 1.0) * baseMax))),
		hx::hexFromDec(static_cast<int>(ceil(hx::clamp(rgb.g, 0.0, 1.0) * baseMax))),
		hx::hexFromDec(static_cast<int>(ceil(hx::clamp(rgb.b, 0.0, 1.0) * baseMax)))
	};
	for (auto& component : components)
	{
		while (component.size() < 2)
			component.insert(0, "0");
	}
	return hx::Strings::concatenate(components);
	//return hx::Strings::upperCase(hx::Strings::concatenate(components));
}

Rgb rgbFromHex(std::string hex)
{
	if (!hx::Strings::doesContainOnly(hx::Strings::upperCase(hex), "0123456789ABCDEF"))
		return{ 0.0, 0.0, 0.0 };

	const unsigned int baseMax{ 255 };
	if (hex.size() > 6)
		return{ 0.0, 0.0, 0.0 };
	while (hex.size() < 6)
		hex.insert(0, "0");
	return
	{
		hx::Tween::linear(0.0, 1.0, static_cast<double>(hx::decFromHex(hex.substr(0, 2))) / baseMax),
		hx::Tween::linear(0.0, 1.0, static_cast<double>(hx::decFromHex(hex.substr(2, 2))) / baseMax),
		hx::Tween::linear(0.0, 1.0, static_cast<double>(hx::decFromHex(hex.substr(4, 2))) / baseMax)
	};
}

Rgb rgbFromValue(long int value)
{
	if (!hx::inRange(value, 0L, 16777215L))
		return{ 0.0, 0.0, 0.0 };
	const int base{ 256 };
	Rgb rgb{ 0.0, 0.0, 0.0 };

	int red{ value / (base * base) };
	value -= red * base * base;
	int green{ value / base };
	value -= green * base;
	int blue{ value };

	rgb.r = hx::Tween::linear(0.0, 1.0, static_cast<double>(red)   / (base - 1));
	rgb.g = hx::Tween::linear(0.0, 1.0, static_cast<double>(green) / (base - 1));
	rgb.b = hx::Tween::linear(0.0, 1.0, static_cast<double>(blue)  / (base - 1));

	return rgb;
}




Rgb trivialRandomColor()
{
	const unsigned int resolution{ 10000 };
	return{ static_cast<double>(rand() % (resolution + 1)) / resolution, static_cast<double>(rand() % (resolution + 1)) / resolution, static_cast<double>(rand() % (resolution + 1)) / resolution };
}

Rgb standardRandomColor()
{
	hx::Random random;
	return{ random.value(0.0, 1.0), random.value(0.0, 1.0), random.value(0.0, 1.0) };
}



	} // namespace Color
} // namespace hx