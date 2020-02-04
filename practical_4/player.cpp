#include "player.h"
using namespace sf;
using namespace std;


void Player::Update(double dt) {
	//Move in four directions based on keys
	float direction = 0.0f;
	float direction2 = 0.0f;

	Vector2f position = Vector2f(_speed * dt, 0);

	Vector2f position2 = Vector2f(-_speed * dt, 0);

	Vector2f position3 = Vector2f(0, _speed * dt);
	Vector2f position4 = Vector2f(0, -_speed * dt);
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		move(position);

	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		move(position2);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		move(position3);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		move(position4);
	}

	/*move(0, direction * _speed * dt));
	move(0, direction * _speed * dt);
	*/


	Entity::Update(dt);
}

Player::Player()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}