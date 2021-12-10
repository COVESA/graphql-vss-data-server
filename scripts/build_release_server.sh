#!/bin/bash

# Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
#   Author: Alexander Domin (Alexander.Domin@bmw.de)
# Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
#   Author: Gabriel Fernandes (g7fernandes@profusion.mobi)
#
# SPDX-License-Identifier: MPL-2.0
#
# This Source Code Form is subject to the terms of the
# Mozilla Public License, v. 2.0. If a copy of the MPL was
# not distributed with this file, You can obtain one at
# http://mozilla.org/MPL/2.0/.

# This script build the server and the Franca C++ Interfaces
# Run it with:
# CMAKE_PREFIX_PATH=/pathTo/Your_dependencies_installation /build_release_server
# Passing the CMAKE_PREFIX_PATH is necessary if some dependency is instaleld
# outside /usr or /usr/local(that is actually the recommended thing to do for
# things that you compiled from source).

set -e

export RED='\033[0;31m'
export BLUE='\033[0;34m'
export NC='\033[0m'

SCRIPT=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT")

cd "$SCRIPT_DIR"
GIT_ROOT=$(git rev-parse --show-toplevel)

printf "%b Generating Franca C++ Interfaces %b\n" "$BLUE" "$NC"

cd "$GIT_ROOT"/commonapi-wrappers
rm -rf build/*
CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH ./gen_wrappers.sh || {
    printf "%b The commonapi-wrappers compilation failed!%b \n Did you passed the correct CMAKE_PREFIX_PATH? See the README for more information.\n" "$RED" "$NC"
    exit 1
}

printf "%b Building the server %b\n" "$BLUE" "$NC"

mkdir -p "$GIT_ROOT"/cpp-server/build
cd "$GIT_ROOT"/cpp-server/build
rm -rf ./*

cmake -G Ninja -DCMAKE_PREFIX_PATH="$CMAKE_PREFIX_PATH" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_COMPILER="$(which clang++)" \
  -DCMAKE_STATIC_LINKER_FLAGS="" \
  -DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=lld -L/usr/local/lib -L$CMAKE_PREFIX_PATH/lib" \
  -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld -L/usr/local/lib" \
  -DPKG_CONFIG_USE_CMAKE_PREFIX_PATH=ON .. || {
    printf "%b The CMake configuration failed!%b \n Did you passed the correct CMAKE_PREFIX_PATH? See the README for more information.\n" "$RED" "$NC"
    exit 1
}

ninja

printf "%b SUCCESS! \n%b" "$BLUE" "$NC"