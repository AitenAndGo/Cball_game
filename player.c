//
// Created by Barto on 02.01.2023.
//

#include "glad/glad.h"
#include "render/render.h"
#include "player.h"
#include <math.h>
#include <stdio.h>

#include "physics.h"

#define SPEED 0.1
#define MAX_SPEED 0.25
#define SPEED_BALL 0.25

void draw_field(render* window, Time* time){

    int w, h;
    glfwGetFramebufferSize(window->window, &w, &h);
    const float ratio = w / (float) h;
    glViewport(0, 0, w, h);

    mat4x4 p, mpv;
    mat4x4_identity(mpv);
    mat4x4_ortho(p, -ratio, ratio, -1.0f, 1.0f, 1.f, -1.f);
    mat4x4_mul(mpv, p, mpv);

    glBindBuffer(GL_ARRAY_BUFFER, window->program->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, window->object->field->vertices, GL_STATIC_DRAW);

    glUseProgram(window->program->program);
    glUniformMatrix4fv(window->program->mvp_location, 1, GL_FALSE, (const GLfloat *) &mpv);
    glBindTexture(GL_TEXTURE_2D, window->object->field->texture);
    glBindVertexArray(window->program->vertex_array);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void draw_player_1(render* window, Time* time){

    glBindBuffer(GL_ARRAY_BUFFER, window->program->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 32, window->object->player_1->vertices, GL_STATIC_DRAW);

    upgrade_position(window, time, window->object->player_1);

    glUseProgram(window->program->program);
    glUniformMatrix4fv(window->program->mvp_location, 1, GL_FALSE, (const GLfloat*) &window->object->player_1->mpv);
    glBindTexture(GL_TEXTURE_2D, window->object->player_1->texture);
    glBindVertexArray(window->program->vertex_array);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 32);
}

void draw_player_2(render* window, Time* time){

    glBindBuffer(GL_ARRAY_BUFFER, window->program->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 32, window->object->player_2->vertices, GL_STATIC_DRAW);

    upgrade_position(window, time, window->object->player_2);

    glUseProgram(window->program->program);
    glUniformMatrix4fv(window->program->mvp_location, 1, GL_FALSE, (const GLfloat*) &window->object->player_2->mpv);
    glBindTexture(GL_TEXTURE_2D, window->object->player_2->texture);
    glBindVertexArray(window->program->vertex_array);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 32);
}

