#pragma once
#include "Object.h"
#include "helper.h"

class Enemy : public Object {
public:
	Enemy();
	Enemy(float x, float y, SDL_Renderer* renderer, std::string filename, int type);

	void move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime);
	void render();
};