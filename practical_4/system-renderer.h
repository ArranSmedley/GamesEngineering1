#pragma once

#include <SFML/Graphics.hpp>

namespace renderer {
	void initialise(sf::RenderWindow &window);
	sf::RenderWindow &getWindow();

	void shutdown();
	void update(const double &dt);
	void queue(const sf::Drawable *drawable);
	void render();
}