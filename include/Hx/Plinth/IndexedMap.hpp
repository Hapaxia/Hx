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

#ifndef HX_PLINTH_INDEXEDMAP_HPP
#define HX_PLINTH_INDEXEDMAP_HPP

#include <vector>
#include <string>
#include <algorithm> // for remove_if

namespace hx
{

template <class keyT, class T>
class IndexedMap
{
public:
	IndexedMap();
	void add(const keyT& key, const T& value);
	void add(const T& value);
	void remove(const keyT& key);
	void remove(unsigned int index);
	T get(const keyT& key);
	T get(unsigned int index);
	T& access(const keyT& key);
	T& access(unsigned int index);
	bool valid(const keyT& key);
	bool valid(unsigned int index);
	void set(const keyT& key, const T& value);
	void set(unsigned int index, const T& value);
	keyT getKey(unsigned int index);
	unsigned int getSize();
	void clear();

private:
	struct Element
	{
		keyT key;
		T value;
	};
	std::vector<Element> m_elements;

	bool indexIsValid(unsigned int index);
};

#include "IndexedMap.inl"

} // namespace hx
#endif // HX_PLINTH_INDEXEDMAP_HPP
