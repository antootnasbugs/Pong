#!/bin/bash

echo "Building the project..."

cmake .. || { echo "CMake failed"; exit 1; }

make || { echo "Make failed"; exit 1; }

open Pong.app || { echo "Failed to open Pong.app"; exit 1; }

echo "Build and run successful!"