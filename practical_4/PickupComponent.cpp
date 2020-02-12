#include <SFML/System.hpp>
#include "ActorMovement.h"
#include "PickupComponent.h"
#include "pacman.h"
#include "main.h"

using namespace std;
using namespace sf;

PickupComponent::PickupComponent(Entity* parent, const bool big) : Component(parent), points(big ? bigPoints : smallPoints) {}

void PickupComponent::update(double dt) {
	for(const auto& entity : gameScene->getEntities()) {
		if(length(parent->getPosition() - entity->getPosition()) < 25.f) {
			const auto entityMovementComponent = entity->getComponent<PlayerMovementComponent>();

			if (entityMovementComponent != nullptr ) {
				entityMovementComponent->setSpeed(entityMovementComponent->getSpeed() + points);
				parent->setForDeletion();
				break;
			}
		}
	}
}

void PickupComponent::render() {}

