#include "ShapeComponent.h"
#include "system-renderer.h"

using namespace std;
using namespace sf;

ShapeComponent::ShapeComponent(Entity* parent) : Component(parent), shape(make_shared<CircleShape>()) {}

void ShapeComponent::update(double dt) {
	shape->setPosition(parent->getPosition());
}

void ShapeComponent::render() {
	renderer::queue(shape.get());
}

Shape& ShapeComponent::getShape() const {
	return *shape;
}
