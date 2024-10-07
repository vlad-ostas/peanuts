cd /d "%~dp0"

cmake -B ../build/Debug -S .. -G "Visual Studio 17 2022" -D CMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_TOOLCHAIN_FILE="./conan_modules/debug/conan_toolchain.cmake"
cmake --build ../build/Debug/ --target ALL_BUILD -t RUN_TESTS