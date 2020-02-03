#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Player.h"
#include "Entity.h"


using namespace sf;
using namespace std;

Player player1;
const int gameWidth = 800;
const int gameHeight = 600;

void Load() {

    Vector2f position = Vector2f(200,200);
    player1.setPosition(position);


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

    player1.Render(window);

}




int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}