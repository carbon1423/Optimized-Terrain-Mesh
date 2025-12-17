#pragma once

#include <glm/glm.hpp>

class Camera {
  public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;    // left/right rotation
    float Pitch;  // up/down rotation

    float MovementSpeed;
    float RotationSpeed;
    float MouseSensitivity = 0.08f;

    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
          MovementSpeed(10.0f),
          RotationSpeed(90.0f) {
      Position = position;
      WorldUp = up;
      Yaw = yaw;
      Pitch = pitch;
      updateCameraVectors();
    }

    glm::mat4 GetViewMatrix() {
      return glm::lookAt(Position, Position + Front, Up);
    }

  private:
   void updateCameraVectors() {
     glm::vec3 front;
     front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
     front.y = sin(glm::radians(Pitch));
     front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
     Front = glm::normalize(front);
     Right = glm::normalize(glm::cross(Front, WorldUp));
     Up = glm::normalize(glm::cross(Right, Front));
   }
}; 
