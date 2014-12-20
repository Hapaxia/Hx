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

#include <SFML/Graphics.hpp>
#include <Hx/Kairos/TimestepLite.hpp>
#include <Hx/Kairos/Stopwatch.hpp>
#include <Hx/Plinth.hpp>

int main()
{
	const std::string windowTitle{ "TimestepLite example" };
	sf::RenderWindow window(sf::VideoMode(800, 600), windowTitle, sf::Style::Default);
	window.setFramerateLimit(100); // max render rate is 100 fps (different to physics timestep)

	hx::Sfml::KeyMap keyMap;
	// WASD controls movement
	keyMap.addControl("up", sf::Keyboard::W);
	keyMap.addControl("down", sf::Keyboard::S);
	keyMap.addControl("left", sf::Keyboard::A);
	keyMap.addControl("right", sf::Keyboard::D);
	// toggles timestep values of 1/5 and 1/60. 1/5 is default state
	keyMap.addControl("toggle step value", sf::Keyboard::Space);

	sf::CircleShape circle(50.f);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setFillColor(sf::Colors::Salmon);
	circle.setOutlineColor(sf::Colors::Mint);
	circle.setOutlineThickness(-5.f);
	const float movementSpeed{ 250.f }; // pixels per second
	sf::Vector2f circlePosition{ window.getSize() / 2u };

	hx::Kairos::Stopwatch clock;
	hx::Kairos::TimestepLite timestep;
	timestep.setStep(1.0 / 5.0); // 'physics' timestep is one fifth of a second, or 5 frames per second.
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == keyMap.getKey("toggle step value"))
				{
					if (timestep.getStep() > 1.0 / 6.0)
						timestep.setStep(1.0 / 60.0);
					else
						timestep.setStep(1.0 / 5.0);
				}
			}
		}

		timestep.update(clock.restart().asSeconds()); // add frame time each cycle
		while (timestep.isTimeToIntegrate()) // this is true as long as there are unprocessed timesteps.
		{
			float dt{ static_cast<float>(timestep.getStep()) };

			if (sf::Keyboard::isKeyPressed(keyMap.getKey("up")))
				circlePosition.y -= movementSpeed * dt;
			if (sf::Keyboard::isKeyPressed(keyMap.getKey("down")))
				circlePosition.y += movementSpeed * dt;
			if (sf::Keyboard::isKeyPressed(keyMap.getKey("left")))
				circlePosition.x -= movementSpeed * dt;
			if (sf::Keyboard::isKeyPressed(keyMap.getKey("right")))
				circlePosition.x += movementSpeed * dt;

			// keep circle inside the window
			circlePosition.x = hx::clamp(circlePosition.x, circle.getRadius(), window.getSize().x - circle.getRadius());
			circlePosition.y = hx::clamp(circlePosition.y, circle.getRadius(), window.getSize().y - circle.getRadius());
		}
		circle.setPosition(circlePosition);

		// shows information in the window title bar
		std::string infoTitle{ windowTitle };
		if (timestep.getStep() > 1.0 / 6.0)
			infoTitle += " | Timestep: 5 FPS";
		else
			infoTitle += " | Timestep: 60 FPS";
		window.setTitle(infoTitle);

		window.clear();
		window.draw(circle);
		window.display();
	}

	return EXIT_SUCCESS;
}
