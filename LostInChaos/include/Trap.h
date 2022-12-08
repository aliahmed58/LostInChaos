#pragma once
#include "Object.h"
#include "helper.h"

class Trap : public Object {
public:
	Trap();
	Trap(float x, float y, SDL_Renderer* renderer, std::string fileName, int type);

	void move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime);

	void render();

private:
	Texture* tower;
};