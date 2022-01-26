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


export INSTALL_DEPENDENCIES_DEFAULTS=1

# Required versions
export CMAKE_VERSION=3.13
export CLANG_VERSION=9.0
export DLT_DAEMON_VERSION=2.18.5
ARCHTYPE="$(uname -p)"
export ARCHTYPE

export LIBBOOST_MIN=1.66
export LIBBOOST_MAX=1.74
export BOOST_RELEASE=https://boostorg.jfrog.io/artifactory/main/release/1.71.0/source/boost_1_71_0.tar.gz
export CPPGRAPHQLGENTAG=v3.6.0
export DEFAULT_BRANCH=master
export COMMONAPI_RELEASE=3.2
export JWT_CPPTAG=v0.5.1
export WEBSOCKETPPTAG=0.8.2

# IUK Interface version
export IUK_INTERFACE_VERSION=35

# Stable dbus version
export DBUS_VERSION=1.12.16
export INSTALL_PATH="/usr/local"
export SUDO=""
export CLEAN_BUILD="false"
export CMAKE_BUILD_TYPE=Release

export CMAKE_OPTIONS_STR="-GNinja -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_COMPILER=/usr/bin/clang"
export CLONE_SHALLOW_SINGLE_BRANCH_STR="--single-branch --depth 1"

export SOURCE_CODE=covesa
