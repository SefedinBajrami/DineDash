#!/bin/bash

# ============================================================================
# OpenGL Car Simulator - Migration Script
# ============================================================================
# This script helps you move the car-simulator directory to your
# ComputerGraphicsProject repository
# ============================================================================

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo ""
echo "╔═══════════════════════════════════════════════════════════════════════╗"
echo "║                                                                       ║"
echo "║         OpenGL Car Simulator - Repository Migration Tool             ║"
echo "║                                                                       ║"
echo "╚═══════════════════════════════════════════════════════════════════════╝"
echo ""

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo -e "${BLUE}Current car-simulator location:${NC}"
echo "  $SCRIPT_DIR"
echo ""

# Check if we're in the car-simulator directory
if [[ ! -f "$SCRIPT_DIR/CMakeLists.txt" ]] || [[ ! -f "$SCRIPT_DIR/README.md" ]]; then
    echo -e "${RED}Error: This script must be run from the car-simulator directory${NC}"
    exit 1
fi

echo -e "${YELLOW}This script will guide you through migrating the car-simulator"
echo -e "to your ComputerGraphicsProject repository.${NC}"
echo ""
echo "You have three options:"
echo ""
echo "  1) Simple Copy Method (Recommended for beginners)"
echo "     - Copies all files to your local ComputerGraphicsProject directory"
echo "     - You then commit and push manually"
echo ""
echo "  2) Automated Git Method"
echo "     - Clones your ComputerGraphicsProject repo"
echo "     - Copies files and creates a commit"
echo "     - You review and push"
echo ""
echo "  3) Show manual instructions"
echo "     - Displays step-by-step commands you can run yourself"
echo ""
echo -e "${BLUE}Choose an option (1, 2, or 3):${NC} "
read -r OPTION

