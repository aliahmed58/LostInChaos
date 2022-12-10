#pragma once
#include "Object.h"
#include "helper.h"
#include "Astar.h"

class Enemy : public Object {
public:
	Enemy();

	// overriding ctor for enemy
	Enemy(float x, float y, SDL_Renderer* renderer, std::string filename, int type);

	// to set a target to any object so that enemy can attack or find that object
	void setTarget(Object* target);

	/*
	 All enemy movement will comprise of 2 basic things: 
		1. Using A star search to find the player and move in that path.
		2. Keep looking for turrets in area.
		3. If turret found:
			a. Stop A* search
			b. Set attack mode to true
			c. Attack turret 
		4. If no turret found, keep following the path.
	*/
	void move(std::array<Tile*, MAP_LENGTH>& map, double deltaTime);

	// virtual render function since somme enemies will have sprite sheet animations like meele attack
	virtual void render();

	// using the virtual fire function, each enemy will define its different type of attacks

protected:

	// attack mode which tells if enemy should attack or follwo A* path
	bool attackMode;

	// target for A* search
	Object* target;
	
	// frame int for enemies that have sprite sheets
	int frame;

	// conter
	int frameCounter;

private:

	// debug only

	void handleInput();

};