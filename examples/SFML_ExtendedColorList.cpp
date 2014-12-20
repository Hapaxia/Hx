#include "Hx/Plinth/SFML/ExtendedColorList.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	const sf::Vector2f rectSize{ 150, 100 };
	const sf::Vector2f startPosition{ 100, 100 };
	const unsigned int rectsPerRow{ 4 };

	std::vector<sf::Color> colors{
		sf::Colors::VeryDarkPeach,
		sf::Colors::DarkPeach,
		sf::Colors::Peach,
		sf::Colors::LightPeach,
		sf::Colors::VeryDarkSalmon,
		sf::Colors::DarkSalmon,
		sf::Colors::Salmon,
		sf::Colors::LightSalmon,
		sf::Colors::VeryDarkPink,
		sf::Colors::DarkPink,
		sf::Colors::Pink,
		sf::Colors::LightPink,
		sf::Colors::VeryDarkHotPink,
		sf::Colors::DarkHotPink,
		sf::Colors::HotPink,
		sf::Colors::LightHotPink,
	};

	std::vector<sf::RectangleShape> rects;
	for (auto& color : colors)
	{
		rects.push_back(sf::RectangleShape());
		rects.back().setFillColor(color);
		rects.back().setSize(rectSize);
	}
	for (unsigned int i{ 0 }; i < rects.size(); ++i)
		rects[i].setPosition((i % rectsPerRow) * rectSize.x + startPosition.x, (i / rectsPerRow) * rectSize.y + startPosition.y);

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Extended Colour List", sf::Style::Default);
	window.setFramerateLimit(10);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		window.clear();
		for (auto& rect : rects)
			window.draw(rect);
		window.display();
	}

	return EXIT_SUCCESS;
}
