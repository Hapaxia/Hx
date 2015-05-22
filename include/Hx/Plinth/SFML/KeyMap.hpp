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

#ifndef HX_PLINTH_SFML_KEYMAP_HPP
#define HX_PLINTH_SFML_KEYMAP_HPP

#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <string>
#include <algorithm> // for remove_if

namespace hx
{
	namespace Sfml
	{

class KeyMap
{
public:
	KeyMap();
	void addControl(const std::string& name, const sf::Keyboard::Key& key);
	void addControl(const sf::Keyboard::Key& key);
	void removeControl(unsigned int controlNumber);
	void removeControl(const std::string& name);
	sf::Keyboard::Key getKey(unsigned int controlNumber);
	sf::Keyboard::Key getKey(const std::string& name);
	void setKey(unsigned int controlNumber, const sf::Keyboard::Key& key);
	std::string getName(unsigned int controlNumber);
	unsigned int getSize();

private:
	struct Control
	{
		std::string name;
		sf::Keyboard::Key key;
	};
	std::vector<Control> m_controls;

	bool controlNumberIsValid(unsigned int controlNumber);
};

	} // namespace Sfml
} // namespace hx
#endif // HX_PLINTH_SFML_KEYMAP_HPP