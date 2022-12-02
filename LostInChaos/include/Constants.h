#pragma once
#include <math.h>
#include <string>

using namespace std;

// WINDOW DIMENSIONS
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;

// PI VALUE
const double PI = M_PI;

// WINDOW TITLE
const string WINDOW_TITLE = "Lost in Chaos";

// RESOURCE FILES 
// ALL ASSETS ARE IN RES FOLDER
const string BASE = "./src/res/";

// MAP TILE DIMENSIONS
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

const int MAP_LENGTH = (SCREEN_WIDTH / TILE_WIDTH) * (704 / TILE_HEIGHT);

// MAP PATH
const string MAP_FILE = BASE + "map.txt";

// SPRITESHEETS FOR ENTITIES
// tiles
const string TILE1 = BASE + "tiles/tile1.png";
const string TILE4 = BASE + "tiles/tile4.png";

// sprites
const string GUNNER_PNG = BASE + "Ranger.png";
const string PLAYER_PNG = BASE + "player.png";

// AUDIO AND SFX

// UI RESOURCES

// COLORS 

// ENUM FOR TYPE OF OBJECTS

enum TAG {
	PLAYER_TAG, GUNNER_TAG
};