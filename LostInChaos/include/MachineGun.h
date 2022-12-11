#pragma once
#include "Trap.h"
#include "MGBullet.h"
#include "Player.h"

class MachineGun : public Trap {
public:
	MachineGun();
	MachineGun(float x, float y, SDL_Renderer* renderer, vector<Object*> targets);

	// fire funciton override
	void fire(vector<Object*>& list, vector<Object*>& bullets, double deltaTime);
};

