#include "ghost.h"
#include <random>
using namespace sf;
using namespace std;


void Ghost::Update(double dt) {
	//Move in four directions based on keys
	float direction = 0.0f;
	float direction2 = 0.0f;
	const int gameWidth = 800;
	const int gameHeight = 600;


	
	Vector2f position = Vector2f(rand() % 200 * dt, rand() % 200 * dt);

	move(position);


	//if (Ghost::getPosition().x > gameWidth || Ghost::getPosition().x < gameWidth)
	//{
	//	position.x--;
	//}
	//else
	//{

	//	move(position);
	//}

	//if (Ghost::getPosition().y > gameHeight || Ghost::getPosition().y < gameHeight)
	//{
	//	position.y--;
	//}
	//else {

	//	move(position);
	//}


	/*move(0, direction * _speed * dt));
	move(0, direction * _speed * dt);
	*/


	Entity::Update(dt);
}

Ghost::Ghost()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Blue);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Ghost::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}