#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMode {
    THIRD_PERSON,
    FIRST_PERSON,
    FREE_CAMERA
};

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    
    float Yaw;
    float Pitch;
    float DistanceFromCar;
    float AngleAroundCar;
    
    CameraMode Mode;
    
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
    
    glm::mat4 GetViewMatrix();
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void UpdateCameraVectors();
    void FollowCar(glm::vec3 carPosition, float carYaw);
    void SetMode(CameraMode mode);

private:
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    
    void calculateZoom(float delta);
    void calculatePitch(float delta);
    void calculateAngleAroundCar(float delta);
};

#endif
