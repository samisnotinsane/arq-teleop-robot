#!/bin/sh

g++ -o object_recognition object_recognition.cpp
echo "Compiled object_recognition. Running object_recognition:"
echo ""

./object_recognition
echo ""
echo "Program terminated successfully"
