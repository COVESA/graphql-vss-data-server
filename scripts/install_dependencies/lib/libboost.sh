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
if [ -z "$GIT_ROOT" ]; then
    cd "$(dirname "$(realpath "$0")")"
    GIT_ROOT=$(git rev-parse --show-toplevel)
    cd -
fi
# shellcheck source-path=scripts/install_dependencies/bin
source "$GIT_ROOT"/scripts/install_dependencies/bin/load_helpers_and_variables.sh
###############################################################

# This file can change exported environment variables set by other install scripts.
# Therefore it must be SOURCED instead of simply executed.

install_libboost () {
    local CURRENT
    local ANS_MIN
    local ANS_MAX
    local BOOST_TAR
    local EXTRACT_BOOST_VERSION

    if [ -n "$FOUND_COMPATIBLE_BOOST" ]; then
        return
    elif grep -q "DBOOST_ROOT" <<< "${CMAKE_OPTIONS[@]}"; then
        return
    elif [ -d "$DEV_DIR/boost/install" ] ; then
        CMAKE_OPTIONS+=(-DBOOST_ROOT="$DEV_DIR/boost/install")
        CMAKE_OPTIONS_STR="${CMAKE_OPTIONS[*]}"
        return
    fi

    EXTRACT_BOOST_VERSION="""
    #include <iostream>
    #include <boost/version.hpp>

    int main() {
    std::cout << BOOST_LIB_VERSION << std::endl;
    }
    """

    if [[ -z $INSTALL_PATH ]]; then
        TEST_INCLUDE_PATH="/usr/include"
    else
        TEST_INCLUDE_PATH=-"$INSTALL_PATH"/include
    fi

    set +e
    echo "$EXTRACT_BOOST_VERSION" > /tmp/check_boost_version.cpp
    ! clang++ /tmp/check_boost_version.cpp -I"$TEST_INCLUDE_PATH" -o /tmp/check_boost_version || {
        chmod a+x /tmp/check_boost_version
        CURRENT="$(/tmp/check_boost_version | sed 's/_/\./g')"
        ANS_MIN=$(compare_version "$CURRENT" "$LIBBOOST_MIN")
        # While max version does not change https://github.com/COVESA/vsomeip/blob/master/CMakeLists.txt#L168
        ANS_MAX=$(compare_version "$CURRENT" "$LIBBOOST_MAX")
        if [ "$ANS_MIN" = ">" ] || [ "$ANS_MAX" = "<" ] ; then
            echo "The installed boost version is compatible."
            export FOUND_COMPATIBLE_BOOST=1
            return
        fi
    }
    set -e

    CURRENT=$( extract_version "$( apt-cache show libboost-dev | grep -m 1 -i "version" | sed 's/~.*//' )")

    ANS_MIN=$(compare_version "$CURRENT" "$LIBBOOST_MIN")
    # While max version does not change https://github.com/COVESA/vsomeip/blob/master/CMakeLists.txt#L168
    ANS_MAX=$(compare_version "$CURRENT" "$LIBBOOST_MAX")
    if [ "$ANS_MIN" = "<" ] || [ "$ANS_MAX" = ">" ] ; then
        BOOST_TAR="$(basename "$BOOST_RELEASE")"
        BOOST_DIR=$(pwd)/${BOOST_TAR//\.tar.gz*/}
        echo "Installing boost from source"
        if [ ! -f "./$(basename "$BOOST_RELEASE")" ]; then
            wget "$BOOST_RELEASE"
        fi
        mkdir -p boost/src
        tar -xf "$BOOST_TAR"
        cd boost
        clean_build
        mkdir -p build
        cd -
        if [ "$(echo "$INSTALL_PATH" | cut -c 1-4)" == "/usr" ]; then
            # Avoid overwrite local libboost
            mkdir -p boost/install
            BOOST_PREFIX=$(pwd)/boost/install
            CMAKE_OPTIONS+=(-DBOOST_ROOT="$BOOST_PREFIX")
            export CMAKE_OPTIONS=("${CMAKE_OPTIONS[@]}")
        else
            BOOST_PREFIX=$INSTALL_PATH
        fi
       cd "$BOOST_DIR"
       ./bootstrap.sh
       ./b2 install --prefix="$BOOST_PREFIX" --build-dir=../build
    else
        echo "Installing boost from ubuntu"
        sudo apt install -y libboost-all-dev
    fi
    cd "$DEV_DIR"
}

install_libboost
