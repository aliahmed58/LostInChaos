#include "../include/Heavy.h"

Heavy::Heavy() {}

Heavy::Heavy(float x, float y, SDL_Renderer* renderer) : Enemy (x, y, renderer, HEAVY_PNG, HEAVY_TAG) {
}
