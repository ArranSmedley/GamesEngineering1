#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::A,   // Player1 UP
    Keyboard::Z,   // Player1 Down
    Keyboard::Up,  // Player2 UP
    Keyboard::Down // Player2 Down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

Text text;
Font font;

Vector2f ballVelocity;
bool server = false;

CircleShape ball;
RectangleShape paddles[2];

Color color;

void Load() {

    for (auto& p : paddles) {
        p.setSize(paddleSize - Vector2f(3, 3));
        p.setOrigin(paddleSize / 2.f);
    }
    ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

    // Set size and origin of ball
    ball.setRadius(ballRadius - 3);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);
    // reset paddle position
    paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
    paddles[1].setPosition(800 - 10, 300);

    paddles[0].setFillColor(color.Red);

    paddles[1].setFillColor(color.Red);

    ball.setFillColor(color.Green);
    // reset Ball Position
    ball.setPosition(gameWidth / 2, gameHeight / 2);

    // Load font-face from res dir
    font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
    // Set text element to use font
    text.setFont(font);
    // set the character size to 24 pixels
    text.setCharacterSize(24);

}


void Reset() {

    for (auto& p : paddles) {
        p.setSize(paddleSize - Vector2f(3, 3));
        p.setOrigin(paddleSize / 2.f);
    }
    ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

    ball.setOrigin(ballRadius / 2, ballRadius / 2);

    paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
    paddles[1].setPosition(800 - 10, 300);

    // reset Ball Position
    ball.setPosition(gameWidth / 2, gameHeight / 2);

    // Update Score Text
    text.setString("1");
    // Keep Score Text Centered
    text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);

}


void Update(RenderWindow& window) {

    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();

    ball.move(ballVelocity * dt);

    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }
 

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

    // handle paddle movement
    float direction = 0.0f;
    float direction2 = 0.0f;
    if (Keyboard::isKeyPressed(controls[0])) {
        direction--;
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        direction++;
    }


    if (Keyboard::isKeyPressed(controls[2])) {
        direction2--;
    }
    if (Keyboard::isKeyPressed(controls[3])) {
        direction2++;
    }

    paddles[0].move(0, direction * paddleSpeed * dt);
    paddles[1].move(0, direction2 * paddleSpeed * dt);


    // check ball collision
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;
    if (by > gameHeight) { //bottom wall
      // bottom wall
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, -10);
    }
    else if (by < 0) { //top wall
   // top wall
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, 10);
    }
    else if (bx > gameWidth) {
        // right wall
        Reset();
    }
    else if (bx < 0) {
        // left wall
        Reset();
    }
    else if (
        //ball is inline or behind paddle
        bx < paddleSize.x + 10 &&
        //AND ball is below top edge of paddle
        by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
        //AND ball is above bottom edge of paddle
        by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
        ) {
        // bounce off left paddle

        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;

    }
    else if ( //ball is inline or behind paddle
        bx > gameWidth - paddleSize.x &&

        by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&

        by < paddles[1].getPosition().y + (paddleSize.y * 0.5)) {
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;

    
    }


}


void Render(RenderWindow& window) {
    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
    window.draw(text);
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