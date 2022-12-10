#include "../include/Gunner.h"

Gunner::Gunner() {};

Gunner::Gunner(float x, float y, SDL_Renderer* renderer) : Enemy(x, y, renderer, GUNNER_PNG, GUNNER_TAG) {
	
}
