#include "../include/Enemy.h"

Enemy::Enemy() {};

Enemy::Enemy(float x, float y, SDL_Renderer* renderer, Map* map, Object* player, std::string filename, int type) : Object(x, y, renderer, filename, type) {
	// calculate A* path from current pos to player pos
	this->map = map;
	target = player;

}

void Enemy::render() {
	SDL_Rect src = { 0,0, collisionRect.w, collisionRect.h };
	sprite->renderCopyEx(&src, &collisionRect, nullptr, angle);

	//SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	// testing purposes
	/*SDL_Rect p = { x + collisionRect.w / 2, y + collisionRect.h / 2, 4, 4 };
	SDL_RenderFillRect(renderer, &p);
	SDL_RenderDrawRect(renderer, &collisionRect);*/
}

void Enemy::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {

	float diffX = target->getX() - x;
	float diffY = target->getY() - y;


	float mag = sqrt(pow(x - target->getX(), 2) + pow(y - target->getY(), 2));
	if (mag <= 200) {
		attackMode = true;
		angle = calcAngle(diffX, diffY) - 90;
		return;
	}
	else {
		attackMode = false;
	}

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

		if (abs(dx) <= 2 && abs(dy) <= 2) {
			path.pop();
			delete k;
		}
		else {
			if (abs(dy) != 0) {
				if (signY < 0) {
					translate(0, -1.0);
					angle = 90;
				}
				else {
					angle = -90;
					translate(0, 1.0);
				}
			}
			if (abs(dx) != 0) {
				if (signX < 0) {
					translate(-1, 0);
					angle = 0;
				}
				else {
					angle = -180;
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
		x -= tx * (float)deltaTime / 23;
		y -= ty * (float)deltaTime / 23;
	}
	else return;

	tx *= friction;
	ty *= friction;

	collisionRect.x = (int)x;
	collisionRect.y = (int)y;
}

bool Enemy::LineOfSight(SDL_Rect* targetRect, int SightRadius, std::array<Tile*, MAP_LENGTH>& map, double deltatime) {

	SDL_Rect Rect = SDL_Rect();

	Rect.w = 10;
	Rect.h = 10;
	Rect.x = (int)(x);
	Rect.y = (int)(y);

	float Vy = target->getY() + targetRect->h / 2 - collisionRect.y - collisionRect.h / 2;
	float Vx = target->getX() + targetRect->w / 2 - collisionRect.x - collisionRect.w / 2;
	float M = sqrt(Vy * Vy + Vx * Vx);

	float stepY = Vy / M;
	float stepX = Vx / M;
	float currStepX = stepX;
	float currStepY = stepY;
	bool isWall = false;
	bool foundTarget = false;


	for (int i = 0; i < SightRadius; i++) {

		for (int j = 0; j < map.size(); j++) {
			if (checkCollision(*targetRect, Rect, 0)) {
				collisionRect.x += (int)stepX;
				collisionRect.y += (int)stepY;
				angle = 180 * atan2((double)stepY, (double)stepX) / 3.14 + 90;
				foundTarget = true;
				return true;
			}
			int type = map[j]->getTileType();
			Tile* t = map.at(j);
			if (t != nullptr) {
				SDL_Rect tRec = t->getRect();
				if (checkCollision(tRec, Rect, 0)) {
					if ((type == SWALL_R || type == SWALL_B || type == SWALL_T ||
						type == SWALL_L || type == MID_WALL || type == MID_WALL_TOP || type == MID_WALL_BOTTOM
						|| type == MID_WALL_VERTICAL || type == MID_WALL_R || type == MID_WALL_L)) {
						isWall = true;
						break;
					}
				}
			}
		}
		if (isWall) {
			break;
		}

		currStepX += stepX;
		currStepY += stepY;
		Rect.x += (int)currStepX;
		Rect.y += (int)currStepY;
	}

	return false;
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