#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;  // position in world space (for lighting calculations)


void main()
{
    // Transform the vertex position to world space
    FragPos = vec3(model * vec4(aPos, 1.0));


    // Final position on screen
    gl_Position = projection * view * vec4(FragPos, 1.0);

}
