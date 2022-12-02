#include "../include/Player.h"

Player::Player() {};

Player::Player(float x, float y, SDL_Renderer* renderer) : Object(x, y, renderer, PLAYER_PNG, PLAYER_TAG) {
	friction = 0.9f;
}

// move player
void Player::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {
	handleInput();

	// future values of x and y calculate before moving
	int tempX = (int) (x - tx);
	int tempY = (int) (y - ty);

	collisionRect.x =  tempX;
	collisionRect.y = tempY;

	if (!(wallCollision(map))) {
		x -= tx * (float) deltaTime / 6;
		y -= ty * (float) deltaTime / 6;
	}

	tx *= friction;
	ty *= friction;
		
	collisionRect.x = (int) x;
	collisionRect.y = (int) y;
}

// Handle player movements 
void Player::handleInput() {
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP]) {
		translate(0, 2.0);
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		translate(0, -2.0);
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		translate(2.0, 0);
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		translate(-2.0, 0);
	}
}