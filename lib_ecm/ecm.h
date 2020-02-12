#pragma once
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>
#include "maths.h"

class Component;

class Entity {
protected:
	std::vector<std::shared_ptr<Component>> components;

	sf::Vector2f position;
	float rotation;

	bool alive; // should be updated
	bool visible; // should be rendered
	bool forDeletion; // should be deleted

public:
	Entity();
	virtual ~Entity();

	virtual void update(double dt);
	virtual void render();

	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& position);

	float getRotation() const;
	void setRotation(float rotation);

	bool isAlive() const;
	void setAlive(bool alive);

	bool isVisible() const;
	void setVisible(bool visible);

	bool isForDeletion() const;
	void setForDeletion();

	template<typename T, typename... Targs> std::shared_ptr<T> addComponent(Targs... params) {
		static_assert(std::is_base_of<Component, T>::value, "must be a component");
		std::shared_ptr<T> component = std::make_shared<T>(this, params...);
		components.push_back(component);
		return component;
	}

	template<typename T> std::shared_ptr<T> getComponent() {
		static_assert(std::is_base_of<Component, T>::value, "must be a component");
		for (const auto& component : components) {
			std::shared_ptr<T> castComponent = std::dynamic_pointer_cast<T>(component);
			if (castComponent && castComponent.use_count() != 0)
				return castComponent;
		}
		return nullptr;
	}

	template<typename T> std::vector<std::shared_ptr<T>> getAllComponents() {
		static_assert(std::is_base_of<Component, T>::value, "must be a component");
		std::vector<std::shared_ptr<T>> components;
		for (const auto& component : this->components) {
			std::shared_ptr<T> castComponent = std::dynamic_pointer_cast<T>(component);
			if (castComponent && castComponent.use_count() != 0)
				components.push_back(castComponent);
		}
		return components;
	}
};

class Component {
protected:
	Entity* const parent;
	bool forDeletion; // should be deleted
	explicit Component(Entity *const parent);

public:
	Component() = delete;
	virtual ~Component();

	bool isForDeletion() const;

	virtual void update(double dt) = 0;
	virtual void render() = 0;
};
