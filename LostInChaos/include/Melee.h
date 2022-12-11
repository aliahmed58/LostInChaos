#pragma once
#pragma once
#include "Enemy.h"
#include "Timer.h"

class Melee : public Enemy {
public:
	Melee();

	Melee(float x, float y, SDL_Renderer* renderer, Map* map, Object* player);

	void render();

private:
	SDL_Rect rects[3];

	void clipSheet();

};