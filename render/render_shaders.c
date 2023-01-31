//
// Created by Barto on 01.01.2023.
//
#include "glad/glad.h"
#include "render.h"

void init_shader(render* window){

    static const char* vertex_shader_text =
            "#version 330\n"
            "uniform mat4 MVP;\n"
            "in vec3 vCol;\n"
            "in vec2 vPos;\n"
            "in vec2 vTex;\n"
            "out vec3 color;\n"
            "out vec2 texpos;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
            "    color = vCol;\n"
            "    texpos = vTex;\n"
            "}\n";


    static const char* fragment_shader_text =
            "#version 330\n"
            "in vec3 color;\n"
            "in vec2 texpos;\n"
            "out vec4 fragment;\n"
            "uniform sampler2D ourTexture;\n"
            "void main()\n"
            "{\n"
//            "    fragment = vec4(color, 1.0);\n"
            "    fragment = texture(ourTexture, texpos);\n"
            "}\n";

    window->program->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(window->program->vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(window->program->vertex_shader);

    window->program->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(window->program->fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(window->program->fragment_shader);

    window->program->program = glCreateProgram();
    glAttachShader(window->program->program, window->program->vertex_shader);
    glAttachShader(window->program->program, window->program->fragment_shader);
    glLinkProgram(window->program->program);

    window->program->mvp_location = glGetUniformLocation(window->program->program, "MVP");
    window->program->vpos_location = glGetAttribLocation(window->program->program, "vPos");
    window->program->vcol_location = glGetAttribLocation(window->program->program, "vCol");
    window->program->vtex_location = glGetAttribLocation(window->program->program, "vTex");

    glGenVertexArrays(1, &window->program->vertex_array);
    glBindVertexArray(window->program->vertex_array);
    glEnableVertexAttribArray(window->program->vpos_location);
    glVertexAttribPointer(window->program->vpos_location, 2, GL_FLOAT, GL_FALSE,
    sizeof(Vertex), (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(window->program->vcol_location);
    glVertexAttribPointer(window->program->vcol_location, 3, GL_FLOAT, GL_FALSE,
    sizeof(Vertex), (void*) offsetof(Vertex, col));
    glEnableVertexAttribArray(window->program->vtex_location);
    glVertexAttribPointer(window->program->vtex_location, 2, GL_FLOAT, GL_FALSE,
    sizeof(Vertex), (void*) offsetof(Vertex, texpos));
}