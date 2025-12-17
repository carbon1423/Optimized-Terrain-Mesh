#include <string> 
#include <fstream> 
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>



#define STB_PERLIN_IMPLEMENTATION
#include "include/HeightGen.h"
#include "include/Camera.h"
#include "include/Mesh.h"

#define screen_width 800
#define screen_height 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


std::string readFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

 int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set OpenGL version to 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Terrain Generation | FPS: 0", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //test 
    // Load OpenGL function pointers with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

    std::string vertexSource = readFile("./shaders/vertex.glsl");
    //std::string geometrySource = readFile("./shaders/geometry.glsl");
    std::string fragmentSource = readFile("./shaders/fragment.glsl");

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    const char* vertexSourceCStr = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSourceCStr, nullptr);

    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex Shader compilation failed:\n" << infoLog << std::endl;
    }

   // GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
   // 
   // const char* geometrySourceCStr = geometrySource.c_str();
   // glShaderSource(geometryShader, 1, &geometrySourceCStr, nullptr);

   // glCompileShader(geometryShader);

   // glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);

   // if (!success) {
   //     char infoLog[512];
   //     glGetShaderInfoLog(geometryShader, 512, nullptr, infoLog);
   //     std::cerr << "Geometry Shader compilation failed:\n" << infoLog << std::endl;
   // }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* fragmentSourceCStr = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourceCStr, nullptr);

    glCompileShader(fragmentShader);

    // Check for compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Fragment Shader compilation failed:\n" << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, geometryShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader Program linking failed:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    std::vector<Vertex> verts;

    Vertex v0;
    v0.position = glm::vec3(0.0f, 0.0f, 0.0f);
    v0.normal   = glm::vec3(0.0f, 1.0f, 0.0f); 
    v0.texcoord = glm::vec2(0.0f, 0.0f);
    verts.push_back(v0);

    Vertex v1;
    v1.position = glm::vec3(0.0f, 0.0f, 1.0f);
    v1.normal   = glm::vec3(0.0f, 1.0f, 0.0f);
    v1.texcoord = glm::vec2(0.0f, 1.0f);    
    verts.push_back(v1);

    Vertex v2;
    v2.position = glm::vec3(1.0f, 0.0f, 0.0f);
    v2.normal   = glm::vec3(0.0f, 1.0f, 0.0f);
    v2.texcoord = glm::vec2(1.0f, 0.0f);
    verts.push_back(v2);

    std::vector<GLuint> idxs = {0, 1, 2};
    
    Mesh tri(verts, idxs);

    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(0);

    Camera camera(glm::vec3(0.0f, 2.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -30.0f);
    

    float lastFpsTime = 0.0f;
    int frameCount = 0;
    float lastTime = 0.0f;
    while (!glfwWindowShouldClose(window)) {
      
      glClearColor(0.14f, 0.5f, 0.7f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      float currentTime = glfwGetTime();  // seconds
      float dt = currentTime - lastTime;
      lastTime = currentTime;
  
      frameCount++;

      if (currentTime - lastFpsTime >= 1.0f) {
        std::string title = "Terrain Generation | FPS: " + std::to_string(frameCount);
        glfwSetWindowTitle(window, title.c_str());

        // Reset for the next second
        frameCount = 0;
        lastFpsTime = currentTime;
      }
      glUseProgram(shaderProgram);
      
      glm::mat4 model = glm::mat4(1.0f);
      glm::mat4 view = camera.GetViewMatrix();
      glm::mat4 proj = glm::perspective(
        glm::radians(45.0f), screen_width / (float)screen_height, 0.1f, 300.0f);
      glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
      glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
      glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
      

      tri.draw();
      glfwSwapBuffers(window);

      glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
} 
