# System Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────────┐
│                     OpenGL Car Simulator                            │
│                    System Architecture                              │
└─────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│                          main.cpp                                   │
│  ┌──────────────────────────────────────────────────────────────┐  │
│  │  • GLFW Window Initialization                                │  │
│  │  • OpenGL Context Setup                                      │  │
│  │  • Game Loop (60+ FPS)                                       │  │
│  │  • Input Processing                                          │  │
│  │  • Render Coordination                                       │  │
│  └──────────────────────────────────────────────────────────────┘  │
└──────────────┬──────────────┬──────────────┬─────────────┬─────────┘
               │              │              │             │
    ┌──────────▼─────┐ ┌─────▼──────┐ ┌────▼─────┐ ┌────▼──────┐
    │   Camera       │ │    Car     │ │Environmt │ │  Shader   │
    │   System       │ │   Model    │ │ Renderer │ │  Manager  │
    └──────┬─────────┘ └─────┬──────┘ └────┬─────┘ └────┬──────┘
           │                 │              │             │
           │                 │              │             │
┌──────────▼──────────────────▼──────────────▼─────────────▼─────────┐
│                        OpenGL API (3.3+)                            │
│  ┌──────────────────────────────────────────────────────────────┐  │
│  │                         GLAD Loader                          │  │
│  └──────────────────────────────────────────────────────────────┘  │
└──────────────────────────────┬──────────────────────────────────────┘
                               │
                    ┌──────────▼───────────┐
                    │   GPU / Graphics     │
                    │   Hardware           │
                    └──────────────────────┘


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

                        Component Details

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

┌─────────────────────────────────────────────────────────────────────┐
│  Camera System (camera.h / camera.cpp)                              │
├─────────────────────────────────────────────────────────────────────┤
│  Modes:                                                             │
│    • Third-Person: Follows car from behind                          │
│    • First-Person: Driver's view inside car                         │
│    • Free Camera: Independent exploration                           │
│                                                                     │
│  Matrices:                                                          │
│    • View Matrix: glm::lookAt(position, target, up)                 │
│    • Position calculated based on car position and mode             │
│                                                                     │
│  Controls:                                                          │
│    • Mouse: Rotate camera (pitch/yaw)                               │
│    • Scroll: Zoom in/out                                            │
│    • Keys 1/2/3: Switch modes                                       │
└─────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│  Car Model (car.h / car.cpp)                                        │
├─────────────────────────────────────────────────────────────────────┤
│  Geometry:                                                          │
│    • Body: Box (2x1x4 units)                                        │
│    • Wheels: 4 cylinders (radius 0.4, height 0.3)                   │
│                                                                     │
│  Physics:                                                           │
│    • Acceleration: 5.0 units/s²                                     │
│    • Max Speed: 20.0 units/s                                        │
│    • Friction: 2.0 units/s²                                         │
│    • Max Steering: ±35°                                             │
│                                                                     │
│  Animation:                                                         │
│    • Wheels rotate based on speed                                   │
│    • Front wheels steer based on input                              │
│    • Smooth steering return to center                               │
│                                                                     │
│  Controls:                                                          │
│    • W: Accelerate forward                                          │
│    • S: Brake / Reverse                                             │
│    • A: Turn left                                                   │
│    • D: Turn right                                                  │
└─────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│  Environment (environment.h / environment.cpp)                      │
├─────────────────────────────────────────────────────────────────────┤
│  Components:                                                        │
│    • Ground: 100x100 units (green grass)                            │
│    • Road: 200 units long, 16 units wide (gray)                     │
│    • Skybox: Gradient from light to dark blue                       │
│    • Trees: ~40 procedurally placed                                 │
│    • Buildings: ~20 procedurally placed                             │
│                                                                     │
│  Rendering:                                                         │
│    • All use same shader (Phong lighting)                           │
│    • Different object colors (uniforms)                             │
│    • Skybox uses separate shader                                    │
└─────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│  Shader System (shader.h / shader.cpp)                              │
├─────────────────────────────────────────────────────────────────────┤
│  Shaders:                                                           │
│    1. Main Shader (vertex.glsl + fragment.glsl)                     │
│       • Phong lighting                                              │
│       • Transformations (MVP)                                       │
│       • Normal transformation                                       │
│                                                                     │
│    2. Skybox Shader (skybox_*.glsl)                                 │
│       • Gradient rendering                                          │
│       • No lighting                                                 │
│                                                                     │
│  Utilities:                                                         │
│    • Compile and link shaders                                       │
│    • Error checking and reporting                                   │
│    • Uniform setters (mat4, vec3, float, etc.)                      │
└─────────────────────────────────────────────────────────────────────┘


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

                        Rendering Pipeline

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

