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

# Call getopt to validate the provided input.
if ! options=$(getopt --longoptions download-dir:,commonapi-source:,commonapi-release:,install-prefix:,iuk-interface-version:,download-in-advance,skip-build-server-libs,debug,help,add-dbus,clean --options "s:,r:,h,d:" -- "$@");
then
    echo "Incorrect options provided"
    show_help
    exit 1
fi

SCRIPT=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT")
SELF_ROOT_DIR=$(dirname "$SCRIPT_DIR")

########## Load helper functions and variables ##############
cd "$SCRIPT_DIR"
GIT_ROOT=$(git rev-parse --show-toplevel)
export GIT_ROOT
cd -

# TODO: Fix why shellcheck doesn't find this file?
# shellcheck disable=SC1091
# shellcheck source-path=scripts/install_dependencies/etc"
source "$GIT_ROOT/scripts/install_dependencies/etc/defaults.sh"

DEV_DIR=$HOME/git # default dev dir.
# shellcheck disable=SC1091
# shellcheck source-path=scripts/install_dependencies/bin
source "$GIT_ROOT/scripts/install_dependencies/bin/utils.sh" --
IFS=" " read -r -a CMAKE_OPTIONS <<< "$CMAKE_OPTIONS_STR"
###############################################################

COMMONAPI_SOURCE_OPTIONS=$(find "$SELF_ROOT_DIR/sources"/* -maxdepth 1 -type d -exec basename {} \;)

show_help() {
    echo "INSTALL DEPENDENCIES"
    echo "use: ./install_dependencies.sh [arguments]"
    echo " "
    echo "Arguments:"
    echo "--commonapi-source, -s [SOURCE]     Specifies the source of CommonAPI. Use one of:"
    echo "                                    $COMMONAPI_SOURCE_OPTIONS"
    echo "--commonapi-release, -r [RELEASE]   Specifies the release. Specify only VERSION.SUBVERION for "
    echo "                                    example 3.1, 3.2 and so on. Defaults 3.2"
    echo "--skip-franca-cpp-interfaces        Will not generate and install the C++ interfaces from franca."
    echo "                                    They are a dependency of the server, you may install them later by running"
    echo "                                    the install_franca_cpp_interfaces.sh script"
    echo "--download-dir, -d                  Specifies the folder the dependencies source code will be"
    echo "                                    downloaded/cloned."
    echo "--debug                             Compile dependencies as Debug instead of Release"
    echo "--install-prefix                    Directory where the dependencies will be installed"
    echo "--add-dbus                          Includes CommonAPI DBus"
    echo "--iuk-interface-version             IUK interface version to generate the CommonaAPI wrappers packages."
    echo "                                    Default IUK interface: $IUK_INTERFACE_VERSION"
    echo "--skip-build-server-libs            If you don't want to install GraphQL VSS Server Libs"
    echo "--download-in-advance,              Clone all necessary repositories in advance (saves time)"
    echo "--clean, -c                         Clean build"
    echo "--gcc                               Uses GCC instead of Clang (default)"
    echo "--help, -h                          Displays help."
}

BUILD_SERVER_LIBS="1"

DOWNLOAD_IN_ADVANCE=""

eval set -- "$options"
while true; do
    case "$1" in
    --clean | -c)
        export CLEAN_BUILD="true"
        shift 1
        ;;
    --download-dir | -d)
        DEV_DIR="$2"
        mkdir -p "$DEV_DIR"
        shift 2
        ;;
    --iuk-interface-version)
        IUK_INTERFACE_VERSION=$2
        shift 2
        ;;
    --add-dbus)
        INSTALL_COMMONAPI_DBUS="true"
        shift 1
        ;;
    --debug)
        CMAKE_BUILD_TYPE=Debug
        shift 1
        ;;
    --install-prefix)
        export INSTALL_PATH=$2
        shift 2
        ;;
    --download-in-advance)
        DOWNLOAD_IN_ADVANCE="1"
        shift 1
        ;;
    --skip-build-server-libs)
        BUILD_SERVER_LIBS=""
        shift 1
        ;;
    --commonapi-source | -s)
        SOURCE_CODE=$2
        shift 2

        [[ ! ${COMMONAPI_SOURCE_OPTIONS[*]} == *"$SOURCE_CODE"* ]] && {
            printf "%b The options for downloading the source code are: ${COMMONAPI_SOURCE_OPTIONS[*]}  %b\n" "$RED" "$NC"
            printf "%b The 'covesa' option downloads from COVESA's github repo. %b\n" "$RED" "$NC"
            exit 1
        }
        export SOURCE_CODE="$SOURCE_CODE"
        echo "Release $COMMONAPI_RELEASE"
        ;;
    --commonapi-release | -r)
        export COMMONAPI_RELEASE=$2
        shift 2
        ;;
    --help | -h)
        show_help
        exit 1
        ;;
    --)
        break
        ;;
    esac
done


printf "%b Using %s %b\n" "$YELLOW" "$COMMONAPI_RELEASE" "$NC"

# shellcheck source=scripts/install_dependencies/sources/covesa/3.2.sh
if ! source "$SELF_ROOT_DIR/sources/$SOURCE_CODE/$COMMONAPI_RELEASE.sh" ; then
    printf "%b ERROR: Releases %s from %s in unknown to this script.%b \n" "$RED" "$COMMONAPI_RELEASE" "$SOURCE_CODE" "$NC"
    printf "%b You may specify the desired sources by editing scripts/custom-source/custom-source.sh %b \n" "$BOLD" "$NC"
    printf "%b and run this script with \`-r custom -s custom\` .%b \n" "$BOLD" "$NC"
    exit 1
fi

# shellcheck disable=SC2206
CMAKE_OPTIONS=(${CMAKE_OPTIONS[@]} -DCMAKE_INSTALL_PREFIX="$INSTALL_PATH" -DCMAKE_PREFIX_PATH="$INSTALL_PATH")
if [ "$INSTALL_PATH" != "/usr/local" ]; then
    mkdir -p "$INSTALL_PATH"
    if [[ "$(stat -c '%U' "$INSTALL_PATH")" != "root" ]]; then
        WILL_DO_SYSTEM_INSTALL="NO"
        export SUDO=""
    else
        export SUDO="sudo"
    fi
fi

# shellcheck disable=SC2206
export CMAKE_OPTIONS_STR="${CMAKE_OPTIONS[*]} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"

echo "CMake options to be used:"
echo "$CMAKE_OPTIONS_STR"

if [ "$(whoami)" = root ]; then
    printf "\n%bYou are about to run this script as root! %b \nUnless you don't have 'sudo', you don't need to run it as root. The permissions may become too strict! \n" "$BOLD" "$NC"
fi

export DEV_DIR="$DEV_DIR"
printf "%b The SOME/IP and CommonAPI source code will be downloaded from: %s %b \n" "$GREEN" "$SOURCE_CODE" "$NC"

printf "%bRelease: %s %b\n%bDo not look away! %bYou may be propted for password several times.\n" "$GREEN" "$COMMONAPI_RELEASE" "$NC" "$RED" "$NC"

printf "%b Download/clone dir: %s\nInstall prefix: %s\nSystem instalation: %s\nStarting in 5... (Hit Ctrl + C to stop.)\n" "$GREEN" "$DEV_DIR" "$INSTALL_PATH" "$WILL_DO_SYSTEM_INSTALL"
sleep 5

# Don't update cache if it was already updated today.
if [[ $(stat -c %y /var/cache/apt/pkgcache.bin | cut -d' ' -f1) != $(date +"%Y-%m-%d") ]]; then
    printf "%b Updating repositories%b\n" "$BGMAGENTA" "$NC"
    sudo apt update
fi

# Clone respositories in advance
if [[ $DOWNLOAD_IN_ADVANCE == "1" ]]; then
    BUILD_SERVER_LIBS=$BUILD_SERVER_LIBS "$GIT_ROOT"/scripts/install_dependencies/lib/"$SOURCE_CODE"/git_clone_all.sh
    export DOWNLOAD_IN_ADVANCE=2 # avoids fetching again
fi

## INSTALLATION BEGINS ##

cd "$DEV_DIR"

"$SELF_ROOT_DIR"/lib/build_tools.sh || runtime_error
"$SELF_ROOT_DIR"/lib/cmake.sh || runtime_error
"$SELF_ROOT_DIR"/lib/jwt.sh || runtime_error
"$SELF_ROOT_DIR"/lib/websocketpp.sh || runtime_error
"$SELF_ROOT_DIR"/lib/googletest.sh || runtime_error

#shellcheck source=scripts/install_dependencies/lib/libboost.sh
source "$SELF_ROOT_DIR"/lib/libboost.sh
echo "$DEV_DIR"
"$SELF_ROOT_DIR"/lib/dlt.sh || runtime_error

"$SELF_ROOT_DIR"/lib/cppgraphqlgen.sh || runtime_error

if [[ $INSTALL_COMMONAPI_DBUS == "true" ]]; then
    "$SELF_ROOT_DIR/lib/$SOURCE_CODE/commonapi-dbus-runtime.sh" || runtime_error
fi

"$SELF_ROOT_DIR/lib/$SOURCE_CODE/commonapi-someip-runtime.sh" || runtime_error

if [ "$BUILD_SERVER_LIBS" == "1" ]; then
    "$SELF_ROOT_DIR"/lib/graphql-vss-server-libs.sh || runtime_error
fi

printf "%bldconfig %b\n" "$BGMAGENTA" "$NC"
sudo ldconfig

printf "%bSUCCESS!%b\n" "$BLUE" "$NC"

exit 0;
