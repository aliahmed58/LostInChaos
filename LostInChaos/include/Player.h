#pragma once
#include "Object.h"
#include "Astar.h"

class Player : public Object {
	
public:
	Player();
	Player(float x, float y, SDL_Renderer* renderer);

	void move(std::array<Tile*, MAP_LENGTH> &map, double deltaTime);

	void handleInput();
	
private:
	Astar astar;
};