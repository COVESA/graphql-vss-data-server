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

install_dlt_from_source() {
    git_clone_and_cd https://github.com/COVESA/dlt-daemon.git "$DEFAULT_BRANCH" "${CLONE_SHALLOW_SINGLE_BRANCH[@]}"
    mkdir -p build
    cd build
    export PKG_CONFIG_PATH=$INSTALL_PATH:$PKG_CONFIG_PATH
    cmake .. -DCMAKE_INSTALL_PREFIX="$INSTALL_PATH"
    make || build_failed_error "dlt-daemon"
    $SUDO make install || build_failed_error "dlt-daemon"
    cd "$DEV_DIR"
}

install_dlt () {
    local CURRENT
    local INSTALLED
    if [ ! -x "$(PATH="$PATH:$INSTALL_PATH/bin:$INSTALL_PATH/local/bin" command -v dlt-daemon)" ]; then
        echo "Installing DLT Daemon"

        CURRENT=$( extract_version "$( apt-cache show dlt-daemon | grep -m 1 -i "version" | sed 's/~.*//' )")
        if [ "$(compare_version "$CURRENT" "$DLT_DAEMON_VERSION")" = "<" ]; then
             echo "Will install dlt-daemon from source."
             install_dlt_from_source
        else
            echo "Will install dlt-daemon $(apt-cache show dlt-daemon | grep -m 1 -i version)"
            sudo apt install -y libdlt-dev dlt-daemon
        fi
    fi
    INSTALLED=$(extract_version "$(dlt-daemon -h)")
    if [ "$(compare_version "$INSTALLED" "$DLT_DAEMON_VERSION")" = "<" ]; then
        lower_version_installed_error "DLT Daemon" "$INSTALLED" "$DLT_DAEMON_VERSION"
    else
        printf "%bDLT Daemon already installed. %b\n" "$BLUE" "$NC"
    fi
}

install_dlt
