#pragma once
#include <cmath>
#include <vector>
#include <SDL.h>
#include "constants.h"

// check for collision between two given objects
bool checkCollision(SDL_Rect &a, SDL_Rect &b, int yOffset);

// calculate unit vectors from difference given
double* calcVector(double diff_x, double diff_y);

// calculate angle according to SDL coordinates given x and y values
double calcAngle(double diff_x, double diff_y);
