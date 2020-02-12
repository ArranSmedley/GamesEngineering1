#pragma once

// window settings
extern int gameWidth;
extern int gameHeight;

constexpr float tileSize = 25.f;

// player settings
constexpr float playerSize = 24.f;
constexpr float playerSpeed = 200.f;
const sf::Color playerColor = sf::Color(255, 255, 0);

// ghost settings
constexpr int ghostCount = 4;
constexpr float ghostSize = 24.f;
constexpr float ghostSpeed = 200.f;

const sf::Color ghostColors[] {
	sf::Color(0xff, 0x00, 0x00), // red
	sf::Color(0x00, 0x00, 0xff), // blue
	sf::Color(0xff, 0x69, 0xb4), // pink
	sf::Color(0xff, 0xa5, 0x00)  // orange
};

// controls settings
const sf::Keyboard::Key playerUp = sf::Keyboard::Up;
const sf::Keyboard::Key playerLeft = sf::Keyboard::Left;
const sf::Keyboard::Key playerDown = sf::Keyboard::Down;
const sf::Keyboard::Key playerRight = sf::Keyboard::Right;

// global resources
extern sf::Font font;

constexpr float bigPoints = 1.f;
constexpr float smallPoints = .5f;
constexpr float bigSize = 20.f;
constexpr float smallSize = 10.f;
const sf::Color bigColor = sf::Color::Cyan;
const sf::Color smallColor = sf::Color::White;
