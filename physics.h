//
// Created by Barto on 05.01.2023.
//

#ifndef MINECRAFT_PHYSICS_H
#define MINECRAFT_PHYSICS_H

#include "render/render.h"
#include "time.h"

bool colision(player * object1, ball * object2, Time* time);
bool field_colision(ball* ball,Time* time);

pos cal_position(v2 v0, pos p0, float t0x, float t0y, Time* time, float a);

#endif //MINECRAFT_PHYSICS_H
