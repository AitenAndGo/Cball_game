//
// Created by Barto on 29.12.2022.
//

#ifndef RENDER_H
#define RENDER_H

#include "../linmath.h"
#include <GLFW/glfw3.h>
#include "../time.h"
#include "stdbool.h"

typedef struct {
    float x;
    float y;
}pos;

typedef struct {
    float x;
    float y;
}v2;

typedef struct{
    vec2 pos;
    vec3 col;
    vec2 texpos;
} Vertex;

typedef struct {
    GLuint texture;
    Vertex vertices[4];
}field;

typedef struct {
    mat4x4 mpv;
    pos position;
    pos p0;
    bool is_moving;
    float mass;
    pos last_position;
    float R;
    v2 v0;
    v2 velocity;
    float t0x;
    float t0y;
    float a;
    bool kick;
    GLuint texture;
    Vertex vertices[32];
}player;

typedef struct {
    mat4x4 mpv;
    pos position;
    float mass;
    pos last_position;
    float kick_time;
    bool is_moving;
    float R;
    v2 velocity;
    float t0x;
    float t0y;
    v2 v0;
    pos p0;
    float a;
    GLuint texture;
    Vertex vertices[32];
}ball;

typedef struct {
    mat4x4 mpv;
    pos position;
    float R;
}goal;

typedef struct {
    GLuint program;
    GLint mvp_location;
    GLint vpos_location;
    GLint vcol_location;
    GLint vtex_location;
    GLuint vertex_array;
    GLint color_uniform;
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint vertex_buffer;
}draw;

typedef struct {
    player* player_1;
    player* player_2;
    ball* ball;
    field* field;
}object;

typedef struct {
    GLFWwindow* window;
    int width;
    int height;
    draw* program;
    object* object;
}render;


void render_init(render* window);
void render_begin(render* window);
void render_end(GLFWwindow* window);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
GLFWwindow* render_init_window(int width, int height);
void init_triangle();
void init_shader(render* window);
void init_player_1(render* window, float x, float y, float mass);
void init_player_2(render* window, float x, float y, float mass);
void init_ball(render* window, float x, float y, float mass);
void init_field(render* window);

#endif //RENDER_H
