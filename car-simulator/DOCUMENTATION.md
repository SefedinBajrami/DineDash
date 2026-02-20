# Computer Graphics Concepts - Detailed Documentation

This document provides an in-depth explanation of the computer graphics concepts implemented in the OpenGL Car Simulator.

## Table of Contents
1. [Rendering Pipeline](#rendering-pipeline)
2. [3D Transformations](#3d-transformations)
3. [Lighting Models](#lighting-models)
4. [Camera Systems](#camera-systems)
5. [Shaders](#shaders)
6. [Physics Simulation](#physics-simulation)

---

## Rendering Pipeline

### Overview
The graphics pipeline transforms 3D vertex data into 2D pixels on the screen through several stages:

```
Application → Vertex Processing → Rasterization → Fragment Processing → Output
```

### Stages in Our Implementation

#### 1. **Vertex Specification**
```cpp
// Define vertices with position, normal, and texture coordinates
float vertices[] = {
    // positions        // normals         // texture coords
    -1.0f, -0.5f, 2.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
    // ...
};
```

#### 2. **Vertex Shader** (GPU)
```glsl
// Transform vertices to clip space
gl_Position = projection * view * model * vec4(aPos, 1.0);
```

#### 3. **Rasterization** (Fixed Function)
- Converts primitives to fragments
- Interpolates vertex attributes

#### 4. **Fragment Shader** (GPU)
```glsl
// Calculate lighting per pixel
vec3 result = (ambient + diffuse + specular) * objectColor;
```

#### 5. **Output Merger**
- Depth testing
- Color blending
- Final pixel color

---

## 3D Transformations

### Transformation Matrices

#### Model Matrix
Transforms from **local space** → **world space**

```cpp
glm::mat4 model = glm::mat4(1.0f);
model = glm::translate(model, position);           // Move object
model = glm::rotate(model, angle, axis);           // Rotate object
model = glm::scale(model, glm::vec3(sx, sy, sz)); // Scale object
```

**Example**: Car positioning
```cpp
glm::mat4 Car::GetModelMatrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Position);      // Move to car position
    model = glm::rotate(model, glm::radians(Yaw), // Rotate car
                       glm::vec3(0.0f, 1.0f, 0.0f));
    return model;
}
```

#### View Matrix
Transforms from **world space** → **camera/view space**

```cpp
glm::mat4 view = glm::lookAt(
    cameraPos,      // Camera position in world space
    cameraTarget,   // Point camera looks at
    upVector        // Up direction (usually (0, 1, 0))
);
```

**Example**: Third-person camera
```cpp
void Camera::FollowCar(glm::vec3 carPosition, float carYaw) {
    float horizontalDistance = DistanceFromCar * cos(glm::radians(Pitch));
    float verticalDistance = DistanceFromCar * sin(glm::radians(Pitch));
    
    float theta = carYaw + AngleAroundCar;
    float offsetX = horizontalDistance * sin(glm::radians(theta));
    float offsetZ = horizontalDistance * cos(glm::radians(theta));
    
    Position.x = carPosition.x - offsetX;
    Position.z = carPosition.z - offsetZ;
    Position.y = carPosition.y + verticalDistance + 2.0f;
}
```

#### Projection Matrix
Transforms from **view space** → **clip space**

```cpp
// Perspective projection
glm::mat4 projection = glm::perspective(
    glm::radians(45.0f),    // Field of view (FOV)
    aspectRatio,             // Width / Height
    0.1f,                    // Near clipping plane
    1000.0f                  // Far clipping plane
);
```

### Coordinate Spaces

1. **Local Space**: Object's own coordinate system
2. **World Space**: Global scene coordinates
3. **View Space**: Relative to camera
4. **Clip Space**: After projection, used for clipping
5. **Screen Space**: Final 2D pixel coordinates

### Transformation Order
**Critical**: Transformations are applied in **reverse order**!

```cpp
gl_Position = projection * view * model * vec4(localPos, 1.0);
```

This means: Local → Model → View → Projection

---

## Lighting Models

### Phong Lighting Model

The Phong model combines three lighting components:

#### 1. Ambient Lighting
Simulates indirect light that illuminates everything equally.

```glsl
float ambientStrength = 0.3;
vec3 ambient = ambientStrength * lightColor;
```

#### 2. Diffuse Lighting
Simulates direct light that depends on surface angle.

```glsl
vec3 norm = normalize(Normal);
vec3 lightDir = normalize(lightPos - FragPos);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = diff * lightColor;
```

**Key concept**: Lambert's Cosine Law
- Light perpendicular to surface = maximum brightness
- Light parallel to surface = no brightness
- Uses dot product: `cos(θ) = dot(normal, lightDir)`

#### 3. Specular Lighting
Simulates shiny highlights (reflections).

```glsl
float specularStrength = 0.5;
vec3 viewDir = normalize(viewPos - FragPos);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
vec3 specular = specularStrength * spec * lightColor;
```

**Parameters**:
- `shininess = 32`: Higher values = shinier surface
- Only visible when view direction ≈ reflection direction

#### Final Color Calculation
```glsl
vec3 result = (ambient + diffuse + specular) * objectColor;
FragColor = vec4(result, 1.0);
```

### Normal Transformation

**Problem**: Rotating/scaling objects requires transforming normals.

**Wrong**: `normal = model * normal` ❌

**Correct**: `normal = transpose(inverse(model)) * normal` ✅

```glsl
Normal = mat3(transpose(inverse(model))) * aNormal;
```

**Why?** Non-uniform scaling breaks perpendicularity. The normal matrix preserves it.

---

## Camera Systems

### 1. Third-Person Camera

Follows the car from behind at a fixed distance.

```cpp
void Camera::FollowCar(glm::vec3 carPosition, float carYaw) {
    // Calculate horizontal and vertical offsets
    float horizontalDistance = DistanceFromCar * cos(glm::radians(Pitch));
    float verticalDistance = DistanceFromCar * sin(glm::radians(Pitch));
    
    // Calculate position behind car
    float theta = carYaw + AngleAroundCar;
    Position.x = carPosition.x - horizontalDistance * sin(glm::radians(theta));
    Position.z = carPosition.z - horizontalDistance * cos(glm::radians(theta));
    Position.y = carPosition.y + verticalDistance;
    
    // Always look at car
    Front = glm::normalize(carPosition - Position);
}
```

### 2. First-Person Camera

Places camera at driver's eye level.

```cpp
Position = carPosition + glm::vec3(0.0f, 1.5f, 0.0f); // Eye height
Yaw = carYaw - 90.0f;  // Look forward
```

### 3. Free Camera

Independent movement controlled by user.

```cpp
// Camera movement
Position += Front * velocity;  // Forward/backward
Position += Right * velocity;  // Left/right
Position += Up * velocity;     // Up/down
```

### Camera Vector Calculation

The camera uses three perpendicular vectors:

```cpp
void Camera::UpdateCameraVectors() {
    // Calculate front vector from yaw and pitch
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    
    // Calculate right and up vectors
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
```

---

## Shaders

### Vertex Shader

**Purpose**: Transform vertices and pass data to fragment shader.

```glsl
#version 330 core
layout (location = 0) in vec3 aPos;      // Vertex position
layout (location = 1) in vec3 aNormal;   // Vertex normal
layout (location = 2) in vec2 aTexCoords;// Texture coordinates

out vec3 FragPos;   // Position for fragment shader
out vec3 Normal;    // Normal for fragment shader
out vec2 TexCoords; // Texture coords for fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Transform position to world space
    FragPos = vec3(model * vec4(aPos, 1.0));
    
    // Transform normal (using normal matrix)
    Normal = mat3(transpose(inverse(model))) * aNormal;
    
    // Pass texture coordinates
    TexCoords = aTexCoords;
    
    // Final position in clip space
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
```

### Fragment Shader

**Purpose**: Calculate pixel color using lighting.

```glsl
#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    // Ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    // Combine
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
```

### Shader Compilation Process

```cpp
// 1. Create shader
unsigned int shader = glCreateShader(GL_VERTEX_SHADER);

// 2. Attach source code
glShaderSource(shader, 1, &shaderCode, NULL);

// 3. Compile
glCompileShader(shader);

// 4. Check for errors
glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

// 5. Create program and link
unsigned int program = glCreateProgram();
glAttachShader(program, vertexShader);
glAttachShader(program, fragmentShader);
glLinkProgram(program);

// 6. Use program
glUseProgram(program);
```

---

## Physics Simulation

### Basic Car Physics

#### 1. Acceleration
```cpp
if (forward) {
    Speed += Acceleration * deltaTime;
}
```

#### 2. Friction
```cpp
if (Speed > 0) {
    Speed -= Friction * deltaTime;
    if (Speed < 0) Speed = 0;
}
```

#### 3. Movement
```cpp
float moveDistance = Speed * deltaTime;
Yaw += SteeringAngle * deltaTime * (Speed / MaxSpeed);

Position.x += moveDistance * sin(glm::radians(Yaw));
Position.z += moveDistance * cos(glm::radians(Yaw));
```

#### 4. Steering
```cpp
if (left && fabs(Speed) > 0.1f) {
    SteeringAngle += SteeringSpeed * deltaTime;
}

// Clamp steering
if (SteeringAngle > MaxSteeringAngle) 
    SteeringAngle = MaxSteeringAngle;
```

### Delta Time

**Problem**: Different computers run at different speeds.

**Solution**: Use delta time to make movement frame-rate independent.

```cpp
// Wrong (frame-rate dependent)
position += velocity;

// Correct (frame-rate independent)
position += velocity * deltaTime;
```

```cpp
float currentFrame = glfwGetTime();
deltaTime = currentFrame - lastFrame;
lastFrame = currentFrame;
```

---

## Best Practices

### 1. Use Uniform Buffer Objects (UBOs) for Shared Data
```cpp
// Instead of setting view/projection for each shader
// Use UBO to set once for all shaders
```

### 2. Minimize State Changes
```cpp
// Group draw calls by shader, then by texture
for (shader in shaders) {
    useShader(shader);
    for (texture in textures) {
        bindTexture(texture);
        drawObjects();
    }
}
```

### 3. Use Indexed Drawing
```cpp
// Instead of duplicate vertices
glDrawArrays(GL_TRIANGLES, 0, vertexCount);

// Use indices
glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
```

### 4. Enable Depth Testing
```cpp
glEnable(GL_DEPTH_TEST);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

### 5. Face Culling for Performance
```cpp
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);
glFrontFace(GL_CCW);
```

---

## Common Issues and Solutions

### Issue: Objects Not Visible
- Check if depth testing is enabled
- Verify near/far planes in projection matrix
- Check if objects are within view frustum

### Issue: Lighting Looks Wrong
- Verify normals are unit length (`normalize()`)
- Check normal transformation (use normal matrix)
- Ensure light position is in world space

### Issue: Textures Appear Black
- Check if texture is loaded correctly
- Verify texture coordinates are in [0, 1] range
- Ensure texture unit is active and bound

### Issue: Car Spins Too Fast
- Check deltaTime calculation
- Verify angular velocity units (degrees vs radians)
- Add steering speed limits

---

## References

1. **OpenGL Programming Guide** (Red Book)
2. **Real-Time Rendering** by Tomas Akenine-Möller
3. **LearnOpenGL** - https://learnopengl.com
4. **OpenGL Specification** - https://www.khronos.org/opengl/

---

This documentation provides the theoretical foundation for understanding the implementation. For practical examples, refer to the source code files.
