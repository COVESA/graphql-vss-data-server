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


# This file must be sourced!

set -e

if [[ -z "$GIT_ROOT" ]]; then
    cd "$(dirname "$(realpath "$0")")"
    GIT_ROOT=$(git rev-parse --show-toplevel)
    cd -
fi

if [[ $INSTALL_DEPENDENCIES_DEFAULTS != 1 ]]; then
    # TODO: Fix why shellcheck doesn't find this file?
    # shellcheck disable=SC1091
    # shellcheck source-path=scripts/install_dependencies/etc"
    source "$GIT_ROOT/scripts/install_dependencies/etc/defaults.sh"
fi

if [[ $INSTALL_DEPENDENCIES_UTILS != 1 ]]; then
    # shellcheck disable=SC1091
    # shellcheck source-path=scripts/install_dependencies/bin
    source "$GIT_ROOT/scripts/install_dependencies/bin/utils.sh"
fi

# It is not possible to export bash arrays, lets rebuild them here.
IFS=" " read -r -a CMAKE_OPTIONS <<< "$CMAKE_OPTIONS_STR"
IFS=" " read -r -a CLONE_SHALLOW_SINGLE_BRANCH <<< "$CLONE_SHALLOW_SINGLE_BRANCH_STR"
