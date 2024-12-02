#!/bin/bash


echo "rm generate for: "
pwd
rm "cmake_install.cmake"
rm "CMakeCache.txt"
rm "Makefile"
rm -rf "CMakeFiles"

echo "rm generate for: "
cd "client"
pwd
rm "cmake_install.cmake"
rm "Makefile"
rm "r_type_client"
rm -rf "CMakeFiles"
cd "../server"

echo "rm generate for: "
pwd
rm "cmake_install.cmake"
rm "Makefile"
rm "r_type_server"

rm -rf "CMakeFiles"

