#!/bin/bash
# filepath: /Users/wilsonliang/Project_D/Scripts/Clean-macOS.sh

echo "Cleaning Core build artifacts..."

# Step 1: Clean using make (if Makefile exists)
if [ -f ../Core/Makefile ]; then
    (cd ../Core && make clean)
fi

# Step 2: Remove Makefile
if [ -f ../Core/Makefile ]; then
    rm ../Core/Makefile
    echo "Removed Core/Makefile"
fi

# Step 3: Remove Binaries directory
if [ -d ../Binaries ]; then
    rm -rf ../Binaries
    echo "Removed Binaries directory"
fi

echo "Cleanup complete."