#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "ecm.h"

struct EntityManager {
	std::vector<std::shared_ptr<Entity>> entities;
	void update(float dt) const;
	void render() const;
};
