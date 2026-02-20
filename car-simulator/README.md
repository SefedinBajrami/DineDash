# OpenGL 3D Car Simulator

A comprehensive 3D car simulator built with OpenGL demonstrating core computer graphics concepts including transformations, lighting, shading, camera systems, and real-time physics.

![OpenGL Car Simulator](https://img.shields.io/badge/OpenGL-3.3+-blue.svg)
![C++](https://img.shields.io/badge/C++-17-green.svg)
![Build](https://img.shields.io/badge/build-CMake-orange.svg)

## 📋 Features

### Core Graphics Concepts
- ✅ **3D Transformations**: Translation, rotation, and scaling matrices
- ✅ **Phong Lighting Model**: Ambient, diffuse, and specular components
- ✅ **Camera System**: Multiple camera modes with smooth transitions
- ✅ **Shading**: Vertex and fragment shaders written in GLSL
- ✅ **Depth Testing**: Proper 3D object rendering
- ✅ **Model-View-Projection Pipeline**: Complete rendering pipeline

### 3D Car Model
- **Procedural Geometry**: Car body and wheels created with custom vertices
- **Animated Wheels**: Front wheels steer, all wheels rotate based on movement
- **Realistic Physics**: Acceleration, deceleration, and friction simulation
- **Steering Mechanics**: Limited steering angles with smooth return to center

### Environment
- **Ground Plane**: Large textured ground (100x100 units)
- **Road System**: Dedicated road with proper texture coordinates
- **Skybox**: Gradient-based sky rendering
- **Scenery**: Procedurally placed trees and buildings along the road

### Camera Modes
1. **Third-Person Camera**: Follows the car from behind with adjustable distance
2. **First-Person Camera**: Driver's view from inside the car
3. **Free Camera**: Manual camera control for exploration

### Lighting & Shading
- **Phong Lighting**: Complete implementation with ambient, diffuse, and specular
- **Directional Light**: Sun-like light source illuminating the scene
- **Per-Fragment Shading**: High-quality lighting calculations
- **Normal Transformation**: Proper normal vector handling for rotated objects

## 🎮 Controls

### Car Movement
| Key | Action |
|-----|--------|
| `W` | Accelerate forward |
| `S` | Brake / Reverse |
| `A` | Turn left |
| `D` | Turn right |

### Camera Controls
| Key | Action |
|-----|--------|
| `1` | Third-person camera mode |
| `2` | First-person camera mode |
| `3` | Free camera mode |
| `Right Mouse Button` | Hold to rotate camera |
| `Mouse Scroll` | Zoom in/out (third-person) |
| `ESC` | Exit application |

## 🛠️ Technologies

- **OpenGL**: 3.3 Core Profile
- **GLFW**: Window and input management
- **GLAD**: OpenGL function loader
- **GLM**: Mathematics library for graphics
- **C++**: 17 or later
- **CMake**: Build system (3.10+)

## 📦 Dependencies

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential cmake
sudo apt-get install libglfw3-dev
sudo apt-get install libglm-dev
sudo apt-get install libgl1-mesa-dev
```

### macOS
```bash
brew install cmake
brew install glfw
brew install glm
```

### Windows (with vcpkg)
```powershell
vcpkg install glfw3:x64-windows
vcpkg install glm:x64-windows
vcpkg integrate install
```

## 🔨 Building

### Linux / macOS
```bash
cd car-simulator
mkdir build
cd build
cmake ..
make
./CarSimulator
```

### Windows (Visual Studio)
```powershell
cd car-simulator
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
.\Release\CarSimulator.exe
```

## 📁 Project Structure

```
car-simulator/
├── CMakeLists.txt          # Build configuration
├── README.md               # This file
├── include/                # Header files
│   ├── glad/
│   │   └── glad.h         # OpenGL loader
│   ├── camera.h           # Camera system
│   ├── car.h              # Car model
│   ├── environment.h      # Environment rendering
│   └── shader.h           # Shader utilities
├── src/                    # Implementation files
│   ├── main.cpp           # Application entry point
│   ├── glad.c             # OpenGL loader implementation
│   ├── camera.cpp         # Camera implementation
│   ├── car.cpp            # Car model implementation
│   ├── environment.cpp    # Environment implementation
│   └── shader.cpp         # Shader utilities implementation
├── shaders/                # GLSL shaders
│   ├── vertex.glsl        # Main vertex shader
│   ├── fragment.glsl      # Main fragment shader (Phong)
│   ├── skybox_vertex.glsl # Skybox vertex shader
│   └── skybox_fragment.glsl # Skybox fragment shader
└── textures/               # Texture files (if any)
```

## 🎓 Graphics Concepts Demonstrated

### 1. Transformations
- **Model Matrix**: Positions and orients objects in world space
- **View Matrix**: Positions camera in the scene
- **Projection Matrix**: Perspective projection for 3D depth
- **Hierarchical Transformations**: Car body + wheels with relative positioning

### 2. Lighting (Phong Model)
```glsl
// Ambient
vec3 ambient = ambientStrength * lightColor;

// Diffuse
float diff = max(dot(normal, lightDir), 0.0);
vec3 diffuse = diff * lightColor;

// Specular
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
vec3 specular = specularStrength * spec * lightColor;
```

### 3. Camera System
- **View Matrix**: `lookAt(position, target, up)`
- **Third-Person**: Calculates position relative to car
- **First-Person**: Positions camera at driver's eye level
- **Free Camera**: Independent movement and rotation

### 4. Physics Simulation
- **Acceleration**: Speed increases over time with input
- **Friction**: Gradual slowdown when no input
- **Steering**: Angular velocity based on speed
- **Constraints**: Maximum speed and steering angle limits

### 5. Rendering Pipeline
```
Vertex Data → Vertex Shader → Rasterization → Fragment Shader → Frame Buffer
     ↓              ↓                                ↓
  Vertices    Transformations              Lighting/Colors
```

## 🔧 Customization

### Modify Car Physics
Edit `car-simulator/src/car.cpp`:
```cpp
Acceleration = 5.0f;      // Change acceleration rate
MaxSpeed = 20.0f;         // Change top speed
Friction = 2.0f;          // Change friction
MaxSteeringAngle = 35.0f; // Change max turn angle
```

### Modify Lighting
Edit `car-simulator/src/main.cpp`:
```cpp
glm::vec3 lightPos(50.0f, 50.0f, 50.0f);  // Light position
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);   // Light color
```

### Adjust Camera
Edit `car-simulator/include/camera.h`:
```cpp
float DistanceFromCar = 10.0f;  // Camera distance in third-person
float Zoom = 45.0f;             // Field of view
```

## 📊 Performance

- **Target FPS**: 60+ FPS
- **Vertices**: ~500 vertices total (car + environment objects)
- **Draw Calls**: Minimal batching for optimal performance
- **Resolution**: Tested at 1280x720, scalable to 4K

## 🐛 Troubleshooting

### Black Screen
- Ensure shaders compiled successfully (check console output)
- Verify OpenGL 3.3+ support: `glxinfo | grep "OpenGL version"`

### Shaders Not Found
- Make sure to run from the build directory: `./CarSimulator`
- CMake copies shaders to build directory automatically

### Car Not Moving
- Check if GLFW input is working
- Verify deltaTime is being calculated correctly
- Print car position to debug: Add `std::cout` in main loop

### Build Errors
- Ensure all dependencies are installed
- Check CMake version: `cmake --version` (need 3.10+)
- Verify C++17 support: `g++ --version`

## 📚 Learning Resources

- [LearnOpenGL](https://learnopengl.com/) - Comprehensive OpenGL tutorial
- [OpenGL Specification](https://www.khronos.org/opengl/) - Official documentation
- [GLM Documentation](https://glm.g-truc.net/) - Mathematics library
- [GLFW Documentation](https://www.glfw.org/docs/latest/) - Window management

## 🎯 Future Enhancements

Potential additions for advanced students:

- [ ] **Collision Detection**: Bounding boxes/spheres with environment
- [ ] **Speedometer UI**: On-screen speed display
- [ ] **Day/Night Cycle**: Animated lighting changes
- [ ] **Headlights**: Spotlight rendering
- [ ] **Particle Effects**: Smoke/dust particles
- [ ] **Sound Effects**: Engine sounds with OpenAL
- [ ] **Mini-map**: 2D top-down view
- [ ] **Texture Loading**: STB image for realistic textures
- [ ] **Model Loading**: Assimp for .obj/.fbx car models
- [ ] **Shadow Mapping**: Real-time shadows
- [ ] **Post-Processing**: Bloom, motion blur effects

## 📝 License

This project is created for educational purposes as part of a Computer Graphics course.

## 👤 Author

Created as a demonstration of OpenGL fundamentals and computer graphics principles.

## 🙏 Acknowledgments

- OpenGL community and tutorials
- GLFW for excellent window management
- GLM for mathematics utilities
- Computer Graphics course materials

---

**Note**: This is a educational project demonstrating computer graphics concepts. The code is designed to be readable and educational rather than production-optimized.
