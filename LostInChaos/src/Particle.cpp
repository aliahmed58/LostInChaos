#include "../include/Particle.h"

Particle::Particle() {};

Particle::Particle(float x, float y, float Angle, int Height, int Width, SDL_Renderer* renderer, std::string path, int type) : Object(x, y, renderer, path, type) {
	angle = Angle;
	height = Height;
	width = Width;
}

void Particle::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {
	angle++;
}

void Particle::render() {

	SDL_Rect src = { 0, 0, sprite->getWidth(), sprite->getHeight()};
	SDL_Rect dst = { (int)x, (int)y, height, width };
	SDL_Point centre = { height / 2, width / 2 };
	sprite->renderCopyEx(&src, &dst, &centre,angle);
}