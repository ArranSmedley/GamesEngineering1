// remove console window in release build
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <SFML/Graphics.hpp>
#include <LevelSystem.h>
#include "main.h"
#include "system-renderer.h"
#include "pacman.h"

using namespace std;
using namespace sf;

Font font;
int gameWidth = 800;
int gameHeight = 600;

void load() {
	font.loadFromFile("C:/Users/Arran/Documents/GitHub/GamesEngineering1/res/Jungle-Land.ttf");

	// load scenes
	menuScene.reset(new MenuScene());
	gameScene.reset(new GameScene());

	gameScene->load();
	menuScene->load();

	// start on menu
	activeScene = menuScene;
}

void reset() {
	// reset rand seed
	srand(time(nullptr));
}

void update() {
	static Clock clock;
	const float dt = clock.restart().asSeconds();
	RenderWindow& window = renderer::getWindow();

	Event event;
	while(window.pollEvent(event)) {
		if (event.type == Event::Closed)
			window.close();
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
		window.close();

	activeScene->update(dt);
}

void render() {
	activeScene->render();
	renderer::render();
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Pacman", Style::Titlebar | Style::Close);
	renderer::initialise(window);

	load();
	reset();

	while(window.isOpen()) {
		window.clear();
		update();
		render();
		window.display();
	}

	renderer::shutdown();

	return 0;
}