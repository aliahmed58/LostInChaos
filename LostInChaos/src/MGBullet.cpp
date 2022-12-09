#include "../include/MGBullet.h"

MGBullet::MGBullet() {};

MGBullet::MGBullet(float x, float y, Object* target, SDL_Renderer* renderer) : Bullet(x, y, target, renderer, MG_BULLET_PNG, MG_BULLET_TAG) {
	damage = 1;
	
}