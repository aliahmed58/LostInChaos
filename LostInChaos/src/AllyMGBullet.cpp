#include "../include/AllyMGBullet.h"

AllyMGBullet::AllyMGBullet() {};

AllyMGBullet::AllyMGBullet(float x, float y, Object* target, float angle, SDL_Renderer* renderer) 
	: AllyBullet(x, y, target, angle, renderer, MG_BULLET_PNG, ALLY_MG_BULLET_TAG) {
	damage = 1;
	
}