#include "car.h"
#include <cmath>

Car::Car(glm::vec3 position) 
    : Position(position), Yaw(0.0f), Speed(0.0f), SteeringAngle(0.0f),
      WheelRotation(0.0f), Acceleration(5.0f), MaxSpeed(20.0f),
      Friction(2.0f), MaxSteeringAngle(35.0f), SteeringSpeed(100.0f) {
    setupCarGeometry();
}

void Car::setupCarGeometry() {
    // Car body vertices (simple box)
    float bodyVertices[] = {
        // positions          // normals           // texture coords
        // Front face
        -1.0f, -0.5f,  2.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
         1.0f, -0.5f,  2.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
         1.0f,  0.5f,  2.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
         1.0f,  0.5f,  2.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -1.0f,  0.5f,  2.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -0.5f,  2.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
        
        // Back face
        -1.0f, -0.5f, -2.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -0.5f, -2.0f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  0.5f, -2.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         1.0f,  0.5f, -2.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -1.0f,  0.5f, -2.0f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -1.0f, -0.5f, -2.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        
        // Left face
        -1.0f,  0.5f,  2.0f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -1.0f,  0.5f, -2.0f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -1.0f, -0.5f, -2.0f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -1.0f, -0.5f, -2.0f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -1.0f, -0.5f,  2.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -1.0f,  0.5f,  2.0f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        
        // Right face
         1.0f,  0.5f,  2.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         1.0f,  0.5f, -2.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         1.0f, -0.5f, -2.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         1.0f, -0.5f, -2.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         1.0f, -0.5f,  2.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         1.0f,  0.5f,  2.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        
        // Top face
        -1.0f,  0.5f, -2.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         1.0f,  0.5f, -2.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         1.0f,  0.5f,  2.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         1.0f,  0.5f,  2.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -1.0f,  0.5f,  2.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -1.0f,  0.5f, -2.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        
        // Bottom face
        -1.0f, -0.5f, -2.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         1.0f, -0.5f, -2.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         1.0f, -0.5f,  2.0f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         1.0f, -0.5f,  2.0f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -1.0f, -0.5f,  2.0f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -1.0f, -0.5f, -2.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f
    };
    
    glGenVertexArrays(1, &bodyVAO);
    glGenBuffers(1, &bodyVBO);
    
    glBindVertexArray(bodyVAO);
    glBindBuffer(GL_ARRAY_BUFFER, bodyVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bodyVertices), bodyVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    // Wheel vertices (cylinder approximation)
    std::vector<float> wheelVertices;
    int segments = 16;
    float radius = 0.4f;
    float height = 0.3f;
    
    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * 3.14159f * float(i) / float(segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        
        // Front circle
        wheelVertices.insert(wheelVertices.end(), {x, y, height/2, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f});
        // Back circle
        wheelVertices.insert(wheelVertices.end(), {x, y, -height/2, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f});
    }
    
    glGenVertexArrays(1, &wheelVAO);
    glGenBuffers(1, &wheelVBO);
    
    glBindVertexArray(wheelVAO);
    glBindBuffer(GL_ARRAY_BUFFER, wheelVBO);
    glBufferData(GL_ARRAY_BUFFER, wheelVertices.size() * sizeof(float), &wheelVertices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Car::ProcessInput(bool forward, bool backward, bool left, bool right, float deltaTime) {
    // Acceleration/Braking
    if (forward) {
        Speed += Acceleration * deltaTime;
    }
    if (backward) {
        Speed -= Acceleration * deltaTime;
    }
    
    // Clamp speed
    if (Speed > MaxSpeed) Speed = MaxSpeed;
    if (Speed < -MaxSpeed * 0.5f) Speed = -MaxSpeed * 0.5f;
    
    // Steering
    if (left && fabs(Speed) > 0.1f) {
        SteeringAngle += SteeringSpeed * deltaTime;
    }
    if (right && fabs(Speed) > 0.1f) {
        SteeringAngle -= SteeringSpeed * deltaTime;
    }
    
    // Clamp steering angle
    if (SteeringAngle > MaxSteeringAngle) SteeringAngle = MaxSteeringAngle;
    if (SteeringAngle < -MaxSteeringAngle) SteeringAngle = -MaxSteeringAngle;
    
    // Return steering to center when not turning
    if (!left && !right) {
        if (SteeringAngle > 0) {
            SteeringAngle -= SteeringSpeed * deltaTime * 2.0f;
            if (SteeringAngle < 0) SteeringAngle = 0;
        }
        else if (SteeringAngle < 0) {
            SteeringAngle += SteeringSpeed * deltaTime * 2.0f;
            if (SteeringAngle > 0) SteeringAngle = 0;
        }
    }
}

void Car::Update(float deltaTime) {
    // Apply friction
    if (!false) { // Always apply friction
        if (Speed > 0) {
            Speed -= Friction * deltaTime;
            if (Speed < 0) Speed = 0;
        }
        else if (Speed < 0) {
            Speed += Friction * deltaTime;
            if (Speed > 0) Speed = 0;
        }
    }
    
    // Update position
    if (fabs(Speed) > 0.01f) {
        float moveDistance = Speed * deltaTime;
        Yaw += SteeringAngle * deltaTime * (Speed / MaxSpeed);
        
        Position.x += moveDistance * sin(glm::radians(Yaw));
        Position.z += moveDistance * cos(glm::radians(Yaw));
        
        // Update wheel rotation
        WheelRotation += moveDistance * 50.0f;
    }
}

glm::mat4 Car::GetModelMatrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Position);
    model = glm::rotate(model, glm::radians(Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    return model;
}

void Car::Draw(unsigned int shaderID) {
    drawBody(shaderID);
    drawWheels(shaderID);
}

void Car::drawBody(unsigned int shaderID) {
    glm::mat4 model = GetModelMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, &model[0][0]);
    
    // Set car body color (red)
    glUniform3f(glGetUniformLocation(shaderID, "objectColor"), 0.8f, 0.1f, 0.1f);
    
    glBindVertexArray(bodyVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Car::drawWheels(unsigned int shaderID) {
    glm::mat4 carModel = GetModelMatrix();
    
    // Wheel positions (4 wheels)
    glm::vec3 wheelPositions[] = {
        glm::vec3(-0.8f, -0.5f,  1.2f),  // Front left
        glm::vec3( 0.8f, -0.5f,  1.2f),  // Front right
        glm::vec3(-0.8f, -0.5f, -1.2f),  // Back left
        glm::vec3( 0.8f, -0.5f, -1.2f)   // Back right
    };
    
    // Set wheel color (dark gray)
    glUniform3f(glGetUniformLocation(shaderID, "objectColor"), 0.2f, 0.2f, 0.2f);
    
    glBindVertexArray(wheelVAO);
    
    for (int i = 0; i < 4; i++) {
        glm::mat4 model = carModel;
        model = glm::translate(model, wheelPositions[i]);
        
        // Front wheels turn with steering
        if (i < 2) {
            model = glm::rotate(model, glm::radians(SteeringAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        
        // All wheels rotate
        model = glm::rotate(model, glm::radians(WheelRotation), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, &model[0][0]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 34);
    }
}
