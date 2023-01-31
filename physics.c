//
// Created by Barto on 05.01.2023.
//

#include "render/render.h"
#include "physics.h"
#include "math.h"

#define g 0.7

#include <stdio.h>

bool colision(player* object1, ball* object2, Time* time){
    if (fabs(object1->position.x - object2->position.x) <= (object1->R + object2->R)
        && fabs(object1->position.y - (object2->position.y)) <= (object1->R + object2->R)){

        return true;
    }
    return false;
}

bool field_colision(ball* ball,Time* time){
    if (ball->position.y >= 0.9 - ball->R){
        ball->v0.y *= -1;
        return true;
    }
    if (ball->position.y <= -0.9 + ball->R){
        ball->v0.y *= -1;
        return true;
    }
<<<<<<< HEAD
    if (ball->position.y > 0.2){
        if (ball->position.x >= 1.6){
=======
    if (ball->position.y >= 0.2){
        if (ball->position.x >= 1.6 - ball->R){
>>>>>>> main
            ball->v0.x *= -1;
            return true;
        }
    }
<<<<<<< HEAD
    if (ball->position.y > 0.2){
        if (ball->position.x <= -1.6){
=======
    if (ball->position.y >= 0.2){
        if (ball->position.x <= -1.6 + ball->R){
>>>>>>> main
            ball->v0.x *= -1;
            return true;
        }
    }
<<<<<<< HEAD
    if (ball->position.y < -0.2){
        if (ball->position.x >= 1.6){
=======
    if (ball->position.y <= -0.2){
        if (ball->position.x >= 1.6 - ball->R){
>>>>>>> main
            ball->v0.x *= -1;
            return true;
        }
    }
<<<<<<< HEAD
    if (ball->position.y < -0.2){
        if (ball->position.x <= -1.6){
=======
    if (ball->position.y <= -0.2){
        if (ball->position.x <= -1.6 + ball->R){
>>>>>>> main
            ball->v0.x *= -1;
            return true;
        }
    }
    return false;
}


pos cal_position(v2 v0, pos p0, float t0x, float t0y, Time* time, float a){
    pos p1 = p0;
    float tx = (time->actual_frame + time->deltaTime) - t0x;
    float ty = (time->actual_frame + time->deltaTime) - t0y;


    float ax, ay;

        ax = fabs(cos(a));
        ay = fabs(sin(a));

    if (v0.x > 0) {
        p1.x = p0.x + (v0.x * tx) - (g * ax * pow(tx, 2));
    } else if (v0.x < 0){
        p1.x = p0.x + (v0.x * tx) + (g * ax * pow(tx, 2));
    }

    if (v0.y > 0) {
        p1.y = p0.y + (v0.y * tx) - (g * ay * pow(tx, 2));
    } else if (v0.y < 0){
        p1.y = p0.y + (v0.y * tx) + (g * ay * pow(tx, 2));
    }
    //printf("p1 x: %lf   y: %lf    v0x: %lf    v0y: %lf        tx: %lf\n", p1.x, p1.y, v0.x, v0.y, tx);

    return p1;
}