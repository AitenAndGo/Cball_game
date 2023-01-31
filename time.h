//
// Created by Barto on 01.01.2023.
//

#ifndef MINECRAFT_TIME_H
#define MINECRAFT_TIME_H

#include "render/render.h"

typedef struct Time{
    double last_frame;
    double actual_frame;
    double deltaTime;
    int FPS;
    int Time_s;
}Time;

void time_f(Time* time);

#endif //MINECRAFT_TIME_H
