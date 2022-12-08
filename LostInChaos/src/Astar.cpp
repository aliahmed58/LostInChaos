#include "../include/Astar.h"

Astar::Astar() {

}

Astar::Astar(SDL_Renderer* renderer, Object* target) {
	this->renderer = renderer;
	this->target = target;
}


int Astar::calc_x(int x) {
	// calculate remainders
	double x_remainder = (double)x / TILE_WIDTH;

	// multiplying decimal remainder value with BLOCK SIZE 
	//gives amount of x, y to be subtracted to reach block start
	x_remainder = (x_remainder - (int)x_remainder) * TILE_WIDTH;

	// subtract from mouse click values
	int x_val = x - (int)x_remainder;


	return x_val;
}

int Astar::calc_y(int y) {
	double y_remainder = double(y) / TILE_WIDTH;

	y_remainder = (y_remainder - (int)y_remainder) * TILE_WIDTH;

	int y_val = y - (int)y_remainder;

	return y_val;
}

void Astar::astar(std::array<Tile*, MAP_LENGTH>& map) {

	Node* s = new Node(calc_x(256), calc_y(64));
	Node g(calc_x(target->getX()), calc_y(target->getY()));

	openList.insert(*s);
	bool closedList[MAP_LENGTH];

	Node* nodes[39][24];

	for (int i = 0; i < MAP_LENGTH; i++) {
		closedList[i] = false;
	}

	for (int i = 0; i < 39; i++) {
		for (int j = 0; j < 24; j++) {
			nodes[i][j] = new Node();
			nodes[i][j]->parent = {};
		}
	}

	while (!openList.empty()) {

		Node q = *openList.begin();

		openList.erase(q);

		if (q == g) {
			break;
		}
		std::array<Node*, 8> successors = generate_successors(&q);

		for (int i = 0; i < successors.size(); i++) {
			Node s = *successors.at(i);

			bool valid = true;

			Tile* t = map.at(38 * (s.y / 32) + ((s.x - 128) / 32));
			if (t != nullptr) {
				if (t->getTileType() == 10) {
					valid = false;
				}
			}

			if (valid) {
				if (s.diagonal) {
					s.g_cost = q.g_cost + 14;
				}
				else {
					s.g_cost = q.g_cost + 10;
				}

				int dx = abs(g.x - s.x);
				int dy = abs(g.y - s.y);

				s.h_cost = 32 * (dx + dy) + (16) * min(dx, dy);
				//s.h_cost = dx + dy;

				s.total_cost = s.g_cost + s.h_cost;


				// if already in closed list skip
				if (closedList[38 * (s.y / 32) + (s.x / 32)] == true) {
					continue;
				}

				set<Node>::iterator it = std::find_if(openList.begin(), openList.end(), s);

				if (it != openList.end()) {

					Node p = *it;

					if (s.g_cost < p.g_cost) {

						nodes[s.x / 32][s.y / 32]->parent = { q.x / 32, q.y / 32 };
					}
					else {
						continue;
					}
				}
				else {
					openList.insert(s);

					nodes[s.x / 32][s.y / 32]->parent = {q.x / 32, q.y / 32};
				}

			}
		}
		// clean successors
		for (int i = 0; i < successors.size(); i++) {
			delete successors.at(i);
		}

		closedList[38 * (q.y / 32) + (q.x / 32)] = true;

	}

	int pX = g.x / 32;
	int pY = g.y / 32;

	while (!(nodes[pX][pY]->parent.x == (pX * 32) && nodes[pX][pY]->parent.y == (pY * 32))) {

		SDL_Rect r = { pX * 32, pY * 32, 32, 32 };
		rs.insert(rs.begin(), r);
		
		int tempX = nodes[pX][pY]->parent.x;
		int tempY = nodes[pX][pY]->parent.y;

		pX = tempX;
		pY = tempY;

	}

	for (int i = 0; i < 39; i++) {
		for (int j = 0; j < 24; j++) {
			delete nodes[i][j];
		}
	}

	delete s;
}


void Astar::tracePath(Node* current) {
}

void Astar::createrect() {

}

void Astar::test() {
	Node z(1, 2);
	Node p(1, 2);
	p.total_cost = 10;
	p.total_cost = 0;
	set<Node> l;
	l.insert(z);

	const bool is_in = std::find_if(l.begin(), l.end(), p) != l.end();
	if (is_in) printf("yeah");
}

std::array<Node*, 8> Astar::generate_successors(Node* n) {

	std::array<Node*, 8> nodes;

	// TOP
	nodes[0] = new Node(n->x, calc_y(n->y - 5));
	// BOTTOM
	nodes[1] = new Node(n->x, calc_y(n->y + TILE_HEIGHT + 5));
	// LEFT
	nodes[2] = new Node(calc_x(n->x - 5), n->y);
	// RIGHT
	nodes[3] = new Node(calc_x(n->x + TILE_WIDTH + 5), n->y);

	// TOP LEFT DIAGONAL
	nodes[4] = new Node(calc_x(n->x - 5), calc_y(n->y - 5));
	// TOP RIGHT DIAGNOAL
	nodes[5] = new Node(calc_x(n->x + TILE_WIDTH + 5), calc_y(n->y - 5));
	// BOTTOM LEFT DIAGNOAL
	nodes[6] = new Node(calc_x(n->x - 5), calc_y(n->y + TILE_HEIGHT + 5));
	// BOTTOM RIGHT DIAGNOAL
	nodes[7] = new Node(calc_x(n->x + TILE_WIDTH + 5), calc_y(n->y + TILE_HEIGHT + 5));

	// set diagonal to true for diagonal nodes
	for (int i = 4; i < 7; i++) {
		nodes[i]->diagonal = true;
	}

	return nodes;

}