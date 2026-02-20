# Quick Commands to Move car-simulator to ComputerGraphicsProject

## OPTION 1: Simple Copy (Fastest & Easiest)

### Step 1: Clone your ComputerGraphicsProject repository (if not already done)
```bash
git clone https://github.com/YOUR_USERNAME/ComputerGraphicsProject.git
cd ComputerGraphicsProject
```

### Step 2: Copy all files from car-simulator
```bash
# Replace /path/to/DineDash with the actual path
cp -r /path/to/DineDash/car-simulator/* .
cp /path/to/DineDash/car-simulator/.gitignore .
```

### Step 3: Commit and push
```bash
git add .
git commit -m "Add OpenGL 3D Car Simulator - Complete Implementation"
git push origin main
```

### Step 4: Build and test
```bash
chmod +x build.sh
./build.sh
cd build
./CarSimulator
```

---

## OPTION 2: Using the Automated Script

```bash
# Navigate to car-simulator directory
cd /path/to/DineDash/car-simulator

# Run the migration script
./migrate_to_repo.sh

# Follow the interactive prompts
```

---

## OPTION 3: One-Line Commands

### For Linux/Mac Users:
```bash
# All in one command (replace paths as needed)
cd ~/ComputerGraphicsProject && \
cp -r /path/to/DineDash/car-simulator/* . && \
cp /path/to/DineDash/car-simulator/.gitignore . && \
git add . && \
git commit -m "Add OpenGL 3D Car Simulator" && \
git push origin main
```

### For Windows Users (PowerShell):
```powershell
# Navigate to your repository
cd C:\Users\YourName\ComputerGraphicsProject

# Copy files
Copy-Item -Path "C:\path\to\DineDash\car-simulator\*" -Destination . -Recurse
Copy-Item -Path "C:\path\to\DineDash\car-simulator\.gitignore" -Destination .

# Commit and push
git add .
git commit -m "Add OpenGL 3D Car Simulator"
git push origin main
```

---

## OPTION 4: Using rsync (Linux/Mac - Preserves permissions)

```bash
cd ~/ComputerGraphicsProject
rsync -av --exclude='.git' /path/to/DineDash/car-simulator/ .
git add .
git commit -m "Add OpenGL 3D Car Simulator"
git push origin main
```

---

## OPTION 5: Download as ZIP

```bash
# Create ZIP from car-simulator
cd /path/to/DineDash
zip -r car-simulator.zip car-simulator/

# Then extract in ComputerGraphicsProject and commit
```

---

## Verification After Migration

After copying files, verify everything is there:

```bash
cd ~/ComputerGraphicsProject
ls -la

# You should see:
# - CMakeLists.txt
# - README.md
# - DOCUMENTATION.md
# - build.sh / build.bat
# - include/ directory
# - src/ directory
# - shaders/ directory
```

---

## Build Test

```bash
# Linux/Mac
chmod +x build.sh
./build.sh

# Windows
build.bat

# Run the simulator
cd build
./CarSimulator    # Linux/Mac
# or
CarSimulator.exe  # Windows
```

---

## Troubleshooting

### Issue: "Permission denied" on build.sh
```bash
chmod +x build.sh
```

### Issue: Files not copying
```bash
# Use absolute paths
cp -r /full/path/to/DineDash/car-simulator/* /full/path/to/ComputerGraphicsProject/
```

### Issue: Git says "nothing to commit"
```bash
# Check if files are there
ls -la
# Force add if needed
git add -A
```

---

## What Gets Copied

All these files will be moved to ComputerGraphicsProject:

```
✓ CMakeLists.txt
✓ README.md (8.9 KB)
✓ DOCUMENTATION.md (13 KB)
✓ ARCHITECTURE.md (20 KB)
✓ INSTALL.md
✓ TRANSFER_GUIDE.md
✓ PROJECT_SUMMARY.md
✓ .gitignore
✓ build.sh
✓ build.bat
✓ include/ (all headers)
✓ src/ (all C++ files)
✓ shaders/ (all GLSL files)
✓ textures/ (directory)
```

---

## After Migration

1. **Update README** if you want to add your name/credits
2. **Build the project** to ensure everything works
3. **Take screenshots** of the running simulator
4. **Add to README** if desired
5. **Set GitHub topics**: opengl, computer-graphics, cpp, glsl

---

## Need Help?

See the detailed guides:
- **TRANSFER_GUIDE.md** - Comprehensive migration instructions
- **README.md** - Project documentation
- **INSTALL.md** - Build and installation guide
- **DOCUMENTATION.md** - Graphics concepts and implementation details
