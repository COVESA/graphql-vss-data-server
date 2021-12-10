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

# shellcheck source=scripts/install_dependencies/lib/cmake.sh
"$GIT_ROOT"/scripts/install_dependencies/lib/cmake.sh

if [ ! -x "$(command -v ninja)" ]; then
    sudo apt install -y ninja-build
fi

if [ ! -x "$(command -v lld)" ]; then
    sudo apt install -y lld
fi

if [ ! -x "$(command -v git)" ]; then
    sudo apt install -y git -y
fi

if [ ! -x "$(command -v wget)" ]; then
    sudo apt install -y wget
fi

if [ ! -x "$(command -v pkg-config)" ]; then
    sudo apt install -y pkg-config
fi

if [ ! -x "$(command -v doxygen)" ]; then
    sudo apt install -y doxygen
fi

"$GIT_ROOT"/scripts/install_dependencies/lib/clang9.sh
