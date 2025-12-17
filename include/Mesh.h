#pragma once

#include "HeightGen.h"
#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Vertex.h"

class Mesh{
  public:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    Mesh();
    Mesh(std::vector<Vertex> verts, std::vector<GLuint> idxs);

    void draw();
};

