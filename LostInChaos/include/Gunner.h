#pragma once
#include "Enemy.h"
#include "Timer.h"

class Gunner : public Enemy {
public:
	Gunner();

	Gunner(float x, float y, SDL_Renderer* renderer);

};