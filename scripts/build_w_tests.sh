#!/bin/bash

# NOTE(Akumanory): to set pwd be only this folder
# so we can call script from wherever 
# ./script/{scipt_name}
# ./{scipt_name}
# Will be the same pwd
cd "$(dirname "$0")"

echo "$PWD"

cmake -B ../build/Debug -S .. -D CMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc-12 -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build ../build/Debug --target all -t test



