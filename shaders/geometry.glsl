#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 FragPos[];

out vec3 Normal;
out vec3 FragPosF;


void main()
{
	vec3 p0 = FragPos[0];
	vec3 p1 = FragPos[1];
	vec3 p2 = FragPos[2];

	vec3 normal = normalize(cross(p1 - p0, p2 - p0));

	for (int i = 0; i < 3; i++) {
        Normal = -normal;
        FragPosF = FragPos[i];
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}