case $OPTION in
    1)
        echo ""
        echo -e "${GREEN}Option 1: Simple Copy Method${NC}"
        echo ""
        echo "Please provide the full path to your ComputerGraphicsProject directory:"
        echo "(e.g., /home/username/projects/ComputerGraphicsProject)"
        echo ""
        echo -n "Path: "
        read -r TARGET_DIR
        
        if [[ ! -d "$TARGET_DIR" ]]; then
            echo ""
            echo -e "${RED}Error: Directory does not exist: $TARGET_DIR${NC}"
            echo ""
            echo "Please either:"
            echo "  1. Create the directory first"
            echo "  2. Clone your repository: git clone https://github.com/YourUsername/ComputerGraphicsProject.git"
            exit 1
        fi
        
        echo ""
        echo -e "${YELLOW}Copying files to $TARGET_DIR...${NC}"
        
        # Copy all files except .git directory
        cp -rv "$SCRIPT_DIR"/* "$TARGET_DIR/" 2>/dev/null || true
        cp -rv "$SCRIPT_DIR"/.gitignore "$TARGET_DIR/" 2>/dev/null || true
        
        echo ""
        echo -e "${GREEN}✓ Files copied successfully!${NC}"
        echo ""
        echo "Next steps:"
        echo "  1. cd $TARGET_DIR"
        echo "  2. git add ."
        echo "  3. git commit -m \"Add OpenGL 3D Car Simulator\""
        echo "  4. git push origin main"
        echo ""
        echo "Then build and test:"
        echo "  ./build.sh     # or build.bat on Windows"
        echo ""
        ;;
        
    2)
        echo ""
        echo -e "${GREEN}Option 2: Automated Git Method${NC}"
        echo ""
        echo "Enter your GitHub username:"
        read -r GH_USERNAME
        echo ""
        echo "Enter your repository name (default: ComputerGraphicsProject):"
        read -r REPO_NAME
        REPO_NAME=${REPO_NAME:-ComputerGraphicsProject}
        
        echo ""
        echo "Where should I clone the repository? (default: ~/ComputerGraphicsProject)"
        read -r CLONE_DIR
        CLONE_DIR=${CLONE_DIR:-~/ComputerGraphicsProject}
        
        # Expand tilde
        CLONE_DIR="${CLONE_DIR/#\~/$HOME}"
        
        echo ""
        echo -e "${YELLOW}Cloning repository...${NC}"
        
        if [[ -d "$CLONE_DIR" ]]; then
            echo -e "${YELLOW}Warning: Directory already exists. Using existing directory.${NC}"
            cd "$CLONE_DIR"
            git pull origin main 2>/dev/null || git pull origin master 2>/dev/null || true
        else
            git clone "https://github.com/$GH_USERNAME/$REPO_NAME.git" "$CLONE_DIR"
            cd "$CLONE_DIR"
        fi
        
        echo ""
        echo -e "${YELLOW}Copying car-simulator files...${NC}"
        
        # Copy all files except .git directory
        cp -rv "$SCRIPT_DIR"/* . 2>/dev/null || true
        cp -rv "$SCRIPT_DIR"/.gitignore . 2>/dev/null || true
        
        # Don't include this migration script in the new repo
        rm -f migrate_to_repo.sh
        
        echo ""
        echo -e "${YELLOW}Creating git commit...${NC}"
        
        git add .
        git status
        
        echo ""
        echo -e "${GREEN}✓ Files copied and staged!${NC}"
        echo ""
        echo "Review the changes above. If everything looks good:"
        echo ""
        echo "  cd $CLONE_DIR"
        echo "  git commit -m \"Add OpenGL 3D Car Simulator - Complete Implementation\""
        echo "  git push origin main"
        echo ""
        echo "Then build and test:"
        echo "  ./build.sh     # or build.bat on Windows"
        echo ""
        ;;
        
    3)
        echo ""
        echo -e "${GREEN}Option 3: Manual Instructions${NC}"
        echo ""
        echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
        echo -e "${BLUE}Method A: Simple Copy (Recommended)${NC}"
        echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
        echo ""
        echo "# 1. Clone your repository (if not already cloned)"
        echo "git clone https://github.com/YourUsername/ComputerGraphicsProject.git"
        echo "cd ComputerGraphicsProject"
        echo ""
        echo "# 2. Copy all files from car-simulator"
        echo "cp -r $SCRIPT_DIR/* ."
        echo "cp $SCRIPT_DIR/.gitignore ."
        echo ""
        echo "# 3. Commit and push"
        echo "git add ."
        echo "git commit -m \"Add OpenGL 3D Car Simulator\""
        echo "git push origin main"
        echo ""
        echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
        echo -e "${BLUE}Method B: Using rsync (preserves permissions)${NC}"
        echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
        echo ""
        echo "# Navigate to your ComputerGraphicsProject"
        echo "cd /path/to/ComputerGraphicsProject"
        echo ""
        echo "# Sync files (preserves permissions for build.sh)"
        echo "rsync -av --exclude='.git' $SCRIPT_DIR/ ."
        echo ""
        echo "# Commit and push"
        echo "git add ."
        echo "git commit -m \"Add OpenGL 3D Car Simulator\""
        echo "git push origin main"
        echo ""
        echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
        echo -e "${BLUE}Method C: Download as ZIP${NC}"
        echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
        echo ""
        echo "# 1. Create ZIP archive"
        echo "cd $SCRIPT_DIR/.."
        echo "zip -r car-simulator.zip car-simulator/"
        echo ""
        echo "# 2. Download and extract in ComputerGraphicsProject"
        echo "# 3. Commit as usual"
        echo ""
        ;;
        
    *)
        echo ""
        echo -e "${RED}Invalid option. Please run the script again and choose 1, 2, or 3.${NC}"
        exit 1
        ;;
esac

echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo -e "${GREEN}Migration process complete!${NC}"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo ""
echo "For more detailed information, see:"
echo "  - TRANSFER_GUIDE.md (comprehensive guide)"
echo "  - README.md (project documentation)"
echo "  - INSTALL.md (build instructions)"
echo ""
