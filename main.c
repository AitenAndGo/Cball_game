#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "render/render.h"
#include "player.h"
#include "game_state.h"
#include "time.h"

#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    render* window = malloc(sizeof (render));
    window->height = 720;
    window->width = 1300;

    //inicjalizacja okna i shaderów
    render_init(window);

    Time* time = malloc(sizeof (Time));

    while (!glfwWindowShouldClose(window->window)) {

        render_begin((render *) window->window);

        draw_field(window, time);
        draw_player_1(window, time);
        draw_player_2(window, time);
        draw_ball(window, time);
        game_state(window, time);

        time_f(time);

        render_end(window->window);
        }

    glfwDestroyWindow(window->window);
    glfwTerminate();


    //free all memory
    free(time);
    free(window->program);
    free(window->object->player_1);
    free(window->object->player_2);
    free(window->object->ball);
    free(window->object);
    free(window);
    return 0;
}
