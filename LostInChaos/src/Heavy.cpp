#include "../include/Heavy.h"

Heavy::Heavy() {}

Heavy::Heavy(float x, float y, SDL_Renderer* renderer, Map* map, Object* player) 
	: Enemy (x, y, renderer, map, player, HEAVY_PNG, HEAVY_TAG) {
}
