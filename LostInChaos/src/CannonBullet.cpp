#include "../include/CannonBullet.h"

CannonBullet::CannonBullet() {};

CannonBullet::CannonBullet(float x, float y, Object* target, SDL_Renderer* renderer) : 
	Bullet(x, y, target, renderer, CANNON_BULLET_PNG, CANNON_BULLET_TAG) {
	damage = 3;
}
