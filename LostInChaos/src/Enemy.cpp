#include "../include/Enemy.h"

Enemy::Enemy() {};

Enemy::Enemy(float x, float y, SDL_Renderer* renderer, std::string filename, int type) : Object(x, y, renderer, filename, type) {
	collisionRect.w = 64;
	collisionRect.h = 64;
}

void Enemy::move(std::array<Tile*, MAP_LENGTH> &map, double deltaTime) {
	
}

void Enemy::render() {

	SDL_SetRenderDrawColor(renderer, 102, 104, 10, 255);
	SDL_RenderFillRect(renderer, &collisionRect);

	SDL_Rect src = { 0,0, sprite->getWidth(), sprite->getHeight() };
	SDL_Rect dst = { (int)x, (int)y, 64, 64 };
	
}