#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ship : public Sprite
{
protected:
	IntRect _sprite;
	//Default constructo is hidden
	Ship();
	bool _exploded;
	float _fadetime = 255;
public:
	bool type;
	//Constructor that takes a sprite
	explicit Ship(IntRect ir);
	//Pure virtual deconstructor
	virtual ~Ship() = 0;
	//Update, virtual so can be overridden
	virtual void Update(const float& dt);
	bool is_exploded() const { return _exploded; };
	virtual void Explode(const float& dt);
};

class Invader : public Ship
{
public:
	static bool direction;
	static float speed;
	Invader(IntRect ir, Vector2f pos, bool t);
	Invader();
	void Update(const float& dt) override;
};

class Player : public Ship
{
public:
	static float speed;
	Player(bool t);
	void Update(const float& dt) override;
};