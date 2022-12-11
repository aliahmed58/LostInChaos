#include "../include/Enemy.h"

Enemy::Enemy() {};

Enemy::Enemy(float x, float y, SDL_Renderer* renderer, Map* map, Object* player, std::string filename, int type) : Object(x, y, renderer, filename, type) {
	// calculate A* path from current pos to player pos
	this->map = map;
	target = player;

}


void Enemy::render() {
	SDL_Rect src = { 0,0, collisionRect.w, collisionRect.h };
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

	sprite->renderCopyEx(&src, &collisionRect, nullptr, angle);

	// testing purposes
	/*SDL_Rect p = { x + collisionRect.w / 2, y + collisionRect.h / 2, 4, 4 };
	SDL_RenderFillRect(renderer, &p);
	SDL_RenderDrawRect(renderer, &collisionRect);*/
}

void Enemy::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {

	Astar astar(target, this);
	if (path.size() == 0) {
		path = astar.astar(map);
	}

	if (path.size() != 0) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

		SDL_Point* k = path.top();
		SDL_Rect r = { k->x + collisionRect.w / 2, k->y + collisionRect.h / 2 , 4, 4 };

		int dx = (int)x - r.x;
		int dy = (int)y - r.y;

		int signX = 1;
		int signY = 1;

		if (dy < 0) signY = -1;
		if (dx < 0) signX = -1;

		//printf("dx: %d\n", dx);

		if (abs(dx) <= 3 && abs(dy) <= 3) {
			path.pop();
			delete k;
		}
		else {
			if (abs(dy) != 0) {
				if (signY < 0) {
					translate(0, -1.0);
					angle = 180;
				}
				else {
					angle = 0;
					translate(0, 1.0);
				}
			}
			if (abs(dx) != 0) {
				if (signX < 0) {
					translate(-1, 0);
					angle = 90;
				}
				else {
					angle = -90;
					translate(1, 0);
				}
			}
		}

		// testing pureposes
		//SDL_RenderFillRect(renderer, &r);
	}

	// future values of x and y calculate before moving
	// multiplied by 5 to have some distance before it collides, in order to prevent getting stuck 
	int tempX = (int)(x - (tx * 5));
	int tempY = (int)(y - (ty * 5));

	SDL_Rect wallCollisionRect = { tempX, tempY, collisionRect.w, collisionRect.h };

	if (!(wallCollision(map, wallCollisionRect))) {
		x -= tx * (float)deltaTime / 16;
		y -= ty * (float)deltaTime / 16;
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