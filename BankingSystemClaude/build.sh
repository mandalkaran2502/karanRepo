#!/bin/bash

# Banking System Manual Build Script
# Alternative to CMake for systems where CMake is not available

echo "========================================="
echo "Banking System - Manual Build Script"
echo "========================================="

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Directories
SRC_DIR="src"
INCLUDE_DIR="include"
BUILD_DIR="build_manual"
BIN_DIR="$BUILD_DIR/bin"
OBJ_DIR="$BUILD_DIR/obj"

# Create directories
mkdir -p $BIN_DIR
mkdir -p $OBJ_DIR

# Compiler settings
CXX="g++"
CXXFLAGS="-std=c++11 -Wall -Wextra -I$INCLUDE_DIR"
LDFLAGS=""

echo "Step 1: Compiling source files..."

# Compile all source files except main.cpp
SOURCES="Transaction FixedDeposit Account BankManager FileManager"
OBJECTS=""

for src in $SOURCES; do
    echo "  Compiling $src.cpp..."
    $CXX $CXXFLAGS -c $SRC_DIR/$src.cpp -o $OBJ_DIR/$src.o
    if [ $? -ne 0 ]; then
        echo -e "${RED}✗ Failed to compile $src.cpp${NC}"
        exit 1
    fi
    OBJECTS="$OBJECTS $OBJ_DIR/$src.o"
done

echo -e "${GREEN}✓ All source files compiled successfully${NC}"

echo "Step 2: Building main executable..."
$CXX $CXXFLAGS $SRC_DIR/main.cpp $OBJECTS -o $BIN_DIR/BankingSystem $LDFLAGS

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Executable built successfully!${NC}"
    echo "Location: $BIN_DIR/BankingSystem"
else
    echo -e "${RED}✗ Failed to build executable${NC}"
    exit 1
fi

# Create data directory
mkdir -p data

echo ""
echo "========================================="
echo "Build completed successfully!"
echo "========================================="
echo "To run the application:"
echo "  ./$BIN_DIR/BankingSystem"
echo ""
echo "Project structure:"
echo "  BankingSystem/"
echo "    ├── $BIN_DIR/BankingSystem  (executable)"
echo "    ├── data/                    (data directory)"
echo "    └── ..."
echo "========================================="
