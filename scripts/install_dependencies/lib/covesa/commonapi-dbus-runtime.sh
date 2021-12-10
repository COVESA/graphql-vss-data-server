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

"$GIT_ROOT"/scripts/install_dependencies/lib/covesa/commonapi-core-runtime.sh

printf "%b Installing CommonAPI Dbus Runtime %b\n" "$BGMAGENTA" "$NC"

skip_if_installed CommonAPI-DBus "$COMMONAPI_CORE_VERSION" EXACT

install_commonapidbus () {
    local CAPICXX_DBUS_DIR=capicxx-dbus-runtime
    git_clone_and_cd https://github.com/COVESA/capicxx-dbus-runtime "$DEFAULT_BRANCH"

    cd ..
    if [ ! -f "./dbus-$DBUS_VERSION.tar.gz" ]; then
        wget http://dbus.freedesktop.org/releases/dbus/dbus-"$DBUS_VERSION".tar.gz
    fi
    tar -xzf "dbus-$DBUS_VERSION.tar.gz"
    for patch in "$CAPICXX_DBUS_DIR"/src/dbus-patches/*.patch; do patch -d "dbus-$DBUS_VERSION" -p1 <"$patch"; done

    if [ "$(echo "$INSTALL_PATH" | cut -c 1-4)" == "/usr" ]; then
        DBUS_INSTALLATION="$INSTALL_PATH"
    else
        # Avoid overwrite local dbus
        mkdir -p "dbus-$DBUS_VERSION/installation"
        DBUS_INSTALLATION="$DEV_DIR/dbus-$DBUS_VERSION/installation"
        for i in "${!CMAKE_OPTIONS[@]}"; do
            if [[ $(echo "${CMAKE_OPTIONS[$i]}" | cut -c2-19) == "DCMAKE_PREFIX_PATH" ]]; then
                CMAKE_OPTIONS[$i]="${CMAKE_OPTIONS[$i]};$DBUS_INSTALLATION"
            fi
        done
    fi
    env -C "dbus-$DBUS_VERSION" ./configure --prefix="$DBUS_INSTALLATION"
    make -C "dbus-$DBUS_VERSION/dbus" install || build_failed_error "dbus"
    make -C "dbus-$DBUS_VERSION/" install-pkgconfigDATA

    cd ../"$CAPICXX_DBUS_DIR"

    mkdir -p build && cd build
    cmake "${CMAKE_OPTIONS[@]}" -DUSE_INSTALLED_COMMONAPI=ON -DPKG_CONFIG_USE_CMAKE_PREFIX_PATH=ON ..
    cmake --build . || build_failed_error "CommonAPI-DBus"
    $SUDO cmake --build . --target install || build_failed_error "CommonAPI-DBus"
    cd "$DEV_DIR"
}

install_commonapidbus
