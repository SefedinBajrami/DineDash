#ifndef CAR_H
#define CAR_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Car {
public:
    glm::vec3 Position;
    float Yaw;
    float Speed;
    float SteeringAngle;
    float WheelRotation;
    
    Car(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
    
    void ProcessInput(bool forward, bool backward, bool left, bool right, float deltaTime);
    void Update(float deltaTime);
    void Draw(unsigned int shaderID);
    glm::mat4 GetModelMatrix();
    
private:
    unsigned int bodyVAO, bodyVBO;
    unsigned int wheelVAO, wheelVBO;
    
    float Acceleration;
    float MaxSpeed;
    float Friction;
    float MaxSteeringAngle;
    float SteeringSpeed;
    
    void setupCarGeometry();
    void drawBody(unsigned int shaderID);
    void drawWheels(unsigned int shaderID);
};

#endif
