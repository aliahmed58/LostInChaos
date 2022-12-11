#pragma once
#pragma once
#include "Enemy.h"
#include "Timer.h"

class Hitman : public Enemy {
public:
	Hitman();

	Hitman(float x, float y, SDL_Renderer* renderer, Map* map, Object* player, vector<Object*>* objects);

	void render();

private:
	SDL_Rect rects[3];

	void clipSheet();

};