void draw_ball(render* window, Time* time){

    glBindBuffer(GL_ARRAY_BUFFER, window->program->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 32, window->object->ball->vertices, GL_STATIC_DRAW);

    //upgrade_position(window);
    int w, h;
    glfwGetFramebufferSize(window->window, &w, &h);
    const float ratio = w / (float) h;
    glViewport(0, 0, w, h);

    if (colision(window->object->player_1, window->object->ball, time) && window->object->player_1->kick == false){
        window->object->ball->t0x = time->actual_frame;
        float a = atan(fabs(window->object->ball->position.y - window->object->player_1->position.y) / fabs(window->object->ball->position.x - window->object->player_1->position.x));
        window->object->ball->v0.x = SPEED_BALL * cos(a);
        window->object->ball->v0.y = SPEED_BALL * sin(a);
        window->object->ball->a = fabs(a);
        if(window->object->ball->position.x - window->object->player_1->position.x < 0) {
            window->object->ball->v0.x *= -1;
        }
        if(window->object->ball->position.y - window->object->player_1->position.y < 0) {
            window->object->ball->v0.y *= -1;
        }
        window->object->ball->is_moving = true;
        window->object->player_1->kick = true;
    } else if (fabs(window->object->player_1->position.x - window->object->ball->position.x) >= (window->object->player_1->R + window->object->ball->R)
               || fabs(window->object->player_1->position.y - window->object->ball->position.y) >= (window->object->player_1->R + window->object->ball->R))
        window->object->player_1->kick = false;


    if (colision(window->object->player_2, window->object->ball, time) && window->object->player_2->kick == false) {
        window->object->ball->t0x = time->actual_frame;
        float a = atan(fabs(window->object->ball->position.y - window->object->player_2->position.y) / fabs(window->object->ball->position.x - window->object->player_2->position.x));
        window->object->ball->a = fabs(a);
        window->object->ball->v0.x = SPEED_BALL * cos(a);
        window->object->ball->v0.y = SPEED_BALL * sin(a);
        if(window->object->ball->position.x - window->object->player_2->position.x < 0) {
            window->object->ball->v0.x *= -1;
        }
        if(window->object->ball->position.y - window->object->player_2->position.y < 0) {
            window->object->ball->v0.y *= -1;
        }
        window->object->ball->is_moving = true;
        window->object->player_2->kick = true;
    } else if (fabs(window->object->player_2->position.x - window->object->ball->position.x) >= (window->object->player_2->R + window->object->ball->R)
    || fabs(window->object->player_2->position.y - window->object->ball->position.y) >= (window->object->player_2->R + window->object->ball->R))
        window->object->player_2->kick = false;

    if (field_colision(window->object->ball, time)){

    }

    if (window->object->ball->is_moving){
        window->object->ball->position = cal_position(window->object->ball->v0, window->object->ball->position, window->object->ball->t0x, 0, time, window->object->ball->a);
    }

    if (window->object->ball->v0.x > 0){
        if ((window->object->ball->position.x - window->object->ball->last_position.x) < 0){
            window->object->ball->is_moving = false;
            window->object->ball->position.x = window->object->ball->last_position.x;
            //printf("right\n");
        }
    }
    if (window->object->ball->v0.x < 0){
        if ((window->object->ball->position.x - window->object->ball->last_position.x) > 0){
            window->object->ball->is_moving = false;
            window->object->ball->position.x = window->object->ball->last_position.x;
            //printf("left\n");
        }
    }
    if (window->object->ball->v0.y > 0){
        if ((window->object->ball->position.y - window->object->ball->last_position.y) < 0){
            window->object->ball->is_moving = false;
            window->object->ball->position.y = window->object->ball->last_position.y;
            //printf("up\n");
        }
    }
    if (window->object->ball->v0.y < 0){
        if ((window->object->ball->position.y - window->object->ball->last_position.y) > 0){
            window->object->ball->is_moving = false;
            window->object->ball->position.y = window->object->ball->last_position.y;
            //printf("down\n");
        }
    }

    window->object->ball->velocity.x = (window->object->ball->position.x - window->object->ball->last_position.x) / time->deltaTime;
    window->object->ball->velocity.y = (window->object->ball->position.y - window->object->ball->last_position.y) / time->deltaTime;

    mat4x4 m, p;
    mat4x4_identity(m);
    mat4x4_translate(m, window->object->ball->position.x, window->object->ball->position.y, 0);
    mat4x4_ortho(p, -ratio, ratio, -1.0f, 1.0f, 1.f, -1.f);
    mat4x4_mul(window->object->ball->mpv, p, m);

    glUseProgram(window->program->program);
    glUniformMatrix4fv(window->program->mvp_location, 1, GL_FALSE, (const GLfloat*) &window->object->ball->mpv);
    glBindTexture(GL_TEXTURE_2D, window->object->ball->texture);
    glBindVertexArray(window->program->vertex_array);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 32);


        window->object->ball->last_position.x = window->object->ball->position.x;
        window->object->ball->last_position.y = window->object->ball->position.y;

    window->object->player_1->last_position.x = window->object->player_1->position.x;
    window->object->player_1->last_position.y = window->object->player_1->position.y;

    window->object->player_2->last_position.x = window->object->player_2->position.x;
    window->object->player_2->last_position.y = window->object->player_2->position.y;
}

