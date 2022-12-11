#pragma once
#include "Enemy.h"

class Zombie : public Enemy {
public:
	
	Zombie();

	Zombie(float x, float y, SDL_Renderer* renderer, Map* map, Object* player, vector<Object*>* objects);

	void render();

private:
	void clipSheet();
	
	SDL_Rect rects[2];

};