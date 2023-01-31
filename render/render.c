//
// Created by Barto on 29.12.2022.
//

#include "../Glad/include/glad/glad.h"
#include "render.h"
#include "../util.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#define SPEED 0.01

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void render_init(render* window){
    window->program = malloc(sizeof (draw));
    window->window = render_init_window(window->width, window->height);

    init_ball(window, 0, 0, 0.5f);
    init_player_1(window, -1, 0, 60);
    init_player_2(window, 1, 0, 60);
    init_field(window);

    init_shader(window);
}
void render_begin(render* window){
    //ustawinie koloru tła i wyczyszczenie buferu aby przygotować do rysowania
    glClearColor(0.0f, 0.3f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void render_end(GLFWwindow* window){
    glfwSwapBuffers(window);
    glfwPollEvents();
}

GLFWwindow* render_init_window(int width,int height){

    //ustawienie wersji na aktualną 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!glfwInit())
    {
        ERROR_EXIT("could not init GLFW: %s\n", glfwGetError((const char **) (const char *) "error"));
    }

    GLFWwindow* window = glfwCreateWindow(width, height, "Cball", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        ERROR_EXIT("Faild to init window: %s\n", glfwGetError((const char **) (const char *) "error"));
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        ERROR_EXIT("Failed to load GL: %s\n", glfwGetError((const char **) (const char *) "error"));
    }

    //ustwanienie odczytywania klakiszy z klawiatury do aktualneog okna
    glfwSetKeyCallback(window, key_callback);

    //zsynchronizowanie odświerzania ekranu i okna
    glfwSwapInterval(1);

    return window;
}

void init_ball(render* window, float x, float y, float mass){
    window->object = malloc(sizeof (object));

    window->object->ball = malloc((sizeof (ball)));
    window->object->ball->position.x = x;
    window->object->ball->position.y = y;
    window->object->ball->last_position.x = x;
    window->object->ball->last_position.y = y;
    window->object->ball->mass = mass;
    window->object->ball->is_moving = false;
    window->object->ball->R = 0.025f;
    window->object->ball->velocity.x = 0.0f;
    window->object->ball->velocity.y = 0.0f;
    window->object->ball->p0.x = x;
    window->object->ball->p0.y = y;
    window->object->ball->t0x = 0;
    window->object->ball->t0y = 0;
    window->object->ball->v0 = window->object->ball->velocity;

    glGenTextures(1, &window->object->ball->texture);
    glBindTexture(GL_TEXTURE_2D, window->object->ball->texture);
// set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("C:/Users/Barto/CLionProjects/mineCraft/mineCraft/assets/ball.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);

    Vertex* vertices = window->object->ball->vertices;

    for (int i = 0; i < 32; i++) {
        float angle = 2 * M_PI * i / 32;
        //next point of circle
        vertices[i].pos[0] = window->object->ball->R * cos(angle);
        vertices[i].pos[1] = window->object->ball->R * sin(angle);
        //color
        vertices[i].col[0] = 0.0f;
        vertices[i].col[1] = 0.0f;
        vertices[i].col[2] = 0.0f;
//        texture
        vertices[i].texpos[0] = (cos(angle) + 1) / 2;
        vertices[i].texpos[1] = (sin(angle) + 1) / 2;
    }


}

void init_player_2(render* window, float x, float y, float mass){
<<<<<<< HEAD

    window->object->player_2 = malloc((sizeof (player)));
    window->object->player_2->position.x = x;
    window->object->player_2->position.y = y;
    window->object->player_2->last_position.x = x;
    window->object->player_2->last_position.y = y;
    window->object->player_2->is_moving = false;
    window->object->player_2->mass = mass;
    window->object->player_2->R = 0.05f;
    window->object->player_2->velocity.x = 0.0f;
    window->object->player_2->velocity.y = 0.0f;
    window->object->player_2->p0.x = x;
    window->object->player_2->p0.y = y;
    window->object->player_2->t0x = 0;
    window->object->player_2->t0y = 0;
    window->object->player_2->v0 = window->object->player_2->velocity;
    window->object->player_2->kick = false;

    glGenTextures(1, &window->object->player_2->texture);
    glBindTexture(GL_TEXTURE_2D, window->object->player_2->texture);
// set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("C:/Users/Barto/CLionProjects/mineCraft/mineCraft/assets/ronaldo.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);

    Vertex* vertices = window->object->player_2->vertices;

    for (int i = 0; i < 32; i++) {
        float angle = 2 * M_PI * i / 32;
        //next point of circle
        vertices[i].pos[0] = window->object->player_2->R * cos(angle);
        vertices[i].pos[1] = window->object->player_2->R * sin(angle);
        //color
        vertices[i].col[0] = 0.0f;
        vertices[i].col[1] = 0.5f;
        vertices[i].col[2] = 1.0f;

        vertices[i].texpos[0] = (sin(angle) + 1) / 2;
        vertices[i].texpos[1] = (cos(angle) + 1) / 2;
    }

}

void init_player_1(render* window, float x, float y, float mass){

    window->object->player_1 = malloc((sizeof (player)));
    window->object->player_1->position.x = x;
    window->object->player_1->position.y = y;
    window->object->player_1->last_position.x = x;
    window->object->player_1->last_position.y = y;
    window->object->player_1->is_moving = false;
    window->object->player_1->mass = mass;
    window->object->player_1->R = 0.05f;
    window->object->player_1->velocity.x = 0.0f;
    window->object->player_1->velocity.y = 0.0f;
    window->object->player_1->p0.x = x;
    window->object->player_1->p0.y = y;
    window->object->player_1->t0x = 0;
    window->object->player_1->t0y = 0;
    window->object->player_1->v0 = window->object->player_1->velocity;
    window->object->player_1->kick = false;

    Vertex* vertices = window->object->player_1->vertices;
=======

    window->object->player_2 = malloc((sizeof (player)));
    window->object->player_2->position.x = x;
    window->object->player_2->position.y = y;
    window->object->player_2->last_position.x = x;
    window->object->player_2->last_position.y = y;
    window->object->player_2->is_moving = false;
    window->object->player_2->mass = mass;
    window->object->player_2->R = 0.05f;
    window->object->player_2->velocity.x = 0.0f;
    window->object->player_2->velocity.y = 0.0f;
    window->object->player_2->p0.x = x;
    window->object->player_2->p0.y = y;
    window->object->player_2->t0x = 0;
    window->object->player_2->t0y = 0;
    window->object->player_2->v0 = window->object->player_2->velocity;
    window->object->player_2->kick = false;

    glGenTextures(1, &window->object->player_2->texture);
    glBindTexture(GL_TEXTURE_2D, window->object->player_2->texture);
// set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("C:/Users/Barto/CLionProjects/mineCraft/mineCraft/assets/ronaldo.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);

    Vertex* vertices = window->object->player_2->vertices;
>>>>>>> main

    for (int i = 0; i < 32; i++) {
        float angle = 2 * M_PI * i / 32;
        //next point of circle
<<<<<<< HEAD
        vertices[i].pos[0] = window->object->player_1->R * cos(angle);
        vertices[i].pos[1] = window->object->player_1->R * sin(angle);
=======
        vertices[i].pos[0] = window->object->player_2->R * cos(angle);
        vertices[i].pos[1] = window->object->player_2->R * sin(angle);
>>>>>>> main
        //color
        vertices[i].col[0] = 0.0f;
        vertices[i].col[1] = 0.5f;
        vertices[i].col[2] = 1.0f;

        vertices[i].texpos[0] = (sin(angle) + 1) / 2;
        vertices[i].texpos[1] = (cos(angle) + 1) / 2;
<<<<<<< HEAD
    }

    glGenBuffers(1, &window->program->vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, window->program->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 32, window->object->player_1->vertices, GL_STATIC_DRAW);

    glGenTextures(1, &window->object->player_1->texture);
    glBindTexture(GL_TEXTURE_2D, window->object->player_1->texture);
// set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("C:/Users/Barto/CLionProjects/mineCraft/mineCraft/assets/messi.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);
}

=======
    }

}

