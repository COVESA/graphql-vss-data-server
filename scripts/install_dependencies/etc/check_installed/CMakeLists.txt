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

# This file is intended just to check if some dependency exists.
# USAGE:
#    cmake -S pathTo/check_installed/CMakeLists.txt -B /tmp -DNAME "NameOfThePacakge" -DVERSION=1.2.3 -DEXACT=EXACT
# -DVERSION and -DEXACT are optional.

project(TestDependecy)
cmake_minimum_required(VERSION 3.13)

if(NOT NAME)
  message(FATAL_ERROR "Name of the package to be searched not specified. Set the CMake variable NAME, e.g. -DNAME=JPEG .")
endif()

find_package(${NAME} ${VERSION} ${EXACT} REQUIRED NO_CMAKE_PACKAGE_REGISTRY)
