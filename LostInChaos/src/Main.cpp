#include <SDL.h>
#include "../include/Enemy.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/Renderer.h"
#include "../include/GlobalVars.h"
#include "../include/TrapHUD.h"
#include "../include/Astar.h"

void updateList(vector<Object*>& objects, Map* map, double deltaTime);


int main(int argc, char* args[]) {

	GlobalVars gvars;
	Renderer* system = new Renderer();
	SDL_Renderer* renderer = system->getRenderer();

	// game objects vector
	vector<Object*> objects;
	

	// map pointer 
	Map* map = new Map(renderer);
	// player poitner
	Player* p = new Player(200, 200, renderer);
	
	// trap hud 
	TrapHUD* trapHUD = new TrapHUD(renderer, &map->getMap(), &objects);

	vector<Node*> ns;


	while (!gvars.gameLoop) {
		// keep updating deltaTime
		system->updateDeltaTime();

		// handle events like mouse click and keyboard presses
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				gvars.gameLoop = true;
			}

			trapHUD->handleTrapsSelection(e);
		}
		// set renderer color
		SDL_SetRenderDrawColor(renderer, BG.r, BG.g, BG.b, BG.a);
		// clear renderer to draw on screen
		SDL_RenderClear(renderer);

		// render map
		map->renderMap();

		// render player
		p->render();
		p->move(map->getMap(), system->getDeltaTime());

		system->renderList(objects);

		updateList(objects, map, system->getDeltaTime());

		// render Traps 
		trapHUD->renderHUD(e);


		// render above entities
		SDL_RenderPresent(renderer);
	}

	// if game exits, delete renderer and all other components
	delete system;
	return 0;
}


void updateList(vector<Object*>& objects, Map* map, double deltaTime) {
	for (int i = 0; i < objects.size(); i++) {
		objects.at(i)->move(map->getMap(), deltaTime);
	}
}
