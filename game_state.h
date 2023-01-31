//
// Created by Barto on 10.01.2023.
//

#ifndef MINECRAFT_GAME_STATE_H
#define MINECRAFT_GAME_STATE_H

#include "render/render.h"
#include "time.h"

int game_state(render* window, Time* time);
void restart_game(render* window);

#endif //MINECRAFT_GAME_STATE_H
