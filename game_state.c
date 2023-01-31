//
// Created by Barto on 10.01.2023.
//
#include "render/render.h"
#include "game_state.h"
#include <stdio.h>

int game_state(render* window, Time* time){
    if(window->object->ball->position.x > (1.6 + window->object->ball->R)){
        printf("BLUE GOAL!!!!!!!!!!!!!!!!\n");
        restart_game(window);
        return 1;
    } else if(window->object->ball->position.x < (-1.6 - window->object->ball->R)){
        printf("ORANGE GOAL!!!!!!!!!!!!!!!!\n");
        restart_game(window);
        return 2;
    }
    return 0;
}

void restart_game(render* window){

    //restart_ball
    window->object->ball->position.x = 0;
    window->object->ball->position.y = 0;
    window->object->ball->last_position.x = 0;
    window->object->ball->last_position.y = 0;
    window->object->ball->is_moving = false;
    window->object->ball->velocity.x = 0.0f;
    window->object->ball->velocity.y = 0.0f;
    window->object->ball->p0.x = 0;
    window->object->ball->p0.y = 0;
    window->object->ball->t0x = 0;
    window->object->ball->t0y = 0;
    window->object->ball->v0.x = 0;
    window->object->ball->v0.y = 0;

    //player_2
    window->object->player_2->position.x = 1;
    window->object->player_2->position.y = 0;
    window->object->player_2->last_position.x = 1;
    window->object->player_2->last_position.y = 0;
    window->object->player_2->is_moving = false;
    window->object->player_2->velocity.x = 0.0f;
    window->object->player_2->velocity.y = 0.0f;
    window->object->player_2->p0.x = 1;
    window->object->player_2->p0.y = 0;
    window->object->player_2->t0x = 0;
    window->object->player_2->t0y = 0;
    window->object->player_2->v0.x = 1;
    window->object->player_2->v0.y = 0;
    window->object->player_2->kick = false;

    //player_1
    window->object->player_1->position.x = -1;
    window->object->player_1->position.y = 0;
    window->object->player_1->last_position.x = -1;
    window->object->player_1->last_position.y = 0;
    window->object->player_1->is_moving = false;
    window->object->player_1->velocity.x = 0.0f;
    window->object->player_1->velocity.y = 0.0f;
    window->object->player_1->p0.x = -1;
    window->object->player_1->p0.y = 0;
    window->object->player_1->t0x = 0;
    window->object->player_1->t0y = 0;
    window->object->player_1->v0.x = -1;
    window->object->player_1->v0.y = 0;
    window->object->player_1->kick = false;
}
