#include "system-renderer.h"
#include <queue>

using namespace std;
using namespace sf;

static queue<const Drawable*> drawables;
static RenderWindow* renderWindow;

void renderer::initialise(sf::RenderWindow& window) {
	renderWindow = &window;
}

RenderWindow& renderer::getWindow() {
	return *renderWindow;
}

void renderer::shutdown() {
	while(!drawables.empty())
		drawables.pop();
}

void renderer::update(const double& dt) {}

void renderer::render() {
	if(renderWindow == nullptr)
		throw "No render window set";
	
	while(!drawables.empty()) {
		renderWindow->draw(*drawables.front());
		drawables.pop();
	}
}

void renderer::queue(const Drawable* drawable) {
	drawables.push(drawable);
}