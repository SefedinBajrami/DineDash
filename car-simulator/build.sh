#!/bin/bash

# OpenGL Car Simulator Build Script

echo "======================================"
echo "OpenGL Car Simulator - Build Script"
echo "======================================"
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check if CMake is installed
if ! command -v cmake &> /dev/null; then
    echo -e "${RED}Error: CMake is not installed${NC}"
    echo "Please install CMake first:"
    echo "  Ubuntu/Debian: sudo apt-get install cmake"
    echo "  macOS: brew install cmake"
    exit 1
fi

# Check CMake version
CMAKE_VERSION=$(cmake --version | head -n1 | cut -d' ' -f3)
echo -e "${YELLOW}CMake version: ${CMAKE_VERSION}${NC}"

# Create build directory
echo ""
echo "Creating build directory..."
mkdir -p build
cd build

# Run CMake
echo ""
echo "Running CMake..."
if cmake ..; then
    echo -e "${GREEN}CMake configuration successful${NC}"
else
    echo -e "${RED}CMake configuration failed${NC}"
    exit 1
fi

# Build the project
echo ""
echo "Building project..."
if make -j$(nproc 2>/dev/null || echo 4); then
    echo ""
    echo -e "${GREEN}======================================"
    echo "Build successful!"
    echo "======================================${NC}"
    echo ""
    echo "To run the simulator:"
    echo "  cd build"
    echo "  ./CarSimulator"
    echo ""
else
    echo -e "${RED}Build failed${NC}"
    exit 1
fi
