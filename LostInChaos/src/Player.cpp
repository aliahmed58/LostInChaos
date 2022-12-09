#include "../include/Player.h"

Player::Player() {};

Player::Player(float x, float y, SDL_Renderer* renderer) : Object(x, y, renderer, PLAYER_PNG, PLAYER_TAG) {
	friction = 0.9f;
	frame = 0;
	collisionRect.w = 35;
	collisionRect.h = 57;
	clipSheet();
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

		if (xP == (int)x && xY == (int)y) {
			printf("Somethin : \n");
		}

		path.pop();
	}


	// future values of x and y calculate before moving
	// multiplied by 5 to have some distance before it collides, in order to prevent getting stuck 
	int tempX = (int) (x - (tx * 5));
	int tempY = (int) (y - (ty * 5));

	SDL_Rect wallCollisionRect = { tempX, tempY, collisionRect.w, collisionRect.h};

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

void Player::render() {
	SDL_Rect dst = {x, y, 35, 35};
	sprite->render(&rects[frame % 6], &collisionRect);

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
	frame++;
}

void Player::clipSheet() {
	// Coordinates of sprites in sprite sheet 
// Total sprites: 6
// i = row, j = col, (i, j)
// (0, 0)
	rects[0].x = 0;
	rects[0].y = 0;
	rects[0].w = 35;
	rects[0].h = 57;
	// (0, 1)
	rects[1].x = 35;
	rects[1].y = 0;
	rects[1].w = 35;
	rects[1].h = 57;
	// (0, 2)
	rects[2].x = 70;
	rects[2].y = 0;
	rects[2].w = 35;
	rects[2].h = 57;
	// (0, 3)
	rects[3].x = 105;
	rects[3].y = 0;
	rects[3].w = 35;
	rects[3].h = 57;
	// (0, 4)
	rects[4].x = 140;
	rects[4].y = 0;
	rects[4].w = 35;
	rects[4].h = 57;
	// (0, 5)
	rects[5].x = 175;
	rects[5].y = 0;
	rects[5].w = 35;
	rects[5].h = 57;

}