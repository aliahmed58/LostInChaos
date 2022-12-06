#include "../include/Trap.h"

Trap::Trap() {};

Trap::Trap(float x, float y, SDL_Renderer* renderer, std::string fileName, int type) : Object(x, y, renderer, fileName, type) {
	tower = new Texture(TOWER_PNG, renderer);
}

void Trap::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {
	int xPos, yPos;
	SDL_GetMouseState(&xPos, &yPos);

	double diffX = xPos - x;
	double diffY = yPos - y;
	angle = calcAngle(diffX, diffY);
}

void Trap::render() {
	SDL_Rect towerSrc = { 0, 0, tower->getWidth(), tower->getHeight() };
	SDL_Rect towerDst = { (int)x - (tower->getWidth() / 4), (int) y + tower->getHeight() / 4, tower->getWidth(), tower->getHeight()};

	tower->render(&towerSrc, &towerDst);

	SDL_Rect src = { 0, 0, sprite->getWidth(), sprite->getHeight() };
	SDL_Rect dst = { x, y, sprite->getWidth(), sprite->getHeight() };

	SDL_Point center = { dst.w / 2, dst.h - dst.h / 4 };

	sprite->renderCopyEx(&src, &dst, &center, angle);
}