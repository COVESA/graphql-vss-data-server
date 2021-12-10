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

#shellcheck source=scripts/install_dependencies/lib/libboost.sh
source "$GIT_ROOT"/scripts/install_dependencies/lib/libboost.sh

printf "%bInstalling VSomeIP %b\n" "$BGMAGENTA" "$NC"
skip_if_installed vsomeip3 "$VSOMEIP_VERSION"

git_clone_and_cd https://github.com/COVESA/vsomeip.git "$VSOMEIP_COMMIT" "${CLONE_SHALLOW_SINGLE_BRANCH[@]}"

mkdir -p build && cd build
cmake "${CMAKE_OPTIONS[@]}" -DENABLE_COMPAT=1 -DDISABLE_DLT=ON ..
cmake --build . || build_failed_error "vSomeIP"
$SUDO cmake --build . --target install || build_failed_error "vSomeIP"
cd "$DEV_DIR"
