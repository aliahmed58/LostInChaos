#include "../include/Trap.h"

Trap::Trap() {};

Trap::Trap(float x, float y, vector<Object*> objects, SDL_Renderer* renderer, std::string fileName, int type) 
	: Object(x, y, renderer, fileName, type) {

	tower = new Texture(TOWER_PNG, renderer);
	targets = objects;
	shot = false;
}

void Trap::move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {

	for (int i = 0; i < targets.size(); i++) {
		if (targets[i]->getType() == MELEE_TAG || targets[i]->getType() == HEAVY_TAG || targets[i]->getType() == GUNNER_TAG) {
			if (LineOfSight(&targets[i]->getCollisionRect(), 100, map, deltaTime)) {
				break;
			}
		}
	}
}

void Trap::render() {
	SDL_Rect towerSrc = { 0, 0, tower->getWidth(), tower->getHeight() };
	SDL_Rect towerDst = { (int)x - (tower->getWidth() / 4), (int) y + tower->getHeight() / 2, tower->getWidth(), tower->getHeight()};

	tower->render(&towerSrc, &towerDst);

	SDL_Rect src = { 0, 0, sprite->getWidth(), sprite->getHeight() };
	SDL_Rect dst = { (int) x, (int) y, sprite->getWidth(), sprite->getHeight() };

	SDL_Point center = { dst.w / 2, dst.h - dst.h / 4 };

	sprite->renderCopyEx(&src, &dst, &center, angle);
}

bool Trap::LineOfSight(SDL_Rect* targetRect, int SightRadius, std::array<Tile*, MAP_LENGTH>& map, double deltatime) {

	SDL_Rect Rect = SDL_Rect();

	Rect.w = 30;
	Rect.h = 30;
	Rect.x = (int)(x);
	Rect.y = (int)(y);

	float Vy = targetRect->y + targetRect->h / 2 - y - collisionRect.h / 2;
	float Vx = targetRect->x + targetRect->w / 2 - x - collisionRect.w / 2;
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
				angle = 180 * atan2((double)stepY, (double)stepX) / 3.14 + 90;
				foundTarget = true;
				return true;
			}
			int type = map[j]->getTileType();
			Tile* t = map.at(j);
			if (t != nullptr) {
				SDL_Rect tRect = t->getRect();
				if (checkCollision(tRect, Rect, 0) && (type == SWALL_R || type == SWALL_B || type == SWALL_T ||
					type == SWALL_L || type == MID_WALL || type == MID_WALL_TOP || type == MID_WALL_BOTTOM
					|| type == MID_WALL_VERTICAL || type == MID_WALL_R || type == MID_WALL_L)) {
					isWall = true;
					break;
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

Object* Trap::getTarget(vector<Object*>& list) {
	for (int i = 0; i < list.size(); i++) {
		// fetch each object, check if it's not a turret itself
		// if not return it and continue
		Object* o = list.at(i);

		// check for nullptr 
		if (o != nullptr) {
			int oType = o->getType();

			if (oType != CANNON && oType != MACHINE_GUN && oType != MISSILE_LAUNCHER) {
				return o;
			}
		}
	}
	// if no target is found return a nullptr
	// no enemies present on map
	return nullptr;
}