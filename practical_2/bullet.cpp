#include "Bullet.h"
#include "Game.h"
#include <iostream>
using namespace sf;
using namespace std;

Bullet::Bullet()
{
	setTexture(spritesheet);
	setTextureRect(IntRect(79, 42, 10, 10));
	_mode = false;
}

unsigned char Bullet::bulletPointer = 1;
Bullet Bullet::bullets[256];

void Bullet::_Update(const float& dt)
{
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32)
	{
		//off screen
		return;
	}
	else
	{
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const FloatRect boundingBox = getGlobalBounds();
		//cout << "Bullet moving" << endl;
		for (auto s : ships)
		{
			if (!_mode && s->type == true)
			{
				//player bullets don't collide with player
				continue;
			}
			if (_mode && s->type == false)
			{
				//invader bullets don't collide with other invaders
				continue;
			}
			if (!s->is_exploded() && s->getGlobalBounds().intersects(boundingBox))
			{
				//Explode the ship
				s->Explode(dt);
				cout << "Hit" << endl;
				//Warp bullet off screen
				setPosition(-100, -100);
				return;
			}
		}
	}
};

