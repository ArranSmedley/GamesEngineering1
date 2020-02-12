#include "Entity.h"

using namespace sf;
using namespace std;

void EntityManager::update(const float dt) const {
	for(auto i = 0; i < entities.size(); i++)
		entities[i]->update(dt);
}

void EntityManager::render() const {
	for(auto i = 0; i < entities.size(); i++)
		entities[i]->render();
}
