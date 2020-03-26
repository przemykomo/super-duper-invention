#shader vertex
#version 450 core
layout (location = 0) in vec3 aPos;

//uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * vec4(aPos, 1.0f);
}

#shader fragment
#version 450 core
out vec4 Color;

void main() {
    Color = vec4(0.5f, 0.0f, 0.0f, 0.0f);
}