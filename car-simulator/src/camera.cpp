#include "camera.h"

Camera::Camera(glm::vec3 position) 
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(2.5f), 
      MouseSensitivity(0.1f), Zoom(45.0f), DistanceFromCar(10.0f),
      AngleAroundCar(0.0f), Mode(THIRD_PERSON) {
    Position = position;
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    Yaw = -90.0f;
    Pitch = 0.0f;
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    if (Mode == FREE_CAMERA) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if (constrainPitch) {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        UpdateCameraVectors();
    }
    else if (Mode == THIRD_PERSON) {
        calculatePitch(yoffset * 0.1f);
        calculateAngleAroundCar(xoffset * 0.1f);
    }
}

void Camera::ProcessMouseScroll(float yoffset) {
    calculateZoom(yoffset);
}

void Camera::UpdateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::FollowCar(glm::vec3 carPosition, float carYaw) {
    if (Mode == THIRD_PERSON) {
        float horizontalDistance = DistanceFromCar * cos(glm::radians(Pitch));
        float verticalDistance = DistanceFromCar * sin(glm::radians(Pitch));
        
        float theta = carYaw + AngleAroundCar;
        float offsetX = horizontalDistance * sin(glm::radians(theta));
        float offsetZ = horizontalDistance * cos(glm::radians(theta));
        
        Position.x = carPosition.x - offsetX;
        Position.z = carPosition.z - offsetZ;
        Position.y = carPosition.y + verticalDistance + 2.0f;
        
        Yaw = 90.0f - theta;
        UpdateCameraVectors();
        
        Front = glm::normalize(carPosition - Position);
    }
    else if (Mode == FIRST_PERSON) {
        Position = carPosition + glm::vec3(0.0f, 1.5f, 0.0f);
        Yaw = carYaw - 90.0f;
        Pitch = 0.0f;
        UpdateCameraVectors();
    }
}

void Camera::SetMode(CameraMode mode) {
    Mode = mode;
}

void Camera::calculateZoom(float delta) {
    DistanceFromCar -= delta;
    if (DistanceFromCar < 5.0f)
        DistanceFromCar = 5.0f;
    if (DistanceFromCar > 50.0f)
        DistanceFromCar = 50.0f;
}

void Camera::calculatePitch(float delta) {
    Pitch -= delta;
    if (Pitch > 45.0f)
        Pitch = 45.0f;
    if (Pitch < -10.0f)
        Pitch = -10.0f;
}

void Camera::calculateAngleAroundCar(float delta) {
    AngleAroundCar -= delta;
}
