#pragma once
#include "Trap.h"
#include "CannonBullet.h"
#include "Player.h"

class Cannon : public Trap {
public:
	Cannon();
	Cannon(float x, float y, SDL_Renderer* renderer, vector<Object*> targets);

	// fire funciton override
	void fire(vector<Object*>& list, vector<Object*>& bullets, double deltaTime);
};

