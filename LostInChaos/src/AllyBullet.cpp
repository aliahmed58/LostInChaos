#include "../include/AllyBullet.h"

AllyBullet::AllyBullet() {};

AllyBullet::AllyBullet(float x, float y, Object* target, float Angle, SDL_Renderer* renderer, std::string path, int type)
	: Bullet(x, y, target, Angle, renderer, path, type) {
	damage = 1;

}