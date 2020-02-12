#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Player.h"
#include "Entity.h"
#include "ghost.h"
#include "system_renderer.h"
#include "scene.h"
#include "pacman.h"


using namespace sf;
using namespace std;


EntityManager em;
Player player1;

vector<Entity*> ghosts;

const int gameWidth = 800;
const int gameHeight = 600;

void Load() {

    gameScene.reset(new GameScene());
    menuScene.reset(new MenuScene());
    gameScene->load();
    menuScene->load();
    // Start at main menu
    activeScene = menuScene;



}


void Reset() {



}


void Update(RenderWindow& window) {

    static Clock clock;
    float dt = clock.restart().asSeconds();
    activeScene->update(dt);



}


void Render(RenderWindow& window) {
    activeScene->render();
    // flush to screen
    Renderer::render();
}




int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PAC-MAN");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}