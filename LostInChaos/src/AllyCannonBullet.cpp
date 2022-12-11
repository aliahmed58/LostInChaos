#include "../include/AllyCannonBullet.h"

AllyCannonBullet::AllyCannonBullet() {};

AllyCannonBullet::AllyCannonBullet(float x, float y, Object* target, float angle, SDL_Renderer* renderer) : 
	AllyBullet(x, y, target, angle, renderer, CANNON_BULLET_PNG, ALLY_CANNON_BULLET_TAG) {
	damage = 3;
}
