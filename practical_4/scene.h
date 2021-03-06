#pragma once
#include <memory>
#include <vector>
#include "Entity.h"

class Scene {
public:
	Scene() = default;

	virtual ~Scene() = default;
	virtual void update(float dt);
	virtual void render();
	virtual void load() = 0;
	std::vector<std::shared_ptr<Entity>> &getEntities();

protected:
	EntityManager entityManager;
};
