#include "../include/MachineGun.h"

MachineGun::MachineGun() {};

MachineGun::MachineGun(float x, float y, SDL_Renderer* renderer, vector<Object*> targets) : Trap(x, y, targets, renderer, MACHINE_GUN_PNG, MACHINE_GUN) {
	// 2 seconds cooldown for cannon turret
	cooldown = 1;
}

void MachineGun::fire(vector<Object*>& list, vector<Object*>& bullets, std::array<Tile*, MAP_LENGTH>& map, double deltaTime) {
	bool target = false;

	// find target
	for (int i = 0; i < targets.size(); i++) {
		if (targets[i]->getType() == GUNNER_TAG || targets[i]->getType() == HEAVY_TAG || targets[i]->getType() == MELEE_TAG) {
			if (LineOfSight(&targets[i]->getCollisionRect(), 100, map, deltaTime)) {
				target = true;
			}
		}
	}
	// if no target do nothing
	if (!target) { return; }

	//fire at target
	if (!shot) {
		// calculate radian angle
		double radAngle = (90 - angle) * (PI / 180);

		// calculate middle values of cannon
		double originX = x + (double)collisionRect.w / 4;
		double originY = y + (double)collisionRect.h / 2;

		// set a radius for the circle
		int radius = -(collisionRect.h);

		// calculate x, y coordinates for the bullet to be fired
		double bX = originX - radius * cos(radAngle);
		double bY = originY + radius * sin(radAngle);

		Object* lol = new Player(500, 500, renderer);
		// create a cannon bullet object
		Object* cBullet = new MGBullet((float)bX, (float)bY, lol, angle, renderer);

		// insert into bullets vector
		bullets.insert(bullets.begin(), cBullet);

		shot = true;
		timer.start();
	}
	else {
		// if bullet was already previously shot, check if cooldown period has passed
		if (timer.getTicks() / 1000 >= cooldown) {
			// if the cooldown period has passed 
			// set shot to false and reset timer;
			shot = false;
			timer.stop();
		}
	}
}