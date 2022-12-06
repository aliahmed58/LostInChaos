#pragma once
#include <SDL.h>
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
const int MAP_LENGTH = ((SCREEN_WIDTH - 64) / TILE_WIDTH) * (SCREEN_HEIGHT / TILE_HEIGHT);

const int TOTAL_TILES = 15;
// tile types
const int PLAIN = 14;
// shadow tiles

// bottom wall 
const int WALL_B = 6;
// top wall | flip of bottom wall 
const int WALL_T = 31;
// right  wall
const int WALL_R = 0;
// top shadow
const int SWALL_T = 1;
// right wall shadow
const int SWALL_R = 3;
// bottom wall shadow | rotate of right wall shadow
const int SWALL_B = 33;
// left wall shadow || horizontal flip of right wall shadow
const int SWALL_L = 34;
// left wall | horizontal flip of right wall
const int WALL_L = 30;
// corner of walls
// bottom right wall
const int CBR_WALL = 11;
// bottom left | horizontal flip of bottom right
const int CBL_WALL = 44;
// top right | horizontal flip of bottom right + rotate 180 degrees
const int CTR_WALL = 45;
// top left | rotate 180 of bottom right 
const int CTL_WALL = 46;
// mid wall
const int MID_WALL = 10;


// MAP PATH
const string MAP_FILE = BASE + "map.txt";

// SPRITESHEETS FOR ENTITIES
// tiles
const string TILESET_PNG = BASE + "tiles/tileset.png";

// sprites
const string GUNNER_PNG = BASE + "Ranger.png";
const string PLAYER_PNG = BASE + "Ranger.png";

// TRAPS SPRITES
const string TOWER_PNG = BASE + "/turrets/tower.png";
const string CANNON_PNG = BASE + "/turrets/cannon.png";
const string MISSILE_LAUNCHER_PNG = BASE + "/turrets/missileLauncher.png";
const string MACHINE_GUN_PNG = BASE + "/turrets/machineGun.png";

//TRAPS ICON
const string CANNON_ICON_PNG = BASE + "/turrets/cannonIcon.png";
const string MISSILE_LAUNCHER_ICON_PNG = BASE + "/turrets/missileLauncherIcon.png";
const string MACHINE_GUN_ICON_PNG = BASE + "/turrets/machineGunIcon.png";

// AUDIO AND SFX

// UI RESOURCES

// COLORS 
//BACKGROUND
const SDL_Color BG = { 199, 230, 249, 255 };
const SDL_Color GRAY = { 121, 144, 158, 150 };
const SDL_Color LIGHT_GRAY = { 82, 109, 126, 150 };

// NUMBER OF TRAPS 
const int NUM_OF_TRAPS = 3;

// ENUM FOR TYPE OF OBJECTS
enum TAG {
	PLAYER_TAG, GUNNER_TAG
};

enum TRAPS {
	MISSILE_LAUNCHER, CANNON, MACHINE_GUN
};