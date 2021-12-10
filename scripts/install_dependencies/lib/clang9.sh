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

clang9_from_repos() {
    sudo apt install -y clang-9 clang-tidy-9 clang-format-9
    sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-9 100
    sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-9 100
    sudo update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-9 100
    sudo update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-9 100
}

# clang
if [ ! -x "$(command -v clang)" ]; then
    echo "Installing Clang"

    CURRENT=$(extract_version "$(apt-cache show clang | grep -i -m 1 version | cut -d ":" -f3)")
    if [ "$(compare_version "$CURRENT" "$CLANG_VERSION")" = "<" ]; then
        echo "Will install Clang 9"
        #shellcheck source=scripts/install_dependencies/lib/clang9.sh
        clang9_from_repos
    else
        echo "Will install Clang $(apt-cache show clang | grep -m 1 -i version)"
        sudo apt install -y clang clang-tidy clang-format
    fi
fi
INSTALLED=$(extract_version "$(clang --version)")
if [ "$(compare_version "$INSTALLED" "$CMAKE_VERSION")" = "<" ]; then
        #shellcheck source=scripts/install_dependencies/lib/clang9.sh
        clang9_from_repos
else
    printf "%b Clang already installed. %b" "$BLUE" "$NC"
fi
