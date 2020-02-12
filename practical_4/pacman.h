#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Scene.h"

// pacman scenes
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene {
private:
	sf::Text text;

public:
	MenuScene() = default;
	void update(float dt) override;
	void render() override;
	void load() override;
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;

	std::shared_ptr<Entity> player;
	std::vector<std::shared_ptr<Entity>> ghosts;
	std::vector<std::shared_ptr<Entity>> nibbles;

	void respawn();
	static std::shared_ptr<Entity> makeNibble(const sf::Vector2ul& coordinates, bool big);

public:
	GameScene() = default;
	void update(float dt) override;
	void render() override;
	void load() override;
};
