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


# Keep this file in the same directory as install_dependencies.sh

set -e # If you source in interactive mode, unset with `set +e` to not close the shell on error.
       # The line above also kills interactive zsh, change to bash before sourcing.

export INSTALL_DEPENDENCIES_UTILS=1

OTHER_DEV_DIR="$1"
if [[ -z "$DEV_DIR" && "$OTHER_DEV_DIR" != "--" && -n "$OTHER_DEV_DIR" ]]; then
    mkdir -p "$OTHER_DEV_DIR"
    export DEV_DIR="$OTHER_DEV_DIR"
fi
if [[ ! $DEV_DIR ]]; then
    export DEV_DIR=$HOME/git
    echo "Development dir not specified!"
    echo "The development directory will be $DEV_DIR"
fi

export RED='\033[0;31m'
export BLUE='\033[0;34m'
export GREEN='\033[0;32m'
export YELLOW='\033[0;33m'
export BGMAGENTA='\033[0;45m'
export BOLD='\033[1m'
export NC='\033[0m' # No Color

if [[ -z $SCRIPT || -z $SCRIPT_DIR || -z $SELF_ROOT_DIR ]]; then
    SCRIPT=$(realpath "$0")
    SCRIPT_DIR=$(dirname "$SCRIPT")
    SELF_ROOT_DIR=$(dirname "$SCRIPT_DIR")
    export SCRIPT
    export SCRIPT_DIR
    export SELF_ROOT_DIR
fi

get_remote_tag_hash() {
    git ls-remote --tags --sort="v:refname" "git://$1" | tail -n1 | cut -d$'\t' -f1 | sed 's/\^{}//'
}

clean_build() {
    if [ "$CLEAN_BUILD" = "true" ]; then
        git reset --hard HEAD
        rm -rf ./build
    fi
}

skip_if_installed() {
    # shellcheck disable=SC2206
    # Checks with CMake if the package was already installed. Usage:
    #     skip_if_installed PackageName [PackageVersion EXACT]
    # PackageVersion and EXACT is optional. It seaches for a minimal version or
    # a exact version. If the package is found, the function exists the script.
    # ex.
    #     skip_if_installed CommonAPI 3.2.0 EXACT
    #     skip_if_installed CommonAPI 3.2.0
    #     skip_if_installed CommonAPI
    #
    # It uses the CMakeLists.txt at scripts/install_dependencies/etc/check_installed/CMakeLists.txt
    # therefore the GIT_ROOT variable must be set to the path to this repository.

    # shellcheck disable=SC2206
    PARAMS=($@)

    rm -rf /tmp/install_dependencies
    mkdir -p /tmp/install_dependencies

    if [[ -n "${PARAMS[2]}" && "${PARAMS[2]}" != "EXACT" ]]; then
        print "%b skip_if_installed bad option: ${PARAMS[2]} %b" "$RED" "$NC"
        echo "at $0"
        exit 1
    fi

    ! cmake -DNAME="${PARAMS[0]}" -DVERSION="${PARAMS[1]}" -DEXACT="${PARAMS[2]}" -DCMAKE_PREFIX_PATH="$INSTALL_PATH" -S "$GIT_ROOT"/scripts/install_dependencies/etc/check_installed -B /tmp/install_dependencies 1>/dev/null 2>/dev/null || {
        if [ "$CLEAN_BUILD" != "true" ]; then
            printf "%b ^ Pacakge %s already installed! Skipping... %b \n" "$BGMAGENTA" "${PARAMS[0]}" "$NC"
            exit 0
        fi
    }
    echo "${PARAMS[0]} shall be installed."
}

compare_version() {
    # The shortest array must be the $1
    # Split in words purposefully
    # shellcheck disable=SC2207,SC2001
    v1=($(sed "s/\./ /g" <<< "$1"))
    # shellcheck disable=SC2207,SC2001
    v2=($(sed "s/\./ /g" <<< "$2"))

    if [ "${#v1[@]}" -le "${#v2[@]}" ]; then
        len=${#v1[@]}
    else
        len=${#v2[@]}
    fi
    local ans="="
    for ((i=0; i<len; i++)); do
        if [ "${v1[$i]}" -gt "${v2[$i]}" ]; then
            ans=">"
            break
        elif [ "${v1[$i]}" -lt "${v2[$i]}" ]; then
            ans="<"
            break
        fi
    done
    echo $ans
}

extract_version() {
    ANS=$(echo "$1" | grep -i -m 1 version | sed -e "s/[^0-9]/ /g; s/^[ ]*//; s/[ ]*$//")
    if [ ! "$ANS" ]; then
        ANS=$(echo "$1" | sed -e "s/[^0-9]/ /g; s/^[ ]*//; s/[ ]*$//")
    fi
    echo "$ANS"
}

lower_version_installed_error() {
    echo "ERROR: The installed version of $1 $2 is lower then the required $3!"
    echo "Uninstall the current version and try again!"
    exit 1
}

git_clone_and_cd() {
    # Clones and cd into the cloned git repository. If it already exits, fetch
    # and rebase.
    # The first parameter is the git URL. The second optional parameter specifies
    # the branch, tag or commit hash to be checked out. The third parameter is
    # clone option
    if [ -n "$DEV_DIR" ]; then
        mkdir -p "$DEV_DIR"
        cd "$DEV_DIR"
    fi
    local PARAMS
    local REPO_URL
    local BRANCH
    local CLONE_OPTIONS
    local CLONE_DIR
    # shellcheck disable=SC2206

    PARAMS=($@)
    REPO_URL=${PARAMS[0]}
    BRANCH=${PARAMS[1]}
    IFS=" " read -r -a CLONE_OPTIONS <<< "${PARAMS[*]:2}"
    CLONE_DIR="$(basename "$REPO_URL" | sed 's/\.git.*//')"

    if [[ "$DOWNLOAD_IN_ADVANCE" == "2" && -d "$CLONE_DIR" ]]; then
        cd "$CLONE_DIR"
        clean_build
        return
    fi

    if [ ! -d "$CLONE_DIR" ]; then
        git clone "${CLONE_OPTIONS[@]}" "$REPO_URL"
        cd "$CLONE_DIR"
    else
        cd "$CLONE_DIR"
        git reset --hard HEAD # discard whatever is there
        git remote remove origin || true
        git remote add origin "$REPO_URL" # make sure origin is what we want
    fi
    git fetch origin
    if git show-ref --quiet --verify refs/remotes/origin/"${BRANCH}"; then
        git checkout "$BRANCH"
        git reset --hard origin/"$BRANCH"
    else
    	# it's a tag or commit hash
	    git fetch origin tag "$BRANCH" --no-tags || {
	    	echo "$BRANCH is not a tag of $REPO_URL, trying to checkout as commit..."
	    	git fetch origin "$BRANCH"
	    }
	    git checkout "$BRANCH"
    fi
    clean_build
}

build_failed_error() {
    printf "%bBUILD FAILED at %s %b \n" "$RED" "$1" "$NC"
    exit 1
}

runtime_error() {
    printf "%bRuntime ERROR at %s %b \n" "$RED" "$0" "$NC"
    exit 1
}

export -f get_remote_tag_hash
export -f clean_build
export -f skip_if_installed
export -f compare_version
export -f extract_version
export -f lower_version_installed_error
export -f git_clone_and_cd
export -f build_failed_error
