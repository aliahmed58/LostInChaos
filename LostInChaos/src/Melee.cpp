#include "../include/Melee.h"

Melee::Melee() {};

Melee::Melee(float x, float y, SDL_Renderer* renderer, Map* map, Object* player) 
	: Enemy(x, y, renderer, map, player, MELEE_PNG, MELEE_TAG) {
	clipSheet();
	collisionRect.w = rects[0].w;
	collisionRect.h = rects[0].h;
}


void Melee::render() {
	int f = frame % 3;
	sprite->renderCopyEx(&rects[f], &collisionRect, nullptr, angle);
}

void Melee::clipSheet() {
	// Coordinates of sprites in sprite sheet 
// Total sprites: 3
// i = row, j = col, (i, j)
// (0, 0)
	rects[0].x = 0;
	rects[0].y = 0;
	rects[0].w = 48;
	rects[0].h = 57;
	// (0, 1)
	rects[1].x = 48;
	rects[1].y = 0;
	rects[1].w = 48;
	rects[1].h = 57;
	// (0, 2)
	rects[2].x = 96;
	rects[2].y = 0;
	rects[2].w = 48;
	rects[2].h = 57;

}
