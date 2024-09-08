#!/bin/bash

cd "$(dirname "$0")"

conan install ../conanfile.py -sbuild_type=Debug -of=../conan_modules/debug --profile=./configs/default_conan_profile --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
