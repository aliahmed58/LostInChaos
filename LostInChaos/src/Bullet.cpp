#include "../include/Bullet.h"

Bullet::Bullet() {};

Bullet::Bullet(float x, float y, Object* target, SDL_Renderer* renderer, std::string path, int type) : Object(x, y, renderer, path, type) {
	damage = -1;
	this->target = target;

	int xp, yp;
	SDL_GetMouseState(&xp, &yp);

	double diffX = x - (double) xp;
	double diffY = y - (double) yp;

	double* unitVectors = calcVector(diffX, diffY);
	unitX = unitVectors[0];
	unitY = unitVectors[1];
	angle = calcAngle(diffX, diffY);
}

void Bullet::move(std::array<Tile*, MAP_LENGTH> &map, double deltaTime) {
	// if bullet collides with wall - destroy it
	if (wallCollision(map, collisionRect)) {
		alive = false;
	}
	else {
		// if bullet is in screen , move it
		if (y > 0) y -= (float) (unitY * (deltaTime / 7));
		if (y > SCREEN_HEIGHT) alive = false;

		if (x > 0 && x < SCREEN_WIDTH - collisionRect.w) x -= (float) (unitX * (deltaTime / 7));
		else alive = false;
	}

	collisionRect.x = (int) x;
	collisionRect.y = (int) y;
}

void Bullet::render() {
	SDL_Rect src = { 0,0, sprite->getWidth(), sprite->getHeight() };
	sprite->renderCopyEx(&src, &collisionRect, nullptr, angle, SDL_FLIP_VERTICAL);
}