//ship.cpp
#include "ship.h"
#include "bullet.h"
#include "game.h"
using namespace sf;
using namespace std;



Ship::Ship() {};
bool Invader::direction;
float Invader::speed;
Player p1;

const Keyboard::Key controls[4] = {
    Keyboard::Space,   // Player1 UP
    Keyboard::Left,   // Player1 Down
    Keyboard::Right,  // Player2 UP
    Keyboard::Down // Player2 Down
};


Ship::Ship(IntRect ir) : Sprite() {
    _sprite = ir;
    spritesheet.loadFromFile("res/invaders_sheet.png");
    setTexture(spritesheet);
    setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos, bool i) : Ship(ir) {
    type = i;
    setOrigin(16, 16);
    setPosition(pos);
}

void Invader::Update(const float& dt) {
    Ship::Update(dt);

    move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

    if ((direction && getPosition().x > gameWidth - 220) ||
        (!direction && getPosition().x < 16)) {
        direction = !direction;
        for (int i = 0; i < ships.size(); ++i) {
            ships[i]->move(0, 24);
        }
    }
}
Player::Player(bool t) : Ship(IntRect(160, 32, 32, 32)) {
    type = t;
    setPosition({ gameHeight * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) {
    Ship::Update(dt);
    static float firetime = 0.0f;
    firetime -= dt;
    float direction = 0.0f;
    float pspeed = 40.f;

    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        direction--;
    }
    p1.move(direction * pspeed * dt, 0);

    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        direction++;
    }
    p1.move(direction * pspeed * dt, 0);

    static vector<Bullet*> bullets;

    Vector2f pos = getPosition();
    if (Keyboard::isKeyPressed(controls[0])) {
        bullets.push_back(new Bullet(pos, false));
    }
    for (const auto s : bullets) {
        s->Update(dt);
    }

    if (firetime <= 0 && Keyboard::isKeyPressed(controls[2])) {
        Bullet::Fire(getPosition(), false);
        firetime = 0.7f;
    }

}

