#include <LevelSystem.h>
#include "ActorMovement.h"
#include "main.h"

using namespace std;
using namespace sf;

// *** ActorMovementComponent class *** //

ActorMovementComponent::ActorMovementComponent(Entity* parent) : Component(parent), speed(100.f) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& position) {
	return LevelSystem::getTileAt(position) != LevelSystem::WALL;
}

float ActorMovementComponent::getSpeed() const {
	return speed;
}

void ActorMovementComponent::setSpeed(float speed) {
	this->speed = speed;
}

void ActorMovementComponent::move(const sf::Vector2f& position) {
	const auto newPosition = parent->getPosition() + position;
	if(validMove(newPosition))
		parent->setPosition(newPosition);
}

void ActorMovementComponent::move(const float x, const float y) {
	move({ x, y });
}

void ActorMovementComponent::update(const double dt) {}

void ActorMovementComponent::render() {}

// *** PlayerMovementComponent class *** //

PlayerMovementComponent::PlayerMovementComponent(Entity* parent) : ActorMovementComponent(parent) {}

void PlayerMovementComponent::update(const double dt) {
	auto moveHorizontal = 0.f;
	auto moveVertical = 0.f;

	const auto halfSize = playerSize * .5f;

	const auto position = parent->getPosition();

	if(Keyboard::isKeyPressed(playerUp) && position.y - halfSize > 0)
		moveVertical += -1;
	if(Keyboard::isKeyPressed(playerLeft) && position.x - halfSize > 0)
		moveHorizontal += -1;
	if(Keyboard::isKeyPressed(playerDown) && position.y + halfSize < gameHeight)
		moveVertical += 1;
	if(Keyboard::isKeyPressed(playerRight) && position.x + halfSize < gameWidth)
		moveHorizontal += 1;

	move({ speed * float(dt) * moveHorizontal, speed * float(dt) * moveVertical });
}

// *** GhostMovementComponent class *** 

GhostMovementComponent::GhostMovementComponent(Entity* parent) : ActorMovementComponent(parent), direction({ 1, 0 }), state(ROAMING) {}
int GhostMovementComponent::count = 0;
static const Vector2i directions[] = {
	{ 1, 0 },
	{ -1, 0 },
	{ 0, 1 },
	{ 0, -1 }
};

const string states[] = {
	"DEADEND",
	"ROAMING",
	"ROTATING",
	"ROTATED"
};

void GhostMovementComponent::update(const double dt) {
	// working variables
	const auto movement = float(dt * speed);
	const auto position = parent->getPosition();
	auto newPosition = position + Vector2f(direction) * movement;
	const auto reverseDirection = -Vector2i(direction);
	auto newDirection = directions[rand() % 4];

	switch(state) {
		case ROAMING:
			if(ls::getTileAt(position) == ls::WAYPOINT || ls::getTileAt(newPosition) == LevelSystem::WALL)
				state = ROTATING;
			else
				move(direction * movement);
			break;
		case ROTATING:
			while (newDirection == reverseDirection || nextTile(position, newDirection) == LevelSystem::WALL) {
				newDirection = directions[rand() % 4];
			}
			direction = Vector2f(newDirection);
			state = ROTATED;
			break;
		case ROTATED:
			if (ls::getTileAt(position) != ls::WAYPOINT)
				state = ROAMING;
			move(direction * movement);
			break;
		case DEADEND:
			break;
		default:
			break;
	}
}

LevelSystem::Tile GhostMovementComponent::nextTile(Vector2f position, Vector2i direction) {
	return ls::getTileAt(position + ls::getTileSize() * Vector2f(direction));
}
