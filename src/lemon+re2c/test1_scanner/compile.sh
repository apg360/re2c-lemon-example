#!/bin/zsh

#Pre-requisite, must be installed in the system :
# (*) Command_Line_Tools_for_Xcode_12.dmg
# (*) LLVM 11 + Clang
# (*) Cmake
# (*) Ninja
# (*) Lemon
# (*) re2c

export PATH=~/MyProjects/Ninja1.10.1/ninja:$PATH
export CC=clang
export CXX=clang++
export SDKROOT='/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk'
export CPATH='/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk:/opt/local/include'
export LIBRARY_PATH='/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib:/opt/local/lib'

#Use cmake to perform OS operation
cmake -E rm -rf build           #delete directory build
cmake -E rm -f src/scanner/scanner.h
cmake -E make_directory build   #create directory build

cmake -E chdir scanner re2c scanner.re2c -o scanner.h -i

#cmake to configure in 'build' directory
#Use Ninja as generator on the CMakeLists in current directory, and generate under directory 'build'
cmake -E time cmake -G Ninja . -B build

#Use cmake to start the build
cmake -E time cmake --build build

#echo -e "\n********* STARTING ********\n"
#build/./Hello
#echo -e "\n\n"
