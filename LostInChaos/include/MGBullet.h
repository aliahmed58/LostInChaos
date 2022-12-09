#pragma once
#include "Bullet.h"
#include "helper.h"

// class for machine gun bullet
class MGBullet : public Bullet {
public:
	// default ctor
	MGBullet();
	
	// overloaded ctor for machine gun bullet
	MGBullet(float x, float y, Object* target,  SDL_Renderer* renderer);

};