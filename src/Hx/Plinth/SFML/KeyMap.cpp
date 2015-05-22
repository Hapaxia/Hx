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

#include "KeyMap.hpp"

namespace hx
{
	namespace Sfml
	{

KeyMap::KeyMap()
{
}

void KeyMap::addControl(const std::string& name, const sf::Keyboard::Key& key)
{
	Control control{ name, key };
	m_controls.push_back(control);
}

void KeyMap::addControl(const sf::Keyboard::Key& key)
{
	addControl("", key);
}

void KeyMap::removeControl(unsigned int controlNumber)
{
	if (controlNumberIsValid(controlNumber))
		m_controls.erase(m_controls.begin() + controlNumber);
}

void KeyMap::removeControl(const std::string& name)
{
	m_controls.erase(std::remove_if(m_controls.begin(), m_controls.end(),
		[&name](const Control& control)
		{
			return control.name == name;
		}),
		m_controls.end());
}

sf::Keyboard::Key KeyMap::getKey(unsigned int controlNumber)
{
	if (controlNumberIsValid(controlNumber))
		return m_controls[controlNumber].key;
	else
		return sf::Keyboard::Unknown;
}

sf::Keyboard::Key KeyMap::getKey(const std::string& name)
{
	sf::Keyboard::Key key{ sf::Keyboard::Unknown };
	for (auto& control : m_controls)
	{
		if (control.name == name)
			key = control.key;
	}
	return key;
}

void KeyMap::setKey(unsigned int controlNumber, const sf::Keyboard::Key& key)
{
	if (controlNumberIsValid(controlNumber))
		m_controls[controlNumber].key = key;
}

std::string KeyMap::getName(unsigned int controlNumber)
{
	if (controlNumberIsValid(controlNumber))
		return m_controls[controlNumber].name;
	else
		return "";
}

unsigned int KeyMap::getSize()
{
	return m_controls.size();
}



// PRIVATE

bool KeyMap::controlNumberIsValid(unsigned int controlNumber)
{
	return controlNumber < m_controls.size();
}

	} // namespace Sfml
} // namespace hx