#pragma once
#include "Bullet.h"
#include "helper.h"

// class for machine gun bullet
class Missile : public Bullet {
public:
	// default ctor
	Missile();

	// overloaded ctor for machine gun bullet
	Missile(float x, float y, Object* target, SDL_Renderer* renderer);

};