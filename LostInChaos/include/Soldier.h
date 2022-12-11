#pragma once
#include "Enemy.h"
#include "Timer.h"

class Soldier : public Enemy {
public:
	Soldier();

	Soldier(float x, float y, SDL_Renderer* renderer, Map* map, Object* player);

	void render();

private:
	void clipSheet();

	SDL_Rect rects[2];
};
