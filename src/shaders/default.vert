#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 fColor;
out vec2 fTexCoord;

uniform mat4 transform;

void main()
{
    mat4 identityMatrix = mat4(
        vec4(1.0, 0.0, 0.0, 1.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );
    gl_Position = transform*vec4(aPos, 1.0);
    fColor = aColor;
    fTexCoord = aTexCoord;
}