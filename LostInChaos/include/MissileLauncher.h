#pragma once
#include "Trap.h"
#include "Missile.h"
#include "Player.h"

class MissileLauncher : public Trap {
public:
	MissileLauncher();
	MissileLauncher(float x, float y, SDL_Renderer* renderer, vector<Object*> targets);

	// fire funciton override
	void fire(vector<Object*>& list, vector<Object*>& bullets, double deltaTime);
};

