#pragma once
#include <array>
#include "Object.h"

class Particle : public Object {
public:
	Particle();
	// ctor for particle class
	Particle(float x, float y, float angle, int height, int width, SDL_Renderer* renderer, std::string path, int type);

	//render particles
	void render();

protected:

	int width;
	int height;
	float alpha;
};