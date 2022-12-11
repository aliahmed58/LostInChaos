#pragma once
#include <array>
#include "Object.h"

class Particle : public Object {
public:
	Particle();
	// ctor for particle class
	Particle(float x, float y, float angle, int height, int width, SDL_Renderer* renderer, std::string path, int type);

	//to alter particle with time
	void move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime);

	//render particles
	void render();

protected:

	int width;
	int height;

};