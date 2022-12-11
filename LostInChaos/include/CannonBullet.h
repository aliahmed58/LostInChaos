#pragma once
#include "Bullet.h"
#include "helper.h"

// class for machine gun bullet
class CannonBullet : public Bullet {
public:
	// default ctor
	CannonBullet();

	// overloaded ctor for cannon gun bullet
	CannonBullet(float x, float y, Object* target, float angle, SDL_Renderer* renderer);

};