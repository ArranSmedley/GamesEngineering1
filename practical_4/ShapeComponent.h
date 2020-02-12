#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "ecm.h"

class ShapeComponent : public Component {
protected:
	std::shared_ptr<sf::Shape> shape;

public:
	ShapeComponent() = delete;
	explicit ShapeComponent(Entity* parent);

	void update(double dt) override;
	void render() override;

	sf::Shape& getShape() const;

	template<typename T, typename... Targs> void setShape(Targs... params) {
		shape.reset(new T(params...));
	}
};
