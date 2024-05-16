#version 430 core

layout (location = 0) in vec3 aPos;

uniform mat4 ortho;
uniform mat4 view;

layout (binding = 1, std430) readonly buffer ssbo1 
{
    mat4 offsets[];
};

void main()
{
    gl_Position = ortho * view * offsets[gl_InstanceID] * vec4(aPos , 1.0);
}