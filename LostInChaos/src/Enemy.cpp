#include "../include/Enemy.h"

Enemy::Enemy() {};

Enemy::Enemy(float x, float y, SDL_Renderer* renderer, std::string filename, int type) : Object(x, y, renderer, filename, type) {
	
}

void Enemy::setTarget(Object* target) {
	this->target = target;
}

void Enemy::render() {
	SDL_Rect src = { 0,0, collisionRect.w, collisionRect.h };
	sprite->renderCopyEx(&src, &collisionRect, nullptr, angle);
}

void Enemy::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {


	// to be fixed only and changed only when needed - might be added separately where needed in class
	frameCounter += (int) deltaTime;

	// change frames for enemies that have sprite sheet
	if (frameCounter > 100) {
		frame++;
		frameCounter = 0;
	}

	handleInput();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &collisionRect);

	// calculate A* path from current pos to player pos
	Astar astar(target, this);

	stack<SDL_Point> path = astar.astar(map);

	while (path.size() != 0) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		int xP = path.top().x;
		int yP = path.top().y;

		SDL_Rect r = { xP, yP, 32, 32 };

		/*
			Make the enemy follow path
		*/

		//SDL_RenderFillRect(renderer, &r);
		path.pop();
	}


	// future values of x and y calculate before moving
	// multiplied by 5 to have some distance before it collides, in order to prevent getting stuck 
	int tempX = (int)(x - (tx * 5));
	int tempY = (int)(y - (ty * 5));

	SDL_Rect wallCollisionRect = { tempX, tempY, collisionRect.w, collisionRect.h };

	if (!(wallCollision(map, wallCollisionRect))) {
		x -= tx * (float)deltaTime / 13;
		y -= ty * (float)deltaTime / 13;
	}
	else return;

	tx *= friction;
	ty *= friction;

	collisionRect.x = (int)x;
	collisionRect.y = (int)y;
}


void Enemy::handleInput() {
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP]) {
		frame++;
		angle = 0;
		translate(0, 2.0);
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		frame++;
		angle = 180;
		translate(0, -2.0);
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		frame++;
		translate(2.0, 0);
		angle = -90;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		frame++;
		angle = 90;
		translate(-2.0, 0);
	}
}