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


########## Load helper functions and variables ##############
cd "$(dirname "$(realpath "$0")")"
GIT_ROOT=$(git rev-parse --show-toplevel)
cd -
# shellcheck source-path=scripts/install_dependencies/bin
source "$GIT_ROOT"/scripts/install_dependencies/bin/load_helpers_and_variables.sh
###############################################################


git_clone_and_cd https://github.com/COVESA/graphql-vss-server-libs "$DEFAULT_BRANCH" "${CLONE_SHALLOW_SINGLE_BRANCH[@]}"
mkdir -p build && cd build
cmake "${CMAKE_OPTIONS[@]}" -DCMAKE_STATIC_LINKER_FLAGS="" -DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=lld -L/usr/local/lib -L$INSTALL_PATH/lib" -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld -L/usr/local/lib" -DPKG_CONFIG_USE_CMAKE_PREFIX_PATH=ON ..
$SUDO cmake --build . --target install || build_failed_error "GraphQL VSS Server Libs"
cd "$DEV_DIR"
