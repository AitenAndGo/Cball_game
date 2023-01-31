//
// Created by Barto on 02.01.2023.
//

#ifndef MINECRAFT_PLAYER_H
#define MINECRAFT_PLAYER_H

#include "render/render.h"
#include "time.h"

void draw_player_1(render* window, Time* time);
void draw_player_2(render* window, Time* time);
void draw_ball(render* window, Time* time);
void upgrade_position(render* window, Time* time, player* player);
void input_upgrade_player_1(render* window, Time* time);
void input_upgrade_player_2(render* window, Time* time);
void draw_goal(render* window, Time* time);
void draw_field(render* window, Time* time);

#endif //MINECRAFT_PLAYER_H
