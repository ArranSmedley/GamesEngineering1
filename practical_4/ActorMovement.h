#pragma once
#include "ecm.h"
#include "LevelSystem.h"

class ActorMovementComponent : public Component {
protected:
	float speed;

	bool validMove(const sf::Vector2f& position);

public:
	ActorMovementComponent() = delete;
	explicit ActorMovementComponent(Entity* parent);

	float getSpeed() const;
	void setSpeed(float speed);

	void move(const sf::Vector2f& position);
	void move(float x, float y);

	void update(double dt) override;
	void render() override;
};

class PlayerMovementComponent : public ActorMovementComponent {
public:
	PlayerMovementComponent() = delete;
	explicit PlayerMovementComponent(Entity* parent);

	void update(double dt) override;
};

class GhostMovementComponent : public ActorMovementComponent {
protected:
	sf::Vector2f direction;
	static ls::Tile nextTile(sf::Vector2f position, sf::Vector2i direction);
	static int count;
	enum State {
		DEADEND,
		ROAMING,
		ROTATING,
		ROTATED
	};

	State state;

public:
	GhostMovementComponent() = delete;
	explicit GhostMovementComponent(Entity* parent);

	void update(double dt) override;
};
