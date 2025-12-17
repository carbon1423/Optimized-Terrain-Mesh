#version 330 core

layout(location = 0) in vec3 aPos;     
layout(location = 1) in vec3 aNormal;  
layout(location = 2) in vec2 aTex;     



uniform mat4 model;      
uniform mat4 view;      
uniform mat4 proj;    


out vec3 FragPos;       
out vec3 Normal;         
out vec2 TexCoord;  
out vec3 ViewSpace;


void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal; // normal transformation
    TexCoord = aTex;
    ViewSpace = (view * model * vec4(aPos, 1.0)).xyz;
    gl_Position = proj * view * model * vec4(aPos, 1.0);
}