┌─────────────────────────────────────────────────────────────────────┐
│  1. Application (CPU)                                               │
│     ├─ Update game state (physics, input)                           │
│     ├─ Calculate matrices (Model, View, Projection)                 │
│     └─ Send data to GPU (vertices, uniforms)                        │
│                                                                     │
│  2. Vertex Shader (GPU)                                             │
│     ├─ Transform vertices: gl_Position = P * V * M * vertex         │
│     ├─ Transform normals: normal = inverse(M) * normal              │
│     └─ Pass data to fragment shader                                 │
│                                                                     │
│  3. Rasterization (GPU - Fixed Function)                            │
│     ├─ Convert triangles to fragments (pixels)                      │
│     ├─ Interpolate vertex attributes                                │
│     └─ Depth testing                                                │
│                                                                     │
│  4. Fragment Shader (GPU)                                           │
│     ├─ Calculate Phong lighting:                                    │
│     │   • Ambient = 0.3 * lightColor                                │
│     │   • Diffuse = max(dot(N, L), 0) * lightColor                  │
│     │   • Specular = pow(max(dot(V, R), 0), 32) * lightColor        │
│     └─ Output final color: ambient + diffuse + specular             │
│                                                                     │
│  5. Output (GPU)                                                    │
│     ├─ Depth test (discard hidden fragments)                        │
│     ├─ Write to framebuffer                                         │
│     └─ Display on screen                                            │
└─────────────────────────────────────────────────────────────────────┘


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

                        Data Flow

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

  Input Devices                       Game Loop
       │                                  │
       │                                  │
   ┌───▼───┐                         ┌───▼────┐
   │Keyboard│──── WASD ────────────► │  Car   │
   │ Mouse  │──── Movement ─────────► │Physics │
   │ Scroll │──── Zoom ─────────────► │Update  │
   └────────┘                         └───┬────┘
                                          │
                                          │
                              ┌───────────▼────────────┐
                              │  Transform Matrices    │
                              │  • Model (car pos/rot) │
                              │  • View (camera)       │
                              │  • Projection (FOV)    │
                              └───────────┬────────────┘
                                          │
                                          │
                              ┌───────────▼────────────┐
                              │   Send to Shaders      │
                              │  • Vertex positions    │
                              │  • Normals             │
                              │  • Matrices            │
                              │  • Light parameters    │
                              └───────────┬────────────┘
                                          │
                                          │
                              ┌───────────▼────────────┐
                              │     GPU Rendering      │
                              │  • Vertex processing   │
                              │  • Lighting calc       │
                              │  • Depth testing       │
                              └───────────┬────────────┘
                                          │
                                          │
                                     ┌────▼─────┐
                                     │  Screen  │
                                     │  Output  │
                                     └──────────┘


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

                    File Dependencies

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

main.cpp
  ├─ includes: shader.h, camera.h, car.h, environment.h
  ├─ links: shader.cpp, camera.cpp, car.cpp, environment.cpp
  └─ uses: GLFW, GLAD, GLM

shader.cpp
  ├─ includes: shader.h, glad.h, glm
  └─ reads: shaders/*.glsl files

camera.cpp
  ├─ includes: camera.h, glad.h, glm
  └─ depends: GLM for matrix math

car.cpp
  ├─ includes: car.h, glad.h, glm
  └─ depends: GLM for transformations

environment.cpp
  ├─ includes: environment.h, glad.h, glm
  └─ depends: GLM for transformations

glad.c
  └─ includes: glad.h

All shaders (*.glsl)
  └─ GLSL 330 core profile


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

                    Build Process

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

CMakeLists.txt
  ├─ Find OpenGL
  ├─ Find GLFW
  ├─ Find GLM
  ├─ Set include directories
  ├─ Add source files
  ├─ Link libraries
  └─ Copy shaders to build directory

Build Scripts
  ├─ build.sh (Linux/Mac)
  │   ├─ Create build directory
  │   ├─ Run CMake
  │   └─ Run Make
  │
  └─ build.bat (Windows)
      ├─ Create build directory
      ├─ Run CMake (Visual Studio)
      └─ Build with MSBuild

Output
  └─ build/CarSimulator (executable)


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

This architecture ensures:
  ✓ Modular design with clear separation of concerns
  ✓ Easy to understand and modify
  ✓ Follows OpenGL best practices
  ✓ Cross-platform compatibility
  ✓ Efficient rendering pipeline
  ✓ Maintainable codebase
```
