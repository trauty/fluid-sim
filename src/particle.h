#pragma once

#include "glm/matrix.hpp"

struct Particle
{
    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec2 force;
    float_t density;
    float_t pressure;
};
