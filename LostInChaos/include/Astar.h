#pragma once
#include "Constants.h"
#include "Object.h"
#include "Map.h"
#include <set>
#include <array>
#include <cmath>
#include <stack>


// Struct to hold a single node
struct Node {
	int x;
	int y;
	int parentX;
	int parentY;
	double g_cost;
	double h_cost;
	double total_cost;
	bool diagonal;

	Node() {};

	Node(int x, int y) {
		parentX = -1;
		parentY = -1;
		g_cost = h_cost = total_cost = 0;
		this->x = x;
		this->y = y;
		diagonal = false;
	}

	bool operator< (const Node& other) const {
		return total_cost < other.total_cost;
	}

	bool operator() (const Node& other) const {
		return x == other.x && y == other.y;
	}

	bool operator ==(const Node& other) const {
		return other.x == x && other.y == y;
	}
};


class Astar {
public:
	Astar();

	Astar(SDL_Renderer* renderer, Object* target);

	// calculate starting position of a block given x value
	int calc_x(int x);

	// calculate starting position of a block given x value
	int calc_y(int y);

	// function that calculates A* path
	void astar(std::array<Tile*, MAP_LENGTH>& map);

	// test function
	void test();

	// stack 
	std::stack<Node*> path;

	// void create rect
	void createrect();

	std::vector<SDL_Rect> rs;

private:

	// start position
	Object* start;
	// goal position
	Object* target;

	// generate successors for a given node
	std::array<Node*, 8> generate_successors(Node* n);

	// trace path from current
	void tracePath(Node* current);

	SDL_Renderer* renderer;

	set<Node> openList;

};

