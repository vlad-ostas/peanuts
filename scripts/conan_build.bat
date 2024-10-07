
cd /d "%~dp0"

conan install ../conanfile.py -sbuild_type=Debug -of ../conan_modules/debug --profile=./configs/windows_default_conan_profile --build=missing -c tools.system.package_manager:mode=install