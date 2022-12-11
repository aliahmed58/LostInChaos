#include "../include/EnemyMGBullet.h"

EnemyMGBullet::EnemyMGBullet() {};

EnemyMGBullet::EnemyMGBullet(float x, float y, Object* target, float angle, SDL_Renderer* renderer)
	: EnemyBullet(x, y, target, angle, renderer, ENEMY_MG_BULLET_PNG, ENEMY_MG_BULLET_TAG) {
	damage = 1;

}