#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "glad/gl.h"
#include "SDL2/SDL.h"
#include "shader-file.h"
#include "SDL2/SDL_opengl.h"

class FluidSim
{
    public:
        GLuint vao;
        GLuint comp_tex;
        GLuint shader_program;
        GLuint compute_program;
        bool init();
        void execute();

    private:
        SDL_Window *window;
        SDL_GLContext ctx;
};