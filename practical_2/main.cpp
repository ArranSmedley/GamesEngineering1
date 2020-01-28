#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Game.h"
#include "Ship.h"
#include "Bullet.h"

using namespace sf;
using namespace std;

Texture spritesheet;
Sprite invader;
vector<Ship*> ships;
//Player player;

void Load()
{
	if (!spritesheet.loadFromFile("res/invaders_sheet.png"))
	{
		cerr << "Failed to load spritesheet!" << endl;
	}

	/*Invader* inv = new Invader(IntRect(0, 0, 32, 32), { 100, 100 });
	ships.push_back(inv);*/

	for (int r = 0; r < invaders_rows; ++r)
	{
		auto rect = IntRect(0, 0, 32, 32);
		for (int c = 0; c < invaders_columns; ++c)
		{
			Vector2f position = Vector2f(32 * c + 10, 32 * r + 10);
			auto inv = new Invader(rect, position, false);
			ships.push_back(inv);
		}
	}

	//Bullet::Load();

	auto player = new Player(true);
	ships.push_back(player);
}

void Update(RenderWindow& window)
{
	//Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();

	//Check and consume events
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	//Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}

	for (auto& s : ships)
	{
		s->Update(dt);
	};

	Bullet::Update(dt);

	//player.Update(dt);
}

void Render(RenderWindow& window)
{
	//Draw Everything
	for (const auto s : ships)
	{
		window.draw(*s);
	}

	Bullet::Render(window);

	//window.draw(player);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Invader");
	Load();
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

	return 0;
}