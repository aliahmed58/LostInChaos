#include "../include/Map.h"

Map::Map() {};

Map::Map(SDL_Renderer* gRenderer) {
	renderer = gRenderer;
	water = new Texture(TILE1, renderer);
	brick = new Texture(TILE4, renderer);
	readMap();
}

Map::~Map() {
	for (int i = 0; i < tiles.size(); i++) {
		delete tiles.at(i);
	}
	water->free();
	brick->free();
}

void Map::readMap() {
	std::ifstream mapFile(MAP_FILE);

	// starting initials of map 
	int x = 0, y = 64;
	// read map file 
	int i = 0;
	for (int i = 0; i < tiles.size(); i++) {
		// determines tile type 
		int tileType = -1;

		// Read type from map file 
		mapFile >> tileType;
		// if error occurs in reading from file
		if (mapFile.fail()) {
			mapFile.close();
			return;
		}
		// read tiles with valid tile types
		if (tileType >= 0) {
			tiles[i] = new Tile(x, y, tileType);
		}
		// increase x values 
		x += TILE_WIDTH;
		// if x value is maxed out, go to next row
		if (x >= SCREEN_WIDTH) {
			x = 0;
			y += TILE_HEIGHT;
		}
	}
	mapFile.close();
}

void Map::renderMap() {
	for (int i = 0; i < tiles.size(); i++) {
		if (tiles[i] != nullptr) {
			SDL_Rect src = { 0, 0, 32, 32 };
			SDL_Rect dst = { tiles[i]->getRect().x, tiles[i]->getRect().y, 32, 32};

			if (tiles[i]->getTileType() == 0) {
				water->render(&src, &dst);
			}
			if (tiles[i]->getTileType() == 4) {
				brick->render(&src, &dst);
			}
		}
	}
}

std::array<Tile*, MAP_LENGTH> &Map::getMap() {
	return tiles;
}
