# Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
#   Author: Alexander Domin (Alexander.Domin@bmw.de)
# Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
#   Author: Gustavo Sverzut Barbieri (barbieri@profusion.mobi),
#   Author: Gabriel Fernandes (g7fernandes@profusion.mobi),
#   Author: Leonardo Ramos (leo.ramos@profusion.mobi)
#
# SPDX-License-Identifier: MPL-2.0
#
# This Source Code Form is subject to the terms of the
# Mozilla Public License, v. 2.0. If a copy of the MPL was
# not distributed with this file, You can obtain one at
# http://mozilla.org/MPL/2.0/.

set(GRAPHQL_SCHEMA ${CMAKE_SOURCE_DIR}/schema.graphql)

set(SCHEMAGEN_COMMAND
  cppgraphqlgen::schemagen
  --schema=${GRAPHQL_SCHEMA}
  --prefix=Vehicle
  --namespace=vehicle
)

if(UPDATE_STUBS)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/introspection)
  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_SOURCE_DIR}/introspection/VehicleSchema.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/introspection/VehicleSchema.h
    COMMAND ${SCHEMAGEN_COMMAND}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      VehicleSchema.cpp
      VehicleSchema.h
      ${CMAKE_CURRENT_SOURCE_DIR}/introspection
    DEPENDS ${GRAPHQL_SCHEMA}
    WORKING_DIRECTORY introspection
    COMMENT "Generating stub VehicleSchema files (introspection)"
  )
endif(UPDATE_STUBS)
add_library(
  vehicleschema_introspection
  EXCLUDE_FROM_ALL
  introspection/VehicleSchema.cpp
)
target_include_directories(
  vehicleschema_introspection
  PUBLIC
  introspection
)
set_target_properties(
  vehicleschema_introspection
  PROPERTIES
  CXX_VISIBILITY_PRESET default
)

if(UPDATE_STUBS)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/no_introspection)
  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_SOURCE_DIR}/no_introspection/VehicleSchema.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/no_introspection/VehicleSchema.h
    COMMAND ${SCHEMAGEN_COMMAND} --no-introspection
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      VehicleSchema.cpp
      VehicleSchema.h
      ${CMAKE_CURRENT_SOURCE_DIR}/no_introspection
    DEPENDS ${GRAPHQL_SCHEMA}
    WORKING_DIRECTORY no_introspection
    COMMENT "Generating stub VehicleSchema files (no introspection)"
  )
endif(UPDATE_STUBS)
add_library(
  vehicleschema_no_introspection
  EXCLUDE_FROM_ALL
  no_introspection/VehicleSchema.cpp
)
target_include_directories(
  vehicleschema_no_introspection
  PUBLIC
  introspection
)
set_target_properties(
  vehicleschema_no_introspection
  PROPERTIES
  CXX_VISIBILITY_PRESET default
)

if(DISABLE_INTROSPECTION)
  set(SCHEMA_LIB vehicleschema_no_introspection)
else()
  set(SCHEMA_LIB vehicleschema_introspection)
endif()

set(GRAPHQL_FILES
  Vehicle.hpp
  Vehicle.cpp
)
add_library(
  vehiclegraphql
  ${GRAPHQL_FILES}
)
target_include_directories(
  vehiclegraphql
  PUBLIC
  ${CMAKE_SOURCE_DIR}
  ${SCHEMA_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${COMMONAPI_INCLUDE_DIRS}
)
target_link_libraries(
  vehiclegraphql
  -Wl,--no-as-needed
  graphql_vss_server_libs::graphql_vss_server_libs-support
  graphql_vss_server_libs::graphql_vss_server_libs-protocol
  ${SCHEMA_LIB}
  CommonAPI-SomeIP
  commonapi_glue
  implementation
)

if(UPDATE_STUBS)
  add_custom_target(
    update-stubs
    ALL
    DEPENDS
      ${CMAKE_CURRENT_SOURCE_DIR}/introspection/VehicleSchema.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/introspection/VehicleSchema.h
      ${CMAKE_CURRENT_SOURCE_DIR}/no_introspection/VehicleSchema.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/no_introspection/VehicleSchema.h
  )
endif(UPDATE_STUBS)
