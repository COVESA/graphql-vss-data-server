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


set -e

########## Load helper functions and variables ##############
cd "$(dirname "$(realpath "$0")")"
GIT_ROOT=$(git rev-parse --show-toplevel)
cd -
# shellcheck source-path=scripts/install_dependencies/bin
source "$GIT_ROOT"/scripts/install_dependencies/bin/load_helpers_and_variables.sh
###############################################################

install_cmake () {
    local CURRENT
    local ANS
    CURRENT=$( extract_version "$( apt-cache show cmake | grep -m 1 -i "version" | sed 's/~.*//' )")
    sudo apt -y install ninja-build

    ANS=$(compare_version "$CURRENT" "$CMAKE_VERSION")
    if [ "$ANS" = "<" ]; then
        echo "Installing cmake from source"
        git_clone_and_cd https://github.com/Kitware/CMake.git "$DEFAULT_BRANCH" "${CLONE_SHALLOW_SINGLE_BRANCH[@]}"
        ./bootstrap --prefix="$INSTALL_PATH"
        make
        $SUDO make install
    else
        echo "Installing cmake from ubuntu"
        sudo apt -y install cmake
    fi
    cd "$DEV_DIR"
}

if [ ! -x "$(command -v cmake)" ]; then
    install_cmake
fi
INSTALLED=$(extract_version "$(cmake --version)")
if [ "$(compare_version "$INSTALLED" "$CMAKE_VERSION")" = "<" ]; then
    lower_version_installed_error "Cmake" "$INSTALLED" "$CMAKE_VERSION"
else
    printf "%b cmake already installed %b\n" "$BLUE" "$NC"
fi