void init_player_1(render* window, float x, float y, float mass){

    window->object->player_1 = malloc((sizeof (player)));
    window->object->player_1->position.x = x;
    window->object->player_1->position.y = y;
    window->object->player_1->last_position.x = x;
    window->object->player_1->last_position.y = y;
    window->object->player_1->is_moving = false;
    window->object->player_1->mass = mass;
    window->object->player_1->R = 0.05f;
    window->object->player_1->velocity.x = 0.0f;
    window->object->player_1->velocity.y = 0.0f;
    window->object->player_1->p0.x = x;
    window->object->player_1->p0.y = y;
    window->object->player_1->t0x = 0;
    window->object->player_1->t0y = 0;
    window->object->player_1->v0 = window->object->player_1->velocity;
    window->object->player_1->kick = false;

    Vertex* vertices = window->object->player_1->vertices;

    for (int i = 0; i < 32; i++) {
        float angle = 2 * M_PI * i / 32;
        //next point of circle
        vertices[i].pos[0] = window->object->player_1->R * cos(angle);
        vertices[i].pos[1] = window->object->player_1->R * sin(angle);
        //color
        vertices[i].col[0] = 0.0f;
        vertices[i].col[1] = 0.5f;
        vertices[i].col[2] = 1.0f;

        vertices[i].texpos[0] = (sin(angle) + 1) / 2;
        vertices[i].texpos[1] = (cos(angle) + 1) / 2;
    }

    glGenBuffers(1, &window->program->vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, window->program->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 32, window->object->player_1->vertices, GL_STATIC_DRAW);

    glGenTextures(1, &window->object->player_1->texture);
    glBindTexture(GL_TEXTURE_2D, window->object->player_1->texture);
// set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("C:/Users/Barto/CLionProjects/mineCraft/mineCraft/assets/messi.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);
}

