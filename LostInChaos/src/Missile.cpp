#include "../include/Missile.h"

Missile::Missile() {};

Missile::Missile(float x, float y, Object* target, SDL_Renderer* renderer) 
	: Bullet(x, y, target, renderer, MISSILE_BULLET_PNG, MISSILE_BULLET_TAG) {
	damage = 3;
}
