#include <SFML/Graphics.hpp>
#include <memory>
#include <LevelSystem.h>
#include "pacman.h"
#include "ecm.h"
#include "ShapeComponent.h"
#include "main.h"
#include "system-renderer.h"
#include "ActorMovement.h"
#include "PickupComponent.h"

using namespace std;
using namespace sf;

shared_ptr<Scene> menuScene;
shared_ptr<Scene> gameScene;
shared_ptr<Scene> activeScene;

void MenuScene::update(float dt) {
	Scene::update(dt);

	// switch to game if space is pressed
	if(Keyboard::isKeyPressed(Keyboard::Space))
		activeScene = gameScene;
}

void MenuScene::render() {
	Scene::render();
	renderer::queue(&text);
}

void MenuScene::load() {
	text.setFont(font);
	text.setCharacterSize(50);
	text.setString("Pacman by Arran Smedley");

	const auto textRect = text.getGlobalBounds();
	text.setOrigin(textRect.width * .5f, textRect.height * .5f);
	text.setPosition(gameWidth * .5f, gameHeight * .5f);
}

void GameScene::update(float dt) {
	Scene::update(dt);

	// switch to menu when enter is pressed
	if(Keyboard::isKeyPressed(Keyboard::Return))
		activeScene = menuScene;

	// detect pacman/ghost collision
	for(const auto& ghost : ghosts)
		if(length(ghost->getPosition() - player->getPosition()) < playerSize * .5f + ghostSize * .5f)
			respawn();
}

void GameScene::render() {
	Scene::render();
	LevelSystem::render(renderer::getWindow());
}

void GameScene::load() {
	entityManager.entities.clear();
	ls::setColor(ls::EMPTY, Color::Black);
	ls::setColor(ls::WALL, { 0x41, 0x69, 0xe1 });

	LevelSystem::setOffset({ tileSize * .5f, tileSize * .5f });
	LevelSystem::loadLevelFile("C:/Users/Arran/Documents/GitHub/GamesEngineering1/res/tile-maps/pacman.map", tileSize);
	gameWidth = float(ls::getWidth()) * ls::getTileSize();
	gameHeight = float(ls::getHeight()) * ls::getTileSize();
	renderer::getWindow().create(VideoMode(gameWidth, gameHeight), "Pacman", Style::Titlebar | Style::Close);

	// create the player game object
	player = make_shared<Entity>();

	auto playerShape = player->addComponent<ShapeComponent>();
	playerShape->setShape<CircleShape>(playerSize * .5f);
	playerShape->getShape().setFillColor(playerColor);
	playerShape->getShape().setOrigin({ playerSize * .5f, playerSize * .5f });

	auto playerController = player->addComponent<PlayerMovementComponent>();
	playerController->setSpeed(playerSpeed);

	entityManager.entities.push_back(player);

	// create 4 ghost game objects
	ghosts.clear();
	for(auto i = 0; i < ghostCount; i++) {
		auto ghost = make_shared<Entity>();

		auto ghostShape = ghost->addComponent<ShapeComponent>();
		ghostShape->setShape<CircleShape>(ghostSize * .5f);
		ghostShape->getShape().setFillColor(ghostColors[i]);
		ghostShape->getShape().setOrigin({ ghostSize * .5f, ghostSize * .5f });

		auto ghostController = ghost->addComponent<GhostMovementComponent>();
		ghostController->setSpeed(ghostSpeed);

		entityManager.entities.push_back(ghost);
		ghosts.push_back(ghost);
	}

	respawn();
}

void GameScene::respawn() {
	entityManager.entities[0]->setPosition(ls::getStartPosition());

	auto ghostSpawns = ls::findTiles(ls::ENEMY);

	for(auto i = 1; i < entityManager.entities.size(); i++) {
		entityManager.entities[i]->setPosition(ls::getTilePosition(ghostSpawns[rand() % ghostSpawns.size()]));
	}
	
	for(auto nibble : nibbles) {
		
			nibble->setForDeletion();
			nibble.reset();
		
	}

	nibbles.clear();

	// white nibbles
	auto locations = ls::findTiles(ls::EMPTY);
	for(const auto& coordinates : locations) {
		const auto nibble = makeNibble(coordinates, false);
		entityManager.entities.push_back(nibble);
		nibbles.push_back(nibble);
	}

	// blue nibbles
	locations = ls::findTiles(ls::WAYPOINT);
	for(const auto& coordinates : locations) {
		const auto nibble = makeNibble(coordinates, true);
		entityManager.entities.push_back(nibble);
		nibbles.push_back(nibble);
	}
}

std::shared_ptr<Entity> GameScene::makeNibble(const sf::Vector2ul& coordinates, bool big) {
	auto nibble = make_shared<Entity>();

	auto shape = nibble->addComponent<ShapeComponent>();
	shape->setShape<CircleShape>(big ? bigSize * .5f : smallSize * .5f);
	shape->getShape().setFillColor(big ? bigColor : smallColor);
	shape->getShape().setOrigin(big ? Vector2f(bigSize * .5f, bigSize * .5f) : Vector2f(smallSize * .5f, smallSize * .5f));

	nibble->addComponent<PickupComponent>(big);
	nibble->setPosition(ls::getTilePosition(coordinates));

	return nibble;
}
