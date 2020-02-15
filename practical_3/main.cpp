#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Player.h"
#include "Entity.h"
#include "LevelSystem.h"


using namespace sf;
using namespace std;

Player player1;
const int gameWidth = 800;
const int gameHeight = 600;

void Load() {

    Vector2f position = Vector2f(200,200);
    player1.setPosition(position);

    ls::loadLevelFile("C:/Users/Arran/Documents/GitHub/GamesEngineering1/res/maze_2.txt");

    // Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            cout << ls::getTile({ x, y });
        }
        cout << endl;
    }

}


void Reset() {



}


void Update(RenderWindow& window) {

    static Clock clock;
    float dt = clock.restart().asSeconds();
    player1.Update(dt);


}


void Render(RenderWindow& window) {
    // Draw Everything
    ls::render(window);
    player1.Render(window);

}



int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "Tile Engine");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}