# Quick Installation Guide

## Prerequisites

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake libglfw3-dev libglm-dev libgl1-mesa-dev
```

### macOS
```bash
brew install cmake glfw glm
```

### Windows
Install Visual Studio 2019 or later, then:
```powershell
# Using vcpkg
vcpkg install glfw3:x64-windows glm:x64-windows
vcpkg integrate install
```

## Build & Run

### Linux / macOS
```bash
chmod +x build.sh
./build.sh
cd build
./CarSimulator
```

### Windows
```cmd
build.bat
cd build\Release
CarSimulator.exe
```

## Manual Build

### All Platforms
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Controls

- **W** - Accelerate
- **S** - Brake/Reverse  
- **A** - Turn Left
- **D** - Turn Right
- **1** - Third-Person Camera
- **2** - First-Person Camera
- **3** - Free Camera
- **Right Mouse** - Rotate Camera
- **Scroll** - Zoom
- **ESC** - Exit

## Troubleshooting

### "GLFW not found"
```bash
# Ubuntu/Debian
sudo apt-get install libglfw3-dev

# macOS
brew install glfw
```

### "GLM not found"
```bash
# Ubuntu/Debian
sudo apt-get install libglm-dev

# macOS  
brew install glm
```

### "Cannot find OpenGL"
```bash
# Ubuntu/Debian
sudo apt-get install libgl1-mesa-dev

# Check OpenGL version
glxinfo | grep "OpenGL version"
```

### Black screen / Shader errors
- Check console output for shader compilation errors
- Ensure running from build directory (shaders must be accessible)
- Update graphics drivers

## System Requirements

- **OpenGL**: 3.3 or higher
- **CPU**: Any modern processor
- **RAM**: 512 MB minimum
- **GPU**: Any GPU with OpenGL 3.3+ support
- **OS**: Linux, macOS 10.12+, Windows 7+

## Next Steps

After successful installation:
1. Read `README.md` for detailed documentation
2. Check `DOCUMENTATION.md` for graphics concepts
3. Modify car physics in `src/car.cpp`
4. Experiment with lighting in shaders

## Quick Test

After building, the simulator should:
- Open a window titled "OpenGL Car Simulator"
- Display a red car on a green ground with gray road
- Show sky gradient background
- Respond to WASD keys
- Allow camera rotation with mouse

If any of these don't work, check the troubleshooting section above.
