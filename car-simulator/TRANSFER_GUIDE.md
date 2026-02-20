# Moving to ComputerGraphicsProject Repository

This document explains how to transfer the OpenGL Car Simulator to your new "ComputerGraphicsProject" repository.

## Quick Transfer Guide

### Option 1: Copy Files Manually

1. **Clone your ComputerGraphicsProject repository**:
   ```bash
   git clone https://github.com/YourUsername/ComputerGraphicsProject.git
   cd ComputerGraphicsProject
   ```

2. **Copy the entire car-simulator directory**:
   ```bash
   cp -r /path/to/DineDash/car-simulator/* .
   ```

3. **Commit and push**:
   ```bash
   git add .
   git commit -m "Add OpenGL 3D Car Simulator project"
   git push origin main
   ```

### Option 2: Using Git Subtree (Recommended)

If you want to preserve git history:

1. **Add DineDash as a remote** (in ComputerGraphicsProject):
   ```bash
   cd ComputerGraphicsProject
   git remote add dinedash https://github.com/SefedinBajrami/DineDash.git
   git fetch dinedash
   ```

2. **Cherry-pick the car-simulator directory**:
   ```bash
   git subtree add --prefix=. dinedash copilot/develop-car-simulator-game:car-simulator
   ```

3. **Push to your repository**:
   ```bash
   git push origin main
   ```

### Option 3: Fresh Start in ComputerGraphicsProject

1. **Navigate to the DineDash repository**:
   ```bash
   cd /path/to/DineDash/car-simulator
   ```

2. **Create a zip archive**:
   ```bash
   zip -r car-simulator.zip .
   ```

3. **Extract in ComputerGraphicsProject**:
   ```bash
   cd /path/to/ComputerGraphicsProject
   unzip /path/to/car-simulator.zip
   git add .
   git commit -m "Initial commit: OpenGL 3D Car Simulator"
   git push origin main
   ```

## Files to Transfer

All files in the `car-simulator/` directory should be transferred:

```
car-simulator/
├── CMakeLists.txt           ✓ Build configuration
├── README.md                ✓ Main documentation
├── DOCUMENTATION.md         ✓ Detailed graphics concepts
├── .gitignore              ✓ Ignore build artifacts
├── build.sh                ✓ Linux/Mac build script
├── build.bat               ✓ Windows build script
├── include/                ✓ All header files
│   ├── glad/glad.h
│   ├── camera.h
│   ├── car.h
│   ├── environment.h
│   └── shader.h
├── src/                    ✓ All implementation files
│   ├── main.cpp
│   ├── glad.c
│   ├── camera.cpp
│   ├── car.cpp
│   ├── environment.cpp
│   └── shader.cpp
├── shaders/                ✓ All GLSL shaders
│   ├── vertex.glsl
│   ├── fragment.glsl
│   ├── skybox_vertex.glsl
│   └── skybox_fragment.glsl
└── textures/               ✓ (currently empty, for future use)
```

## Post-Transfer Steps

### 1. Update README (if needed)

If you want to customize the README for your repository, edit:
- Repository name references
- Author information
- License information

### 2. Test Build

After transferring, test the build process:

**Linux/Mac**:
```bash
chmod +x build.sh
./build.sh
```

**Windows**:
```cmd
build.bat
```

### 3. Create GitHub Repository Features

Add these to your ComputerGraphicsProject repository:

**README.md badge updates**:
```markdown
![License](https://img.shields.io/badge/license-MIT-blue.svg)
![OpenGL](https://img.shields.io/badge/OpenGL-3.3+-blue.svg)
![C++](https://img.shields.io/badge/C++-17-green.svg)
```

**GitHub Topics** (in repository settings):
- opengl
- computer-graphics
- 3d-graphics
- game-development
- cpp
- glsl
- phong-lighting
- camera-system

### 4. Add Screenshots

To make your repository more attractive:

1. Build and run the simulator
2. Take screenshots of:
   - Third-person view
   - First-person view
   - Different camera angles
   - Day lighting

3. Create a `screenshots/` directory and add images
4. Update README.md with image references:
   ```markdown
   ## Screenshots
   
   ### Third-Person View
   ![Third Person](screenshots/third-person.png)
   
   ### First-Person View
   ![First Person](screenshots/first-person.png)
   ```

### 5. Optional: Add GitHub Actions

Create `.github/workflows/build.yml` for automatic builds:

```yaml
name: Build

on: [push, pull_request]

jobs:
  build-linux:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v2
    - name: Install dependencies
      run: |
        sudo apt-get update
        sudo apt-get install -y cmake libglfw3-dev libglm-dev libgl1-mesa-dev
    - name: Build
      run: |
        chmod +x build.sh
        ./build.sh
```

## Verification Checklist

After transfer, verify:

- [ ] All files copied successfully
- [ ] CMakeLists.txt present in root
- [ ] README.md renders correctly on GitHub
- [ ] .gitignore excludes build/ directory
- [ ] Build scripts are executable
- [ ] Project builds without errors
- [ ] Application runs correctly
- [ ] All controls work (WASD, mouse, etc.)
- [ ] Camera modes switch properly (1, 2, 3)
- [ ] Documentation is accurate

## Repository Structure Recommendation

For a clean ComputerGraphicsProject repository:

```
ComputerGraphicsProject/
├── .github/
│   └── workflows/
│       └── build.yml
├── screenshots/
│   ├── third-person.png
│   ├── first-person.png
│   └── free-camera.png
├── CMakeLists.txt
├── README.md
├── DOCUMENTATION.md
├── LICENSE
├── .gitignore
├── build.sh
├── build.bat
├── include/
├── src/
├── shaders/
└── textures/
```

## Additional Resources

### Dependencies Installation

**Ubuntu/Debian**:
```bash
sudo apt-get install build-essential cmake libglfw3-dev libglm-dev libgl1-mesa-dev
```

**macOS**:
```bash
brew install cmake glfw glm
```

**Windows** (vcpkg):
```powershell
vcpkg install glfw3:x64-windows glm:x64-windows
```

### Common Issues

1. **GLFW not found**:
   - Install GLFW development package
   - Or set `CMAKE_PREFIX_PATH`

2. **GLM not found**:
   - Install GLM (header-only library)
   - Or copy GLM headers to project

3. **OpenGL version too old**:
   - Update graphics drivers
   - Check: `glxinfo | grep "OpenGL version"`

## Next Steps

Once transferred to ComputerGraphicsProject:

1. **Add a LICENSE file** (e.g., MIT License)
2. **Create a CONTRIBUTING.md** if you want contributions
3. **Add project to your portfolio**
4. **Share with classmates/professors**
5. **Consider adding bonus features**:
   - Texture loading
   - Model importing (.obj files)
   - Collision detection
   - Speedometer UI
   - Sound effects

## Support

If you encounter issues during transfer:

1. Check that all files are present
2. Verify dependencies are installed
3. Read the README.md troubleshooting section
4. Check DOCUMENTATION.md for implementation details

---

**Note**: This car-simulator project is completely standalone and can be moved to any repository. All dependencies are clearly documented, and the build system is portable across platforms.
