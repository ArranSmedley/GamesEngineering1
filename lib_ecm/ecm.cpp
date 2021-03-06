#include "ecm.h"

using namespace sf;
using namespace std;

// *** Entity class *** //

Entity::Entity() : rotation(0.f), alive(true), visible(true), forDeletion(false) {}

Entity::~Entity() = default;

void Entity::update(double dt) {
	for(const auto& component : components)
		component->update(dt);
}

void Entity::render() {
	for(const auto& component : components)
		component->render();
}

const Vector2f& Entity::getPosition() const {
	return position;
}

void Entity::setPosition(const Vector2f& position) {
	this->position = position;
}

float Entity::getRotation() const {
	return rotation;
}

void Entity::setRotation(const float rotation) {
	this->rotation = rotation;
}

bool Entity::isAlive() const {
	return alive;
}

void Entity::setAlive(const bool alive) {
	this->alive = alive;
}

bool Entity::isVisible() const {
	return visible;
}

void Entity::setVisible(const bool visible) {
	this->visible = visible;
}

bool Entity::isForDeletion() const {
	return forDeletion;
}

void Entity::setForDeletion() {
	this->forDeletion = true;
}

// *** Component class *** //

Component::Component(Entity* const parent) : parent(parent), forDeletion(false) {}

Component::~Component() = default;

bool Component::isForDeletion() const {
	return forDeletion;
}
