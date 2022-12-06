#include "../include/TrapHUD.h"

TrapHUD::TrapHUD() {
	map = nullptr;
	objects = nullptr;
	renderer = nullptr;
	selectedTrap = -1;
	for (int i = 0; i < 3; i++) {
		icons[i] = nullptr;
	}
};

TrapHUD::TrapHUD(SDL_Renderer* renderer, std::array<Tile*, MAP_LENGTH>* map, vector<Object*>* objects) {
	this->map = map;
	this->objects = objects;
	this->renderer = renderer;

	icons[MISSILE_LAUNCHER] = new TrapIcon(32, startPosY, MISSILE_LAUNCHER_ICON_PNG, MISSILE_LAUNCHER, renderer, 30);
	icons[CANNON] = new TrapIcon(32, startPosY + 112, CANNON_ICON_PNG, CANNON, renderer, 5);
	icons[MACHINE_GUN] = new TrapIcon(32, startPosY + 224, MACHINE_GUN_ICON_PNG, MACHINE_GUN, renderer, 5);

	selectedTrap = -1;
}

TrapHUD::~TrapHUD() {
	for (int i = 0; i < NUM_OF_TRAPS; i++) {
		delete icons[i];
	}
}

void TrapHUD::renderHUD(SDL_Event& e) {
	renderSelectedTrap();
	for (int i = 0; i < NUM_OF_TRAPS; i++) {
		icons[i]->render();
	}
}

void TrapHUD::renderSelectedTrap() {
	if (selectedTrap != -1) {

		bool isLegal = isPositionLegal();
		renderIllegalPlacement(isLegal);
		// get mouse positions
		int xPos, yPos;
		SDL_GetMouseState(&xPos, &yPos);

		// fill selected icon with a background
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, GRAY.r, GRAY.g, GRAY.b, GRAY.a);
		SDL_RenderFillRect(renderer, &icons[selectedTrap]->getBgRect());

		// get texture reference
		selectedIcon = *icons[selectedTrap];

		// adjust x and y values to center
		int x = xPos - (icons[selectedTrap]->getBoundaryRect().w / 2);
		int y = yPos - (icons[selectedTrap]->getBoundaryRect().h / 2);

		SDL_Rect src = { 0 , 0, icons[selectedTrap]->getBoundaryRect().w, icons[selectedTrap]->getBoundaryRect().h };
		SDL_Rect dst = { x, y, icons[selectedTrap]->getBoundaryRect().w, icons[selectedTrap]->getBoundaryRect().h };
		selectedIcon.renderAtMouse();
	}
}

void TrapHUD::handleTrapsSelection(SDL_Event& e) {
	// only check if mouse clicked 
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		// if no trap is selected look for selection
		if (selectedTrap == -1) {
			// check for trap selection based on id
			if (checkMouseClick(icons[MISSILE_LAUNCHER]->getBoundaryRect(), e)) {
				if (!icons[MISSILE_LAUNCHER]->isPlaced()) {
					selectedTrap = MISSILE_LAUNCHER;
				}
			}
			else if (checkMouseClick(icons[CANNON]->getBoundaryRect(), e)) {
				if (!icons[CANNON]->isPlaced()) {
					selectedTrap = CANNON;
				}
			}
			else if (checkMouseClick(icons[MACHINE_GUN]->getBoundaryRect(), e)) {
				if (!icons[MACHINE_GUN]->isPlaced()) {
					selectedTrap = MACHINE_GUN;
				}
			}
		}
		// if trap is selected look for placement
		else placeTrap(e);
	}
	// if escape key pressed, cancel any trap selection.
	else if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_ESCAPE) {
			selectedTrap = -1;
		}
	}
}

void TrapHUD::placeTrap(SDL_Event& e) {
	int x = e.button.x - (icons[selectedTrap]->getBoundaryRect().w / 4);
		int y = e.button.y - (icons[selectedTrap]->getBoundaryRect().h / 2);

	// do not place if attempted to be placed at illegal position
	if (!isPositionLegal()) {
		return;
	}

	Object* trap = nullptr;

	if (selectedTrap == CANNON) {
		trap = new Trap((float)x, (float)y, renderer, CANNON_PNG, CANNON);
	}
	else if (selectedTrap == MISSILE_LAUNCHER) {
		trap = new Trap((float)x, (float)y, renderer, MISSILE_LAUNCHER_PNG, MISSILE_LAUNCHER);
	}
	else if (selectedTrap == MACHINE_GUN) {
		trap = new Trap((float)x, (float)y, renderer, MACHINE_GUN_PNG, MACHINE_GUN);
	}
	if (trap != nullptr) {
		objects->insert(objects->begin(), trap);
		icons[selectedTrap]->setPlaced();
	}
	selectedTrap = -1;
}

void TrapHUD::renderIllegalPlacement(bool isLegal) {
	// render a green background if its legal to place
	if (isLegal) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
		SDL_RenderFillRect(renderer, &selectedIcon.getBoundaryRect());
	}
	// render a red background if illegal to place 
	else {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
		SDL_RenderFillRect(renderer, &selectedIcon.getBoundaryRect());
	}
}

bool TrapHUD::isPositionLegal() {
	// check if trap collides with walls or boundaries
	for (int i = 0; i < map->size(); i++) {
		if (map->at(i) != nullptr) {
			SDL_Rect tile = map->at(i)->getRect();
			int type = map->at(i)->getTileType();
			if (type == SWALL_R || type == SWALL_B || type == SWALL_T || type == SWALL_L) {
				if (checkCollision(selectedIcon.getBoundaryRect(), tile, 0)) {
					return false;
				}
			}
		}
	}
	// check if trap collides with existing objects in list
	for (int i = 0; i < objects->size(); i++) {
		if (checkCollision(objects->at(i)->getCollisionRect(), selectedIcon.getBoundaryRect(), 0)) {
			return false;
		}
	}

	if (selectedIcon.getBoundaryRect().x <= 128) return false;

	return true;
}