#pragma once
#include "Texture.h"
#include "Tile.h"
#include "helper.h"
#include <vector>
#include <array>

class Object {
public:
	Object();
	Object(float x, float y, SDL_Renderer* gRenderer, std::string file_name, int type);
	virtual ~Object();

	// render object on screen
	virtual void render();

	// move object given x, y and delta Time.
	virtual void move(std::array<Tile*, MAP_LENGTH> &map, double deltaTime) = 0;

	// if object collides with walls 
	virtual bool wallCollision(std::array<Tile*, MAP_LENGTH> &map, SDL_Rect &rect);

	// kill an object.
	virtual void kill(double deltaTime);

	// firing ability of an object
	virtual void fire(vector<Object*>& list, vector<Object*>& bullets, double deltaTime);

	// setting a target
	virtual void setTarget(Object* target);

	// translate object to x and y offsets.
	void translate(float x_val, float y_val);

	// return true if object is alive.
	bool isAlive();

	// get collision SDL_Rect for object
	SDL_Rect& getCollisionRect();

	// get type of object
	int getType();

	// x and y position getters.
	float getX();
	float getY();

protected:
	float x;
	float y;
	double angle;
	int health;
	bool alive;
	SDL_Rect collisionRect;
	float friction;
	float tx;
	float ty;
	Texture* sprite;
	int type;
	SDL_Renderer* renderer;

};