void upgrade_position(render* window, Time* time, player* player){

    int width, height;
    glfwGetFramebufferSize(window->window, &width, &height);
    const float ratio = width / (float) height;
    glViewport(0, 0, width, height);

    if (player == window->object->player_1)
        input_upgrade_player_1(window, time);
    else
        input_upgrade_player_2(window, time);

    if ((player->v0.x) >= MAX_SPEED){
        player->v0.x = MAX_SPEED;
    } else if (player->v0.x <= -MAX_SPEED)
        player->v0.x = -MAX_SPEED;
    if ((player->v0.y) >= MAX_SPEED){
        player->v0.y = MAX_SPEED;
    } else if (player->v0.y <= -MAX_SPEED)
        player->v0.y = -MAX_SPEED;


    if (player->is_moving) {
        player->position = cal_position(player->v0, player->p0, player->t0x, player->t0y, time, 1);
        //printf("v0: %lf, %lf        p0: %lf, %lf       t0: %lf           pos: %lf\n", player->v0.x, player->v0.y, player->p0.x, player->p0.y, player->t0, player->position.x);
    }

//    if (fabs(player->last_position.x - player->position.x)  < 0.01 && fabs(player->last_position.y - player->position.y)  < 0.01){
//        player->is_moving = false;
//    }


    if (player->v0.x > 0){
        if ((player->position.x - player->last_position.x) < 0){
            player->is_moving = false;
            player->position.x = player->last_position.x;
            //printf("right\n");
        }
    }
    if (player->v0.x < 0){
        if ((player->position.x - player->last_position.x) > 0){
            player->is_moving = false;
            player->position.x = player->last_position.x;
            //printf("left\n");
        }
    }
    if (player->v0.y > 0){
        if ((player->position.y - player->last_position.y) < 0){
            player->is_moving = false;
            player->position.y = player->last_position.y;
            //printf("up\n");
        }
    }
    if (player->v0.y < 0){
        if ((player->position.y - player->last_position.y) > 0){
            player->is_moving = false;
            player->position.y = player->last_position.y;
            //printf("down\n");
        }
    }

    player->velocity.x = (player->position.x - player->last_position.x) / time->deltaTime;
    player->velocity.y = (player->position.y - player->last_position.y) / time->deltaTime;
//
    if (player->velocity.x == 0){
        player->v0.x = 0;
    }
    if (player->velocity.y == 0){
        player->v0.y = 0;
    }

    mat4x4 m, p;
    mat4x4_identity(m);
    mat4x4_translate(m, player->position.x, player->position.y, 0);
    mat4x4_ortho(p, -ratio, ratio, -1.0f, 1.0f, 1.f, -1.f);
    mat4x4_mul(player->mpv, p, m);
}

void input_upgrade_player_1(render* window, Time* time) {
    if(glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS
       && glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS){
        window->object->player_1->v0.y += SPEED * sqrtf(2);
        window->object->player_1->v0.x += -SPEED * sqrtf(2);
        window->object->player_1->t0x = time->actual_frame;
        window->object->player_1->p0 = window->object->player_1->position;
        window->object->player_1->is_moving = true;
        return;
    }
    if(glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS
       && glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS){
        window->object->player_1->v0.y += -SPEED * sqrtf(2);
        window->object->player_1->v0.x += -SPEED * sqrtf(2);
        window->object->player_1->t0x = time->actual_frame;
        window->object->player_1->p0 = window->object->player_1->position;
        window->object->player_1->is_moving = true;
        return;
    }
    if(glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS
       && glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS){
        window->object->player_1->v0.y += SPEED * sqrtf(2);
        window->object->player_1->v0.x += SPEED * sqrtf(2);
        window->object->player_1->t0x = time->actual_frame;
        window->object->player_1->p0 = window->object->player_1->position;
        window->object->player_1->is_moving = true;
        return;
    }
    if(glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS
       && glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS){
        window->object->player_1->v0.y += -SPEED * sqrtf(2);
        window->object->player_1->v0.x += SPEED * sqrtf(2);
        window->object->player_1->t0x = time->actual_frame;
        window->object->player_1->p0 = window->object->player_1->position;
        window->object->player_1->is_moving = true;
        return;
    }

    if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS) {
        window->object->player_1->v0.y += SPEED;
        window->object->player_1->v0.x = 0;
        window->object->player_1->t0x = time->actual_frame;
        window->object->player_1->p0 = window->object->player_1->position;
        window->object->player_1->a = 1.570796326795f;
        window->object->player_1->is_moving = true;
    }
    if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS) {
        window->object->player_1->v0.y -= SPEED;
        window->object->player_1->v0.x = 0;
        window->object->player_1->t0x = time->actual_frame;
        window->object->player_1->p0 = window->object->player_1->position;
        window->object->player_1->is_moving = true;
        window->object->player_1->a = 1.570796326795f;
    }
    if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS) {
        window->object->player_1->v0.x -= SPEED;
        window->object->player_1->v0.y = 0;
        window->object->player_1->t0x = time->actual_frame;
        window->object->player_1->p0 = window->object->player_1->position;
        window->object->player_1->is_moving = true;
        window->object->player_1->a = 0.0f;
    }
    if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS) {
        window->object->player_1->v0.x += SPEED;
        window->object->player_1->v0.y = 0;
        window->object->player_1->t0x = time->actual_frame;
        window->object->player_1->p0 = window->object->player_1->position;
        window->object->player_1->is_moving = true;
        window->object->player_1->a = 0.0f;
    }
}

