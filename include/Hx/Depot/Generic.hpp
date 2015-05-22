//////////////////////////////////////////////////////////////////////////////
//
// Hx
// --
//
// Depot
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

#ifndef HX_DEPOT_GENERIC_HPP
#define HX_DEPOT_GENERIC_HPP

#include <vector>
#include <string>
#include <fstream>
#include <memory>

namespace hx
{
	namespace Depot
	{

void loadTextFile(std::vector<std::string>& lines, const std::string& filename, bool stripTrailingNewlines = true);
unsigned int loadBinaryFile(char* data, const std::string& filename); // returns size of data memory block
unsigned int loadBinaryFile(std::unique_ptr<char[]>& data, const std::string& filename); // returns size of data memory block

void saveTextFile(const std::vector<std::string>& lines, const std::string& filename, bool addNewlines = true);
void saveBinaryFile(const char* data, const std::string& filename, unsigned int size);
void saveBinaryFile(const std::unique_ptr<char[]>& data, const std::string& filename, unsigned int size);

	} // namespace Depot
} // namespace hx
#endif // HX_DEPOT_GENERIC_HPP