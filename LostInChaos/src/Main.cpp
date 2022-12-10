#include <SDL.h>
#include "../include/Enemy.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/Renderer.h"
#include "../include/GlobalVars.h"
#include "../include/TrapHUD.h"
#include "../include/Heavy.h"
#include "../include/Melee.h"

void updateList(vector<Object*>& objects, vector<Object*>& bullets, Map* map, double deltaTime);

int main(int argc, char* args[]) {

	GlobalVars gvars;
	Renderer* system = new Renderer();
	SDL_Renderer* renderer = system->getRenderer();

	// game objects vector to store objects such as enemies and turrets
	vector<Object*> objects;

	// bullets and particles are stored in another vector to make collision detection
	// simpler and easier
	vector<Object*> bullets;

	// map pointer 
	Map* map = new Map(renderer);
	// player poitner
	Player* p = new Player(250, 200, renderer);
	// trap hud 
	TrapHUD* trapHUD = new TrapHUD(renderer, &map->getMap(), &objects);

	Object* g = new Melee(1100, 200, renderer);

	g->setTarget(p);
	objects.insert(objects.begin(), g);



	while (!gvars.gameLoop) {
		// keep updating deltaTime
		system->updateDeltaTime();

		// handle events like mouse click and keyboard presses
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				gvars.gameLoop = true;
			}
			// handle trap selection when user clicks on traps and places them
			// ESC key to cancel selection
			// Left Mouse Click to select a turret
			// Left Mouse Click to place a turret if the position is valid
			trapHUD->handleTrapsSelection(e);
		}

		// set renderer color
		SDL_SetRenderDrawColor(renderer, BG.r, BG.g, BG.b, BG.a);
		// clear renderer to draw on screen
		SDL_RenderClear(renderer);

		/*
		Map rendered below every entity 
		*/
		map->renderMap();

		/*
		All player rendering, movements, and attack goes below this code
		*/
		p->render();
		//p->move(map->getMap(), system->getDeltaTime());

		/* Player End */
		/*
		both vectors are rendered using a helper function in Renderer class 
		*/
		system->renderList(objects);
		system->renderList(bullets);
		
		/* List Rendering End*/

		/*
		Lists are updated such as movement, attack and other function calls
		*/
		updateList(objects, bullets, map, system->getDeltaTime());
		updateList(objects, bullets, map, system->getDeltaTime());

		/* List updating End */

		/*
		Trap HUD shown at right side of the game is rendered
		*/
		trapHUD->renderHUD(e);

		/* Trap HUD Rendering End*/

		// render above entities
		SDL_RenderPresent(renderer);

	}
	// if game exits, delete renderer and all other components
	delete system;
	return 0;
}


void updateList(vector<Object*> &objects, vector<Object*>& bullets, Map *map, double deltaTime) {

	// move and fire enemies, turrets
	for (int i = 0; i < objects.size(); i++) {
		objects.at(i)->move(map->getMap(), deltaTime);
		objects.at(i)->fire(objects, bullets, deltaTime);
	}

	// move and fire bullet and particles 
	for (int i = 0; i < bullets.size(); i++) {
		bullets.at(i)->move(map->getMap(), deltaTime);
		bullets.at(i)->fire(objects, bullets, deltaTime);
	}

	// clear bullets list for non alive elements
	for (int i = 0; i < bullets.size(); i++) {
		if (!(bullets.at(i)->isAlive())) {
			delete bullets.at(i);
			bullets.erase(bullets.begin() + i);
		}
	}

	// clear objects list for non alive elements
	for (int i = 0; i < objects.size(); i++) {
		if (!(objects.at(i)->isAlive())) {
			delete objects.at(i);
			objects.erase(objects.begin() + i);
		}
	}

}