void input_upgrade_player_2(render* window, Time* time) {

    if(glfwGetKey(window->window, GLFW_KEY_UP) == GLFW_PRESS
    && glfwGetKey(window->window, GLFW_KEY_LEFT) == GLFW_PRESS){
        window->object->player_2->v0.y += SPEED * sqrtf(2);
        window->object->player_2->v0.x += -SPEED * sqrtf(2);
        window->object->player_2->t0x = time->actual_frame;
        window->object->player_2->p0 = window->object->player_2->position;
        window->object->player_2->is_moving = true;
        return;
    }
    if(glfwGetKey(window->window, GLFW_KEY_DOWN) == GLFW_PRESS
       && glfwGetKey(window->window, GLFW_KEY_LEFT) == GLFW_PRESS){
        window->object->player_2->v0.y += -SPEED * sqrtf(2);
        window->object->player_2->v0.x += -SPEED * sqrtf(2);
        window->object->player_2->t0x = time->actual_frame;
        window->object->player_2->p0 = window->object->player_2->position;
        window->object->player_2->is_moving = true;
        return;
    }
    if(glfwGetKey(window->window, GLFW_KEY_UP) == GLFW_PRESS
       && glfwGetKey(window->window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        window->object->player_2->v0.y += SPEED * sqrtf(2);
        window->object->player_2->v0.x += SPEED * sqrtf(2);
        window->object->player_2->t0x = time->actual_frame;
        window->object->player_2->p0 = window->object->player_2->position;
        window->object->player_2->is_moving = true;
        return;
    }
    if(glfwGetKey(window->window, GLFW_KEY_DOWN) == GLFW_PRESS
       && glfwGetKey(window->window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        window->object->player_2->v0.y += -SPEED * sqrtf(2);
        window->object->player_2->v0.x += SPEED * sqrtf(2);
        window->object->player_2->t0x = time->actual_frame;
        window->object->player_2->p0 = window->object->player_2->position;
        window->object->player_2->is_moving = true;
        return;
    }

    if (glfwGetKey(window->window, GLFW_KEY_UP) == GLFW_PRESS) {
        window->object->player_2->v0.y += SPEED;
        window->object->player_2->v0.x = 0;
        window->object->player_2->t0x = time->actual_frame;
        window->object->player_2->p0 = window->object->player_2->position;
        window->object->player_2->is_moving = true;
    }
    if (glfwGetKey(window->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        window->object->player_2->v0.y -= SPEED;
        window->object->player_2->v0.x = 0;
        window->object->player_2->t0x = time->actual_frame;
        window->object->player_2->p0 = window->object->player_2->position;
        window->object->player_2->is_moving = true;
    }
    if (glfwGetKey(window->window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        window->object->player_2->v0.x -= SPEED;
        window->object->player_2->v0.y = 0;
        window->object->player_2->t0x = time->actual_frame;
        window->object->player_2->p0 = window->object->player_2->position;
        window->object->player_2->is_moving = true;
    }
    if (glfwGetKey(window->window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        window->object->player_2->v0.x += SPEED;
        window->object->player_2->v0.y = 0;
        window->object->player_2->t0x = time->actual_frame;
        window->object->player_2->p0 = window->object->player_2->position;
        window->object->player_2->is_moving = true;
    }
}