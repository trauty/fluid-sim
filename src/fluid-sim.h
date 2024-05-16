#pragma once

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "glad/gl.h"
#include "SDL2/SDL.h"
#include "shader-file.h"
#include "SDL2/SDL_opengl.h"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/random.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_opengl3_loader.h"
#include "imgui_impl_sdl2.h"
#include "particle.h"
#include "constants.h"

class FluidSim
{
    public:
        GLuint vao;
        GLuint comp_tex;
        GLuint shader_program;

        uint32_t num_particles = 400;
        glm::vec2 gravity = glm::vec2(0.0f, -10.0f);
        float_t rest_dens = 300.0f;
        float_t gas_const = 2000.0f;
        float_t smoothing_radius = 28.0f;
        float_t smoothing_radius_q = smoothing_radius * smoothing_radius;
        float_t mass = 20.0f;
        float_t visc = 1.0f;
        float_t time_step = 1.0f / 60.0f;

        const float_t poly6 = 4.0f / (Constants::PI * std::pow(smoothing_radius, 8.0f));
        const float_t spiky_grad = -10.0f / (Constants::PI * std::pow(smoothing_radius, 5.0f));
        const float_t visc_lap = 40.0f / (Constants::PI * std::pow(smoothing_radius, 5.0f));

        float_t boundary_eps = smoothing_radius;
        float_t boundary_damping = -0.5f;

        float_t delta_time;

        bool init();
        void execute();

    private:
        SDL_Window *window;
        SDL_GLContext ctx;

        float_t particle_scale = 8.0f;

        void update(std::vector<Particle> &particles, std::vector<glm::mat4> &model_matrices, uint32_t w, uint32_t h);
        void compute_density_pressure(std::vector<Particle> &particles);
        void compute_forces(std::vector<Particle> &particles);
        void integrate(std::vector<Particle> &particles, uint32_t w, uint32_t h);
};