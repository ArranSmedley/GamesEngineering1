#include "Ship.h"
#include "Game.h"
#include "Bullet.h"
#include <iostream>

using namespace sf;
using namespace std;

//Ship Class
Ship::Ship() { }

Ship::Ship(IntRect ir) : Sprite()
{
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
	_exploded = false;
}

void Ship::Update(const float& dt) { }

Ship::~Ship() = default;

void Ship::Explode(const float& dt)
{
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
};

//Invader Class
bool Invader::direction = false;
float Invader::speed = 24;

Invader::Invader() : Ship() { }

Invader::Invader(IntRect ir, Vector2f pos, bool t) : Ship(ir)
{
	setOrigin(16, 16);
	setPosition(pos);
	type = t;
}

void Invader::Update(const float& dt)
{
	Ship::Update(dt);
	static float firetime = 0.0f;
	firetime -= dt;

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16))
	{
		direction = !direction;
		for (auto s : ships)
		{
			if (s->type == false)
			{
				s->move(0, 24);
			}
		}
	}

	if (is_exploded() && _fadetime > 0)
	{
		_fadetime--;
		setColor(Color(255, 255, 255, _fadetime));
	}

	if (firetime <= 0 && rand() % 100 == 0 && !is_exploded())
	{
		Bullet::Fire(getPosition(), true);
		firetime = 4.0f + (rand() % 60);
		cout << "Enemy Fired" << endl;
	}
}

//Player class
float Player::speed = 200;

Player::Player(bool t) : Ship(IntRect(160, 32, 32, 32))
{
	setPosition({ gameWidth * 0.5f, gameHeight - 32.0f });
	type = t;
}

void Player::Update(const float& dt)
{
	Ship::Update(dt);
	//static vector<Bullet*> bullets;
	static float firetime = 0.0f;
	firetime -= dt;

	for (auto s : ships)
	{
		if (s->type == true)
		{


			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				s->move(-speed * dt, 0);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D))
			{
				s->move(speed * dt, 0);
			}

			if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space) && !is_exploded())
			{
				Bullet::Fire(getPosition(), false);
				firetime = 0.7f;
				cout << "Fired" << endl;
			}

			if (s->getPosition().x < 0)
			{
				s->setPosition(0, s->getPosition().y);
			}
			else if (s->getPosition().x > gameWidth - 32)
			{
				s->setPosition(gameWidth - 32, s->getPosition().y);
			}

			if (is_exploded() && _fadetime > 0)
			{
				_fadetime--;
				setColor(Color(255, 255, 255, _fadetime));
			}
		}
	}
}