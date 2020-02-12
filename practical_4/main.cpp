#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Player.h"
#include "Entity.h"
#include "ghost.h"
#include "system_renderer.h"


using namespace sf;
using namespace std;


EntityManager em;
Player player1;

vector<Entity*> ghosts;

const int gameWidth = 800;
const int gameHeight = 600;

void Load() {

    Vector2f position = Vector2f(200, 200);


  //  em.list.push_back(p1);

    for (const auto s : ghosts)
    {
        s->setPosition(position);
    }




}


void Reset() {



}


void Update(RenderWindow& window) {

    static Clock clock;
    float dt = clock.restart().asSeconds();

    player1.Update(dt);
    for(const auto s : ghosts)
    {
        s->Update(dt);
    }



}


void Render(RenderWindow& window) {
    // Draw Everything

    player1.Render(window);
    for (const auto s : ghosts)
    {
       s->Render(window);
    }

    Renderer::queue();
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