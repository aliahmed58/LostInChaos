#pragma once
#include "Enemy.h"

class Heavy : public Enemy {
public:
	
	Heavy();

	Heavy(float x, float y, SDL_Renderer* renderer);

};