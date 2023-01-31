//
// Created by Barto on 01.01.2023.
//

#include "time.h"
#include "render/render.h"
#include <stdio.h>
#include <stdlib.h>

void time_f(Time* time){
    //system("cls");
    time->actual_frame = glfwGetTime();
    if (time->actual_frame < 0.1){
        time->last_frame = 0;
        time->Time_s = 0;
    }

    time->deltaTime = time->actual_frame - time->last_frame;

    time->FPS =  1.0 / time->deltaTime;

    if (time->actual_frame - time->Time_s > 1){
        time->Time_s = (int)time->actual_frame;
        printf("FPS: %i\n", time->FPS);
    }

    time->last_frame = time->actual_frame;
}
