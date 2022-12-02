#include <SDL.h>
#include "../include/Enemy.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/Renderer.h"
#include "../include/GlobalVars.h"

int main(int argc, char* args[]) {

	GlobalVars gvars;
	Renderer* system = new Renderer();
	SDL_Renderer* renderer = system->getRenderer();

	Map* m = new Map(renderer);
	Player* p = new Player(200, 200, renderer);
	Enemy x(SCREEN_WIDTH / 2 - 32, 0, renderer, GUNNER_PNG, GUNNER_TAG);

	while (!gvars.gameLoop) {
		// keep updating deltaTime
		system->updateDeltaTime();

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				gvars.gameLoop = true;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
		SDL_RenderClear(renderer);

		m->renderMap();

		p->render();
		p->move(m->getMap(), system->getDeltaTime());

		x.render();

		SDL_RenderPresent(renderer);
	}
	delete system;
	return 0;
}

