# Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
#   Author: Alexander Domin (Alexander.Domin@bmw.de)
# Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
#   Author: Gabriel Fernandes (g7fernandes@profusion.mobi),
#   Author: Leonardo Ramos (leo.ramos@profusion.mobi)
#
# SPDX-License-Identifier: MPL-2.0
#
# This Source Code Form is subject to the terms of the
# Mozilla Public License, v. 2.0. If a copy of the MPL was
# not distributed with this file, You can obtain one at
# http://mozilla.org/MPL/2.0/.

file(GLOB_RECURSE IMPLEMENTATION_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(implementation ${IMPLEMENTATION_SRC})
target_link_libraries(
  implementation
  graphql_vss_server_libs::graphql_vss_server_libs-support
  graphql_vss_server_libs::graphql_vss_server_libs-protocol
  commonapi_glue
)
target_include_directories(
  implementation
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../commonapi-wrappers/playground/include
  ${CMAKE_CURRENT_SOURCE_DIR}
)
