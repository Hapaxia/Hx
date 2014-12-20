//////////////////////////////////////////////////////////////////////////////
//
// Hx
// --
//
// Hx
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

#include <Hx/Plinth/Random.hpp>
#include <iostream>

int main()
{
	hx::Random random;

	std::cout << "unsigned int [0u, 100u]" << std::endl;
	for (int i{ 0 }; i < 5; ++i)
		std::cout << random.value(0u, 100u) << std::endl; // random unsigned integer in the range [0, 100]
	std::cout << "\nint [-50, 50]" << std::endl;
	for (int i{ 0 }; i < 5; ++i)
		std::cout << random.value(-50, 50) << std::endl; // random signed integer in the range [-50, 50]
	std::cout << "\ndouble [-0.5, 0.5]" << std::endl;
	for (int i{ 0 }; i < 5; ++i)
		std::cout << random.value(-0.5, 0.5) << std::endl; // random double in the range [-0.5, 0.5]

	return EXIT_SUCCESS;
}
