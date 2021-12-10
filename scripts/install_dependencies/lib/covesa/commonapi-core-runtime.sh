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

printf "%b Installing CommonAPI Core %b\n" "$BGMAGENTA" "$NC"

skip_if_installed CommonAPI "$COMMONAPI_CORE_VERSION" EXACT

git_clone_and_cd https://github.com/covesa/capicxx-core-runtime.git  "$COMMONAPI_CORE_COMMIT" "${CLONE_SHALLOW_SINGLE_BRANCH[@]}"

mkdir -p build && cd build

cmake "${CMAKE_OPTIONS[@]}" -DPKG_CONFIG_USE_CMAKE_PREFIX_PATH=ON -DCMAKE_CXX_FLAGS="-Wno-ignored-attributes"  ..
cmake --build . || build_failed_error "CommonAPI core"
$SUDO cmake --build . --target install || build_failed_error "CommonAPI core"
cd "$DEV_DIR"
