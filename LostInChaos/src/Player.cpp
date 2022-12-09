#include "../include/Player.h"

Player::Player() {};

Player::Player(float x, float y, SDL_Renderer* renderer) : Object(x, y, renderer, PLAYER_PNG, PLAYER_TAG) {
	friction = 0.9f;
}

// move player
void Player::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {
	handleInput();

	Astar astar(this, nullptr);

	stack<SDL_Point> path = astar.astar(map);

	while (path.size() != 0) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		int xP = path.top().x;
		int xY = path.top().y;
		SDL_Rect r = { xP, xY, 32, 32 };
		SDL_RenderFillRect(renderer, &r);

		if (xP == (int) x && xY == (int) y) {
			printf("Somethin : \n");
		}

		path.pop();
	}

	// future values of x and y calculate before moving
	// multiplied by 5 to have some distance before it collides, in order to prevent getting stuck 
	int tempX = (int) (x - (tx * 5));
	int tempY = (int) (y - (ty * 5));

	SDL_Rect wallCollisionRect = { tempX, tempY, sprite->getWidth(), sprite->getHeight()};

	if (!(wallCollision(map, wallCollisionRect))) {
		x -= tx * (float)deltaTime / 5;
		y -= ty * (float)deltaTime / 5;
	}
	else return;

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