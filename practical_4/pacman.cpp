#include "pacman.h"
#include "scene.h"
#include "player.h"
#include "ghost.h"
#include "system_renderer.h"
#include "../lib/sfml/extlibs/headers/vulkan/vulkan_core.h"
#include "../practical_1/Main.cpp"

using namespace sf;
using namespace std;


const int Width = 800;

const int Height = 600;




RenderWindow window(VideoMode(Width, Height), "PAC-MAN");


void Scene::update(double dt) {
	static Clock clock;
	float dtime = clock.restart().asSeconds();

	dt = dtime;

	_ents.update(dt);
}

void Scene::render() { _ents.render(window); }

void MenuScene::update(double dt) {
	Scene::update(dt);
	text.setString("Almost Pacman");
}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void MenuScene::load() {
	Text text;
	Font font;

	// Load font-face from res dir
	font.loadFromFile("C:/Users/Arran/Documents/GitHub/GamesEngineering1/resJungle-Land.ttf");
	// Set text element to use font
	text.setFont(font);
	// set the character size to 24 pixels
	text.setCharacterSize(24);
	text.setString("PLAY");

	text.setPosition((Width * .5f) - (text.getLocalBounds().width * .5f), 0);

	text.setColor(color.Blue);

}


void GameScene::load() {

	auto player = new Player();

		_ents.list.push_back(player);

		for (int i = 0; i < 4; i++)
		{
			auto ghost = new Ghost();
			_ents.list.push_back(ghost);
		}
	
	

}

void GameScene::update(double dt) {
	Scene::update(dt);
}

void  GameScene::render() {
	Renderer::queue(&text);
	Scene::render();
}