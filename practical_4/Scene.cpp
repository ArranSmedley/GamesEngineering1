#include "Scene.h"

using namespace std;

void Scene::update(float dt) {
	entityManager.update(dt);
	auto deleteIterator = entityManager.entities.begin();
	while (deleteIterator != entityManager.entities.end()) {
		if ((*deleteIterator)->isForDeletion())
			deleteIterator = entityManager.entities.erase(deleteIterator);
		else
			++deleteIterator;
	}
}

void Scene::render() {
	entityManager.render();
}

vector<shared_ptr<Entity>>& Scene::getEntities() {
	return entityManager.entities;
}
