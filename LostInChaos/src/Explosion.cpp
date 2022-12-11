#include "../include/Explosion.h"

Explosion::Explosion() {};

Explosion::Explosion(float x, float y, float angle, int height, int width, SDL_Renderer* renderer) : Particle(x, y, angle, height, width, renderer, EXPLOSION_PNG, EXPLOSION_TAG) {

}

void Explosion::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {
	angle++;
}