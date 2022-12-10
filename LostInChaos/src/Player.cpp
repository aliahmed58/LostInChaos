#include "../include/Player.h"

Player::Player() {};

Player::Player(float x, float y, SDL_Renderer* renderer) : Object(x, y, renderer, PLAYER_PNG, PLAYER_TAG) {
	friction = 0.9f;
	frame = 0;
	clipSheet();
	collisionRect.w = rects[0].w;
}

// move player
void Player::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {
	handleInput();

	Astar astar(this, nullptr);

	

	// future values of x and y calculate before moving
	// multiplied by 5 to have some distance before it collides, in order to prevent getting stuck 
	int tempX = (int) (x - (tx * 2));
	int tempY = (int) (y - (ty * 2));

	SDL_Rect wallCollisionRect = { tempX, tempY, collisionRect.w, collisionRect.h};

	if (!(wallCollision(map, wallCollisionRect))) {
		x -= tx * (float)deltaTime / 9;
		y -= ty * (float)deltaTime / 9;
	}
	else return;

	tx *= friction;
	ty *= friction;

	collisionRect.x = (int)x;
	collisionRect.y = (int)y;
}

void Player::render() {

	int f = (frame % 30) / 6;

	SDL_Rect dst = {collisionRect.x , collisionRect.y, rects[f].w, rects[f].h};
	
	sprite->renderCopyEx(&rects[f], &dst, nullptr, angle);

}

// Handle player movements 
void Player::handleInput() {
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP]) {
		frame++;
		angle = -90;
		translate(0, 2.0);
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		angle = 90;
		frame++;
		translate(0, -2.0);
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		frame++;
		translate(2.0, 0);
		angle = -180;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		angle = 0;
		frame++;
		translate(-2.0, 0);
	}
}

void Player::clipSheet() {
	// Coordinates of sprites in sprite sheet 
	// Total sprites: 6
	// i = row, j = col, (i, j)
	// (0, 0)
	rects[0].x = 0;
	rects[0].y = 0;
	rects[0].w = 35;
	rects[0].h = 42;
	// (0, 1)
	rects[1].x = 35;
	rects[1].y = 0;
	rects[1].w = 35;
	rects[1].h = 42;
	// (0, 2)
	rects[2].x = 70;
	rects[2].y = 0;
	rects[2].w = 35;
	rects[2].h = 42;
	// (0, 3)
	rects[3].x = 105;
	rects[3].y = 0;
	rects[3].w = 35;
	rects[3].h = 42;
	// (0, 4)
	rects[4].x = 140;
	rects[4].y = 0;
	rects[4].w = 35;
	rects[4].h = 42;
	// (0, 5)
	rects[5].x = 175;
	rects[5].y = 0;
	rects[5].w = 35;
	rects[5].h = 42;


}