>>>>>>> main
void init_field(render* window){

    window->object->field = malloc(sizeof(field));

    glGenTextures(1, &window->object->field->texture);
    glBindTexture(GL_TEXTURE_2D, window->object->field->texture);
// set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("C:/Users/Barto/CLionProjects/mineCraft/mineCraft/assets/boisko.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    Vertex* vertices = window->object->field->vertices;

    vertices[0].pos[0] = -1.6f;
    vertices[0].pos[1] = 0.9f;
    vertices[0].col[0] = 1;
    vertices[0].col[1] = 1;
    vertices[0].col[2] = 1;
    vertices[0].texpos[0] = 0;
    vertices[0].texpos[1] = 1;

    vertices[1].pos[0] = -1.6f;
    vertices[1].pos[1] = -0.9f;
    vertices[1].col[0] = 1;
    vertices[1].col[1] = 1;
    vertices[1].col[2] = 1;
    vertices[1].texpos[0] = 0;
    vertices[1].texpos[1] = 0;


    vertices[2].pos[0] = 1.6f;
    vertices[2].pos[1] = -0.9f;
    vertices[2].col[0] = 1;
    vertices[2].col[1] = 1;
    vertices[2].col[2] = 1;
    vertices[2].texpos[0] = 1;
    vertices[2].texpos[1] = 0;


    vertices[3].pos[0] = 1.6f;
    vertices[3].pos[1] = 0.9f;
    vertices[3].col[0] = 1;
    vertices[3].col[1] = 1;
    vertices[3].col[2] = 1;
    vertices[3].texpos[0] = 1;
    vertices[3].texpos[1] = 1;
}
