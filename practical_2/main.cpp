#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "ship.h"
#include "game.h"

using namespace sf;
using namespace std;

//Main.cpp
sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship*> ships;
Player p1;

void Load() {
    
   


    for (int r = 0; r < invaders_rows; ++r) {
        auto rect = IntRect(0, 0, 32, 32);
        for (int c = 0; c < invaders_columns; ++c) {
            Vector2f position = Vector2f(32 * c + 10, 32 * r + 10);
            auto inv = new Invader(rect, position, false);
            ships.push_back(inv);
        }
    }
  
    Invader::speed = 40.f;


}


void Update(RenderWindow& window) {

    static Clock clock;
    float dt = clock.restart().asSeconds();
  

    for (auto& s : ships) {
        s->Update(dt);
    }



}

void Render(sf::RenderWindow& window) {

    window.draw(p1);
    
    for (const auto s : ships) {
        window.draw(*s);
    }

}

int main() {
    RenderWindow window(VideoMode(gameHeight, gameWidth), "SPACE INVADERS");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}
