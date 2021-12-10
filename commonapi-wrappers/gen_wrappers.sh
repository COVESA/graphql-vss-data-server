#!/bin/bash

# Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
#   Author: Alexander Domin (Alexander.Domin@bmw.de)
# Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
#   Author: Gabriel Fernandes Silva (g7fernandes@profusion.mobi)
#
# SPDX-License-Identifier: MPL-2.0
#
# This Source Code Form is subject to the terms of the
# Mozilla Public License, v. 2.0. If a copy of the MPL was
# not distributed with this file, You can obtain one at
# http://mozilla.org/MPL/2.0/.

set -e

SCRIPT=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT")

########## Load helper functions and variables ##############
cd "$SCRIPT_DIR"
GIT_ROOT=$(git rev-parse --show-toplevel)
export GIT_ROOT
cd "$GIT_ROOT"/commonapi-wrappers
ARCHTYPE="$(uname -p)"

### Defaults

COMMONAPI_TOOLS_RELEASE=3.2.0.1
GEN_DIR="$HOME"/Downloads/generators
INSTALL_PATH="$GIT_ROOT"/commonapi-wrappers/playground
GEN_PATH="$GIT_ROOT"/commonapi-wrappers

###

if ! options=$(getopt --longoptions dir:commonapi-tools-release:,dir:,install-prefix:,help --options "r:,i:,h" -- "$@");
then
    echo "Incorrect options provided"
    show_help
    exit 1
fi

show_help() {
    printf 'CommonAPI C++ Franca Interfaces Generator

This script generates the so called "commonapi wrappers" for communicating
via SOME/IP with CommonAPI.

Usage:
  ./gen_wrappers.sh [OPTIONS]
  CMAKE_PREFIX_PATH=/Path/To/dependencies_installation ./gen_wrappers.sh [OPTIONS]

OPTIONS:
  --commonapi-tools-release, -r [RELEASE]   Specifies the release of the CommmonAPI Tools and
                                            CommonAPI SOME/IP Tools that you want to use to generate
                                            your code. Default: %s
  --dir [DIRECTORY]                         Directory where you want to download the generators.
                                            Defalt: %s
  --install-prefix, -i [DIRECTORY]          Path to where you want to install the generated includes
                                            and libraries from the Franca files. Default: %s
  --help, -h                                Show help.

If the dependencies of this code (CommonAPI Core Runtime and CommonAPI SomeIP Runtime) are installed
outside /usr or /usr/local, specify the path to the dependencies by exporting or passing the
CMAKE_PREFIX_PATH variable to this script.
' "$COMMONAPI_TOOLS_RELEASE" "$GEN_DIR" "$GEN_PATH"
}

eval set -- "$options"
while true; do
    case "$1" in
    --commonapi-tools-release | -r)
        COMMONAPI_TOOLS_RELEASE=$2
        shift 2
        ;;
    --dir)
        GEN_DIR="$2"
        mkdir -p "$GEN_DIR"
        shift 2
        ;;
    --install-prefix | i)
        INSTALL_PATH="$2"
        shift2
        ;;
    --help | -h)
        show_help
        exit 1
        ;;
    --)
        break
        ;;
    esac
done

build_install_interfaces() {
    cd "$GEN_PATH"
    mkdir -p build
    cd build
    cmake -G Ninja -DCMAKE_INSTALL_PREFIX="$INSTALL_PATH" \
    -DCMAKE_PREFIX_PATH="$CMAKE_PREFIX_PATH" \
    -DCMAKE_CXX_COMPILER="$(which clang++)" \
    -DCMAKE_STATIC_LINKER_FLAGS="" \
    -DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=lld -L/usr/local/lib -L$CMAKE_PREFIX_PATH/lib" \
    -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld -L/usr/local/lib" ..
    ninja install
}

if [[ -d "$GEN_PATH"/generated && -d "$GEN_PATH"/include ]]; then
    build_install_interfaces
    exit
fi

mkdir -p "$GEN_DIR"

CGEN_CORE="$GEN_DIR"/commonapi_core_generator/commonapi-core-generator-linux-"$ARCHTYPE"
CGEN_SOMEIP="$GEN_DIR"/commonapi_someip_generator/commonapi-someip-generator-linux-"$ARCHTYPE"

cd "$GEN_DIR"
if [ ! -f "$CGEN_CORE" ]; then
    wget "https://github.com/COVESA/capicxx-core-tools/releases/download/$COMMONAPI_TOOLS_RELEASE/commonapi_core_generator.zip"
    mkdir -p commonapi_core_generator
    unzip commonapi_core_generator.zip -d commonapi_core_generator
fi
if [ ! -f "$CGEN_SOMEIP" ]; then
    wget "https://github.com/COVESA/capicxx-someip-tools/releases/download/$COMMONAPI_TOOLS_RELEASE/commonapi_someip_generator.zip"
    mkdir -p commonapi_someip_generator
    unzip commonapi_someip_generator.zip -d commonapi_someip_generator
fi
cd -

mkdir -p "$GEN_PATH"
FDEPLS=$( find "$GIT_ROOT"/franca/instances -name '*.fdepl' 2> /dev/null )

mkdir -p "$GEN_PATH"/include
mkdir -p "$GEN_PATH"/src

# Call code generators
PACKAGE=$(basename "${FDEPLS/.fdepl/}")

$CGEN_CORE -nv --skel \
--dest-common "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/core/common \
--dest-proxy "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/core/proxy \
--dest-stub "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/core/stub \
--dest-skel "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/core/skel \
"$FDEPLS"

$CGEN_SOMEIP -nv \
--dest-common "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/someip/common \
--dest-proxy "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/someip/proxy \
--dest-stub "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/someip/stub \
"$FDEPLS"

# Copy include files to one folder

! find "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/core/skel -name '*.hpp' || cp -a "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/core/skel/. "$GEN_PATH"/include/
! find "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/core/common -name '*.hpp' || cp -a "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/core/common/. "$GEN_PATH"/include/
! find "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/core/proxy -name '*.hpp' || cp -a "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/core/proxy/. "$GEN_PATH"/include/
! find "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/core/stub -name '*.hpp' || cp -a "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/core/stub/. "$GEN_PATH"/include/

! find "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/someip/common -name '*.hpp' || cp -a "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/someip/common/. "$GEN_PATH"/include/
! find "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/someip/proxy -name '*.hpp' || cp -a "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/someip/proxy/. "$GEN_PATH"/include/
! find "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/someip/stub -name '*.hpp' || cp -a "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE"/someip/stub/. "$GEN_PATH"/include/

mkdir -p "$GEN_PATH"/generated/
cp -r "$GIT_ROOT"/commonapi-wrappers/"$PACKAGE" "$GEN_PATH"/generated/

build_install_interfaces
