#include "../include/MachineGun.h"

MachineGun::MachineGun() {};

MachineGun::MachineGun(float x, float y, SDL_Renderer* renderer) : Trap(x, y, renderer, MACHINE_GUN_PNG, MACHINE_GUN) {
	// 2 seconds cooldown for cannon turret
	cooldown = 1;
}

void MachineGun::fire(vector<Object*>& list, vector<Object*>& bullets, double deltaTime) {
	Object* target = getTarget(list);

	// if target is found, then shoot bullets
	if (true) {

		if (!shot) {
			// calculate radian angle
			double radAngle = (90 - angle) * (PI / 180);

			// calculate middle values of cannon
			double originX = x + (double)collisionRect.w / 2;
			double originY = y + (double)collisionRect.h / 2;

			// set a radius for the circle
			int radius = -20;

			// calculate x, y coordinates for the bullet to be fired
			double bX = originX - radius * cos(radAngle);
			double bY = originY + radius * sin(radAngle);

			Object* lol = new Player(500, 500, renderer);
			// create a cannon bullet object
			Object* cBullet = new MGBullet(bX, bY, lol, renderer);

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
	// if target not found, do nothing
	else return;
}