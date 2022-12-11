#include "../include/Hitman.h"

Hitman::Hitman() {};

Hitman::Hitman(float x, float y, SDL_Renderer* renderer, Map* map, Object* player, vector<Object*>* objects)
	: Enemy(x, y, renderer, map, player, objects, HITMAN_PNG, HITMAN_TAG) {
	clipSheet();
	collisionRect.w = rects[0].w;
}


void Hitman::render() {
	if (attackMode) frame = 1;
	else frame = 0;
	sprite->renderCopyEx(&rects[frame], &collisionRect, nullptr, angle);
}

void Hitman::clipSheet() {
	// Coordinates of sprites in sprite sheet 
// Total sprites: 2
// i = row, j = col, (i, j)
// (0, 0)
	rects[0].x = 0;
	rects[0].y = 0;
	rects[0].w = 32;
	rects[0].h = 32;
	// (0, 1)
	rects[1].x = 32;
	rects[1].y = 0;
	rects[1].w = 32;
	rects[1].h = 32;

}
