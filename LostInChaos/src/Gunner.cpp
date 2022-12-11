#include "../include/Gunner.h"

Gunner::Gunner() {};

Gunner::Gunner(float x, float y, SDL_Renderer* renderer, Map* map, Object* player) : 
	Enemy(x, y, renderer, map,player, GUNNER_PNG, GUNNER_TAG) {
	
}
